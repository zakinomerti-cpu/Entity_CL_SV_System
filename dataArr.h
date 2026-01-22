#ifndef DATAARRAY_H
#define DATAARRAY_H

typedef struct dataArr {
	int size;
	int capacity;
	void** data;
	void* (*getElement)(struct dataArr*, int index);
	void (*addToArray)(struct dataArr*, void* data);
} dataArr;

dataArr* dataArr_new();

#endif