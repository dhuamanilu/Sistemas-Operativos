#include <list>
#include <string>
#include <iostream>
using namespace std;
int main (){
	list<string> list;
	list.push_back("Hola");
	list.push_back("Mundo");
	cout << "List size = " << list.size() << '\n';
	return 0;
}

