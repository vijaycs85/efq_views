<?php

/**
 * @file
 * Contains  \Drupal\efq_views\Plugin\sort\Entity.
 */

namespace Drupal\efq_views\Plugin\sort;

use Drupal\views\Plugin\views\sort\SortPluginBase;

/**
 * Sort handler for entity keys.
 *
 * @ViewsSort("efq_entity")
 */
class Entity extends SortPluginBase {

  /**
   * {@inheritdoc}
   */
  function query() {
    $this->query->query->entityOrderBy($this->real_field, $this->options['order']);
  }

}
