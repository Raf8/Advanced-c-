/*
In general a c++ class allows developers to put implementation and interface parts into the public and private access specifiers. If you separate these into two classes one for the implementation also known as the body and one for the interface also known as the handle. A client uses the handle class to interact with the body class, we previously looked at the adapter pattern which uses the handle/body idiom by wrapping classes into another interface which is the handle to the client.
*/

#include <iostream>
#include <string>

using namespace std;

class Body{

public:
		Body() : str("") {}
		
		void printBody() {
			cout << "printBody called. \n";
		}

		void updateTxt(string s){
			str = s;
		}
		
		void printTxt(){
			cout << str << "\n";
		}

private:
		string str;
};

class Handle{
public:
		Handle(): bdy(new Body()){}
		
		void handleBody(string ss){
			bdy->printBody();
			bdy->updateTxt(ss);
			bdy->printTxt();		
		}

		~Handle() {
			if (bdy){
				delete bdy;		
			}
		}
private:
		Body* bdy;
};

int main(int argc, char* argv[]){
	Handle hand;
	hand.handleBody("main function call.");
	return 0;
}
