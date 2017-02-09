#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "he853.h"

int main(int argc, char **argv)
{
	char protocol = 'E';
	// Check arguments
	if (argc < 3 || argc > 4 || ( argc == 4 && strlen(argv[3]) != 1 )) {
		printf("Usage: %s <DeviceID> <Command> [<Protocol>]\n", argv[0]);
		printf("    DeviceID - ID of the device to act on\n");
		printf("    Command  - 0=OFF, 1=ON\n");
		printf("      NOTE: AnBan has also values > 1\n");
		printf("    Protocol - A=AnBan, U=UK, E=EU, K=KAKU, N=KAKUNEW, L=ALL\n");
		printf("      Default protocol is '%c'\n", protocol);
		printf("      NOTE: Protocol ALL is meant for tests and sends out with all protocols!\n");
		return 1;
	}
	int deviceId = atoi(argv[1]);
	int command = atoi(argv[2]);
	if (argc == 4) {
		protocol = argv[3][0];
	}

	HE853Controller *remote = new HE853Controller();
	// Exit if something went wrong during accessing device
	if (remote->getDeviceInitialized() == false) {
		return 2;
	}

	switch(protocol)
	{
		case 'A':
			printf("Sending command[%i] to deviceId[%i] with protocol AnBan\n", command, deviceId);
			remote->sendAnBan((uint16_t)deviceId, (uint8_t)command);
			break;
		case 'E':
			printf("Sending command[%i] to deviceId[%i] with protocol EU\n", command, deviceId);
			remote->sendEU((uint16_t)deviceId, (uint8_t)command);
			break;
		case 'U':
			printf("Sending command[%i] to deviceId[%i] with protocol UK\n", command, deviceId);
			remote->sendUK((uint16_t)deviceId, (uint8_t)command);
			break;
		case 'K':
			printf("Sending command[%i] to deviceId[%i] with protocol KAKU\n", command, deviceId);
			remote->sendKaku((uint16_t)deviceId, (uint8_t)command);
			break;
		case 'N':
			printf("Sending command[%i] to deviceId[%i] with protocol KAKUNEW\n", command, deviceId);
			remote->sendKakuNew((uint16_t)deviceId, (uint8_t)command);
			break;
		case 'L':
			printf("Sending command[%i] to deviceId[%i] with ALL protocols\n", command, deviceId);
			remote->sendAll((uint16_t)deviceId, (uint8_t)command);
			break;
		default:
			printf("Unknown protocol\n");
			return 1;
	}

	return 0;
}
