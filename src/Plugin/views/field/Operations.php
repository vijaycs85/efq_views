<?php

/**
 * @file
 * Contains \Drupal\efq_views\Plugin\views\field\Entity
 */

namespace Drupal\efq_views\Plugin\views\field;

use Drupal\system\Plugin\views\field\BulkForm;
use Drupal\views\ResultRow;

/**
 * Views Bulk Operations handler field.
 *
 * @ingroup views_field_handlers
 *
 * @ViewsField("efq_operations")
 */
class Operations extends BulkForm {

  /**
   * {@inheritdoc}
   *
   * Checks if the base table referenced is EFQ-enabled. If so, returns the
   * expected entity type.
   */
  public function getEntityType() {
    if (substr($this->view->base_table, 0, 4) === 'efq_') {
      return substr($this->view->base_table, 4);
    }
    else {
      return parent::getEntityType();
    }
  }

  /**
   * {@inheritdoc}
   *
   * Attempts to extract and return the entity ID for the given row.
   */
  public function getValue(ResultRow $row, $field = NULL) {
    $entity_type = $this->getEntityType();
    $ids = entity_extract_ids($entity_type, $row);

    if (isset($ids[0]) && !empty($ids[0])) {
      return $ids[0];
    }
    else {
      return parent::getValue($row, $field);
    }
  }

}
