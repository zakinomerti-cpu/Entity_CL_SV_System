#include "DSnapshotMaker.h"
#include "dataArr.h"
#include "HashArray.h"
#include <stdio.h>
#include "SEntity.h"

dataArr* snapshotMaker(HashArray* arr) {
    if(!arr) return NULL;
    dataArr* out = dataArr_new();
    for(int i = 0; i < arr->elementCount; i += 1) {
        if(!arr->InnerArrayIsExist(arr, i)) continue;
        uint64_t innerSize = arr->getInnerArraySize(arr, i);
        for(int j = 0; j < innerSize; j += 1) {
            SEntity* ent = arr->getObjectByIndex(arr, i, j);
            uint8_t* se = SEntitySerializeFull(ent);

            for(int i = 0; i < 102; i++) {
                printf("%x", se[i]);
            }
            printf("\n", se[i]);

            out->addToArray(out, se);
        }
    }

    return out;
}