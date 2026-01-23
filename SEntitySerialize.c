#include "SEntity.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void SerializeUint16LE(unsigned char* buf, uint16_t a) {
	buf[0] = (a >> 0) & 0xFF;
	buf[1] = (a >> 8) & 0xFF;
}

void SerializeUint32LE(unsigned char* buf, uint32_t a) {
	buf[0] = (a >> 0) & 0xFF;
	buf[1] = (a >> 8) & 0xFF;
	buf[2] = (a >> 16) & 0xFF;
	buf[3] = (a >> 24) & 0xFF;
}

void SerializeFloat(unsigned char* buf, float a) {
	uint32_t tmp;
	memcpy(&tmp, &a, sizeof(float));
	SerializeUint32LE(buf, tmp);
}

unsigned char* SEntitySerializeFull(SEntity* ent) {
	unsigned char* out = malloc(sizeof(unsigned char)*102);
	if(!out) return NULL;

	int offset = 0;
	SerializeUint16LE(out, netID); offset += 2;
	memcpy(out + offset, ent->core->SEntityName); offset += 32;
	memcpy(out + offset, ent->core->SEntityType); offset += 32;

	SerializeFloat(out + offset, ent->core->pos[0]); offset += 4;
	SerializeFloat(out + offset, ent->core->pos[1]); offset += 4;
	SerializeFloat(out + offset, ent->core->pos[2]); offset += 4;

	SerializeFloat(out + offset, ent->core->rot[0]); offset += 4;
	SerializeFloat(out + offset, ent->core->rot[1]); offset += 4;
	SerializeFloat(out + offset, ent->core->rot[2]); offset += 4;

	SerializeFloat(out + offset, ent->core->scl[0]); offset += 4;
	SerializeFloat(out + offset, ent->core->scl[1]); offset += 4;
	SerializeFloat(out + offset, ent->core->scl[2]); offset += 4;
	return out;
}

unsigned char* SEntitySerializeDelta(SEntity* ent) {
}

/*
typedef struct SEntityDelta {
	uint16_t netID;
	uint8_t movValue[3];
	uint8_t rotValue[3];
	uint8_t sclValue;
} SEntityDelta;

typedef struct netPack; {
	uint32_t tick;
	uint24_t entcount;
	unsigned char* ents;
} netPack;
*/