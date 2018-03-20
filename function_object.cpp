#include <iostream>
#include <vector>
#include <algorithm>

/*
A function object is an object that behaves like a function meaning it is callable but we use an object as the object can also store data. The object usually defines the operator operator() which is known as the call operator this is what gets executed when our function object is invoked as a function. 
*/

struct sortedStruct
{
	int val;

	sortedStruct(int k) : val(k) {}

	bool operator < (const sortedStruct& rhs) const
	{
		return (val < rhs.val);
	}
};

class sortedClass
{
public:
	sortedClass(int x) :val(x) {}
	~sortedClass() {};
	int getVal() const { return val; }
	bool operator < (const sortedClass& sc) const { 
		return val < sc.getVal(); 
	}
private:
	int val;
};

class lessThan {
public:
	lessThan() {};
	~lessThan() {};
	bool operator()(const sortedClass& lhs, const sortedClass& rhs) const { 
		return lhs < rhs; 
	};
	bool operator()(const sortedStruct& lhs, const sortedStruct& rhs) const {
		return lhs < rhs;
	};
};


class greaterThan {
public:
	greaterThan(int cmp): X(cmp) {};
	~greaterThan() {};
	bool operator()(const sortedClass& z) const { return z.getVal() > X; } //> comparison
	bool operator()(const sortedStruct& z) const { return z.val > X; } //> comparison
private:
	int X;
};

int main(int argc, char* argv[]) {

	vector<sortedClass> vecSortClas;
	vector<sortedStruct> vecSortStru;
	for (int i = 0; i < 50; i++) {
		sortedClass sc(i);
		sortedStruct ss(i);
		vecSortClas.push_back(sc);
		vecSortStru.push_back(ss);
	}

	randomise(vecSortClas.begin(),vecSortClas.end());

	randomise(vecSortStru.begin(), vecSortStru.end());

	//Sorted Class

	cout << "Vector of sortedClass classes before sorting is " << "\n\n";

	for (vector<sortedClass>::iterator it = vecSortClas.begin(); it != vecSortClas.end(); it++) {
		cout << "sortedClass index " << distance(vecSortClas.begin(),it) << " has value " << it->getVal() << "\n";
	}

	std::sort(vecSortClas.begin(),vecSortClas.end(),lessThan());

	cout << "\n\n" << "Vector of sortedClass classes after sorting is " << "\n\n";

	for (vector<sortedClass>::iterator it = vecSortClas.begin(); it != vecSortClas.end(); it++) {
		cout << "sortedClass index " << distance(vecSortClas.begin(), it) << " has value " << it->getVal() << "\n";
	}

	cout << "\n\n";

	//SortedStruct
	cout << "Vector of sortedStruct Structs before sorting is " << "\n\n";

	for (vector<sortedStruct>::iterator it = vecSortStru.begin(); it != vecSortStru.end(); it++) {
		cout << "sortedClass index " << distance(vecSortStru.begin(), it) << " has value " << it->val << "\n";
	}

	std::sort(vecSortStru.begin(), vecSortStru.end(), lessThan());

	cout << "\n\n" << "Vector of sortedStruct structs after sorting is " << "\n\n";

	for (vector<sortedStruct>::iterator it = vecSortStru.begin(); it != vecSortStru.end(); it++) {
		cout << "sortedClass index " << distance(vecSortStru.begin(), it) << " has value " << it->val << "\n";
	}

	cout << "\n\n" << "Vector of sortedStruct structs which are greater than 45 " << "\n\n";

	for (vector<sortedStruct>::iterator it = vecSortStru.begin(); it != vecSortStru.end(); it++) {
		vector<sortedStruct>::iterator it2 = it;
		auto ittemp = find_if(it2, it2+1, greaterThan(45));
		if (ittemp != it2+1) {
			cout << "sortedClass index " << distance(vecSortStru.begin(), it) << " is greater than 45 " << ittemp->val << "\n";
		}
	}

	//Destroy elements.
	vecSortClas.empty();
	vecSortStru.empty();

	return 0;
} 

//overload []
/*
We would usually only overload the subscript operator in classes that are going to hold a sequence of elements and although as we discussed above you could provide access functions to the elements it is a better solution to overload the subscript operator. A secondary reason may be you want to handle the array out of bounds behaviour like I did above by returning the last elements in the array instead of the program execution ending uncontrolled.
*/

template<typename arrayType,int size>
class genericArray {
private:
	arrayType m_array[size];

public:
	arrayType& operator[] (const int index) { //Writing
		if (index > size) {
			cout << "Index out of bounds" << endl;
			// return last element.
			return m_array[size-1];
		}
		return m_array[index];
	}

	arrayType operator[] (int index) const { //Reading
		if (index > size) {
			cout << "Index out of bounds" << endl;
			// return last element.
			return m_array[size-1];
		}
		return m_array[index];
	}

};

int main(int argc, char* argv[]) {

	genericArray<int, 5> myIntArray;
	genericArray<double, 5> myDoubleArray;
	genericArray<float, 5> myFloatArray;

	for (int i = 0; i < 5; i++) {
		myIntArray[i] = i*2;
		myDoubleArray[i] = (double)(i * 2.0);
		myFloatArray[i] = (float)(i * 2.0);
	}

	for (int i = 0; i < 5; i++) {
		cout << "myIntArray[" << i << "] is " << myIntArray[i] << "\n";
	}

	cout << "\n\n";

	for (int i = 0; i < 5; i++) {
		printf("myFloatArray[%i] is %lf \n", i, myFloatArray[i]);
	}

	cout << "\n\n";

	for (int i = 0; i < 5; i++) {
		printf("myFloatArray[%i] is %f \n", i, myFloatArray[i]);
	}

	cout << "\n\n";

	cout << myIntArray[99] << "\n\n";

	return 0;
}
