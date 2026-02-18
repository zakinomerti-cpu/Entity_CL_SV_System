#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "EntLoader.h"
#include "MapLoader.h"
#include "UserCmdReceiver.h"
#include "EntityUpdate.h"
#include "DSnapshotMaker.h"
#include "SnapshotSender.h"
#include "dataArr.h"
#include "HashArray.h"
#include "globals.h"

#include <unistd.h>

void init() {
	dataArr* clients = dataArr_new();
	HashArray* worldList = loadValidEntityList();
	HashArray* entList = loadMap();
}

void pausen() {
	printf("12\n");
	usleep(500000); // 500 мс
}

int main() {

	init();
	uint32_t tick = 0;
	char serverRunning = 1;
	while(serverRunning) {
		receiveUserCmds();
		updateEntities(tick);
		snapshotMaker();
		snapshotSender();

		tick += 1;
		pausen();
	}

	return 0;
}