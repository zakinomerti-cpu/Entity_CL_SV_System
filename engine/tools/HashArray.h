#ifndef HASHARRAYCLASS_H
#define HASHARRAYCLASS_H

#include <stdint.h>
typedef struct dataArr dataArr;

typedef struct HashArrayElement {
	char* name;
	void* data;
} HashArrayElement;

typedef struct HashArray {
	//public
	void (*addObject)(struct HashArray*, void*, const char*);
	void* (*getObject)(struct HashArray*, const char*);
	char (*InnerArrayIsExist)(struct HashArray*, uint64_t);
	void* (*getObjectByIndex)(struct HashArray*, uint64_t x, uint64_t y);
	uint64_t (*getInnerArraySize)(struct HashArray*, uint64_t);
	uint64_t elementCount;

	//private
	dataArr* (*getInnerArray)(struct HashArray*, uint64_t);
	dataArr* Data;
} HashArray;

HashArray* HashArray_new(uint64_t);

#endif