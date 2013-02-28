#include "stdafx.h"

static void init_g2log (const char* prefix,const char* location) {
	g2::initializeLogging(new g2LogWorker(prefix, location));
}

int main(int argc, char* argv[])
{
	init_g2log("g2log_benchmark","");

	typedef std::chrono::high_resolution_clock Clock;
    
	for (int t=0; t<30; t++) {
		auto t1 = Clock::now();
		int count=100000;
		for (int i=0; i<count; i++) {
			LOG(INFO)<<"test "<<i;
		}
		auto t2 = Clock::now();
		auto diff=t2-t1;
		std::cout<<"benchmark : "<<std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()<<std::endl;
	}

	std::cout<<"finished"<<std::endl;
	return 0;
}