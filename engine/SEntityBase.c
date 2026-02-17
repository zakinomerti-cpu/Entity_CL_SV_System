#include "SEntityBase.h"
#include "stdlib.h"
#include "string.h"

void SEntityBase_setPosition(SEntityBase* ent, 
	float x, float y, float z) 
{
	ent->pos[0] = x; ent->pos[1] = y; ent->pos[2] = z;
}

void SEntityBase_setRotation(SEntityBase* ent, 
	float x, float y, float z) 
{
	ent->rot[0] = x; ent->rot[1] = y; ent->rot[2] = z;
}

void SEntityBase_setScale(SEntityBase* ent, 
	float x, float y, float z) 
{
	ent->scl[0] = x; ent->scl[1] = y; ent->scl[2] = z;
}

float* SEntityBase_getPosition(SEntityBase* ent) {
	float* out = malloc(sizeof(float)*3);
	out[0] = ent->pos[0];
	out[1] = ent->pos[1];
	out[2] = ent->pos[2];
	return out;
}
float* SEntityBase_getRotation(SEntityBase* ent) {
	float* out = malloc(sizeof(float)*3);
	out[0] = ent->rot[0];
	out[1] = ent->rot[1];
	out[2] = ent->rot[2];
	return out;
}
float* SEntityBase_getScale(SEntityBase* ent) {
	float* out = malloc(sizeof(float)*3);
	out[0] = ent->scl[0];
	out[1] = ent->scl[1];
	out[2] = ent->scl[2];
	return out;
}

SEntityBase* SEntityBase_new(const char* name, const char* type, uint16_t netID) {
	SEntityBase* out = malloc(sizeof(SEntityBase));
	if(!out) return NULL;

	strcpy(out->entityName, name);
	strcpy(out->entityType, type);

	out->pos[0] = 0.; out->pos[1] = 0.; out->pos[2] = 0.;
	out->rot[0] = 0.; out->rot[1] = 0.; out->rot[2] = 0.;
	out->scl[0] = 1.; out->scl[1] = 1.; out->scl[2] = 1.;

	out->setPosition = SEntityBase_setPosition;
	out->setRotation = SEntityBase_setRotation;
	out->setScale = SEntityBase_setScale;

	out->getPosition = SEntityBase_getPosition;
	out->getRotation = SEntityBase_getRotation;
	out->getScale = SEntityBase_getScale;
	return out;
}