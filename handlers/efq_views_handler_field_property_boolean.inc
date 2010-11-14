<?php
// $Id$

/**
 * Field handler for boolean properties.
 */
class efq_views_handler_field_property_boolean extends views_handler_field_boolean {
  /**
   * Called to determine what to tell the clicksorter.
   */
  function click_sort($order) {
    $this->query->query->propertyOrderBy($this->real_field, $order);
  }

  /**
   * Override the parent's query method, since it doesn't need to do anything.
   */
  function query() {}

  function render($values) {
    $wrapper = entity_metadata_wrapper($this->query->entity_type, $values);
    $value = $wrapper->{$this->real_field}->value();

    if (!empty($this->options['not'])) {
      $value = !$value;
    }

    if (isset($this->formats[$this->options['type']])) {
      return $value ? $this->formats[$this->options['type']][0] : $this->formats[$this->options['type']][1];
    }
    else {
      return $value ? $this->formats['yes-no'][0] : $this->formats['yes-no'][1];
    }
  }
}
