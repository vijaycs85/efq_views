<?php
// $Id$

/**
 * Numeric field handler for entity metadata.
 * Maps the entity keys to real returned data (for example: entity_id => nid, for node).
 *
 * This is actually the same code as in efq_views_handler_field_entity,
 * it just inherits a different class.
 */
class efq_views_handler_field_entity_numeric extends views_handler_field_numeric {
  /**
   * Override the parent's query method, since it doesn't need to do anything.
   */
  function query() {}

  function render($values) {
    if ($this->field == 'entity_type') {
      return $values->entity_type;
    }

    $this->query->entity_type = 'node';
    $entity_info = entity_get_info($values->entity_type);

    $id_map = array(
      'entity_id' => $entity_info['entity keys']['id'],
      'revision_id' => $entity_info['entity keys']['revision'],
      'bundle' => $entity_info['entity keys']['bundle'],
    );
    $field = $id_map[$this->field];

    $value = $values->{$field};
    return check_plain($value);
  }
}