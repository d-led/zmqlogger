#include "stdafx.h"

static __int64 epochmilliseconds()
{
    auto start = std::chrono::steady_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::microseconds>(start).count();
}

int main (int argc,char* argv[])
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_PUSH);

    socket.connect ("tcp://localhost:5555");

    for (int request_nbr = 0; request_nbr != 10; request_nbr++) {

        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        picojson::object o;
        o["from"]=picojson::value(argv[0]);
        o["id"]=picojson::value((double)_getpid());
        o["when"]=picojson::value((double)epochmilliseconds());
        picojson::value v(o);
        std::string msg(v.serialize());

        zmq::message_t request (msg.length());
        memcpy ((void *) request.data (), msg.c_str(), msg.length());
        socket.send (request);
    }

    if (argc>1) {
        zmq::socket_t kill_socket (context, ZMQ_PUSH);
        kill_socket.connect ("tcp://localhost:6666");
        std::string msg("mutabor");
        zmq::message_t request (msg.length());
        memcpy ((void *) request.data (), msg.c_str(), msg.length());
        kill_socket.send (request);
    }
    return 0;
}
