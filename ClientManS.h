// cannot open file
void* ListeningThr(void* i);
void* ClientThr(void *);

class ClientManS{
	private:
		set<Client*> curClients;
		Client* Clientptr;
		
		int listener;
		int server;
		
		struct sockaddr_in server_addr;
		socklen_t serverlen;

		pthread_t Lthread;

		static ClientManS* cptr;
		
		bool createListeningThr(){
			if(pthread_create(&Lthread, NULL, ListeningThr, (void *)&Lthread)){
				cerr << "creating lthread failed" << endl;
				return false;
			}
			else
				return true;
		}
		
		bool loggedin(string name){
			set<Client*>::iterator it;
			for (it = curClients.begin(); it != curClients.end(); it++)
				if ((*it)->getUname() == name)
					return true;
			return false;
		}
		
		ClientManS(){};
		ClientManS(const ClientManS&){};
		ClientManS& operator=(ClientManS const&){};
		
			
	public:
		static ClientManS* getInstance(){
			if (!cptr)
				cptr = new ClientManS;
			return cptr;
		}
		
		bool setup(){
			if (createListeningThr())
				return true;
			return false;
		}
		
		bool validU(string name, string passwd){
			
			//if name has already logged in, return false;
			if(loggedin(name))
				return false;

			//verify password
			ifstream pfile;
			bool Valid = false;
			pfile.open(".UserPtab.dat");
			string str;
			while(pfile >> str){
				if(str.substr(0,str.find(":")) == name){
					if(str.substr(str.find(":")+1) == passwd){
						Valid = true;
						break;
					}
				}
			}
			pfile.close();
			return Valid;
		}
		
		bool addClient(string name){
			// add name 
			Clientptr = new Client(name);
			curClients.insert(Clientptr);
			cout << "..." << name << " has logged in!" << endl;
			return true;
		}
		
		bool delClient(string name){
			set<Client*>::iterator it;
			for (it = curClients.begin(); it != curClients.end(); it++)
				if((*it)->getUname() == name){
					curClients.erase(it);
					return true;
				}
			return true;
		}
		
		bool adduser(){};
		bool delUser(){};
		bool closeAllConn(){}
		
};


void* ListeningThr(void* i){
	
	int server;
	int listener = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1500);
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	socklen_t serverlen = sizeof(server_addr);
	vector<pthread_t*> vPthreads;
	pthread_t* cthread;
			
	if (bind(listener,(struct sockaddr *)&server_addr, serverlen) < 0){
		cerr << "Cannot bind a listener socket to a name..." << endl;
	}
	if (listen(listener, MAXUSERS) < 0){
		cerr << "Cannot set the listener to listen..." << endl;
	}
			
	cout << "Server is ready!" << endl;
	
	while(1){
		server = accept(listener, (struct sockaddr*)&server_addr, &serverlen);
		if (server < 0){
			cerr << "cannot accpet connection from client..." << endl;
			exit(1);
		}
		cout << "New connection established!" << endl;
		
		cthread = new pthread_t;
		vPthreads.push_back(cthread);
		if(pthread_create(cthread, NULL, ClientThr, (void*)(long)server)){
			cerr << "Cannot create a new client thread..." << endl;
		}
	}

	pthread_exit(NULL);
};

void* ClientThr(void *id){ 

	//Validation part
	
	ClientManS* p = ClientManS::getInstance();
	int server = (int)(long)id;
	char validationC[1024];
	char response[1024];
	string name;
	string passwd;

	
	strcpy(response,"Enter Name and password to login.");
	if(send(server, response, sizeof(response), 0) < 0){
		cerr << "Cannot send hint message to client..." << endl;
		close(server);
		pthread_exit(NULL);
	}

	while(1){
		if(recv(server, validationC, sizeof(validationC), 0) <= 0){
			cerr << "Cannot receive message from client..." << endl;
			close(server);
			pthread_exit(NULL);
		}
		
		//user information verified here
		string str(validationC);
		cout << str << endl;
		name = str.substr(0, str.find(":"));
		passwd = str.substr(str.find(":")+1);
		
		if (name == "exit"){
			close(server);
			cout << "Thread forfeited!" << endl;
			pthread_exit(NULL);
		}
			
		if(p->validU(name, passwd)){
			cout << "valid" << endl;
			strcpy(response,"User information Valid!");
			if (send(server, response, sizeof(response), 0) < 0){
				cerr << "Cannot response to client, closing connection..." << endl;
				close(server);
				pthread_exit(NULL);
			}
			p->addClient(name);
			break;
		}
		else{
			strcpy(response, "User information invalid or username has logged in!");
			if (send(server, response, sizeof(response), 0) < 0){
				cerr << "Cannot response to client, closing connection..." << endl;
				close(server);
				pthread_exit(NULL);
			}
		}
	}
	
	//processing part

	char queryC[QUERYSIZE];
	string query;
	char resultC[QUERYSIZE];
	string result;
	RequestManS* mptr = RequestManS::getInstance();
	
	while(1){
	
		if(recv(server, queryC, sizeof(queryC), 0) <= 0){
			cerr << "Cannot receive query from client, closing connection..." << endl;
			break;
		}

		query = queryC;
		if (query != "exit"){
			result = mptr-> getResult(query);
			strcpy(resultC, result.c_str());
		
			if (send(server, resultC, sizeof(resultC), 0) <= 0){
				cerr << "Cannot response to client, closing connection..." << endl;
				break;
			}
		}
		else
			break;
	}
	p->delClient(name);
	close(server);
	cout << "client " << name << " thread ended." << endl; 
	pthread_exit(NULL);
};

