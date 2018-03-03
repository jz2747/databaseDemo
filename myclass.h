class MyClass{
	private:
		stack<int> s;
		pthread_t *ptr;
	public:
		bool test(){
			ptr = new pthread_t;
			pthread_create(ptr, NULL, thrfunc, (void *)this);
			return true;
		}

		bool add(int a){
			s.push(a);
			return 0;
		}

		bool print(){
			cout << s.top() << endl;
			return true;
		}
};

void *thrfunc(void* i){
	MyClass* ptr = (MyClass*) i;
	ptr->add(10);
	pthread_exit(NULL);
};

