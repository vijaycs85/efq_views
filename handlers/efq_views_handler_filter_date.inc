<?php

/**
 * Filter handler for date properties.
 */
class efq_views_handler_filter_date extends views_handler_filter_date {
  function value_form(&$form, &$form_state) {
    parent::value_form($form, $form_state);
    unset($form['value']['type']);
    $form['value']['value']['#description'] = t('A date in any machine readable format. CCYY-MM-DD HH:MM:SS is preferred.');
  }

  function query() {
    $info = $this->operators();
    if (!empty($info[$this->operator]['method'])) {
      $this->{$info[$this->operator]['method']}($this->real_field);
    }
  }

  function op_between($field) {
    if ($this->operator == 'between') {
      $a = strtotime($this->value['min'], 0);
      $b = strtotime($this->value['max'], 0);
    }
    else {
      $a = strtotime($this->value['max'], 0);
      $b = strtotime($this->value['min'], 0);
    }
    return array($a, $b);
  }

  function op_simple($field) {
    $value = strtotime($this->value['value'], 0);
    if ($value < 100000) {
      $value += time();
    }
    return $value;
  }

}
