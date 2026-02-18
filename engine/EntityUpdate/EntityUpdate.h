#ifndef ENTITYUPDATEFUNCTION_H
#define ENTITYUPDATEFUNCTION_H
#include "stdint.h"

typedef struct HashArray HashArray;
void updateEntities(HashArray* arr, uint32_t tick);

#endif