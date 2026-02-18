#include "EntityUpdate.h"
#include "HashArray.h"
#include "dataArr.h"
#include "SEntity.h"
#include "stdint.h"
#include "stdio.h"

void updateEntities(HashArray* arr, uint32_t tick) {
    if(arr == NULL) return;
    for(int i = 0; i < arr->elementCount; i += 1) {
        dataArr* innerArr = arr->Data->data[i];
        if(innerArr == NULL) { continue; }
        
        for(int j = 0; j < innerArr->size; j += 1) {
            HashArrayElement* element = (HashArrayElement*)innerArr->data[j];
            SEntity* ent = (SEntity*)element->data;
            ent->onUpdate(ent, tick);
        }
    }
}