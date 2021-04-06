#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mp5.h"
#include "mp10.h"

#define MY_INFINITY 1000000000

//introduction:
//This file is used to find the nearest dist from a set of points to a set of points

//find_nodes:
//inputs: locale_t *loc, vertex_set_t *vs, pyr_tree_t *p, int32_t nnum
//outputs:  vertex_set_t *vs
//return: void
//side effects: no
//description: find vertex in the loc using p start at nnum
void find_nodes(locale_t *loc, vertex_set_t *vs, pyr_tree_t *p, int32_t nnum)
{
    // Do not modify the following line nor add anything above in the function.
    record_fn_call();
    //first check if this is a leaf node
    int32_t* id_copy;
    if (nnum * 4 + 1 >= p->n_nodes)
    {
        //if it is a leaf node, check if it is in the range
        if(in_range(loc, p->node[nnum].x, p->node[nnum].y_left)){
            //if it is in the range, check if the vs set full
            if (vs->count == vs->id_array_size)
            {
                //if full, reallocate
                id_copy = realloc(vs->id, 2*vs->id_array_size*sizeof(int32_t));
                if(id_copy == NULL){
                    return;
                }
                vs->id = id_copy;
                vs->id_array_size *= 2;
            }
            //if not full, put the node into the vs set and use intersection sort           
            int32_t current = p->node[nnum].id;
            vs->count++;
            int32_t i;
            for(i = vs->count - 1; i > 0; i--){
                if(current > vs->id[i - 1]){
                    break;
                }
                vs->id[i] = vs->id[i - 1];
            }
            vs->id[i] = current; 
        }
        return;
    }
    //if it is not a leaf node
    int32_t r = loc->range;
    int32_t cx = loc->x;
    int32_t cy = loc->y;
    if (cx + r <= p->node[nnum].x){
        //only check the left half
        if (cy + r <= p->node[nnum].y_left){
            //only check the 4N+1 part
            find_nodes(loc, vs, p, nnum * 4 + 1);
        }else if (cy - r >= p->node[nnum].y_left){
            //only check the 4N+3 part
            find_nodes(loc, vs, p, nnum * 4 + 3);
        }else{
            //otherwise check both 4N+1 and 4N+3 parts
            find_nodes(loc, vs, p, nnum * 4 + 1);
            find_nodes(loc, vs, p, nnum * 4 + 3);
        }
    }else if(cx - r >= p->node[nnum].x){
        //only check the right half
        if (cy + r <= p->node[nnum].y_right){
            //only check the 4N+2 part
            find_nodes(loc, vs, p, nnum * 4 + 2);
        }else if (cy - r >= p->node[nnum].y_right){
            //only check the 4N+4 part
            find_nodes(loc, vs, p, nnum * 4 + 4);
        }else{
            //otherwise check both 4N+2 and 4N+4 parts
            find_nodes(loc, vs, p, nnum * 4 + 2);
            find_nodes(loc, vs, p, nnum * 4 + 4);
        }
    }else{
        //otherwise check all 4 parts         
        if(p->node[nnum].y_right >= p->node[nnum].y_left){
            if(cy - r >= p->node[nnum].y_left){
                if(cy + r <= p->node[nnum].y_right){
                    find_nodes(loc, vs, p, nnum * 4 + 2);
                    find_nodes(loc, vs, p, nnum * 4 + 3);
                }else if(cy - r >= p->node[nnum].y_right){
                    find_nodes(loc, vs, p, nnum * 4 + 3);
                    find_nodes(loc, vs, p, nnum * 4 + 4);  
                }else{
                    find_nodes(loc, vs, p, nnum * 4 + 2);
                    find_nodes(loc, vs, p, nnum * 4 + 3);
                    find_nodes(loc, vs, p, nnum * 4 + 4);
                }
            }else{
                if(cy + r <= p->node[nnum].y_left){
                    find_nodes(loc, vs, p, nnum * 4 + 1);
                    find_nodes(loc, vs, p, nnum * 4 + 2);     
                }else if(cy + r <= p->node[nnum].y_right){
                    find_nodes(loc, vs, p, nnum * 4 + 1);
                    find_nodes(loc, vs, p, nnum * 4 + 2);
                    find_nodes(loc, vs, p, nnum * 4 + 3);
                }else{
                    find_nodes(loc, vs, p, nnum * 4 + 1);
                    find_nodes(loc, vs, p, nnum * 4 + 2);
                    find_nodes(loc, vs, p, nnum * 4 + 3);
                    find_nodes(loc, vs, p, nnum * 4 + 4);
                }  
            }
        }else{
            if(cy - r >= p->node[nnum].y_right){
                if(cy + r <= p->node[nnum].y_left){
                    find_nodes(loc, vs, p, nnum * 4 + 1);
                    find_nodes(loc, vs, p, nnum * 4 + 4);
                }else if(cy - r >= p->node[nnum].y_left){
                    find_nodes(loc, vs, p, nnum * 4 + 3);
                    find_nodes(loc, vs, p, nnum * 4 + 4);
                }else{
                    find_nodes(loc, vs, p, nnum * 4 + 1);
                    find_nodes(loc, vs, p, nnum * 4 + 4);
                    find_nodes(loc, vs, p, nnum * 4 + 3);
                }
            }else{
                if(cy + r <= p->node[nnum].y_right){
                    find_nodes(loc, vs, p, nnum * 4 + 1);
                    find_nodes(loc, vs, p, nnum * 4 + 2);     
                }else if(cy + r <= p->node[nnum].y_left){
                    find_nodes(loc, vs, p, nnum * 4 + 1);
                    find_nodes(loc, vs, p, nnum * 4 + 2);
                    find_nodes(loc, vs, p, nnum * 4 + 4);
                }else{
                    find_nodes(loc, vs, p, nnum * 4 + 1);
                    find_nodes(loc, vs, p, nnum * 4 + 2);
                    find_nodes(loc, vs, p, nnum * 4 + 3);
                    find_nodes(loc, vs, p, nnum * 4 + 4);
                }   
            }
        }   
    }
}

