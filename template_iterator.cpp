#include <iostream>
#include <vector>
#include <forward_list>
#include <list>

using namespace std;

template<typename InputIterator, typename valueType>
InputIterator findfirstinstance(InputIterator iterBegin, InputIterator iterEnd, const 	valueType& findEle){
	while (iterBegin != iterEnd && *iterBegin != findEle) {
		++iterBegin;
	}

	return iterBegin;
}
/*
the algorithm loops over both input iterators copying the result for the comparison operator < into the output iterator. When one of the input iterators reaches the end the first loop finishes and execution proceeds to the second and third loops. These loops copy the remaining elements from the input that did not finish in the first loop, only one of these loops should execute as the other loop with have already reached it's end in the first loop. Since the input iterators are sorted then we only need copy the remaining elements to the results iterator.
*/
template<class InputIterator, class OutputIterator>
OutputIterator mergeSortedContainers(InputIterator lhsBegin, InputIterator lhsEnd, InputIterator rhsBegin, InputIterator rhsEnd, OutputIterator result){
	while(lhsBegin != lhsEnd && rhsBegin != rhsEnd){
		if(*lhsBegin <= *rhsBegin){
			*result = *lhsbegin;
			++lhsBegin;		
		}else{
			*result = *rhsBegin;
			++rhsBegin;
		}
		++result;
	}	
	while (lhsBegin != lhsEnd){
		*result = *lhsBegin;
		++lhsBegin;
		++result;
	}

	while(rhsBegin != rhsEnd){
		*result = *rhsBegin;
		++rhsBegin;
		++result;
	}
	return result;
}
/*
 find and replace function that uses a forward iterator to iterate over a container and find all elements that match the parameter argument oldEle and replace them with newEle. It is ideally suited to forward iterators as we only need to iterate over the container in a forward direction once to find and replace elements.
*/
template<class ForwardIterator, typename ElementType>
void findandreplace(ForwardIterator iterBegin, ForwardIterator iterEnd,const ElementType& oldEle, const ElementType& newEle) {
	while (iterBegin != iterEnd) {
		if (*iterBegin == oldEle) {
		*iterBegin = newEle;
		}
		++iterBegin;
	}
}  

/*
The reverseCopy algorithm returns a reversed copy of the input container, It does this by looping over the bi directional input iterator and writing out the elements in reverse to the output iterator.
*/

template<class BidirectionalIterator, class OutputIterator>
OutputIterator reverseCopy(BidirectionalIterator iterBegin,BidirectionalIterator iterEnd,OutputIterator result){

	//Copy elements from iterEnd to results container.
	while (iterBegin != iterEnd) {
		*result++ = *--iterEnd;
	}

	return result;
	}
/*
he randomise algorithm randomises the elements in a container.It works by iterating over the container using the random access iterator parameter arguments and then calls the rand function to get a random number, then it applies the modulo operator to this and adds it to the input iterator beginning to get the random offset of an element.
*/
template<class RandomAccessIterator>
void randomise(RandomAccessIterator iterBegin, RandomAccessIterator iterEnd) {
	while (iterBegin < iterEnd) {
		iter_swap(iterBegin, iterBegin + rand() % (iterEnd - iterBegin)); //randomInteger(iterEnd - iterBegin));
		++iterBegin;
	}
}

/*
The randomise algorithm randomises the elements in a container.It works by iterating over the container using the random access iterator parameter arguments and then calls the rand function to get a random number, then it applies the modulo operator to this and adds it to the input iterator beginning to get the random offset of an element.

and the code we use to call these algorithms is below.*/

int main(int argc,char* argv[]) {

	//Containers used as to apply algorithms to.
	std::forward_list<int> firstList = { 34, 77, 16, 2 };
	std::forward_list<int> secondList = { 35, 76, 18, 2 };

	std::list<int> List = { 34, 77, 16, 2, 35, 76, 18, 2 };

	std::vector<int> resultsList(8);

	//Sort containers.
	firstList.sort();
	secondList.sort();

	//Find first instance example.
	cout << "findfirstinstance of 16 in firstList and 76 in secondlist is " << *findfirstinstance(firstList.begin(),firstList.end(),16) << " " << *findfirstinstance(secondList.begin(), secondList.end(), 76) << "\n";
	cout << "\n";

	//mergeSortedContainers example.
	cout << "Results of calling mergeSortedContainers with firstList and secondList are." << "\n";
	mergeSortedContainers(firstList.begin(),firstList.end(),secondList.begin(),secondList.end(),resultsList.begin());

	for (std::vector<int>::iterator it = resultsList.begin(); it != resultsList.end(); it++) {
	cout << *it << " ";
	}
	cout << "\n\n";

	//findandreplace example.
	cout << "Results of calling findandreplace on firstList with values 16 and 23" << "\n";
	findandreplace(firstList.begin(),firstList.end(),16,23);
	for (std::forward_list<int>::iterator it = firstList.begin(); it != firstList.end(); it++) {
	cout << *it << " ";
	}
	cout << "\n\n";

	cout << "Results of calling findandreplace on secondList with values 76 and 1006" << "\n";
	findandreplace(secondList.begin(), secondList.end(), 76, 1006);
	for (std::forward_list<int>::iterator it = secondList.begin(); it != secondList.end(); it++) {
		cout << *it << " ";
	}
	cout << "\n\n";


	//reverseCopy example.
	cout << "Results of calling reverseCopy on firstList is " << "\n";
	resultsList.empty();
	resultsList.resize(List.size());
	reverseCopy(List.begin(),List.end(),resultsList.begin());
	for (std::vector<int>::iterator it = resultsList.begin(); it != resultsList.end(); it++) {
		cout << *it << " ";
	}
	cout << "\n\n";

	//randomise example.
	cout << "Calling randomise on sorted vector " << "\n";
	List.sort();
	std::vector<int> temp(List.begin(), List.end());
	for (std::vector<int>::iterator it = temp.begin(); it != temp.end(); it++) {
		cout << *it << " ";
	}
	cout << "\n\n";

	cout << "Results after calling randomise on sorted vector are " << "\n";
	randomise(temp.begin(),temp.end());
	for (std::vector<int>::iterator it = temp.begin(); it != temp.end(); it++) {
		cout << *it << " ";
	}
	cout << "\n\n";

}

