<?php
// $Id$

/**
 * @todo
 */
class efq_views_handler_argument_property_string extends views_handler_argument_string {
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
    // We don't support glossary currently.
    unset($form['glossary']);
  }

  function query() {
    if (!$this->options['column']) {
      return;
    }
    $argument = $this->argument;
    if (!empty($this->options['transform_dash'])) {
      $argument = strtr($argument, '-', ' ');
    }

    $this->query->query->propertyCondition($this->options['column'], $argument, '=');
  }
}