//trim_nodes:
//inputs: graph_t *g, vertex_set_t *vs, locale_t *loc
//outputs:  vertex_set_t *vs
//return: void
//side effects: no
//description: delete vertices not in loc from vs
void trim_nodes(graph_t *g, vertex_set_t *vs, locale_t *loc)
{
    int32_t new_copy[vs->count];    //to hold points in range
    int32_t new_count = 0;          //to calc new #
    for (int32_t i = 0; i < vs->count; i++) //loop through all points in vs
    {       
        if(in_range (loc, g->vertex[vs->id[i]].x, g->vertex[vs->id[i]].y)){
            new_copy[new_count++] = vs->id[i];//if in range, put in new_copy and increase #
        }
    }
    //copy back
    vs->count = new_count;
    for (int32_t i = 0; i < vs->count; i++){
        vs->id[i] = new_copy[i];
    }
}




//heapify
//inputs:graph_t *g, heap_t* h, int32_t n, int32_t i
//outputs: *h
//return: no
//side effect: no
//description: set up a sub heap from i;
void heapify(graph_t *g, heap_t* h, int32_t n, int32_t i)
{
    int32_t smallest = i;  // Initialize smallest as root
    int32_t l = 2*i + 1;  // left = 2*i + 1
    int32_t r = 2*i + 2;  // right = 2*i + 2
 
    // If left child is smaller than root
    if (l < n && g->vertex[h->elt[l]].from_src < g->vertex[h->elt[smallest]].from_src)
    {
        smallest = l;
    }
 
    // If right child is smaller than smallest so far
    if (r < n && g->vertex[h->elt[r]].from_src < g->vertex[h->elt[smallest]].from_src)
    {
        smallest = r;
    }
    // If smallest is not root
    if (smallest != i)
    {
        int32_t buff = h->elt[smallest];
        h->elt[smallest] = h->elt[i];
        h->elt[i] = buff;
        // Recursively heapify the affected sub-tree
        heapify(g, h, n, smallest);
    }
}

//heap_sort
//inputs:graph_t *g, heap_t* h, int32_t n
//outputs: *h
//return: no
//side effect: no
//description: set up a min heap and shift down;
void heap_sort(graph_t *g, heap_t* h, int32_t n){
    for(int32_t i = n/2 - 1; i >= 0; i--){
        heapify(g, h, n, i);
    }
    for(int32_t j = n - 1; j >= 0; j--){
        int32_t buff = h->elt[0];
        h->elt[0] = h->elt[j];
        h->elt[j] = buff;
        // Recursively heapify the affected sub-tree
        heapify(g, h, j, 0);
    }

}

