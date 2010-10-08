<?php
// $Id$

/**
 * Filter on an entity property
 */
class efq_views_handler_filter_property extends views_handler_filter {
  /**
   * This filter is not exposable.
   */
  function can_expose() {
    return FALSE;
  }

  function admin_summary() {
    return check_plain($this->value['column'] . ' ' . $this->operator . ' ' . $this->value['value']);
  }

  /**
   * Defines all possible operators (for both numeric and string operations).
   *  We do so because we don't know whether the property is numeric or string.
   */
  function operators() {
    $operators = array(
      '<' => array(
        'title' => t('Is less than'),
        'method' => 'op_simple',
        'short' => t('<'),
        'values' => 1,
      ),
      '<=' => array(
        'title' => t('Is less than or equal to'),
        'method' => 'op_simple',
        'short' => t('<='),
        'values' => 1,
      ),
      '=' => array(
        'title' => t('Is equal to'),
        'method' => 'op_simple',
        'short' => t('='),
        'values' => 1,
      ),
      '!=' => array(
        'title' => t('Is not equal to'),
        'method' => 'op_simple',
        'short' => t('!='),
        'values' => 1,
      ),
      '>=' => array(
        'title' => t('Is greater than or equal to'),
        'method' => 'op_simple',
        'short' => t('>='),
        'values' => 1,
      ),
      '>' => array(
        'title' => t('Is greater than'),
        'method' => 'op_simple',
        'short' => t('>'),
        'values' => 1,
      ),
      'between' => array(
        'title' => t('Is between'),
        'method' => 'op_between',
        'short' => t('between'),
        'values' => 2,
      ),
      'contains' => array(
        'title' => t('Contains'),
        'short' => t('contains'),
        'method' => 'op_contains',
        'values' => 1,
      ),
      'starts' => array(
        'title' => t('Starts with'),
        'short' => t('begins'),
        'method' => 'op_starts',
        'values' => 1,
      ),
    );

    return $operators;
  }

  function operator_options($which = 'title') {
    $options = array();
    foreach ($this->operators() as $id => $info) {
      $options[$id] = $info[$which];
    }

    return $options;
  }

  function operator_values($values = 1) {
    $options = array();
    foreach ($this->operators() as $id => $info) {
      if (isset($info['values']) && $info['values'] == $values) {
        $options[] = $id;
      }
    }

    return $options;
  }

  /**
   * Provide a simple textfield for equality
   */
  function value_form(&$form, &$form_state) {
    $form['value']['column'] = array(
      '#type' => 'textfield',
      '#title' => t('Property column'),
      '#default_value' => $this->value['column'],
      '#description' => t('Name of the database column to use in the comparison.'),
    );

    $form['value']['value'] = array(
      '#type' => 'textfield',
      '#title' => t('Value'),
      '#size' => 30,
      '#default_value' => $this->value['value'],
      '#description' => t('Value of the column, compared using the selected operater. If using BETWEEN, separate the first and last value with a comma.'),
    );
  }

  function query() {
    if (!$this->value['column']) {
      return;
    }

    $info = $this->operators();
    if (!empty($info[$this->operator]['method'])) {
      $this->{$info[$this->operator]['method']}();
    }
  }

  function op_simple() {
    $this->query->query->propertyCondition($this->value['column'], $this->value['value'], $this->operator);
  }

  function op_between() {
    $ranges = array_map('trim', explode(',', $this->value['value']));
    $this->query->query->propertyCondition($this->value['column'], $ranges, "BETWEEN");
  }

  function op_contains() {
    $this->query->query->propertyCondition($this->value['column'], $this->value['value'], "CONTAINS");
  }

  function op_starts() {
    $this->query->query->propertyCondition($this->value['column'], $this->value['value'], "STARTS_WITH");
  }
}