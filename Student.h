class Student{
	private:
		string name;
		int id;
		int mark;

	public:
		Student(string Name, int ID, int Mark){
			name = Name;
			id = ID;
			mark = Mark;
		}

		Student(string s){
			stringstream ss(s);
			ss >> name >> id >> mark;
		}

		string getName(){
			return name;
		}

		int getId(){
			return id;
		}

		int getMark(){
			return mark;
		}

		string print(){
			stringstream ss;
			ss << name << " " << id << " " << mark;
			return ss.str();
		}
};
