#include "myheader.h"
#include "Student.h"
#include "RequestManage.h"
#include "Client.h"
#include "ClientManagement.h"

int main(){
	cout << "Welcome to Student File Management System(1.0)" << endl << 
		"Established by Jiange Zhao, 2017.11" << endl << 
		"Copyright Reserved. Don't email me, it is a test program!)" << endl;

	RequestManage manager;	
	ClientManagement cadm(manager);

	if(!cadm.setup()){
		cerr << "Cannot setup server, going to exit..." << endl;
		exit(1);
	}

	while(cadm.doListening(1)){
		manager.doProcess(1);
	}

	return 0;
}
