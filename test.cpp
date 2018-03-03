#include<iostream>
#include<unistd.h>
using namespace std;

int main(){
	string name;
	string password;
	char *pas;
	const char prompt[30] = "password: ";
	pas = getpass("password: ");
	password = pas;
	cout << pas << endl;
	cout << "\"" << password << "\"" << endl;
	return 0;
}
