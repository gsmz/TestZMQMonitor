#include "ZMQClient.h"
#include "zmq.hpp"
#include <iostream>
#include <fstream>
#include "Config.h"
#include <thread>


ZMQClient::ZMQClient(std::string clientName, SocketType type, const int threads): clientName_(clientName), type_(type), threads_(threads){
	initialize();
}

ZMQClient::~ZMQClient() {

}
void doMonitor(Monitor &monitor, zmq::socket_t &socket) {
	std::cout << "start" << std::endl;
	monitor.monitor(socket, "inproc://monitor.req", ZMQ_EVENT_ALL);
}
void ZMQClient::initialize() {
	std::cout << __FUNCTION__ << std::endl;
	try
	{
		zmq::context_t *context = new zmq::context_t(threads_);
		socket_ = new zmq::socket_t(*context, type_);
		monitor_ = new Monitor();
		std::thread thr = std::thread(std::bind(doMonitor, std::ref(*monitor_), std::ref(*socket_)));
		thr.detach();
	}
	catch (zmq::error_t &e)
	{
		std::cout << __FUNCTION__ << ": " << e.what() << std::endl;
	}
}

void ZMQClient::connect() {
	std::string filename = clientName_ + ".config";
	Config::ConfigTable configTable = Config::readConfig(filename);
	for (Config::ConfigTable::iterator itr = configTable.begin(); itr != configTable.end(); itr++)
	{
		std::cout << itr->first << ": " << itr->second << std::endl;
	}
	std::string ipaddr = configTable["ip"];
	std::string port = configTable["port"];
	socket_->connect("tcp://" + ipaddr + ":" + port);

}

void ZMQClient::send(std::string send_msg) {
	zmq::message_t msg(send_msg.size());
	memcpy(msg.data(), send_msg.data(), send_msg.size());
}