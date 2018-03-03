class Client{
	private:
		int socket;
		string uname;
		RequestManage* mptr;
	
	public:
		Client(int s, string un, RequestManage* m){
			socket = s;
			uname = un;
			mptr = m;
		}

		
};
