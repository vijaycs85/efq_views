<?php
// $Id$

/**
 * Implements hook_views_data().
 */
function efq_views_views_data() {
  $data['efq']['table']['group'] = t('EntityFieldQuery');

  // Add a EFQ base table for each defined entity
  foreach (entity_get_info() as $type => $info) {
    $data['efq_' . $type]['table']['base'] = array(
      'title' => 'EntityFieldQuery: ' . $info['label'],
      'help' => t('Uses EntityFieldQuery for querying the !type entity type', array('!type' => $type)),
      'query class' => 'efq_query',
      'field' => $info['entity keys']['id'],
    );
    $data['efq_' . $type] += _efq_views_get_entity_data($info, true);
    $data['efq_' . $type] += _efq_views_get_field_data();
    $data['efq_' . $type] += _efq_views_get_property_data($type, $info);

    // Entity: Bundle is not supported for these two entity types.
    if ($type == 'comment' || $type == 'taxonomy_term') {
      unset($data['efq_' . $type]['bundle']);
    }
  }

  // Now add the EFQ: Multiple base table, for querying across
  // multiple entity types.
  $data['efq_multiple']['table']['base'] = array(
    'title' => t('EntityFieldQuery: Multiple'),
    'help' => t('Uses EntityFieldQuery for querying multiple entity types.'),
    'query class' => 'efq_query',
    'field' => '',
  );
  $data['efq_multiple'] += _efq_views_get_entity_data();
  $data['efq_multiple'] += _efq_views_get_field_data();
  $data['efq_multiple'] += _efq_views_get_property_data();

  return $data;
}

/**
 * Helper for efq_views_views_data()
 * Returns all possible entity metadata variants
 * (entity_id, revision_id, entity_type, bundle).
 *
 * @param $info Entity info array.
 * @param boolean $exclude_type Whether to exclude entity_type (in cases when
 *                              it's already specified through the base table)
 */
function _efq_views_get_entity_data($info = NULL, $exclude_type = FALSE) {
  $data['entity_id'] = array(
    'group' => t('Entity'),
    'title' => t('Entity ID'),
    'help' => t('The entity ID of the entity.'),
    'field' => array(
      'click sortable' => TRUE,
      'handler' => 'efq_views_handler_field_entity',
    ),
    'filter' => array(
      'handler' => 'efq_views_handler_filter_entity_numeric',
    ),
    'sort' => array(
      'handler' => 'efq_views_handler_sort_entity',
    ),
    'argument' => array(
     'handler' => 'efq_views_handler_argument_entity_numeric',
    ),
  );
  $data['revision_id'] = array(
    'group' => t('Entity'),
    'title' => t('Revision ID'),
    'help' => t('The revision ID of the entity revision.'),
    'field' => array(
      'click sortable' => TRUE,
      'handler' => 'efq_views_handler_field_entity',
    ),
    'filter' => array(
      'handler' => 'efq_views_handler_filter_entity_numeric',
    ),
    'sort' => array(
      'handler' => 'efq_views_handler_sort_entity',
    ),
    'argument' => array(
     'handler' => 'efq_views_handler_argument_entity_numeric',
    ),
  );

  if (!$exclude_type) {
    $data['entity_type'] = array(
      'group' => t('Entity'),
      'title' => t('Entity Type'),
      'help' => t('The type of an entity (for example, "node", "comment", etc)..'),
      'field' => array(
        'click sortable' => TRUE,
        'handler' => 'efq_views_handler_field_entity',
      ),
      'filter' => array(
        'handler' => 'efq_views_handler_filter_entity_type',
      ),
      'sort' => array(
        'handler' => 'efq_views_handler_sort_entity',
      ),
      'argument' => array(
       'handler' => 'efq_views_handler_argument_entity_type',
      ),
    );
  }

  $data['bundle'] = array(
    'group' => t('Entity'),
    'title' => t('Bundle'),
    'help' => t('The entity bundle (for example, "article", "page", etc for nodes).'),
    'field' => array(
      'click sortable' => TRUE,
      'handler' => 'efq_views_handler_field_entity',
    ),
    'filter' => array(
      'handler' => 'efq_views_handler_filter_entity_bundle',
    ),
    'sort' => array(
      'handler' => 'efq_views_handler_sort_entity',
    ),
    'argument' => array(
     'handler' => 'efq_views_handler_argument_entity_bundle',
    ),
  );

  $data['label'] = array(
    'group' => t('Entity'),
    'title' => t('Label'),
    'help' => t('The entity label (for example, node title for nodes).'),
    'field' => array(
      'click sortable' => FALSE,
      'handler' => 'efq_views_handler_field_entity_label',
    ),
  );
  // We can only do click sorting and filters/sorts/arguments when the label is
  // stored in the database, instead of being generated in a callback.
  if (isset($info['entity keys']['label']) && !isset($info['label callback'])) {
    $data['label']['field'] = array(
      'click sortable' => TRUE,
      'handler' => 'efq_views_handler_field_entity_label',
      'label column' => $info['entity keys']['label'],
    );
    $data['label']['filter'] = array(
      'handler' => 'efq_views_handler_filter_entity_label',
      'label column' => $info['entity keys']['label'],
    );
    $data['label']['sort'] = array(
      'handler' => 'efq_views_handler_sort_entity_label',
      'label column' => $info['entity keys']['label'],
    );
    $data['label']['argument'] = array(
      'handler' => 'efq_views_handler_argument_entity_label',
      'label column' => $info['entity keys']['label'],
    );
  }

  return $data;
}

