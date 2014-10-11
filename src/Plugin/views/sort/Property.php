<?php

/**
 * @file
 * Contains  \Drupal\efq_views\Plugin\sort\Property.
 */

namespace Drupal\efq_views\Plugin\sort;

use Drupal\views\Plugin\views\sort\SortPluginBase;

/**
 * Sort handler for entity properties.
 *
 * @ViewsSort("efq_entity")
 */
class Property extends SortPluginBase {

  /**
   * {@inheritdoc}
   */
  function query() {
    $this->query->query->propertyOrderBy($this->real_field, $this->options['order']);
  }

}
