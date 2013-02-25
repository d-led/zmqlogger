#include "stdafx.h"

using optparse::OptionParser;

static void configure_parser(OptionParser& parser)
{
	parser.description("0mq + g2log async logging server");

	parser.add_option("-p", "--port")
		.dest("port")
		.set_default<unsigned int>(5555)
		.help("set listening port");

	parser.add_option("-k", "--kill")
		.dest("kill")
		.set_default("mutabor")
		.help("termination token secret word");
}

static std::unique_ptr<g2LogWorker> current_worker;

static void init_g2log (const char* prefix,const char* location) {

	current_worker.reset(new g2LogWorker(prefix, location));
	g2::initializeLogging(current_worker.get());
}

template <typename TReq>
std::string to_string(TReq&& request)
{
	return std::string(static_cast<char*>(request.data()),request.size());
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
	std::string socket_config="tcp://*:"; //todo:configurable as a whole (?)
	socket_config+=port;

	init_g2log(port.c_str(),""/*todo configurable*/);

	// main socket
	zmq::socket_t log_socket(context, ZMQ_PULL);
	log_socket.bind(socket_config.c_str());
	// kill socket (port 6666)
	zmq::socket_t kill_socket(context, ZMQ_PULL);
	kill_socket.bind("tcp://*:6666");

	// secret word
	std::string kill_secret=options.get("kill");

    // Initialize poll set
    zmq::pollitem_t items [] = {
        { log_socket, 0, ZMQ_POLLIN, 0 },
        { kill_socket, 0, ZMQ_POLLIN, 0 }
    };

	std::cout<<"Starting listening at "<<socket_config<<std::endl;

	bool to_kill=false;

	while (!to_kill) {

		zmq::message_t request;
		zmq::poll (&items [0], 2, -1);

		// log entries
		if (items [0].revents & ZMQ_POLLIN) {
			log_socket.recv(&request);

			std::string msg=to_string(request);
			LOG(INFO)<<msg;
			std::cout<<"received : "<<msg<<std::endl;
		}

		// kill or not?
		if (items [1].revents & ZMQ_POLLIN) {
			kill_socket.recv(&request);
			std::string kill=to_string(request);
			if (kill==kill_secret) {
				std::cout<<"stopped using kill token"<<std::endl;
				to_kill=true;
				log_socket.close();
				kill_socket.close();
			}
			// set kill flag if secret word sent
		}
	}

	return 0;
}