This module enables Views to use EntityFieldQuery as the query backend,
allowing you to query fields stored in non-sql storage (such as mongodb).

This backend doesn't support relationships.
EntityFieldQuery can't and won't support joins, which means
that this functionality would have to be emulated in the query class
(entity_load() on all related ids.)

Note that EntityFieldQuery does not need an entity_type specified, it can
query multiple entity types with the same field attached. This is reflected
in the driver (EntityFieldQuery: Multiple).
Choosing a base table (such as EntityFieldQuery: Node) sets the entity_type
and only shows fields attached to that entity type.

Also, the BETWEEN operator in the property filter uses one field for it's value,
instead of two (min and max) because dependent forms are currently broken in Views,
see http://drupal.org/node/667950.

Introduction article: http://vividintent.com/introducing-efq-views

Errata
------
1. EntityFieldQuery: Comment doesn't work.
Drupal core issue: http://drupal.org/node/938462.

2. Filtering strings with STARTS_WITH and CONTAINS has been known to give me
some odd results.