//heap_initialization
//inputs: graph_t *g, heap_t *h
//outputs: *h
//return: no
//side effects: no
//description:set size of heap equal to graph; 1-to-1 conrespond id of vertex in graph and heap
void heap_initialization(graph_t *g, heap_t *h){
    int32_t nnum = g->n_vertices;
    h->n_elts = g->n_vertices;
    for(int32_t i = 0; i < nnum; i++){
        h->elt[i] = i;
    }
}

//heap_remove
//inputs; heap_t *h
//outputs: heap_t *h
//return: min id
//descripttion: remove the last one on the heap and return the min id. 
//side effects: have to satisfy heap is not empty when use it
int32_t heap_remove(heap_t *h){
    return h->elt[--h->n_elts];
}

//in_src
//inputs: vertex_set_t *src, int32_t check
//outputs: *src
//return: 1 for in the set, 0 for not in the set
//side effects: no
//description: check if a vertex whose id is check is in src
int32_t in_src(vertex_set_t *src, int32_t check){
    for(int32_t i = 0; i < src->count; i++){
        if(src->id[i] == check){
            return 1;
        }
    }
    return 0;
}

//dijkstra:
//inputs: graph_t *g, heap_t *h, vertex_set_t *src, vertex_set_t *dest, path_t *path
//outputs: *path
//return: 1 for success, 0 for failure
//side_effect: no
//description: use min heap as priory queue to find the smallest dist from src to dest
int32_t
dijkstra(graph_t *g, heap_t *h, vertex_set_t *src, vertex_set_t *dest,
         path_t *path)
{
    //heap initialization
    heap_initialization(g, h);

    //initialize all dist to infinity
    int32_t nnum = g -> n_vertices;
    for(int32_t i = 0; i < nnum; i++){
        g -> vertex[i].from_src = MY_INFINITY;
    }

    //assume src set as a single point
    int32_t src_nnum = src -> count;
    for(int32_t i = 0; i < src_nnum; i++){
        g -> vertex[src->id[i]].from_src = 0;
    }
    
    
    //calculate the dist between src and all verteces in the graph
    while(h->n_elts != 0){
        heap_sort(g, h, h->n_elts);
        int32_t min = heap_remove(h);
        int32_t alt;
        for(int32_t i = 0; i < g->vertex[min].n_neighbors; i++){
            alt = g->vertex[min].from_src + g->vertex[min].distance[i];
            if(alt < g->vertex[g->vertex[min].neighbor[i]].from_src){
                g->vertex[g->vertex[min].neighbor[i]].from_src = alt;
                g->vertex[g->vertex[min].neighbor[i]].pred = min;
            }
        }
    }

    //find the nearest point in dest set
    int32_t dest_nnum = dest -> count;
    int32_t nearest = MY_INFINITY;
    int32_t nearest_id;
    for(int32_t i = 0; i < dest_nnum; i++){
        if(g -> vertex[dest->id[i]].from_src < nearest){
            nearest = g -> vertex[dest->id[i]].from_src;
            nearest_id = dest->id[i];
        }
    }
    //if no way to match, return failure
    if(nearest == MY_INFINITY){
        return 0;
    }
    //find the path backward

    
    path->tot_dist = g -> vertex[nearest_id].from_src;
    int32_t p_id = nearest_id;
    path->n_vertices = 0;
    //count length
    while(!(in_src(src,p_id))){
        (path->n_vertices)++;
        p_id = g -> vertex[p_id].pred;        
    }
    //add the start point in length
    (path->n_vertices)++;

    path->id = malloc(path->n_vertices * sizeof(int32_t));
    if(path->id == NULL){
        return 0;   //if fail malloc, return 0
    }
    //make the backward path
    p_id = nearest_id;
    int32_t i;
    for (i = path->n_vertices - 1; i > 0; i--){       
        path->id[i] = p_id;
        p_id = g -> vertex[p_id].pred;
    }
    path->id[i] = p_id;//add the src point
    return 1;
}
