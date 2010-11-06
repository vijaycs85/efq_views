<?php
// $Id$

/**
 * Field handler for entity labels.
 */
class efq_views_handler_field_entity_label extends views_handler_field {
  /**
   * Override the parent's query method, since it doesn't need to do anything.
   */
  function query() {}

  function render($values) {
    return entity_label($values->entity_type, $values);
  }
}