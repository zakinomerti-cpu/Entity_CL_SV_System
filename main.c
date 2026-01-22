#include <stdio.h>
#include <stdlib.h>
#include "SEntityBase.h"
#include "SEntity.h"
#include "dataArr.h"
#include <unistd.h>


int main() {
	unsigned int tick = 0;
	dataArr* list = dataArr_new();
	list->addToArray(list, SEntityTest_new("12"));
	list->addToArray(list, SEntityTest_new("13"));

	while(1) {
		for (int i = 0; i < list->size; i+=1) {
			SEntity* ent = list->getElement(list, i);
			ent->onUpdate(ent, tick);
			printf("%f\t%f\t%f\n", ent->core->pos[0], 
				ent->core->pos[1], ent->core->pos[2]);
		}

		usleep(64 * 1000);
		tick += 1;
	}

	return 0;
}