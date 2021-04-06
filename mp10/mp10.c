#include <stdint.h>
#include <stdio.h>

#include "mp10.h"

/*mark_vertex_minimap:
  input: g, p
  output: 0/1
  return value: 0 for failure, 1 for success
  side effect: no
  description: mark each vertex in a graph with a bit 
  indicating which node in the fourth level of a
  pyramid tree is the ancestor of the pyramid tree 
  node corresponding to the vertex.
*/
int32_t 
mark_vertex_minimap (graph_t* g, pyr_tree_t* p)
{
    if(g->n_vertices <= 64){
        //if less or equal to 64, just copy id
        for(int32_t i = 0; i < g->n_vertices; i++){
            g->vertex[i].mm_bit = i;
        }
    }else{
        //otherwise for every non_node vertex
        for(int32_t i = p->n_nodes - g->n_vertices; i < p->n_nodes ; i++){
            int32_t j = i;
            //loop until forth level
            while(j > 84){
                j = (j - 1)/4;
            }
            g->vertex[p->node[i].id].mm_bit = j - 21;
        }
    }
    return 1;
}

/*build_vertex_set_minimap:
  input: g, vs
  output: no
  return value: no
  side effect: no
  description: build minimaps for the vertex sets
*/
void 
build_vertex_set_minimap (graph_t* g, vertex_set_t* vs)
{
    vs->minimap = 0;
    for(int32_t i = 0; i < vs->count; i++){
        vs->minimap |= (1ULL << g->vertex[vs->id[i]].mm_bit);//or all flags
    }
}

/*build_vertex_set_minimap:
  input: g, p
  output: no
  return value: no
  side effect: no
  description: build minimaps for the paths
*/
void 
build_path_minimap (graph_t* g, path_t* p)
{
    p->minimap = 0;
    for(int32_t i = 0; i < p->n_vertices; i++){
        p->minimap |= (1ULL << g->vertex[p->id[i]].mm_bit);//or all flags
    }
}

/*merge_vertex_sets:
  input: v1,v2,vint
  output: 0/1
  return value: 0 for failure, 1 for success
  side effect: no
  description: merges two vertex sets into a third set.
*/
int32_t
merge_vertex_sets (const vertex_set_t* v1, const vertex_set_t* v2,
		   vertex_set_t* vint)
{   
    int32_t i;
    int32_t j = 0;
    vint->count = 0;
    for(i = 0; i < v1->count; i++){
        for(; j< v2->count; j++){
            if(v1->id[i] == v2->id[j]){
                //if same, add
                vint->id[vint->count] = v1->id[i];
                vint->count++;
            }else if(v1->id[i] > v2->id[j]){
                //if v1 larger, increment j
                continue;
            }else{
                //otherwise increment i; 
                break;
            }
        }
    } 
    if(vint->count == 0){
        return 0;//if empty, fail
    }
    return 1;//otherwise success
}

