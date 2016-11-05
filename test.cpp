
#ifndef nullptr
#define nullptr 0
#endif


#include <string>
#include <iostream>

using namespace std;



int main(){
	
	std::string str = "hEeery";

	cout << str.size() << endl;
	
	for (int i = 0; i < str.size(); i++){
		if (str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z'){
		//	cout << "Illegal" << endl;
			break;
			
		}
	}
}
