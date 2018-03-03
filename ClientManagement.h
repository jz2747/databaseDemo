class ClientManagement{
	private:
		vector<Client*> vClient;
		int listener;
		int server;
		struct sockaddr_in server_addr;
		socklen_t serverlen;
		Client* Clientptr;
		RequestManage* mptr;
		pthread_t* threadptr;
		vector<pthread_t> vPthread;

	public:
		ClientManagement( RequestManage& m){
			mptr = &m;
		}

		bool setup(){		
			listener = socket(AF_INET,SOCK_STREAM,0);
			server_addr.sin_family = AF_INET;
			server_addr.sin_port = htons(1500);
			server_addr.sin_addr.s_addr = htons(INADDR_ANY);
			serverlen = sizeof(server_addr);

			if (bind(listener,(struct sockaddr *)&server_addr, serverlen) < 0){
				cerr << "Cannot bind a listener socket to a name..." << endl;
				return false;
			}
			if (listen(listener, MAXUSERS) < 0){
				cerr << "Cannot set the listener to listen..." << endl;
				return false;
			}
			cout << "Server is ready!" << endl;
			return true;
		}

		bool listening(){

			server = accept(listener, (struct sockaddr*)&server_addr, &serverlen);
			if (server < 0){
				cerr << "cannot accpet connection from client..." << endl;
				exit(1);
			}
			cout << "New connection established!" << endl;

			char hint[30] = "Enter User Name to Login.";
			if(send(server, hint, sizeof(hint), 0) < 0){
				cerr << "Cannot send hint message to client..." << endl;
				exit(1);
			}

			char validationC[1024];
			if(recv(server, validationC, sizeof(validationC), 0) < 0){
				cerr << "Cannot receive message from client..." << endl;
				exit(1);
			}
			string validation(validationC);
			char response[50];
			if(validU(validation)){
				string un = validation.substr(0,validation.find(":"));
				Clientptr = new Client(server, un, mptr);
				vClient.push_back(Clientptr);
				threadptr = new pthread_t;
				// pthread_create(threadptr, NULL, threadfunc , (void *)Clientptr);
				vPthread.push_back(*threadptr);
				cout << "..." << un << " has logged in!" << endl;
				strcpy(response,"User information Valid!");
			}
			else{
				strcpy(response, "User information invalid! closing socket!");
				cerr << "Invalid user information..." << endl;
				close(server);
			}
				
			if (send(server, response, sizeof(response), 0) < 0){
				cerr << "Cannot response to client, closing connection..." << endl;
			}

			return true;	
		}

		bool validU(string validation){
			ifstream pfile;
			bool pValid = false;
			pfile.open(".UserPTab.dat", ios::in);
			string name;

			while(pfile >> name){
				if(validation == name){
					pValid = true;
					break;
				}
			}
			pfile.close();
			return pValid;
		}

		bool addUser(){
			string newUser;
			cout << "	Enter new user name: ";
			cin >> newUser;
			ofstream userfile;
			userfile.open(".UserTab.dat",ios::app);
			userfile << newUser << endl;
			userfile.close();
			return true;
		}
		
		bool doListening(int timelimit){
			clock_t end = clock() + timelimit;
		        //do{
				listening();
			//}while(end >= clock());
			return true;		
		}
};

void *threadfunc(void* p){
	Client* c = (Client *)p;
	// 1. enter a command
	// 2. preprocess the command
	// 3. send the request
	// 4. receive the response
	// 5. display the response
	// 6. return to step 1
	pthread_exit(NULL);
};
