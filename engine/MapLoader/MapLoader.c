#include "MapLoader.h"
#include "HashArray.h"
#include "stdio.h"
#include "SEntity.h"
#include "SEntityBase.h"

HashArray* loadMap() {
    HashArray* out = HashArray_new(1024);
    SEntity* test = SEntityTest_new("test_entity");
    out->addObject(out, test, test->core->entityName);
    return out;
}