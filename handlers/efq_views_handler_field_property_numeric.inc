<?php

/**
 * Field handler for numeric properties.
 */
class efq_views_handler_field_property_numeric extends entity_views_handler_field_numeric {
  /**
   * Called to determine what to tell the clicksorter.
   */
  function click_sort($order) {
    $this->query->query->propertyOrderBy($this->real_field, $order);
  }
}
