void* ListeningThr(void* i);

class ClientManS{
	private:
		vector<Client*> vClient;
		int listener;
		int server;
		struct sockaddr_in server_addr;
		socklen_t serverlen;
		Client* Clientptr;
		pthread_t Lthread;
		vector<pthread_t> vPthread;
		static ClientManS* cptr;
		
		
		bool setInet(){
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
			cout << "Test: " << listener << endl;
			return true;
		
		}
		
		bool createListeningThr(){
			if(pthread_create(&Lthread, NULL, ListeningThr, (void *)&Lthread)){
				cerr << "Cannot create listening thread..." << endl;
				return false;
			}
			else
				return true;
		}
		
		ClientManS(){};
		ClientManS(const ClientManS&){};
		ClientMans& operator=(ClientManS const&){};
		
			
	public:
		static ClientManS* getInstance(){
			if (!mInstance)
				mInstance = new ClientManS;
			return mInstance;
		}
		
		bool setup(){
			if (setInet() && createListeningThr())
				return true;
			else
				return false;
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
		
		int printLT(){
			return listener;
		}
};


void* ListeningThr(void* i){

	ClientManS* ptr;
	ptr = ClientManS.getInstance();
	cout << "Test in Listening thread: " << ptr->printLT() << endl;
	
	/*
	while(1){
		server = accept(listener, (struct sockaddr*)&server_addr, &serverlen);
		if (server < 0){
			cerr << "cannot accpet connection from client..." << endl;
			exit(1);
		}
		cout << "New connection established!" << endl;
		
		pthread_t temp;
		if(pthread_create(&temp, NULL, ClientThr, (void*) &temp)){
			cerr << "Cannot create a new client thread..." << endl;
		}
	}*/
	return 0;
};

void* ClientThr(void* i){
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
	
	// above is authentification
	// below is query processing

	while(1){
	// receiving request
	// processing request
	// send back request
	}
	pthread_exit(NULL);
}
