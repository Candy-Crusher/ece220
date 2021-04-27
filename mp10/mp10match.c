#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mp5.h"
#include "mp10.h"

//
// These variables hold the heads of two singly-linked lists of
// requests.
//
// The avaialble list consists of unpaired requests: partner
// should be NULL, and next is used to form the list.
//
// The shared list consists of groups with non-empty start and end
// vertex intersections.  Only one of the requests in the group is in
// the list.  The others are linked through the first's partner field
// and then through the next field of the others in the group.  The
// next field of the first request in a group is used to form the
// shared list.
//
// Note: for MP2, you should only build groups of two in the shared
// list.
//

static request_t *available = NULL;
static request_t *shared = NULL;


/*introduction
  This week’s program reads a file consisting of many requests. For each request, 
  your code must attempt to find a matching request from among those requests that 
  have not already been matched. If a match is found, your code must find a path 
  as before and record the trip information in a list of matched requests. If no 
  match is found, your code must add the request to the list of unmatched requests.*/


/*handle_request:
  input: g, p, h, r
  output: 0/1
  return value: 0 for failure, 1 for success
  side effect: no
  description: This function processes a single request, allocating structures as necessary, 
               then comparing it with all unpaired requests handled previously. If a match 
               is found, the function moves the new request and the matching request into a 
               separate list.
*/

int32_t
handle_request(graph_t *g, pyr_tree_t *p, heap_t *h, request_t *r)
{
    //Allocate vertex sets for the request and for use with matching
    r->src_vs = new_vertex_set();
    if(r->src_vs == NULL)
    {
        return 0;
    }
    r->dst_vs = new_vertex_set();
    if(r->dst_vs == NULL)
    {
        free_vertex_set(r->src_vs);
        return 0;
    }
    vertex_set_t *src_vint = new_vertex_set();
    if(src_vint == NULL){
        free_vertex_set(r->src_vs);
        free_vertex_set(r->dst_vs);
        return 0;
    }
    vertex_set_t *dst_vint = new_vertex_set();
    if(dst_vint == NULL){
        free_vertex_set(r->src_vs);
        free_vertex_set(r->dst_vs);
        free_vertex_set(src_vint);
        return 0;
    }
    //Allocate a path for use with matching.
    r->path = new_path();
    if (NULL == r->path)
    {
        free_vertex_set(src_vint);
        free_vertex_set(dst_vint);
        free_vertex_set(r->src_vs);
        free_vertex_set(r->dst_vs);
        return 0;
    }
    //If any allocation fails, clean up (free any successful allocations) and return 0

    /*Fill in the vertex sets for the request. If either is empty, 
      the function should return 0. Be sure to free any vertex sets 
      and path allocated by the function before returning.*/

    find_nodes(&(r->from), r->src_vs, p, 0);
    find_nodes(&(r->to), r->dst_vs, p, 0);
    if (r->src_vs->count == 0 || r->dst_vs->count == 0)
    {
        free_vertex_set(src_vint);
        free_vertex_set(dst_vint);
        free_vertex_set(r->src_vs);
        free_vertex_set(r->dst_vs);
        free_path(r->path);
        return 0;
    }
    //Create minimaps for the request’s source and destination vertex sets.
    build_vertex_set_minimap(g, r->src_vs);
    build_vertex_set_minimap(g, r->dst_vs);

    /*Allocate id arrays for the vertex sets to be used for matching. 
      Make these large enough that they can hold any intersection with 
      the request’s corresponding vertex set. Note that you must clean 
      up and return 0 if allocation fails.*/
   
    //?????????????????????????????????

    /*Try to find a matching request in the available list. Skip any requests 
      that have no overlap in the source vertex set minimaps or no overlap in 
      the destination vertex set minimaps. For those with overlap, use 
      merge_vertex_sets to check for non-empty intersections, then call dijkstra 
      to find a path (if both are non-empty). If everything succeeds, pair the 
      two requests.*/
    r->partner = NULL;
    request_t **a_pointer;
    for (a_pointer = &available; *a_pointer != NULL; a_pointer = &(*a_pointer)->next)
    {
        if (0 == (r->src_vs->minimap & (*a_pointer)->src_vs->minimap) || 0 == (r->dst_vs->minimap & (*a_pointer)->dst_vs->minimap))
        {
            continue;
        }
        if (0 != merge_vertex_sets(r->src_vs, (*a_pointer)->src_vs, src_vint) && 0 != merge_vertex_sets(r->dst_vs, (*a_pointer)->dst_vs, dst_vint))
        {
            if(0 == dijkstra(g, h, src_vint, dst_vint, r->path)){
                continue;
            };
            r->partner = *a_pointer;
            break;
        }
    }
    /*If no match is found, add the request to the available list and return 1 
      for success. Again, be sure to free any dynamically allocated structures 
      (specifically, those used for testing matches).*/
    if (r->partner == NULL)
    {
        r->next = available;
        available = r;
        free_vertex_set(src_vint);
        free_vertex_set(dst_vint);
        return 1;
    }

    /*If a matching request is found, remove the matching request from the available list, free both
      requests vertex sets (these should be replaced with the intersected vertex sets), and make both
      requests point to the intersected vertex sets and the path filled in by dijkstra . Be sure to build
      minimaps for both intersected vertex sets and for the path. Link the two requests as described
      previously into the shared list and return 1 for success.*/
    *a_pointer = (*a_pointer)->next;

    free_vertex_set(r->src_vs);
    free_vertex_set(r->dst_vs);
    free_vertex_set(r->partner->src_vs);
    free_vertex_set(r->partner->dst_vs);

    build_vertex_set_minimap(g,src_vint);
    build_vertex_set_minimap(g,dst_vint);
    build_path_minimap(g,r->path);

    r->src_vs = src_vint;
    r->dst_vs = dst_vint;
    r->partner->src_vs = src_vint;
    r->partner->dst_vs = dst_vint;
    r->partner->path = r->path;


    r->partner->next = NULL;
    r->partner->partner = NULL;

    r->next = shared;
    shared = r;
    return 1;
}

