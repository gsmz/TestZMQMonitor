#include "ZMQClient.h"

int main() {
	ZMQClient client("TestClient", ZMQ_REQ);
	client.connect();
	while (1)
	{
//		client.send("ok");
	}
	return 0;
}