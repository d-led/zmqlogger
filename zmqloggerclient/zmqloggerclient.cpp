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

    return 0;
}
