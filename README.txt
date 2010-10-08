This module enables Views to use EntityFieldQuery as the query backend,
allowing you to query fields stored in non-sql storage (such as mongodb).

This backend will never support relationships, since EntityFieldQuery
can't and won't support joins.

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
The comment entity type has "node_type" defined as the bundle column, but that
column doesn't exist in the table {comment}, so when EntityFieldQuery tries to
select it, an error is generated.

2. Filtering strings with STARTS_WITH and CONTAINS has been known to give me
some odd results.