#include <stdint.h>
#include <stdlib.h>

#include "mp10.h"

/*new_vertex_set:
  input: no
  output: NULL for failure, pointer to vertex_set for success
  return value: NULL for failure, pointer to vertex_set for success
  side effect: no
  description: set up new vertex set
*/
vertex_set_t*
new_vertex_set ()
{
    vertex_set_t* vs = malloc(sizeof(vertex_set_t));
    if(vs == NULL){
        return NULL;//if fail to malloc, return NULL
    }
    vs->count = 0;
    vs->id_array_size = 100;
    vs->id = malloc(vs->id_array_size* sizeof(int32_t));
    if(vs->id == NULL){
        return NULL;
    }
    return vs;   
}

/*free_vertex_set:
  input: vs
  output: no
  return value: no
  side effect: no
  description: free vertex set
*/
void
free_vertex_set (vertex_set_t* vs)
{
    if(vs == NULL){
        return;//if NULL, no need to free
    }
    if(vs->id != NULL){
        free(vs->id);//free id field
    }
    free(vs);
}

/*new_path:
  input: no
  output: NULL for failure, pointer to path for success
  return value: NULL for failure, pointer to path for success
  side effect: no
  description: set up new path
*/
path_t*
new_path ()
{
    path_t* p = malloc(sizeof(path_t));
    if(p == NULL){
        return NULL;//if fail to malloc, return NULL
    }
    p->id = malloc(500 * sizeof(int32_t));
    if(p->id == NULL){
        return NULL;
    }
    return p;  
}

/*free_path:
  input: path
  output: no
  return value: no
  side effect: no
  description: free path
*/
void
free_path (path_t* path)
{
    if(path == NULL){
        return;
    }
    if(path->id != NULL){
        free(path->id);
    }
    free(path);
}

