/*What is a member function pointer, an normal function pointer holds the address of the function to call but a member function pointer holds the offset of the function address in the objects list of functions, If it is a virtual function then it is an offset into the virtual table of function pointers. You can only use them on behalf of an object to dereference the function, let's look at an example */

//Normal function pointer
void printString(string s) {
	cout << s << endl;
}

//Member function pointer.
class funcPointer{
	public:
		void printString(string s) {
			cout << s << endl;
		}

};

//Polymorphism use.
class Base {
public:
	virtual void sayHello() {
		cout << "Hello from Base class. \n";
	}
};

class Derived : public Base {
public:
	void sayHello() {
		cout << "Hello from Derived class. \n";
	}
};


int main(int argc, char* argv[]) {

	//Standard function pointer example
	string ss = "Hello World.";

	void(*funcPtr)(string) = &printString;

	(*funcPtr)(ss);


	//Member function pointer example.
	string str = "Hello from member function pointer.!!";
	void (funcPointer::*memFuncPtr)(string) = &funcPointer::printString;

	funcPointer fP;

	(fP.*memFuncPtr)(str);

	//Virtual member function example.
	void (Base::*baseFuncPtr)() = &Base::sayHello;
	void (Derived::*derivedFuncPtr)() = &Derived::sayHello;

	Base bP;
	Derived dP;

	(bP.*baseFuncPtr)();  //call Base::sayHello
	(dP.*derivedFuncPtr)(); //call Derived::sayHello
	(dP.*baseFuncPtr)();  //call Derived::sayHello using base pointer and derived object. 


	return 0;
}    

/*
The first function is used as an example of a normal function pointer, class funcPointer is used to show member function pointer use. The Base class and derived class are used to show polymorphism using member function pointers. The main method creates a string to use as a parameter to the printString function then create a function pointer to the printString function and invokes the function using the string which prints out Hello World. It next defines another string to use in the member function pointer memFuncPtr. The member function is defines as return_type (className::*pointerName)(parameter types) so in this case the return type is void, the className is funcPointer, the pointerName is memFuncPtr and the parameter types are std::string. The address reference on the right had side uses the syntax &className::function_name so here className is funcPointer and the function name is printString. Next we create an instance of the class funcPointer fP and we use this too invoke the memFuncPtr with the string str as a parameter. The invocation uses the form result = (object.*memberPointerName)(parameters) here there is no result as the function is void, the object is fP, the member pointer name is memFuncPtr and the parameter is the string str. The main method then defines two more member function pointers baseFuncPtr and derivedFuncPtr which have no parameter types and point to the functions Base::sayHello and Derived::sayHello. The we create two objects of type Base and Derives and use these to invoke their sayHello functions. The last invocation demonstrates polymorphism as we use the derived class object with the base class member pointer to call the Derived::sayHello function.

*/
