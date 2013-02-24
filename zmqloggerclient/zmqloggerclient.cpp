#include "stdafx.h"

int main ()
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    socket.connect ("tcp://localhost:5555");

    for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
        std::string msg("hello");
		msg+=(char)0;
		std::cout<<socket.send (msg.c_str(),msg.length());
    }
    return 0;
}
