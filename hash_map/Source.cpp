#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include "hash_map.h"


using namespace std;




int main()
{
	
	hash_map<int, string> obj(10);

	obj.insert(10, "ten");
	std::cout << obj.get_size() << std::endl;

	obj.insert(20, "twenty");
	std::cout << obj.get_size() << std::endl;


	return 0;
}