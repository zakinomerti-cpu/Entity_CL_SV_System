#ifndef SENTITY_H
#define SENTITY_H

#include <stdint.h>

typedef struct SEntityBase SEntityBase;
typedef struct dataArr dataArr;

typedef struct SEntity {
	SEntityBase* core;  
	void (*setInputData)(struct SEntity*, dataArr* data);
	void (*onUpdate)(struct SEntity*, unsigned int tick);
	void (*onCreate)(struct SEntity*);
	void (*entityInit)(struct SEntity*);

	dataArr* LocalData;
	dataArr* InData;
	char isReady;
} SEntity;

SEntity* SEntityTest_new(const char* name);

//for first load
unsigned char* SEntitySerializeFull(SEntity* ent);

//for update
unsigned char* SEntitySerializeDelta(SEntity* ent);

#endif