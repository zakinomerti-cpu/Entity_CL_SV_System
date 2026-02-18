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

dataArr* clients = NULL;
HashArray* worldList = NULL;
HashArray* entList = NULL;

void init() {
	clients = dataArr_new();
	worldList = loadMap();
	entList = loadValidEntityList();
}

void pausen() {
	usleep(500000); // 500 мс
}

int main() {

	init();
	uint32_t tick = 0;
	char serverRunning = 1;
	while(serverRunning) {
		receiveUserCmds();
		updateEntities(worldList, tick);
		dataArr* sArr = snapshotMaker(worldList);
		snapshotSender(sArr);

		tick += 1;
		pausen();
	}

	return 0;
}