/*
Association is a relationship structure that shows objects of one class are connected to another class, for example a student class could have an association to a library card class. This means that every library card object would be owned by one student object. The delegation pattern allows composition to achieve similar code reuse capabilities as inheritance, an object will delegate a request to another object or handler and in doing so is reusing the handlers code, this is similar to a derived class referring to it's base class in inheritance except in delegation there is no polymorphic relationship between the classes.
*/

#include <iostream>

using std::cout;

class LibraryCard{
public:
		LibraryCard() : cardNbr(rand()){}
		
		int getCard(){
			return cardNbr;
		}
private:
		int cardNbr;
};

class Student{
public:
	Student() : lc(NULL){}
	~Student() {}
	void setLibraryCard(LibraryCard* llc){
		lc = llc;
	}
	//Association Student class does not control lifecycle of LibraryCard but accesses functions.
	//Delagation Student delagates request to LibraryCard. 
	int libraryCardNumber() {
		if (lc) {
			return lc->getCard();
		}
		else {
			return NULL;
		}
	}
private:
	LibraryCard* lc;
};


int main(int argc,char* argv[]) {

	LibraryCard myCard;
	Student me;
	me.setLibraryCard(&myCard);

	cout << "My library card number is " << me.libraryCardNumber() << "\n";

	return 0;
}
