#include <iostream>
#include "SLinkedList.h"

using namespace std;

int main() {
	// Part 1: Demonstrate the very basic prinicpals of a linked list.
	srand(time(NULL));
	// Create a list node (there is no list object).
	//std::unique_ptr<SListNode<int>> p1 = std::make_unique<SListNode<int>>(3);
	// Create a second list node, and link the first node to the second.
	//p1->setNext(std::make_unique<SListNode<int>>(4));
	// Loop through each node in the list.
	//for (SListNode<int> *pCurrent = p1.get(); pCurrent != nullptr; pCurrent = pCurrent->next().get())
	//{
	//	cout << (*pCurrent).element() << endl;
	//}
	// Q: What happens if the next line is uncommented?
	//p1 = std::move(p1->next());

	// Part 2: Create a linked list using a list object.

	
	SLinkedList<int, SListIterator<int>> list;
	list.insertLast(20);
	list.insertLast(10);
	list.insertLast(5);

	SListIterator<int> start = list.begin();

	//cout << "First element: " << *start << endl;

	//cout << list.size() << endl;
	//
	//system("PAUSE");

	SListIterator<int> position(list.tail());

	list.insertBefore(position,9);
	std::cout << list.size() << std::endl;
	
	list.reverse();

	SListIterator<int> newHead(list.tail());

	list.makeNewHead(newHead);

	std::list<int> list2;
	list2.push_front(30);
	list2.push_front(40);
	list2.push_front(50);

	SListIterator<int> insertLocation(list.head());
	list.splice(insertLocation, list2);

	std::list<int> list3;
	while (list3.size() < 20)
	{
		list3.push_front(rand() % 10 + 1);
	}

	std::list<int> dest;

	auto it = find(list3.rbegin(),list3.rend(),2).base();

	auto itE = find(it, list3.end(),4);

	dest.splice(dest.begin(),list3, it, itE);
	/*start++;

	auto result = list.remove(start);*/

	system("PAUSE");
}
