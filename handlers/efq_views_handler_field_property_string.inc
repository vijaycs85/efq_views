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
    if (isset($this->definition['getter callback'])) {
      $value = $this->definition['getter callback']($values, array(), $this->real_field);
    }
    else {
      $value = $values->{$this->real_field};
    }

    // Is the property already sanitized?
    // Does it have special ideas regarding how it should be sanitized?
    if (isset($this->definition['sanitized']) && $this->definition['sanitized'] == TRUE) {
      return $value;
    }
    else if (isset($this->definition['sanitize'])) {
      return $this->definition['sanitize']($value);
    }
    else {
      return check_plain($value);
    }
  }
}