#include<string.h>
#include<stdlib.h>
#include<stdint.h>

#define NULL_NODE ((size_t)-1)

typedef struct{
size_t next;
char buff[];
}node_t;

typedef struct{
size_t obj_size;
size_t used;
size_t cap;
node_t* nodes;
}list_t;

#define GET_R(L,I) ((node_t)((char*)L->nodes+\
((I)*(sizeof(node_t)+L->obj_size)))

list_t* list_new(size_t obj_size){
size_t capacity=1024;
size_t mem_required=(sizeof(node_t)+obj_size)*
capacity;
list_t* l=malloc(sizeof *l);
if(!l) return l;
memset(l,0,sizeof *l);
node_t* nodes=malloc(mem_required);
if(!nodes){free(l); return nodes;}
memset(nodes,255,mem_required);
l->nodes=nodes;
l->cap=capacity;
l->obj_size=obj_size;
return l;
}
void list_destroy(list_t* l){
if(!l) return ;
free(l->nodes);
free(l);
}

static node_t* get_node(list_t* list){
size_t padding=sizeof(node_t)+list->obj_size;
char* mem= (char*)list->nodes;
for(size_t idx=0;idx<list->used;idx++){
node_t* node=(node_t*)(mem+padding*idx);
if(node->next ==NULL_NODE){ return node;}
}
list->used++;
return (node_t*)(mem+padding*list->used);
}
#define free_node(x) do{\
 (x)->next=NULL_NODE;} while(0)
// Under development: Dynamic growth not added
static node_t* get_node_at(list_t* list,
size_t idx){
if (idx>=list->used) return NULL;
node_t* curr=list->nodes;
size_t padding=sizeof(node_t)+list->obj_size;
while(idx--){
curr= (node_t*)((char*)list->nodes + padding*curr->next);
}
return curr;
}
void* list_get(list_t* list,size_t idx){
node_t* n=get_node_at(list,idx);
return x ? x->buff : x; // return null if not found.
}