/**
 * Helper for efq_views_views_data()
 * Returns defined fields & their columns for the given entity type
 * (or, if absent, all entity types).
 *
 * Based on field_views_field_default_views_data() from field.views.inc
 */
function _efq_views_get_field_data($entity_type = NULL) {
  foreach (field_info_fields($entity_type) as $field) {
    $bundle_names = array();
    foreach ($field['bundles'] as $entity_type => $bundles) {
      foreach ($bundles as $bundle) {
        $bundles_names[] = t('@entity:@bundle', array('@entity' => $entity_type, '@bundle' => $bundle));
      }
    }
    $field_name = $field['field_name'];

    // This provides a Views field.
    // Arguments/filters/sorts are provided per column, so there are none here.
    $data[$field_name] = array(
      'group' => t('Fields'),
      'title' => $field_name,
      'title short' => $field_name,
      'help' =>  t('Appears in: @bundles', array('@bundles' => implode(', ', $bundles_names))),
      'field' => array(
        'click sortable' => TRUE,
        'handler' => 'efq_views_handler_field_field',
        'field_name' => $field_name,
      ),
    );

    foreach ($field['columns'] as $column => $attributes) {
      $allow_sort = TRUE;

      // Identify likely filters and arguments for each column based on field type.
      switch ($attributes['type']) {
        case 'int':
        case 'mediumint':
        case 'tinyint':
        case 'bigint':
        case 'serial':
        case 'numeric':
        case 'float':
          $filter = 'efq_views_handler_filter_field_numeric';
          $argument = 'efq_views_handler_argument_field_numeric';
          break;
        case 'text':
        case 'blob':
          // It does not make sense to sort by blob or text.
          $allow_sort = FALSE;
        default:
          $filter = 'efq_views_handler_filter_field_string';
          $argument = 'efq_views_handler_argument_field_string';
          break;
      }

      if (count($field['columns']) == 1 && $column == 'value') {
        $title = t('@label (!name)', array('@label' => $field_name, '!name' => $field_name));
        $title_short = $field_name;
      }
      else {
        $title = t('@label (!name) - !column', array('@label' => $field_name, '!name' => $field_name, '!column' => $column));
        $title_short = t('@label-truncated - !column', array('@label-truncated' => $field_name, '!column' => $column));
      }

      // $data[$field_name][$column] doesn't work because $field_name is not a base table
      // hence, this ugly thing.
      $data[$field_name . '-' . $column] = array(
        'group' => t('Fields'),
        'title' => $title,
        'title short' => $title_short,
        'help' =>  t('Appears in: @bundles', array('@bundles' => implode(', ', $bundles_names))),
        'argument' => array(
         'field' => $column,
         'handler' => $argument,
         'field_name' => $field['field_name'],
         'empty field name' => t('<No value>'),
        ),
        'filter' => array(
          'field' => $column,
          'handler' => $filter,
          'field_name' => $field_name,
          'allow empty' => TRUE,
        ),
      );
      if (!empty($allow_sort)) {
        $data[$field_name . '-' . $column]['sort'] = array(
          'field' => $column,
          'handler' => 'efq_views_handler_sort_field',
          'field_name' => $field_name,
        );
      }
    }
  }

  return $data;
}

/**
 * Helper for efq_views_views_data()
 * Returns the property data.
 *
 * @param $type Entity type for which the properties are being loaded.
 * @param $info Entity info array for the given entity type.
 */
