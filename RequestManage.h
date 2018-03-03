class RequestManage{
	private:
		queue<struct request_t*> rQue;
	public:
		bool enque(struct request_t* rptr){
			if (rQue.size() >= MAXQUESIZE)
				return false;
			rQue.push(rptr);
			return true;
		}
		
		bool doProcess(int timelimit){
			clock_t end = clock() + timelimit;
			//do{
				process();
			//}while(end >= clock());
			return true;
		}

		bool process(){
			// struct request_t request = *(rQue.top());

			return true;
		}

		bool addTable(){}
		bool delTable(){}
		bool listTable(){}

		bool addRecord(){
			ofstream file;
		        file.open(".StudentFile.dat", ios::app);
			string name;
			int id;
			int mark;
			cout << "Enter \"Name id mark\", with space seperating them" << endl;
			cin >> name >> id >> mark;
			Student obj(name,id,mark);
			file << obj.print() << endl;
			file.close();
			return true;
		}

		bool listRecord(){
			ifstream file;
			file.open("StudentFile.dat",ios::in);
			string tmpstr;
			while(getline(file, tmpstr)){
				cout << tmpstr << endl;
			}
			file.close();
			return true;
		}

		bool modifyRecord(){
			string name;
			int id;
			cout << "	Enter name and id to identify the record" << endl;
			cout << "	";
			cin >> name >> id;
			if (0){
				cout << "	Need at least a name or an id to identify record..." << endl;
				return false;
			}
			string newName;
			int newId;
			int newMark;
			cout << "	Enter new record \"Name id mark\", seperate with space." << endl;
			cout << "	";
			cin >> newName >> newId >> newMark;
			return true;
		}

		bool deleteRecord(){
			cout << "	this is deleteRecord func" << endl;
			if (0){
				cout << "Need at least a name or an id to identify record..." << endl;
				return false;
			}

			return true;
		}

};
