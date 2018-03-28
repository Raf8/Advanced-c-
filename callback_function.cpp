/*A call back function is used to notify the program execution that an event has taken place, this is commonly use in GUI development. When a user clicks on a button a call back function will be invoked to handle the users request. They can be used for other purposes though, suppose for example we wanted to write some code to fill an array and we wanted to be able to reuse that code to fill lots of arrays with data types from different functions. Consider the following example*/

#include <iostream>
using namespace std;

template<typename arrayType,typename func>
void fillArray(arrayType *array, size_t arraySize,func f) {
	for (int i = 0; i < arraySize; i++) {
		array[i] = f();
	}
}

template<typename arrayType>
void printArray(arrayType *array, size_t arraySize) {
	cout << "Array contains the following elements. \n";
	for (int i = 0; i < arraySize; i++) {
		cout << array[i] << "\n";
	}
	cout << "\n\n";
}

void nonTemplateFillArray(int *array, size_t arraySize,int(*getElement)(void)) {
	for (int i = 0; i < arraySize; i++) {
		array[i] = getElement();
	}

}


int fillWithInts() {
	return rand();
}


char fillWithChars() {
	return char('A' + rand() % 24);
}

int main(int argc, char* argv[]) {

	int intArray[10];
	fillArray(intArray, 10, fillWithInts);

	printArray(intArray,10);

	int intArrayNoTemplate[10];
	nonTemplateFillArray(intArrayNoTemplate, 10, fillWithInts);
	cout << "Using non templated array fill call back function. \n";
	printArray(intArrayNoTemplate, 10);

	char charArray[10];
	fillArray(charArray, 10, fillWithChars);

	printArray(charArray, 10);

	return 0;
}

