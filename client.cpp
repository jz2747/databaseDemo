#include "myheader.h"

int main(){
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1500);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        socklen_t serverlen = sizeof(server_addr);
	int client = socket(AF_INET,SOCK_STREAM,0);

	if (client < 0){
		cout << "Cannot get a socket..." << endl;
		exit(1);
	}
	
	if(connect(client, (struct sockaddr*)&server_addr, serverlen) < 0){
		cerr << "Cannot connect to server..." << endl;
		exit(1);
	}

	char msg[50];
	if(recv(client, msg, sizeof(msg),0) < 0){
		cerr << "Cannot receive the message..." << endl;
		exit(1);
	}
	cout << msg;

	string name;
	string password;
	cout << "\nUser Name: ";
	cin >> name;
	cout << "Password: ";
	cin >> password;
	string temp = name + ":" + password;
	char validation[1024];
        strcpy(validation, temp.c_str());
	if(send(client, validation, sizeof(validation), 0) < 0){
		cerr << "Cannot send message to server..." << endl;
		exit(1);
	}
	if(recv(client, msg, sizeof(msg), 0) < 0){
		cerr << "Cannot receive the message..." << endl;
		exit(1);
	}
	cout << msg << endl;
	return 0;
}	
