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
#include<string.h>
#include<pthread.h>
#include<time.h>

#define MAXUSERS 100
#define MAXQUESIZE 10000
using namespace std;

struct request_t{
	int socket;
	string command;
};
