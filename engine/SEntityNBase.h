#ifndef SENTITYNBASE_H
#define SENTITYNBASE_H

#include <stdint.h>

typedef struct SEntityNBase {
	uint16_t netID;
    uint16_t purMask;
    uint8_t[12] entMask;
} SEntityNBase;

SEntityNBase* SEntityBase_new(uint16_t netID, uint16_t purMask);

#endif