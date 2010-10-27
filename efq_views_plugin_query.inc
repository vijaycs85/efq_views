<?php
// $Id$

class efq_views_plugin_query extends views_plugin_query {
  /**
   * The EntityFieldQuery object used for the query.
   */
  var $query;

  /**
   * Entity type, if set.
   */
  var $entity_type;

  /**
   * Constructor; Create the basic query object and fill with default values.
   */
  function init($base_table, $base_field, $options) {
    parent::init($base_table, $base_field, $options);

    $this->query = new EntityFieldQuery;

    // An entity type (such as EntityFieldQuery: Node) was selected.
    // We have entity type passed in as base table, prefixed with 'efq_'
    if ($base_table != 'efq_multiple') {
      $entity_type = str_replace('efq_', '', $base_table);
      $this->entity_type = $entity_type;
      $this->query->entityCondition('entity_type', $entity_type);
    }
  }

  /**
   * Builds the necessary info to execute the query.
   */
  function build(&$view) {
    $view->init_pager($view);

    // Let the pager modify the query to add limits.
    $this->pager->query();

    $count_query = clone $this->query;
    $count_query->count(true);

    $view->build_info['efq_query'] = $this->query;
    $view->build_info['count_query'] = $count_query;
  }

  /**
   * This is used by the style row plugins for node view and comment view.
   */
  function add_field($base_table, $base_field) {
    return $base_field;
  }

  /**
   * Executes the query and fills the associated view object with according
   * values.
   *
   * Values to set: $view->result, $view->total_rows, $view->execute_time,
   * $view->pager['current_page'].
   */
  function execute(&$view) {
    $query = $view->build_info['efq_query'];
    $count_query = $view->build_info['count_query'];
    $args = $view->build_info['query_args'];

    $query->addMetaData('view', $view);
    $count_query->addMetaData('view', $view);

    $start = microtime(true);

    // if we are using the pager, calculate the total number of results
    if ($this->pager->use_pager()) {
      try {
        $this->pager->total_items = $count_query->execute();

        if (!empty($this->pager->options['offset'])) {
          $this->pager->total_items -= $this->pager->options['offset'];
        }

        $this->pager->update_page_info();
      }
      catch (Exception $e) {
        // Show the full exception message in Views admin.
        // However, don't show that to the user on the frontend.
        if (!empty($view->live_preview)) {
          drupal_set_message($e->getMessage(), 'error');
        }
        else {
          drupal_set_message(t('An error occured while generating the requested view.'), 'error');
        }
        return;
      }
    }

    // Let the pager set limit and offset.
    $this->pager->pre_execute($query, $args);

    if (!empty($this->limit) || !empty($this->offset)) {
      // We can't have an offset without a limit, so provide a very large limit instead.
      $limit  = intval(!empty($this->limit) ? $this->limit : 999999);
      $offset = intval(!empty($this->offset) ? $this->offset : 0);
      $query->range($offset, $limit);
    }

    $view->result = array();
    try {
      $results = $query->execute();

      foreach ($results as $entity_type => $ids) {
        $entities = entity_load($entity_type, array_keys($ids));

        // This is later used for field rendering
        foreach ($entities as $entity_id => $entity) {
          $entities[$entity_id]->entity_type = $entity_type;
        }
        $view->result += $entities;
      }

      $this->pager->post_execute($view->result);
      if ($this->pager->use_pager()) {
        $view->total_rows = $this->pager->get_total_items();
      }
    }
    catch (Exception $e) {
      // Show the full exception message in Views admin.
      // However, don't show that to the user on the frontend.
      if (!empty($view->live_preview)) {
        drupal_set_message($e->getMessage(), 'error');
      }
      else {
        drupal_set_message(t('An error occured while generating the requested view.'), 'error');
      }
      return;
    }

    $view->execute_time = microtime(true) - $start;
  }
}
