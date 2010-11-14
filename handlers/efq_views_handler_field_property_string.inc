<?php
// $Id$

/**
 * Field handler for textual properties.
 */
class efq_views_handler_field_property_string extends views_handler_field {
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
    $value = $wrapper->{$this->real_field}->value(array('sanitize' => TRUE));
    
    return $value;
  }
}
