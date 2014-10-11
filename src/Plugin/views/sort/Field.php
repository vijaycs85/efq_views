<?php

/**
 * @file
 * Contains  \Drupal\efq_views\Plugin\sort\Field.
 */

namespace Drupal\efq_views\Plugin\sort;

use Drupal\views\Plugin\views\sort\SortPluginBase;

/**
 * Sort handler for field.
 *
 * @ViewsSort("efq_entity")
 */
class Field extends SortPluginBase {

  /**
   * {@inheritdoc}
   */
  function query() {
    $this->query->query->fieldOrderBy($this->definition['field_name'], $this->real_field, $this->options['order']);
  }

}