function _efq_views_get_property_data($type = NULL, $info = NULL) {
  $data['property'] = array(
    'group' => t('Property'),
    'title' => t('Property'),
    'help' => t('Entity-specific property.'),
    'field' => array(
      'click sortable' => TRUE,
      'handler' => 'efq_views_handler_field_property',
    ),
    'filter' => array(
      'handler' => 'efq_views_handler_filter_property',
    ),
    'sort' => array(
      'handler' => 'efq_views_handler_sort_property',
    ),
    'argument' => array(
     'handler' => 'efq_views_handler_argument_property',
    ),
  );

  // No single entity_type specified, we can't find more info
  // through the entity definition. So, return what we have so far.
  if (!isset($info)) {
    return $data;
  }

  // Provide additional help.
  if (isset($info['schema_fields_sql']['base table'])) {
    $available_properties = $info['schema_fields_sql']['base table'];
    $data['property']['field']['available_properties'] = $available_properties;
    $data['property']['filter']['available_properties'] = $available_properties;
    $data['property']['sort']['available_properties'] = $available_properties;
    $data['property']['argument']['available_properties'] = $available_properties;
  }

  // Get individual properties using Entity Metadata
  $supported_types = array('integer', 'decimal', 'duration', 'date', 'text', 'token', 'boolean', 'uri');
  $metadata = entity_metadata_get_info($type);
  foreach ($metadata['properties'] as $property => $property_info) {
    // We already handle entity keys through the Entity handlers.
    if (in_array($property, $info['entity keys'])) {
      continue;
    }
    // Only allow the properties whose type we know how to handle
    if (isset($property_info['type']) && !in_array($property_info['type'], $supported_types)) {
      continue;
    }

    // Avoid generating a million notices.
    if (!isset($property_info['type'])) {
      $property_info['type'] = '';
    }

    // Identify likely handlers for each property, based on property type.
    switch ($property_info['type']) {
      case 'integer':
      case 'decimal':
      case 'duration':
        $field = 'efq_views_handler_field_property_numeric';
        $filter = 'efq_views_handler_filter_property_numeric';
        $argument = 'efq_views_handler_argument_property_numeric';
        break;
      case 'boolean':
        // Views proper doesn't let boolean fields have argument handlers,
        // so neither do we.
        $field = 'efq_views_handler_field_property_boolean';
        $filter = 'efq_views_handler_filter_property_boolean';
        $argument = NULL;
        break;
      case 'date':
        $field = 'efq_views_handler_field_property_date';
        $filter = 'efq_views_handler_filter_property_date';
        $argument = NULL;
        break;
      case 'uri':
        // URIs aren't stored in the database, no need for additional handlers.
        $field = 'efq_views_handler_field_property_uri';
        break;
      case 'text':
      case 'token':
      default:
        $field = 'efq_views_handler_field_property_string';
        $filter = 'efq_views_handler_filter_property_string';
        $argument = 'efq_views_handler_argument_property_string';
        break;
    }

    $data[$property] = array(
      'group' => $info['label'],
      'title' => $property_info['label'],
      'help' =>  $property_info['description'],
      'field' => array(
        'click sortable' => FALSE,
        'handler' => $field,
      ),
    );

    // This property is a db column, we can do fun stuff with it.
    if (in_array($property, $info['schema_fields_sql']['base table'])) {
      $data[$property]['field'] = array(
        'click sortable' => TRUE,
        'handler' => $field,
      );
      $data[$property]['filter'] = array(
        'handler' => $filter,
      );
      $data[$property]['sort'] = array(
        'handler' => 'efq_views_handler_sort_property',
      );

      if (isset($argument)) {
        $data[$property]['argument'] = array(
          'handler' => $argument,
        );
      }
    }
  }

  return $data;
}

/**
 * Implements hook_views_plugins().
 */
function efq_views_views_plugins() {
  return array(
    'query' => array(
      'efq_query' => array(
        'title' => t('EntityFieldQuery'),
        'help' => t('Uses EntityFieldQuery for querying entities and fields.'),
        'handler' => 'efq_views_plugin_query',
      ),
    ),
  );
}

/**
 * Implements hook_views_plugins_alter().
 *
 * This allows us to use the node view style with EntityFieldQuery: Node
 * and comment view style with EntityFieldQuery: Comment
 * (just like with regular nodes and comments).
 *
 * Note that these style plugins do an entity_load() even though they already
 * get fully loaded entities from our query engine.
 * However, entity_load has internal caching, so the only real overhead is an
 * extra function call.
 */
function efq_views_views_plugins_alter(&$plugins) {
  $plugins['row']['node']['base'][] = "efq_node";
  $plugins['row']['comment']['base'][] = "efq_comment";
}
