#include <map>
#include <string>
#include <iostream>
using namespace std;
 
void map_insert(map < string, string > *mapStudent, string index, string x)
{
	mapStudent->insert(map < string, string >::value_type(index, x));
}
 
int main(int argc, char **argv)
{
	char tmp[32] = "";
	map < string, string > mapS;
	
	//insert element
	map_insert(&mapS, "192.168.0.128", "xiong");
	map_insert(&mapS, "192.168.200.3", "feng");
	map_insert(&mapS, "192.168.200.33", "xiongfeng");
	
	map < string, string >::iterator iter;
	
	cout << "We Have Third Element:" << endl;
	cout << "-----------------------------" << endl;
	
	//find element
	iter = mapS.find("192.168.0.33");
	if (iter != mapS.end()) {
		cout << "find the elememt" << endl;
		cout << "It is:" << iter->second << endl;
	} else {
		cout << "not find the element" << endl;
	}
	
	//see element
	for (iter = mapS.begin(); iter != mapS.end(); iter ) {
		
		cout << "| " << iter->first << " | " << iter->
			second << " |" << endl;
		
	}
	cout << "-----------------------------" << endl;
	
	map_insert(&mapS, "192.168.30.23", "xf");
	
	cout << "After We Insert One Element:" << endl;
	cout << "-----------------------------" << endl;
	for (iter = mapS.begin(); iter != mapS.end(); iter ) {
		
		cout << "| " << iter->first << " | " << iter->
			second << " |" << endl;
	}
	
	cout << "-----------------------------" << endl;
	
	//delete element
	iter = mapS.find("192.168.200.33");
	if (iter != mapS.end()) {
		cout << "find the element:" << iter->first << endl;
		cout << "delete element:" << iter->first << endl;
		cout << "=================================" << endl;
		mapS.erase(iter);
	} else {
		cout << "not find the element" << endl;
	}
	for (iter = mapS.begin(); iter != mapS.end(); iter ) {
		
		cout << "| " << iter->first << " | " << iter->
			second << " |" << endl;
		
	}
	cout << "=================================" << endl;
	
	return 0;
}