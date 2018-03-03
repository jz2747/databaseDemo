using namespace std;
#define MAXUSERS 100
#define MAXQUESIZE 10000
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
#include<string.h>
#include<pthread.h>
#include<time.h>

class User{
	
	private:
		struct sockaddr_in server_addr;
		socklen_t serverlen;
		int client;
		string name;
		
		bool closeconnection(){
			close(client);
			return true;
		}

	public:
		bool setup(){
			char msg[50];

			server_addr.sin_family = AF_INET;
			server_addr.sin_port = htons(1500);
			server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
			serverlen = sizeof(server_addr);
			client = socket(AF_INET,SOCK_STREAM,0);
	
			if (client < 0){
				cout << "Cannot get a socket..." << endl;
				exit(1);
			}
	
			if(connect(client, (struct sockaddr*)&server_addr, serverlen) < 0){
				cerr << "Cannot connect to server..." << endl;
				exit(1);
			}

			if(recv(client, msg, sizeof(msg),0) < 0){
				cerr << "Cannot receive the message..." << endl;
				exit(1);
			}
			cout << msg;
			return true;
		}
	
		bool verification(){
	
			char validation[1024];
			string password;
			string temp;
			bool Exit = false;
		
			while(!Exit){
		
				cout << "\nUser Name: ";
				cin >> name;
				if (name == "exit"){
					temp = "exit";
					Exit = true;
				}
				else{
					password = getpass("Password: ");
					temp = name + ":" + password;
				}
				strcpy(validation, temp.c_str());
				if(send(client, validation, sizeof(validation), 0) < 0){
					cerr << "Cannot send message to server..." << endl;
					closeconnection();
					break;
				}
		
				if (Exit){
					closeconnection();
					break;
				}
					
				if(recv(client, validation, sizeof(validation), 0) <= 0){
					cerr << "Cannot receive the message..." << endl;
					closeconnection();
					break;
				}
				cout << "\"" << validation << "\"" << endl;
				if (!strcmp(validation, "User information Valid!"))
					break;
			}
			return true;
		}

		//processing queries
	
		bool processing(){

			string command;
			char commandC[COMMANDSIZE];
	
			while(1){
				cout << "Command: ";
				cin >> command;
				strcpy(commandC, command.c_str());
				if(send(client, commandC, sizeof(commandC), 0) < 0){
					cerr << "Cannot send message to server..." << endl;
					break;
				}
		
				if (command == "exit"){
					break;
				}
					
				if(recv(client, commandC, sizeof(commandC), 0) <= 0){
					cerr << "Cannot receive the message..." << endl;
					break;
				}
				cout << "Result: " << commandC << endl;
			}
	
			close(client);
			cout << "You have logged out." << endl;
			return true;
		}
};
