#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "EntLoader.h"
#include "MapLoader.h"
#include "UserCmdReceiver.h"
#include "EntityUpdate.h"
#include "DSnapshotMaker.h"
#include "SnapshotSender.h"

int main() {
	loadValidEntityList();
	loadMap();


	uint32_t tick = 0;
	char serverRunning = 1;
	while(serverRunning) {
		receiveUserCmds();
		updateEntities(tick);
		snapshotMaker();
		snapshotSender();
	}

	return 0;
}