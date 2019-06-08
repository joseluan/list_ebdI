/*! @file main.cpp
    @brief classe principal onde pode a lista pode ser ultilizada
*/
#include <iostream>
#include <stdlib.h>
#include "../include/list.h"
using namespace std;

int main(int argc, char const *argv[]){
	
	sc::list<int> lista{};
	for (int i = 0; i < 3; ++i){
		lista.push_front(56+i);  
	}
	
	
	cout << lista.back() << endl;

	return 0;
}