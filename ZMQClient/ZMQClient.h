#pragma once
#include <zmq.hpp>
#include <iostream>
#include "Monitor.h"
typedef int SocketType;
class ZMQClient {
private:
	int threads_;
	zmq::socket_t *socket_;
	Monitor * monitor_;

	std::string addr_;
	SocketType type_;
	std::string clientName_;
public:
	/* constructor */
	ZMQClient(std::string clientName, SocketType type, const int threads = 1);

	/* destructor */
	~ZMQClient();

public:
	void connect();
	void send(std::string send_msg);
private:

	void initialize();

};