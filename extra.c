#include "extra.h"

void vector_init(vector *v)
{
    v->capacity=4;
    v->total=0;
    v->items=malloc(sizeof(struct object *)*v->capacity);
}

static void vector_resize(vector *v,int capacity)
{
    object **items=realloc(v->items, sizeof(struct object *)*capacity);
    if(items)
    {
	v->items=items;
	v->capacity=capacity;
    }
}

void vector_add(vector *v,object *item)
{
    if(v->capacity == v->total)
    {
	vector_resize(v,v->capacity*2);
    }
    v->items[v->total++]=item;
}

object* vector_get(vector *v,int index)
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

int str_length(char* string)
{
    int i;
    for(i=0;string[i]!='\0';i++);
    return i;
}

void str_append(char* string,char c)
{
     string[str_length(string)]=c;
     string[str_length(string)]='\0';
}

void str_delete(char* string)
{ 
    string[str_length(string)-1]='\0';
}
