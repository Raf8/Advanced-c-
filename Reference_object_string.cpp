/*The current most popular way of implementing strings is the use of small string optimisation technique. This is done by representing small strings as buffers that are stored entirely within the string object and not allocated on the heap. We will look at an example.*/

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

class SSOString : public refCounter {

public:

	SSOString() : strBeg(NULL) {}

	SSOString(const char* strptr) : strSize(strlen(strptr)) {
		if (strSize < 16) {
			//< 16 chars store in array.
			memcpy(&str[0], strptr, strSize + 1);
			strBeg = NULL;
		}
		else {
			//> 16 chars alloctae on heap.
			strBeg = new char[strSize + 1];
			memcpy(strBeg, strptr, strSize + 1);
		}
	}

	char* begin() {
		return strSize < 16 ? &str[0] : strBeg; 
	}

	char* end() {
		return begin() + strSize;
	}

	unsigned length() const { 
		return strSize;
	}


	~SSOString() {
		if (strBeg) {
			delete[] strBeg;
		}
	}

private:
	unsigned strSize;
	char* strBeg;
	char str[16];
};

int main(int argc, char* argv[]) {

	//Create referenced object.
	ReferencedObject< SSOString > ref(new SSOString("Hello World!!")); //13 chars

	ReferencedObject< SSOString > ref16(new SSOString("This string is over 16 characters long so allocated on Heap")); //13 chars

	//Invocation access
	cout << "ref value is " << ref->begin() << " with size " << ref->length() << "\n\n";

	cout << "ref16 value is " << ref16->begin() << " with size " << ref16->length() << "\n\n";

	ReferencedObject< SSOString > refCopy(new SSOString());  // = ref;  // (new SSOString("Hello World!!")); //13 chars
	refCopy = ref;

	ReferencedObject< SSOString > ref16Copy(new SSOString());  // = ref16;
	ref16Copy = ref16;

	cout << "refCopy value is " << refCopy->begin() << "\n\n";

	cout << "ref16Copy value is " << ref16Copy->begin() << "\n\n";

	return 0;

}  
