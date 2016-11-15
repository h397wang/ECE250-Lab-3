
#ifndef nullptr
#define nullptr 0
#endif

#include "Trie_node.h"
#include "Trie.h"

#include <string>
#include <iostream>

using namespace std;


/*

int main(){
	
	Trie t = Trie();
	cout << "Should be empty" << t.empty() << endl;
	
	string s1 = "invalidstring69";
	
	try{
		cout << "Check member() " << t.member(s1) << endl; 
	}catch (illegal_argument e){
		cout << "Exception caught" << endl;
	}
	
	cout << "Test insertion" << endl;
	
	string s2 = "Validstring";
	cout << s2 << " Inserted " << t.insert(s2) << endl;
	string s3 = "Valid";
	cout << s3 << " Inserted " << t.insert(s3) << endl;
	cout << "Size " << t.size() << endl;
	cout << s3 << " Insert should fail " << t.insert(s3) << endl;
	cout << "Check member s3 should be true " << t.member(s3) << endl;
	string s4 = "notin";
	cout << "Try erasing something not in it " << t.erase(s4) << endl;
	cout << "Erase s3 " << t.erase(s3) << endl;
	cout << "s3 should be gone, so 0 " << t.member(s3) << endl;
	t.clear();
	cout << "Cleared everything, should be empty " << t.empty() << endl;
	

}

*/
