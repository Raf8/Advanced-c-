/*We have already seen the concept of lazy loading with the singleton design pattern, in the singleton pattern we developed the single object will not be created until someone requests an instance of it. This was done by using a pointer and only allocating the object when a function on the object was invoked. We could do a similar behaviour by only creating the object when the pointer operators are invoked if the object has not already been created. This way we could put a bunch of pointers objects in a container and only those which we use the indirection operator on would be created. Let's look at an example.
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class someObject {
public:
	someObject() : var1(rand()), var2("Hello World.") {}

	void printAttr() {
		cout << "var1 is " << var1 << " var2 is " << var2 << "\n";
	}

	void setString(string ss) {
		var2 = ss;
	}

	~someObject() {
		cout << "someObject de constructor called " << var1 << ". \n";
	}

private:
	int var1;
	string var2;
};

template<class classType>
class LazyObject {
public:

	LazyObject() : objPtr(NULL) {}

	~LazyObject() {
		if (objPtr) {
			delete objPtr;
		}
	}

	classType& operator* () {
		return *(getInstance());
	}

	classType* operator-> () {
		return getInstance();
	}

private:
	classType* objPtr;
	classType* getInstance(void) {
		if (!objPtr) {
			objPtr = new classType();
		}
		return objPtr;
	}

};

int main(int argc, char* argv[]) {

	vector<LazyObject<someObject>> lazyVec;

	for (int i = 0; i < 10; i++) {
		lazyVec.push_back(LazyObject<someObject>());
	}

	for (int t = 0; t < 10; t++) {
		if (t % 2 == 0) {
			//Access lazyVec element causes someObject to be created.
			lazyVec[t]->printAttr();
		}
	}

	return 0;
}

/*
Here we have the someObject class for the last example and a new template class LazyObject which will have a private pointer member of the template type parameter. This pointer will be initialised to null when the LazyObject is created and will only be instantiated when the class indirection or dereference operator is invoked. This will invoke the private member function getInstance which creates a new instance of the template class type is the pointer is null. So this operates very similar to the smart pointer class in the previous example. The LazyObject de constructor will delete the object pointed to by the pointer if the pointer is not null, this will invoke the de constructor of the object pointed to by the pointer in this case it's the someObject class. The main function declares a vector container to hold the LazyObjects, it then uses a for loop to allocate 10 LazyObject instances in the vector. Another for loop invokes the printAttr function on the someObject which causes the object to be created/loaded this is when the lazy loading takes place. The loop will only do this for even integer values of the for loop counter and since there is 10 elements it should only call the someObject constructor 5 times. When the vector is destroyed by the program finishing the de constructors will be invoked on those objects which were created so this will only happen 5 times. We can check this is happening by printing to standard output from the someObject de constructor, the output look like this
*/

