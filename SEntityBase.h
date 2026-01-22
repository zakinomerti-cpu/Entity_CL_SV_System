#ifndef SENTITYBASE_H
#define SENTITYBASE_H

typedef struct SEntityBase{
	char entityName[32];
	char entityType[32];
	float pos[3];
	float rot[3];
	float scl[3];

	void (*setPosition)(struct SEntityBase*, float, float, float);
	void (*setRotation)(struct SEntityBase*, float, float, float);
	void (*setScale)(struct SEntityBase*, float, float, float);

	float* (*getPosition)(struct SEntityBase*);
	float* (*getRotation)(struct SEntityBase*);
	float* (*getScale)(struct SEntityBase*);
} SEntityBase;

SEntityBase* SEntityBase_new(const char* name, const char* type);

#endif