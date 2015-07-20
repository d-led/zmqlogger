#include "stdafx.h"

using optparse::OptionParser;

static void configure_parser(OptionParser& parser)
{
	parser.description("0mq + g2log async logging server");

	parser.add_option("-p", "--port")
		.dest("port")
		.set_default<unsigned int>(5555)
		.help("set listening port");
}

template <typename TReq>
std::string to_string(TReq&& request)
{
	return std::string(static_cast<char*>(request.data()),request.size());
}

template <typename TReq>
void log(TReq&& request)
{
	std::string msg=to_string(request);
	LOG(INFO)<<msg;
}

int main(int argc, char* argv[])
{
	// prepare context
	zmq::context_t context (1);

	// prepare options
	OptionParser parser = OptionParser();
	configure_parser(parser);
	optparse::Values options = parser.parse_args(argc, argv);

	std::string port=options.get("port");
	std::string socket_config="tcp://*:";
	socket_config+=port;

    using namespace g2; // --> g3
    auto defaultHandler = LogWorker::createWithDefaultLogger(argv[0], "");
    g2::initializeLogging(defaultHandler.worker.get());

	// main socket
	zmq::socket_t log_socket(context, ZMQ_PULL);
	log_socket.bind(socket_config.c_str());

	std::cout<<"Starting listening at "<<socket_config<<std::endl;

	bool to_kill=false;

	while (!to_kill) {
		zmq::message_t request;
		log_socket.recv(&request);
		log(request);
	}

	return 0;
}