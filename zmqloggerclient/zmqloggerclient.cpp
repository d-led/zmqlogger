#include "stdafx.h"

int main ()
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    socket.connect ("tcp://localhost:5555");

	for (int request_nbr = 0; request_nbr != 10; request_nbr++) {

		picojson::object o;
		o["from"]=picojson::value("test client");
		o["id"]=picojson::value((double)request_nbr);
		picojson::value v(o);
		std::string msg(v.serialize());

        zmq::message_t request (msg.length());
        memcpy ((void *) request.data (), msg.c_str(), msg.length());
        socket.send (request);

        // Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
		//bogus
    }

    return 0;
}
