#include "stdafx.h"

static std::unique_ptr<g2LogWorker> current_worker;

static void init_g2log (const char* prefix,const char* location) {

	current_worker.reset(new g2LogWorker(prefix, location));
	g2::initializeLogging(current_worker.get());
}

int main(int argc, char* argv[])
{
	init_g2log("g2log_benchmark","");
	int count=100000;
	for (int i=0; i<count; i++) {
		LOG(INFO)<<"test "<<i;
	}
	std::cout<<"finished"<<std::endl;
	return 0;
}