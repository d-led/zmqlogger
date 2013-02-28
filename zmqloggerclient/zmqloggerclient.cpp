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

    //for (int request_nbr = 0; request_nbr != 10; request_nbr++) {

    //    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    //    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //    picojson::object o;
    //    o["from"]=picojson::value(argv[0]);
    //    o["id"]=picojson::value((double)_getpid());
    //    o["when"]=picojson::value((double)epochmilliseconds());
    //    picojson::value v(o);
    //    std::string msg(v.serialize());

    //    zmq::message_t request (msg.length());
    //    memcpy ((void *) request.data (), msg.c_str(), msg.length());
    //    socket.send (request);
    //}

	typedef std::chrono::high_resolution_clock Clock;

	char buf[1024];
	std::string msg;
	for (int t=0; t<30; t++) {
		auto t1 = Clock::now();
		int count=100000;
		for (int i=0; i<count; i++) {
			sprintf(buf,"test %d",i);
			msg=buf;
			zmq::message_t request (msg.length());
			memcpy ((void *) request.data (), msg.c_str(), msg.length());
			socket.send (request);
		}
		auto t2 = Clock::now();
		auto diff=t2-t1;
		std::cout<<"benchmark : "<<std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()<<std::endl;
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
