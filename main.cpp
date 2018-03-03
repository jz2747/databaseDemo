using namespace std;
#define MAXUSERS 100
#define MAXQUESIZE 10000
#define QUERYSIZE 1024
#define COMMANDSIZE 1024

#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<queue>
#include<pthread.h>
#include<unistd.h>
#include<cstring>
#include<set>

#include"RequestManS.h"
#include"Client.h"
#include"ClientManS.h"

ClientManS* ClientManS::cptr = NULL;
RequestManS* RequestManS::rptr = NULL;

int main(){
	RequestManS* rman = RequestManS::getInstance();
	ClientManS* cman = ClientManS::getInstance();

	if(!cman->setup())
		exit(1);

	while(1)
		rman->processing();

	return 0;
}
