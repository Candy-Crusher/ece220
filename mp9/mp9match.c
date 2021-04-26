#include <stdint.h>
#include <stdio.h>

#include "mp5.h"
#include "mp9.h"

//match_requests
//inputs: graph_t* g, pyr_tree_t* p, heap_t* h,
//		  request_t* r1, request_t* r2,
//		  vertex_set_t* src_vs, vertex_set_t* dst_vs, path_t* path
//outputs: path
//return: 1 for success, 0 for failure
//side effects: no
//description: to implement a request matching and
//			   pathfinding subroutines for a tool that helps people to
//			   find walking partners.
int32_t
match_requests (graph_t* g, pyr_tree_t* p, heap_t* h,
		request_t* r1, request_t* r2,
		vertex_set_t* src_vs, vertex_set_t* dst_vs, path_t* path)
{
	src_vs->count = 0;
	dst_vs->count = 0;
	//initialization to 0
	find_nodes (&(r1->from), src_vs, p, 0);
	trim_nodes(g, src_vs, &(r2 -> from));
	find_nodes (&(r1->to), dst_vs, p, 0);
	trim_nodes(g, dst_vs, &(r2->to));
	//set up src and dest set
	printf("src:%d\ndst:%d\n", src_vs->count,dst_vs->count);
	//check if failure
	if(src_vs == NULL || dst_vs == NULL || 0 == dijkstra(g, h, src_vs, dst_vs, path)){
		return 0;
	}
	return 1;
}