void print_results()
{
    request_t *r;
    request_t *prt;

    printf("Matched requests:\n");
    for (r = shared; NULL != r; r = r->next)
    {
        printf("%5d", r->uid);
        for (prt = r->partner; NULL != prt; prt = prt->next)
        {
            printf(" %5d", prt->uid);
        }
        printf(" src=%016lX dst=%016lX path=%016lX\n", r->src_vs->minimap,
               r->dst_vs->minimap, r->path->minimap);
    }

    printf("\nUnmatched requests:\n");
    for (r = available; NULL != r; r = r->next)
    {
        printf("%5d src=%016lX dst=%016lX\n", r->uid, r->src_vs->minimap,
               r->dst_vs->minimap);
    }
}

int32_t
show_results_for(graph_t *g, int32_t which)
{
    request_t *r;
    request_t *prt;

    // Can only illustrate one partner.
    for (r = shared; NULL != r; r = r->next)
    {
        if (which == r->uid)
        {
            return show_find_results(g, r, r->partner);
        }
        for (prt = r->partner; NULL != prt; prt = prt->next)
        {
            if (which == prt->uid)
            {
                return show_find_results(g, prt, r);
            }
        }
    }

    for (r = available; NULL != r; r = r->next)
    {
        if (which == r->uid)
        {
            return show_find_results(g, r, r);
        }
    }
    return 0;
}

static void
free_request(request_t *r)
{
    free_vertex_set(r->src_vs);
    free_vertex_set(r->dst_vs);
    if (NULL != r->path)
    {
        free_path(r->path);
    }
    free(r);
}

void free_all_data()
{
    request_t *r;
    request_t *prt;
    request_t *next;

    // All requests in a group share source and destination vertex sets
    // as well as a path, so we need free those elements only once.
    for (r = shared; NULL != r; r = next)
    {
        for (prt = r->partner; NULL != prt; prt = next)
        {
            next = prt->next;
            free(prt);
        }
        next = r->next;
        free_request(r);
    }

    for (r = available; NULL != r; r = next)
    {
        next = r->next;
        free_request(r);
    }
}
