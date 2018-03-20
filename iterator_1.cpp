#include<iostream>
#include<vector>
#include<string>
#include<istream>
#include<iterator>
#include<list>
#include<forward_list>

int main(){

std::istreambuf_iterator<char> isbuf(std::cin.rdbuf());
// This is created to read the characters a user types into the terminal that's what the cin.rdbuf() function call does


//And we use a for loop to traverse the iterator like so, we will also need to detect end of stream.

std::istreambuf_iterator<char> isbeos; 
std::string mystring;
while (isbuf != isbeos && *isbuf != '\n') {
	mystring += *isbuf++;
}
std::cout << "\n" << "The text you entered is " << mystring.c_str() << '\n";

int val1, val2;
std::cout << "Please enter two integers";

std::istream_iterator<int> iseos;
std::istream_iterator<int> is(std::cin);

if(is != iseos && *is != '\n'){
	val1 = *is;
}

++is;
if(is != iseos && *is != '\n'){
	val2 = *is;
}

std::cout << "\n" << "You entered values:" << val1 << " and " << val2 << "\n\n";
//forward iterator - singly linked list that only provides traversal in the forward direction and no random access.

forward_list<int> fwdlist;
forward_list<int>::iterator fwdlistiter;
fwdlist.push_front(3);
fwdlist.push_front(2);
fwdlist.push_front(1);

cout << "Forward iterator traversal of forward_list." << endl;
for (fwdlistiter = fwdlist.begin(); fwdlistiter != fwdlist.end(); fwdlistiter++) {
	cout << (*fwdlistiter) << endl;
}

//list is implemented as a double linked list which means we can go forward and back but they don't support random access hence it uses a bi directional iterator. 
list<int> li;
list<int>::iterator listiter;
list<int>::reverse_iterator revlistiter;
li.push_back(1);
li.push_back(2);
li.push_back(3);

//Forward traversal
cout << "Forward traversal of list." << endl;
for (listiter = li.begin(); listiter != li.end(); listiter++) {
	cout << (*listiter) << endl;
}

//Reverse traversal.
cout << "Reverse traversal of list." << endl;
for (revlistiter = li.rbegin(); revlistiter != li.rend(); revlistiter++) {
	cout << (*revlistiter) << endl;
}

//random access

vector<int> v;
vector<int>::iterator iter;

v.push_back(1);
v.push_back(2);
v.push_back(3);

iter = v.begin();
iter +=2;
cout << *iter << endl;

//You might have noticed iterators have similar behaviour to pointers and we can use a for loop to iterate an array with a pointer like so.

cout << "Traverse int array with pointer " << endl;
int intarray[3];
intarray[0] = 1;
intarray[1] = 2;
intarray[2] = 3;
int* endintarray = intarray + 3;
for (int* ptr = intarray; ptr < endintarray; ptr += 1)
{
	cout << *ptr << endl;
}
}

