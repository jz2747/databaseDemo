class RequestManS{
	private:
		static RequestManS* rptr;
		RequestManS(){};
		RequestManS(const RequestManS&){};
		RequestManS& operator=(RequestManS const&){};

	public:
		static RequestManS* getInstance(){
			if(!rptr)
				rptr = new RequestManS;
			return rptr;
		}
		
		bool processing(){
		
			return 0;
		}
		
		string getResult(string str){ return str; };
		
};
