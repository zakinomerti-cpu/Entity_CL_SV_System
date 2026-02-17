#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void loadGame() {}
void loadMap() {}
void receiveUserCmds() {}
void updateEntities(uint32_t tick) {}

void snapshotMaker() {}
void snapshotSender() {}

int main() {
	loadGame();
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