#include<iostream>
#include<pthread.h>
#include<stack>
#include<cstdlib>

using namespace std;

void *thrfunc(void* );

class MyClass{
	private:
		stack<int> s;
		pthread_t *ptr;
	public:
		bool test(){
			ptr = new pthread_t;
			cout << "Step 1" << endl;
			pthread_create(ptr, NULL, thrfunc, (void *)this);
			cout << "Step 2" << endl;
			return true;
		}

		bool add(int a){
			s.push(a);
			cout << "Step 3" << endl;
			return 0;
		}

		bool print(){
			cout << "Step 4" << endl;
			cout << s.top() << endl;
			cout << "Step 5" << endl;
			return true;
		}
};

void *thrfunc(void* i){
	MyClass* ptr = (MyClass*) i;
	cout << "Step 6" << endl;
	ptr->add(10);
	cout << "Step 7" << endl;
	pthread_exit(NULL);
};


int main(){
	MyClass m;
	m.test();
	m.print();
	return 0;
}
