#include "DataStreamer.h"
#include "ActivityLog.h"

int main()
{
	ActivityLog myLog;

	/*try {
		DataStreamer streamer("204.27.61.92");
		streamer.startUp();
		streamer.connectToServer();
		streamer.sendData("GET /beej/inet_ntoaman.html http/1.1\nHOST: retran.com\n\n");
		std::cout << streamer.getResponse();
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}*/

	return 0;
}