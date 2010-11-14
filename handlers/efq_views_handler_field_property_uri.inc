<?php
// $Id$

/**
 * Field handler for URL/URI properties.
 */
class efq_views_handler_field_property_uri extends views_handler_field_url {
  /**
   * Override the parent's query method, since it doesn't need to do anything.
   */
  function query() {}

  function render($values) {
    $wrapper = entity_metadata_wrapper($this->query->entity_type, $values);
    $value = $wrapper->{$this->real_field}->value();

    if (!empty($this->options['display_as_link'])) {
      return l(check_plain($value), $value, array('html' => TRUE));
    }
    else {
      return $value;
    }
  }
}
