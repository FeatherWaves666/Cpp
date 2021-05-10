#ifndef __SEQUELIST__H__
#define __SEQUELIST__H__

#include<cstring>
#include<iostream>
#include<assert.h>
#define SLDATESIZE 100
typedef int SLDATETYPE;

typedef struct SL {
	SLDATETYPE *a;
	int size;
	int capacity;
}SL;

void initSL(SL& s);

void SLCheckCapacity(SL&);
void pushBack(SL&,SLDATETYPE);
void pushFront(SL&, SLDATETYPE);
void popBack(SL&, SLDATETYPE);
void popFront(SL&, SLDATETYPE);
void insert(SL&, int, SLDATETYPE);
void erase(SL&, SLDATETYPE);
void destory(SL&);
void print(SL&);
int find(SL&, SLDATETYPE);
void modify(SL&,int, SLDATETYPE);
#endif