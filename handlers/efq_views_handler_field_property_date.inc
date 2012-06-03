<?php

/**
 * Field handler for date properties.
 */
class efq_views_handler_field_property_date extends entity_views_handler_field_date {
  /**
   * Called to determine what to tell the clicksorter.
   */
  function click_sort($order) {
    $this->query->query->propertyOrderBy($this->real_field, $order);
  }
}
