#include "stdafx.h"

using optparse::OptionParser;

static void configure_parser(OptionParser& parser)
{
	parser.description("0mq json logger");

	parser.add_option("-p", "--port")
				.dest("port")
				.set_default<unsigned int>(5555)
				.help("set listening port");
}

static std::unique_ptr<g2LogWorker> current_worker=nullptr;

static void init_g2log (const char* prefix,const char* location) {

	current_worker.reset(new g2LogWorker(prefix, location));
	g2::initializeLogging(current_worker.get());
}

int main(int argc, char* argv[])
{
    // prepare context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);

	// prepare options
	OptionParser parser = OptionParser();
	configure_parser(parser);
	optparse::Values options = parser.parse_args(argc, argv);

	std::string port=options.get("port");
	std::string socket_config="tcp://*:"; //todo:configurable as a whole (?)
	socket_config+=port;

	init_g2log(port.c_str(),""/*todo configurable*/);

	socket.bind (socket_config.c_str());

	std::cout<<"Starting listening on port "<<port<<std::endl;
	LOG(INFO)<<"Starting listening on port "<<port;

    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);

		std::string msg;
		std::istringstream iss(static_cast<char*>(request.data()));
        iss >> msg;
		std::cout<<"received "<<msg<<std::endl;
		LOG(INFO)<<msg;
    }
    return 0;
}

