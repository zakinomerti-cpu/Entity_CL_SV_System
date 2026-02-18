#include "HashArray.h"
#include "dataArr.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

uint64_t HashArrToolSimpleHash(const char* str) {
    uint64_t hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = hash * 33 + c;
    }

    return hash;
}

uint64_t HashArrToolGetInnerArraySize(HashArray* arr, uint64_t index) {
    dataArr* tmp = arr->Data->getElement(arr->Data, index);
    if(!tmp) return 0;

    return (uint64_t)tmp->size;
}

void* HashArrToolGetObjectByIndex(HashArray* arr, uint64_t x, uint64_t y) {
    dataArr* tmp = arr->Data->getElement(arr->Data, x);
    if(!tmp) return NULL;

    HashArrayElement* hae = tmp->getElement(tmp, y);
    if(!hae) return NULL;

    return hae->data;
}

char HashArrToolInnerArrayIsExist(HashArray* arr, uint64_t index) {
    dataArr* tmp = arr->Data->getElement(arr->Data, index);
    if(!tmp) return 0;
    return 1;
}

dataArr* HashArrToolGetInnerArray(HashArray* arr, uint64_t index) {
    dataArr* tmp = arr->Data->getElement(arr->Data, index);
    if (!tmp) {
        tmp = dataArr_new();
         arr->Data->data[index] = tmp;
    }
    return tmp;
}


void HashArrToolAddObject(HashArray* arr, void* data, const char* name) {
    if (data == NULL) return;
    uint64_t hashIndex = HashArrToolSimpleHash(name) % arr->elementCount;
    dataArr* innerArr = HashArrToolGetInnerArray(arr, hashIndex);
    HashArrayElement* element = (HashArrayElement*)malloc(
        sizeof(HashArrayElement)); if (!element) return;

    element->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    if (!element->name) return;

    element->data = data;
    memcpy(element->name, name, strlen(name) + 1);

    innerArr->addToArray(innerArr, element);
}

void* HashArrToolGetObject(HashArray* arr, const char* name) {
    size_t hashIndex = (size_t)HashArrToolSimpleHash(name) % (size_t)arr->elementCount;
    dataArr* innerArr = HashArrToolGetInnerArray(arr, hashIndex);
    for (size_t iter = 0; iter < innerArr->size; iter++) {
        HashArrayElement* temp = 
            (HashArrayElement*)innerArr->getElement(innerArr, iter);
        if (strcmp(temp->name, name) == 0) {
            return temp->data;
        }
    }

    return NULL;
}

HashArray* HashArray_new(uint64_t size)
{
    HashArray* arr = (HashArray*)malloc(sizeof(HashArray));
    if (!arr) return NULL;

    arr->addObject = HashArrToolAddObject;
    arr->getObject = HashArrToolGetObject;
    arr->getInnerArray = HashArrToolGetInnerArray;
    arr->InnerArrayIsExist = HashArrToolInnerArrayIsExist;
    arr->getObjectByIndex = HashArrToolGetObjectByIndex;
    arr->getInnerArraySize = HashArrToolGetInnerArraySize;
    arr->elementCount = size;
    arr->Data = dataArr_new();
    if (!arr->Data) {
        free(arr);
        return NULL;
    }

    for (size_t i = 0; i < size; i += 1) {
        arr->Data->addToArray(arr->Data, NULL);
    }

    return arr;

}