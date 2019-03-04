#include "LinkedBinaryTree.h"
#include "BinaryTreeIterator.h"

#include <iostream>
#include <stack>

template <typename T>
void binaryPreorder(BinaryTreeNode<T> * node);

template <typename T>
void binaryInorder(BinaryTreeNode<T>* node);

int main() {	

	LinkedBinaryTree<int, BinaryTreeIterator<int>> myTree(10);
	BinaryTreeIterator<int> iter = myTree.root();
	BinaryTreeIterator<int> parentOfIter = myTree.parent(iter);
	myTree.insertItem(5, iter, parentOfIter);
	myTree.insertItem(15, iter, parentOfIter);
	myTree.insertItem(25, iter, parentOfIter);
	myTree.insertItem(35, iter, parentOfIter);
    
	//Uncomment the below to test your solution to Lab Exercise 5.
	iter = myTree.root();
	
	iter.downRight();
	iter.downRight();
	iter.downRight();
	std::cout << "Depth of node: " << *iter << " is " << myTree.recursiveDepth(iter) << std::endl;
	std::cout << "Depth of node: " << *iter << " is " << myTree.nonRecursiveDepth(iter) << std::endl;
	// Reset the tree iterator to the root.
	iter = myTree.root();
	std::cout << "Tree minimum rooted at: " << *myTree.root() << " is " << *myTree.treeMinimum(iter) << std::endl;


	std::cout << "Binary Preorder" << std::endl;

	binaryPreorder(myTree.root().node());
	
	std::cout << "Binary Ineorder" << std::endl;

	binaryInorder(myTree.root().node());


	LinkedBinaryTree<int, BinaryTreeIterator<int>> myTree2(13);
	BinaryTreeIterator<int> iter2 = myTree2.root();
	BinaryTreeIterator<int> parentOfIter2 = myTree2.parent(iter2);
	myTree2.insertItem(10, iter2, parentOfIter2);
	myTree2.insertItem(1, iter2, parentOfIter2);
	myTree2.insertItem(12, iter2, parentOfIter2);
	myTree2.insertItem(11, iter2, parentOfIter2);

	myTree2.insertItem(15, iter2, parentOfIter2);
	myTree2.insertItem(13, iter2, parentOfIter2);
	myTree2.insertItem(17, iter2, parentOfIter2);
	myTree2.insertItem(21, iter2, parentOfIter2);
	myTree2.insertItem(18, iter2, parentOfIter2);

	std::cout << "Height: " << myTree2.height(iter2) << std::endl;
	binaryPreorder(myTree2.root().node());
	BinaryTreeIterator<int> deleteIter = myTree2.treeSearch(1, iter2);
	BinaryTreeIterator<int> deleteIter2 = myTree2.treeSearch(21, iter2);
	BinaryTreeIterator<int> deleteIter3 = myTree2.treeSearch(17, iter2);
	BinaryTreeIterator<int> deleteIter4 = myTree2.treeSearch(13, iter2);

	std::cout << "Original:" << std::endl;
	binaryPreorder(myTree2.root().node());
	myTree2.deleteItem(deleteIter);
	std::cout << "Post Delete:" << std::endl;
	binaryPreorder(myTree2.root().node());

	myTree2.deleteItem(deleteIter2);
	std::cout << "Post Delete2:" << std::endl;
	binaryPreorder(myTree2.root().node());

	myTree2.deleteItem(deleteIter3);
	std::cout << "Post Delete3:" << std::endl;
	binaryPreorder(myTree2.root().node());

	myTree2.deleteItem(deleteIter4);
	std::cout << "Post Delete4:" << std::endl;
	binaryPreorder(myTree2.root().node());

	system("PAUSE");
	
}

template <typename T>
void binaryPreorder(BinaryTreeNode<T> * node)
{
	std::cout << "Visiting: " << node->element() << std::endl;
	if (node->leftChild() != nullptr)
	{
		binaryPreorder(node->leftChild().node());
	}

	if (node->rightChild() != nullptr)
	{
		binaryPreorder(node->rightChild().node());
	}
}


template <typename T>
void binaryInorder(BinaryTreeNode<T>* node)
{
	std::stack<BinaryTreeNode<int>*> m_stack;

	while (m_stack.size() != 0 || node != nullptr)
	{
		while (node != nullptr)
		{
			m_stack.push(node);
			node = node->leftChild().node();
		}

		if (node == nullptr)
		{
			node = m_stack.top();
			m_stack.pop();
			std::cout << "Visiting " << node->element() << std::endl;
			node = node->rightChild().node();
		}
	}
}