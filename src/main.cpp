#include <iostream>
#include <stdlib.h>
#include "../include/list.h"
using namespace std;

int main(int argc, char const *argv[]){
	
	sc::list<int> lista{};
	lista.push_back(56);
//	lista.push_front(132);
	
	lista.assign(11212, 123);

	cout <<  " : " << lista.size() << endl; 
	
	return 0;
}