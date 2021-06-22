#include <stdlib.h>
#include "libqhull_r.h"

qhT *qh_alloc_qh() {
  return (qhT*) malloc(sizeof(qhT));
}

void qh_free_qh(qhT *qh) {
  if (qh) qh_freeqhull(qh, qh_ALL);
  free(qh);
}

facetT *qh_get_facet_list(qhT *qh) {
  return qh->facet_list;
}

int qh_get_num_points(qhT *qh) {
  return qh->num_points;
}

int qh_get_num_facets(qhT *qh) {
  return qh->num_facets;
}

int qh_get_num_vertices(qhT *qh) {
  return qh->num_vertices;
}

pointT *qh_get_first_point(qhT *qh) {
  return qh->first_point;
}

int *qh_get_hull_dim(qhT *qh) {
  return qh->hull_dim;
}

vertexT *qh_get_vertex_list(qhT *qh) {
  return qh->vertex_list;
}
