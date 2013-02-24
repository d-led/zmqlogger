#include "stdafx.h"

int main(int argc, char* argv[])
{
	using optparse::OptionParser;

    // prepare context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);

	// prepare options
	OptionParser parser = OptionParser().description("0mq json logger");

	parser.add_option("-p", "--port")
                  .dest("port")
				  .set_default("5555")
                  .help("set listening port");

	optparse::Values options = parser.parse_args(argc, argv);

	std::string port=options.get("port");
	std::string socket_config="tcp://*:";

	socket_config+=port;

	socket.bind (socket_config.c_str());

	std::cout<<"Starting listening on port "<<port<<std::endl;

    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);
        std::cout << "Received Hello" << std::endl;

        //  Do some 'work'
        //sleep (1);

        //  Send reply back to client
        zmq::message_t reply (5);
        memcpy ((void *) reply.data (), "World", 5);
        socket.send (reply);
    }
    return 0;
}

