<?php
// $Id$

/**
 * Field handler for fields.
 */
class efq_views_handler_field_field extends views_handler_field_field {
  /**
   * Override the parent's methods since they don't need to do anything.
   */
  function query() {}

  /**
   * Prepare $values to a format that the parent::render method understands,
   * so that we don't have to reinvent it.
   */
  function pre_render(&$values) {
    foreach ($values as $id => $entity) {
      $values[$id]->_field_cache[$this->field_alias] = array(
            'entity_type' => $entity->entity_type,
            'object' => $entity,
      );
    }
  }
}