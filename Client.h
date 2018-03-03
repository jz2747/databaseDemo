class Client{
	private:
		int socket;
		string uname;
		set<string> usableTs;
		
		bool inflateS(){
		
			return true;
		}
	
	public:
		Client(string name){
			uname = name;
			inflateS();
		}
		
		Client(int s, string name){
			socket = s;
			uname = name;
			inflateS();
		}
		
		string getUname(){
			return uname;
		}

		bool authorize(string tName){
			if(usableTs.find(tName) != usableTs.end())
				return true;
			return false;
		}
		
};
