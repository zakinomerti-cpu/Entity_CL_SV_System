#include <stdio.h>
#include <stdlib.h>
#include "SEntityBase.h"
#include "SEntity.h"
#include "dataArr.h"
#include <unistd.h>


int main() {
	unsigned int tick = 0;
	dataArr* list = dataArr_new();
	list->addToArray(list, SEntityTest_new("12", list->size));
	list->addToArray(list, SEntityTest_new("13", list->size));

	while(1) {
		for (int i = 0; i < list->size; i+=1) {
			SEntity* ent = list->getElement(list, i);
			ent->onUpdate(ent, tick);
			printf("%f\t%d\t0x", ent->core->pos[0], 
				ent->core->dpos[0]);
			for(int i = 0; i < 8; i++) {
				printf("%d", ((ent->core->mask >> i) & 0xf));
			}
			printf("LE!!\n");
		}

		usleep(512 * 1000);
		tick += 1;
	}

	return 0;
}