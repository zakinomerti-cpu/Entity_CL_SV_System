#include "dataArr.h"
#include <stdlib.h>

void dataArr_addToArray(dataArr* arr, void* element) {
	if(arr->size >= arr->capacity) {
		arr->capacity = (arr->capacity == 0) ? 2 :
			arr->capacity * 2;
		void** tmp = realloc(arr->data, arr->capacity);
		if(!tmp) return;
		arr->data = tmp;
	}
	
	arr->data[arr->size] = element;
	arr->size += 1;
}

void* dataArr_getElement(dataArr* arr, int index) {
	if(index < 0 || index >= arr->size)
		return NULL;
	return arr->data[index];
}

dataArr* dataArr_new() {
	dataArr* arr = malloc(sizeof(dataArr));
	if(!arr) return NULL;

	arr->size = 0;
	arr->capacity = 0;
	arr->data = NULL;
	arr->getElement = dataArr_getElement;
	arr->addToArray = dataArr_addToArray;
	return arr;
} 