<?php
// $Id$

/**
 * Numeric argument handler for entity properties.
 */
class efq_views_handler_argument_property_numeric extends views_handler_argument_numeric {
  function option_definition() {
    $options = parent::option_definition();
    $options['column'] = array('default' => '');

   return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['column'] = array(
      '#type' => 'textfield',
      '#title' => t('Property column'),
      '#default_value' => $this->options['column'],
      '#description' => t('Name of the database column to use in the comparison.'),
    );
  }

  function query() {
    if (!$this->options['column']) {
      return;
    }

    if (!empty($this->options['break_phrase'])) {
      views_break_phrase($this->argument, $this);
    }
    else {
      $this->value = array($this->argument);
    }

    if (count($this->value) > 1) {
      $operator = empty($this->options['not']) ? 'IN' : 'NOT IN';
      $this->query->query->propertyCondition($this->options['column'], $this->value, $operator);
    }
    else {
      $operator = empty($this->options['not']) ? '=' : '!=';
      $this->query->query->propertyCondition($this->options['column'], $this->argument, $operator);
    }
  }
}