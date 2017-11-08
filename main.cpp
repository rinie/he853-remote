#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "he853.h"

int main(int argc, char **argv)
{
	// Default protocol - see help text
	char protocol = 'E';

	// Check arguments
	if (argc != 1 && argc != 3 && !(argc >= 4 && strlen(argv[3]) == 1) ) {
		printf("Usage: %s [<DeviceID> <Command> [<Protocol>] [<Repeats>]]\n", argv[0]);
		printf("    DeviceID - ID of the device to act on\n");
		printf("    Command  - 0=OFF, 1=ON\n");
		printf("      NOTE: AnBan has also values > 1\n");
		// NOTE: "N=KAKUNEW" removed, contains currently only a static call
		printf("    Protocol - A=AnBan, U=UK, E=EU, K=KAKU, L=ALL\n");
		printf("      Default protocol is '%c'\n", protocol);
		printf("      NOTE: KAKU ID is device + group * 16\n");
		printf("      NOTE: Protocol ALL is meant for tests and sends out with all protocols!\n");
		printf("    Repeats: Repeat this number of times. Sometimes needed for more distant or slower devices (default: 1)\n");
		printf("    Without parameters the device status will be shown\n");
		return 1;
	}

	HE853Controller *remote = new HE853Controller();
	// Exit if something went wrong during accessing device
	if (!remote->getDeviceStatus()) {
		return 2;
	}

	// just show status and exit
	if (argc == 1) {
		printf("HE853 USB device (04d9:01357 Holtek Semiconductor, Inc.) is ready and accessible\n");
		return 0;
	}

	// assign parameters
	int deviceId = atoi(argv[1]);
	int command = atoi(argv[2]);

	// Protocol parameter requested?
	if (argc >= 4) {
		protocol = argv[3][0];
	}

	int repeats = 1;
	if (argc >= 5)
		repeats = atoi(argv[4]);

	for( int i = 0; i < repeats; i++ ) {
		if( i > 0 ) {
			struct timespec time = {
				.tv_sec = 0,
				.tv_nsec = 100000000,
			};
			nanosleep( &time, NULL );
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
			// case 'N':
			// 	printf("Sending command[%i] to deviceId[%i] with protocol KAKUNEW\n", command, deviceId);
			// 	remote->sendKakuNew((uint16_t)deviceId, (uint8_t)command);
			// 	break;
			case 'L':
				printf("Sending command[%i] to deviceId[%i] with ALL protocols\n", command, deviceId);
				remote->sendAll((uint16_t)deviceId, (uint8_t)command);
				break;
			default:
				printf("Unknown protocol\n");
				return 1;
		}
	}

	return 0;
}
