#include "SEntity.h"
#include "SEntityBase.h"
#include "dataArr.h"
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

void SEntityTest_setInputData(SEntity* ent, dataArr* data) {

}

void SEntityTest_onUpdate(SEntity* ent, unsigned int tick) {
	ent->core->pos[0] += 0.01f;
	ent->core->pos[1] -= 0.001f;
	ent->core->pos[2] += 0.002f;
	printf("%f\t%f\t%f\t%d\n", ent->core->pos[0], 
		ent->core->pos[1], ent->core->pos[2], tick);
}

void SEntityTest_onCreate(SEntity* ent) {

}

void SEntityTest_entityInit(SEntity* ent) {
	ent->isReady = 1;
}

SEntity* SEntityTest_new(const char* name) {
	SEntity* ent = malloc(sizeof(SEntity));
	if(!ent) return NULL;

	ent->core = SEntityBase_new(name, "ent_tst");
	ent->setInputData = SEntityTest_setInputData;
	ent->onUpdate = SEntityTest_onUpdate;
	ent->onCreate = SEntityTest_onCreate;
	ent->entityInit = SEntityTest_entityInit;
	ent->LocalData = NULL;
	ent->InData = NULL;
	ent->isReady = 0;
	return ent;
}