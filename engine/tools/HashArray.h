#ifndef HASHARRAYCLASS_H
#define HASHARRAYCLASS_H

#include <stdint.h>
typedef struct dataArr dataArr;

typedef struct HashArrayElement {
	char* name;
	void* data;
} HashArrayElement;

typedef struct HashArray {
	void (*addObject)(struct HashArray*, void*, const char*);
	void* (*getObject)(struct HashArray*, const char*);

	dataArr* (*getInnerArray)(struct dataArr*, uint64_t);
	uint64_t elementCount;
	dataArr* Data;
} HashArray;

HashArray* HashArray_new(uint64_t);

#endif