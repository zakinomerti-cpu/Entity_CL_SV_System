#include "EntityUpdate.h"
#include "HashArray.h"
#include "dataArr.h"
#include "SEntity.h"
#include "stdint.h"
#include "stdio.h"

void updateEntities(HashArray* arr, uint32_t tick) {
    if(arr == NULL) return;
    for(int i = 0; i < arr->elementCount; i += 1) {
        if(!arr->InnerArrayIsExist(arr, i)) continue;
        uint64_t size = arr->getInnerArraySize(arr, i);
        for(int j = 0; j < size; j += 1) {
            SEntity* ent = arr->getObjectByIndex(arr, i, j);
            ent->onUpdate(ent, tick);
        }
    }
}