#include<iostream>
#include<fstream>
using namespace std;

int main(){
	ifstream f("UserPtab.dat");
	if(!f.is_open()){
		cout << "file cannot be opened." << endl;
	}
	
	string str;
	f >> str;
	cout << str << endl;
	f.close();
	return 0;
}
