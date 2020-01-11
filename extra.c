#include "extra.h"

void vector_init(vector *v)
{
    v->capacity=4;
    v->total=0;
    v->items=malloc(sizeof(struct asteroid *)*v->capacity);
}

static void vector_resize(vector *v,int capacity)
{
    asteroid **items=realloc(v->items, sizeof(struct asteroid *)*capacity);
    if(items)
    {
	v->items=items;
	v->capacity=capacity;
    }
}

void vector_add(vector *v,asteroid *item)
{
    if(v->capacity == v->total)
    {
	vector_resize(v,v->capacity*2);
    }
}

asteroid* vector_get(vector *v,int index)
{
    if(index>=0&&index<v->total)
    {
	return v->items[index];
    }
    else
    {
	return NULL;
    }
}

void vector_delete(vector *v, int index)
{
    if (index<0||index >= v->total)return;
    
    //usunac asteroide

    v->items[index]=NULL;
    
    for (int i = index; i < v->total - 1; i++) 
    {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = NULL;
    }
    
    v->total--;

    if (v->total > 0 && v->total == v->capacity / 4)
    {	
	vector_resize(v, v->capacity / 2);
    }
}

sfVector2f vec2d(float x,float y)
{
    sfVector2f vec;
    vec.x=x;
    vec.y=y;
    return vec;
}
