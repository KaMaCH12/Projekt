#include <stdio.h>
#include <string.h>
#include "extra.h"

void vector_init(vector *v)
{
    v->capacity=4;
    v->total=0;
    v->items=malloc(sizeof(struct object *)*v->capacity);
}

void vector_resize(vector *v,int capacity)
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

void save_score(char* name_src,int score_src)
{
    if(strlen(name_src)==0)return;
    FILE* highscores;
    FILE* temp;
    highscores=fopen("./data/highscores.txt","ar+");
    temp=fopen("./data/temp.txt","w");
    char name[1000];
    char score[1000];
    char a='a';
    int i=0;
    int written=0;
    a=fgetc(highscores);
    while(a!=EOF)
    {
	//wypelnianie stringow z wiersza
	i=0;
	while(a!=';')
	{
	    name[i]=a;
	    a=fgetc(highscores);
	    i++;
	}
	name[i]='\0';
	a=fgetc(highscores);
	i=0;
	while(a!=';')
	{
	    score[i]=a;
	    a=fgetc(highscores);
	    i++;
	}
	score[i]='\0';
	//sprawdzanie czy gracz nie osiagnal juz lepszego wyniku
	if(strcmp(name,name_src)==0)
	{
	    if(strtol(score,NULL,10)>score_src)
	    {
		fclose(highscores);
		fclose(temp);
		remove("./data/temp.txt");
		return;
	    }
	}
	//sprawdzanie czy juz dotarlismy na pulap gracza
	if(strtol(score,NULL,10)<score_src&&written==0)
	{
	    written=1;
	    fprintf(temp,"%s;%d;\n",name_src,score_src);
	}
	if(strcmp(name,name_src)!=0)
	{
	    fprintf(temp,"%s;%s;\n",name,score);
	}
	a=fgetc(highscores);
	if(a==EOF)break;
	a=fgetc(highscores);
    }
    if(written==0)
    {
	fprintf(temp,"%s;%d;\n",name_src,score_src);
    }
    //podmiana temp i higscores
    fclose(highscores);
    fclose(temp);
    remove("./data/highscores.txt");
    rename("./data/temp.txt","./data/highscores.txt");
    return;
}

void read_score(char* dst)
{
    FILE* highscores;
    highscores=fopen("./data/highscores.txt","ar+");
    char a=fgetc(highscores);
    int i=0;
    int l=0;
    while(a!=EOF)
    {
	if(a==';')
	{
	    a=' ';
	    l++;
	    if(l==20)break;
	}
	dst[i++]=a;
	a=fgetc(highscores);
    }
    dst[i]='\0';
    fclose(highscores);
    return;
}
