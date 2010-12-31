<?php
// $Id$

/**
 * The 'entity' row plugin
 *
 * Displays a single entity.
 *
 * @ingroup views_row_plugins
 */
class efq_views_plugin_row_entity extends views_plugin_row {
  /**
   * The entity type of the entity being displayed.
   */
  var $entity_type;

  function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);

    // Our base table is entity_type prepended with 'efq_'.
    $this->entity_type = str_replace('efq_', '', $view->base_table);
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['build_mode'] = array('default' => 'teaser');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $entity_info = entity_get_info($this->entity_type);
    $options = array();
    if (!empty($entity_info['view modes'])) {
      foreach ($entity_info['view modes'] as $mode => $settings) {
        $options[$mode] = $settings['label'];
      }
    }

    $form['view_mode'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#title' => t('View mode'),
      '#default_value' => $this->options['view_mode'],
     );
  }

  function render($entity) {
    $view_mode = $this->options['view_mode'];
    $content = entity_view($this->entity_type, array($entity), $view_mode);

    return drupal_render($content);
  }
}
