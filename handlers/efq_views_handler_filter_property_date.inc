<?php
// $Id$

/**
 * Filter handler for date properties.
 */
class efq_views_handler_filter_property_date extends views_handler_filter_date {
  function value_form(&$form, &$form_state) {
    parent::value_form($form, $form_state);
    unset($form['value']['type']);
  }

  function query() {
    if (empty($this->value)) {
      $this->query->query->propertyCondition($this->real_field, 0, "=");
    }
    else {
      $this->query->query->propertyCondition($this->real_field, 0, "!=");
    }
  }

  function op_between($field) {
    if ($this->operator == 'between') {
      $a = intval(strtotime($this->value['min'], 0));
      $b = intval(strtotime($this->value['max'], 0));
    }
    else {
      $a = intval(strtotime($this->value['max'], 0));
      $b = intval(strtotime($this->value['min'], 0));
    }
    $this->query->query->propertyCondition($this->real_field, array($a, $b), 'BETWEEN');
  }

  function op_simple($field) {
    $value = intval(strtotime($this->value['value'], 0));
    $this->query->query->propertyCondition($this->real_field, $value, '=');
  }
}
