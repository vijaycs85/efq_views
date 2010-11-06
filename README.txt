This module enables Views to use EntityFieldQuery as the query backend,
allowing you to query fields stored in non-sql storage (such as mongodb).

Note that EntityFieldQuery does not need an entity_type specified, it can
query multiple entity types with the same field attached. This is reflected
in the driver (EntityFieldQuery: Multiple).
Choosing a base table (such as EntityFieldQuery: Node) sets the entity_type
and only shows fields attached to that entity type.

Introduction article: http://vividintent.com/introducing-efq-views

Limitations
-----------
1. Entity: Bundle (field/filter/sort) is not supported for
"EntityFieldQuery: Comment" and "EntityFieldQuery: Taxonomy term".
For taxonomy terms, the "vid" property can be used instead.
This is a Drupal 7 limitation: http://drupal.org/node/938462.

2. This backend doesn't support relationships.
EntityFieldQuery can't and won't support joins, which means
that this functionality would have to be emulated in the query class
(entity_load() on all related ids.)

3. Click sorting (table headers) doesn't work for fields or entity labels.
