<?php
// $Id$

/**
 * @todo
 *   Add a description
 */
class efq_views_handler_argument_entity_type extends views_handler_argument {
  function query() {
    $this->query->query->entityCondition('entity_type', $this->argument, '=');
  }
}