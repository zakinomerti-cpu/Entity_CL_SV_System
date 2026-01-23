#include "SEntity.h"
#include "SEntityBase.h"
#include "dataArr.h"
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

void SEntityTest_setInputData(SEntity* ent, dataArr* data) {

}

#include <math.h>  // для fabsf, roundf если нужно

void SEntityTest_onUpdate(SEntity* ent, unsigned int tick) {
    // 1. Вычисляем новую позицию
    ent->core->pos[0] += sinf(tick*0.25);
    float tmp = ent->core->pos[0]; // лучше sinf и масштабирование
    
    // 2. Берем дробную часть (всегда положительную)
    float fractional = tmp - (int)tmp; // дробная часть от -1 до 1
    
    // 3. Извлекаем первые две цифры (всегда положительные)
    int fractional_part = (int)(fabsf(fractional) * 100.0f + 0.5f); // с округлением
    
    // 4. Убеждаемся в пределах 0-99
    fractional_part = fractional_part % 256;
    
    // 5. Записываем в dpos (гарантированно 0-99)
    int8_t delta = (int8_t)ent->core->dpos[0] - (int8_t)fractional_part;
    
    // 6. Устанавливаем/сбрасываем бит знака
    if (delta < 0) {
        // Устанавливаем бит 0 (знак минус)
        ent->core->mask |= 0x00000001;  // ИЛИ для установки бита
    } else {
        // Сбрасываем бит 0 (знак плюс)
        ent->core->mask &= ~0x00000001; // И с инверсией для сброса
    }

    ent->core->dpos[0] = (uint8_t)fractional_part;
}

void SEntityTest_onCreate(SEntity* ent) {

}

void SEntityTest_entityInit(SEntity* ent) {
	ent->isReady = 1;
}

SEntity* SEntityTest_new(const char* name, uint16_t netID) {
	SEntity* ent = malloc(sizeof(SEntity));
	if(!ent) return NULL;

	ent->core = SEntityBase_new(name, "ent_tst", netID);
	ent->setInputData = SEntityTest_setInputData;
	ent->onUpdate = SEntityTest_onUpdate;
	ent->onCreate = SEntityTest_onCreate;
	ent->entityInit = SEntityTest_entityInit;
	ent->LocalData = NULL;
	ent->InData = NULL;
	ent->isReady = 0;
	return ent;
}