class Cat {
public:
	void makeCatMeow() {
		cout << catnoise.c_str() << endl;
	}
private:
	string catnoise = "meow meow";
};  

class AnimalInterface {
public:
	//Destructor
	virtual ~AnimalInterface() {}
	//Pure virtual execute function has to be implemented by derived classes.
	virtual void execute() = 0;
};

template <class T>
class AnimalAdapter : public AnimalInterface {
public:
	//Constructor
	AnimalAdapter(T *o, void(T:: *m)()) {
		animalObject = o;
		animalfunction = m;
	}
	//Deconstructor.
	~AnimalAdapter() {
		delete animalObject;
	}
	//Implement AnimalInterface pure virtual function.
	void execute() {
		(animalObject->*animalfunction)();
	}
private:
	//Members to hold object and function pointers
	T *animalObject;
	void(T:: *animalfunction)();
};  

int main(){
	AnimalAdapter<Cat> cata(new Cat(), &Cat::makeCatMeow);
	cat.execute();
	return 0;
}
