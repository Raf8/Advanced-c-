/*
When we want to share one object between many other objects we need to keep a count of how many objects are using that instance otherwise when it is destroyed all the other objects referencing it will break when they try to use it. This concept is called reference counting, the question is where do you store the counter. If we store it on the references this will increase the memory footprint of each reference, we could also put another object in between the reference and the object to hold the count and a single pointer to the object. This would have a smaller memory footprint than storing the count on each reference but it means a pointer must be de references twice to reach the object which would be slower. The best solution is to store the counter on the object and increment it each time a new reference is made to the object. The polymorphic way to do this is to create a class for reference counting which has functions to increment and decrement the counter and use this as a base class for classes that need reference counting.
*/

//Reference counter base class.
class refCounter {

private:
	//The counter.
	int count;

public:

	//Constructor initialis count to 1.
	refCounter() : count(1){}

	//Increment count variable
	void increaseCount() {
		count++;
		cout << "increaseCount called count is " << count << "\n";
	}

	//Decrement count variable.
	int decreaseCount() {
		return --count;
		cout << "decreaseCount called count is " << count << "\n";
	}
};

/*
we could inherit this class directly in the class we want to reference count and then call the increaseCount and decreaseCount functions in the copy constructor and copy assignment operators or we could make a template class to do this for us and then when ever we want to reference count an object we just wrap it in the template class.
*/

/*
The template class takes one template argument which is the type of the object we want to reference count. The private members are a pointer to the object being reference counted and a destructor which deletes the pointer if the reference counter is zero. The public functions consist of a dummy class to be thrown as an exception if for some reason the internal pointer becomes null. Next we have the constructor which initialises the private reference pointer then next we have the invocation operator which returns the private pointer. The assignment operator is also defined, this does the standard self reference check and then increments the reference counter on the argument object. The destructor is then called on the current object which decrements the reference count to this object and then deletes the object if the count is zero. next it assigns the private pointer to the argument and returns. The final function is the destructor which call the private destructor since the delete operator call can throw and exception and destructor's are not allowed to throw exceptions.


*/

template< class referencedObject >
class ReferencedObject {

private:
	//The object being referenced.
	referencedObject *refObject;

	//Private destructor throws exception.
	void destructor() throw () {
		if (refObject != NULL && refObject->decreaseCount() == 0) {
			cout << "referenced object pointer being deleted. \n";
			delete refObject;
			refObject = NULL;
		}
	}

public:
	//Empty dummy class to throw
	class classToThrow {};

	//Constructor
	ReferencedObject(referencedObject *newObj = NULL) : refObject(newObj) {}

	//Invocation operator
	referencedObject *operator-> () throw (classToThrow) {
		if (!refObject) {
			throw classToThrow();
		}
		return refObject;
	}

	ReferencedObject< referencedObject > &operator= (ReferencedObject< referencedObject > &rhs) {

		//Check if same object if so return.
		if (this == &rhs) {
			return *this;
		}

		//Increment reference count.
		if (rhs.refObject) {
			rhs.refObject->increaseCount();
		}

		//Destroy current refObject which decrease reference count.
		destructor();

		//Assign new refObject to private member refObject.
		refObject = rhs.refObject;

		//Return object.
		return *this;
	}	

	//Destructor calls private destructor which can throw exception from delete.
	~ReferencedObject< referencedObject >() {
		cout << "ReferencedObject destructor called \n";
		destructor();
	}
};

/*
 create a class that inherits the base class refCounter and test the reference counting by creating an instance of it and assigning it to another instance.
*/
class SharedObject : public refCounter {

public:
	SharedObject() {
		std::cout << "SharedObject created" << std::endl;
	}

	void SharedObjectAccess(const char *src) {
		cout << "SharedObjectAccess called parameter argument is " << src << "\n";
	}

	~SharedObject() {
		std::cout << "SharedObject destroyed" << std::endl;
	}
};

/*

*/
int main(int argc, char* argv[]) {

	//Create referenced object.
	ReferencedObject< SharedObject > ref(new SharedObject());

	//Invocation access
	ref->SharedObjectAccess("Hello World !!!");

	cout << "copying ref will increase counter \n";

	ReferencedObject< SharedObject > ref2(new SharedObject());
	ref2 = ref;

	//Invocation access
	ref2->SharedObjectAccess("Hello from ref2");

	cout << "\n\n";
	//Indirection access
	cout << "ref val called via indirection operator is " << (*ref).getVal() << "\n\n";

	return 0;
}	
