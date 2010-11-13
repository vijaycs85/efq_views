<?php
// $Id$

/**
 * Filter handler for boolean properties.
 */
class efq_views_handler_filter_property_boolean extends views_handler_filter_boolean_operator {
  /**
   * Note, $this->accept_null is absolutely useless, since EFQ
   * doesn't support comparing with NULL.
   */
  function query() {
    if (empty($this->value)) {
      $this->query->query->propertyCondition($this->real_field, 0, "=");
    }
    else {
      $this->query->query->propertyCondition($this->real_field, 0, "!=");
    }
  }
}
