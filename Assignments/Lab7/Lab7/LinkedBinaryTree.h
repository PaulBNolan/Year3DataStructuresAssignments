#ifndef LINKEDBINARYTREE_H
#define LINKEDBINARYTREE_H
#include <algorithm>
// Forward references.
template <typename T, typename Iterator>class BinaryTree;
template <typename T>class BinaryTreeNode;
template <typename T>class Container;

template <typename T, typename Iterator>
class LinkedBinaryTree : public BinaryTree<T, Iterator> {      
public:       
    // LinkedBinaryTree specific member functions
    // Constructor          
    LinkedBinaryTree(T element);
    // Copy constructor
    LinkedBinaryTree(LinkedBinaryTree<T, Iterator> const & other) {
       copy(other);
    }
    // Destructor
    ~LinkedBinaryTree() {
       destroy();
    }
        
    // Generic container functions
    virtual int size() const;
    virtual bool isEmpty() const;          
    
    // Generic SimpleTree functions
    virtual Iterator root() const;
    virtual Iterator parent(Iterator & position) const;  
    virtual bool isInternal(Iterator & position) const;
    virtual bool isExternal(Iterator & position) const;
    virtual bool isRoot(Iterator & position) const;   
    virtual void swap(Iterator & first, Iterator & second);
    virtual void replace(Iterator & position, T element);
    
    // BinaryTree functions
    virtual Iterator & leftChild(Iterator & position) const;
    virtual Iterator & rightChild(Iterator & position) const;
   
    virtual int recursiveDepth(Iterator  position);
	virtual int nonRecursiveDepth(Iterator position);

	virtual Iterator treeMinimum(Iterator & n) const;

	virtual int height(Iterator n);

	void deleteItem(Iterator const & position);

	// Functions to return tree iterators
	Iterator & begin();
	Iterator & end();

    // Binary search tree function - inserts a new key
	Iterator insertItem(T key, Iterator iter, Iterator iterParent);
	// Binary search tree function - searches for a key
	Iterator treeSearch(T key, Iterator iter);
	
   
private:
    BinaryTreeNode<T>* m_root;     // Pointer to the root node
    int m_count;                    // Number of nodes in the tree
        
    void copy(LinkedBinaryTree<T, Iterator> const & other);
    void destroy();
};

template <typename T, typename Iterator>
LinkedBinaryTree<T, Iterator>::LinkedBinaryTree(T element) : m_count(1) {
    m_root = new BinaryTreeNode<T>(element, this, 0);    
}

template <typename T, typename Iterator>
void LinkedBinaryTree<T, Iterator>::copy(LinkedBinaryTree<T, Iterator> const & other) {
    m_root = new BinaryTreeNode<T>(*(other.m_root));        
    m_count = other.m_count;
}

template <typename T, typename Iterator>
void LinkedBinaryTree<T, Iterator>::destroy() {
   delete m_root;
}


template <typename T, typename Iterator>
int LinkedBinaryTree<T, Iterator>::size() const {
    return m_count;
}

template <typename T, typename Iterator>
bool LinkedBinaryTree<T, Iterator>::isEmpty() const {
    return (m_count == 0);
}

template <typename T, typename Iterator>
void LinkedBinaryTree<T, Iterator>::swap(Iterator & first, Iterator & second) {
   T temp = (*first);
   (*first) = (*second);
   (*second) = temp;   
}

template <typename T, typename Iterator>
void LinkedBinaryTree<T, Iterator>::replace(Iterator & position, T element) {
    (*position) = element;	
}

template <typename T, typename Iterator>
Iterator LinkedBinaryTree<T, Iterator>::root() const {
    return Iterator(m_root);
}

template <typename T, typename Iterator>
Iterator LinkedBinaryTree<T, Iterator>::parent(Iterator & position) const {     
	return position.node()->parent();
}

template <typename T, typename Iterator>
bool LinkedBinaryTree<T, Iterator>::isInternal(Iterator & position) const {	
	return ( position.node()->leftChild() != 0 || position.node()->rightChild() != 0);    
}

template <typename T, typename Iterator>
bool LinkedBinaryTree<T, Iterator>::isExternal(Iterator & position) const {
	return ( position.node()->leftChild() == 0 && position.node()->rightChild() == 0);    
}

template <typename T, typename Iterator>
bool LinkedBinaryTree<T, Iterator>::isRoot(Iterator & position) const {	
    return ( position == m_root );
}

template <typename T, typename Iterator>
Iterator & LinkedBinaryTree<T, Iterator>::leftChild(Iterator & position) const {    	
	Iterator & iter = position;
	if ( position.node() != 0 ) {
		iter = position.node()->leftChild();
	}
	return iter;
}

template <typename T, typename Iterator>
Iterator & LinkedBinaryTree<T, Iterator>::rightChild(Iterator & position) const {    
    Iterator & iter = position;
	if ( position.node() != 0 ) {
		iter = position.node()->rightChild();
	}
	return iter;
}

template<typename T, typename Iterator>
int LinkedBinaryTree<T,Iterator>::recursiveDepth(Iterator position)
{
    //If position is the root
    //Return 0
    if(isRoot(position))
    {
        return 0;
    }

    //Else
    //Return 1+depth(parent(position))
    else
    {
		return 1 + recursiveDepth(parent(position));
    }
}

template<typename T, typename Iterator>
int LinkedBinaryTree<T, Iterator>::nonRecursiveDepth(Iterator position)
{
	int depth = 0;

	while (isRoot(position) == false)
	{
		depth++;
		position = parent(position);
	}

	return depth;
}

template<typename T, typename Iterator>
Iterator LinkedBinaryTree<T,Iterator>::treeMinimum(Iterator & n) const
{
	if (n.downLeft())
	{
		n = treeMinimum(n);
	}
	// while (n.downLeft());
	// while (n.node()->leftChild() != null)
	// {   n = leftChild(n); }
	return n;
}

template<typename T, typename Iterator>
int LinkedBinaryTree<T, Iterator>::height(Iterator n)
{
	//std::cout << "Node: " << n.node()->element() << std::endl;
	if (isInternal(n) == true)
	{
		//std::cout << "1";
		int x = 0;
		int y = 0;
		if (n.node()->leftChild() != nullptr)
		{
			n = leftChild(n);
			x = height(n);
			n = parent(n);
		}
		if (n.node()->rightChild() != nullptr)
		{
			n = rightChild(n);
			y = height(n);
			n = parent(n);
		}
		std::cout << "Node: " << n.node()->element() << " X: " << x << " Y: " << y << std::endl;
		return std::max(x, y) + 1;
	}
	else
	{
		//std::cout << n.node()->element() << std::endl;
	}
	return 0;
}

template <typename T, typename Iterator>
Iterator LinkedBinaryTree<T, Iterator>::treeSearch(T key, Iterator iter) {
	/*if n is an external node and key(n) <> k then
  return NULL KEY
if k == key(n) then
  return n
else if k < key(n) then
  return treeSearch(k, T.leftChild(n))
else
  { we know that k > key(n) }
  return treeSearch(k, T.rightChild(n))*/
	
	if ( iter.node() == 0 || isExternal(iter) && (*iter) != key ) {
		return Iterator(0);
	}
	if ( key == (*iter) ) {
		return iter;
	}	
	else if ( key < (*iter) ) {
		return treeSearch( key, leftChild(iter) );
	}
	else {
		return treeSearch( key, rightChild(iter) );
	}
}


template <typename T, typename Iterator>
Iterator LinkedBinaryTree<T, Iterator>::insertItem(T key, Iterator iter, 
													          Iterator iterParent) {
    BinaryTreeNode<T> * node = iter.node();
	if ( node == 0) {       
       node = new BinaryTreeNode<T>(key, this);
       node->setLeftChild(0);
       node->setRightChild(0);
       node->setParent(iterParent.node());
	   m_count++;
    }
    else if (key < node->element()) {
       Iterator tempIter = insertItem(key, node->leftChild(), iter );
       node->setLeftChild( tempIter.node() );       
    }
    else if (key >= node->element()) {
	   Iterator tempIter = insertItem(key, node->rightChild(), iter );
       node->setRightChild( tempIter.node() );              
    }
    
    return Iterator(node);    
}
template <typename T, typename Iterator>
void LinkedBinaryTree<T, Iterator>::deleteItem(Iterator const & position)
{
	//auto parent = position.node()->parent().node();
	auto iter = position;
	auto parent = iter.node()->parent();
	if (iter.node()->leftChild() == nullptr && iter.node()->rightChild() == nullptr)
	{
		if (parent.node()->element() < iter.node()->element())
		{
			parent.node()->setRightChild(nullptr);
		}
		else if (parent.node()->element() > iter.node()->element())
		{
			parent.node()->setLeftChild(nullptr);
		}
		delete  iter.node();
	}

	else if (iter.node()->leftChild() == nullptr && iter.node()->rightChild() != nullptr)
	{
		if (parent.node()->element() < iter.node()->element())
		{
			parent.node()->setRightChild(iter.node()->rightChild().node());
		}
		else if (parent.node()->element() > iter.node()->element())
		{
			parent.node()->setLeftChild(iter.node()->rightChild().node());
		}
		delete  iter.node();
	}
	else if (iter.node()->leftChild() != nullptr && iter.node()->rightChild() == nullptr)
	{
		if (parent.node()->element() < iter.node()->element())
		{
			parent.node()->setRightChild(iter.node()->leftChild().node());
		}
		else if (parent.node()->element() > iter.node()->element())
		{
			parent.node()->setLeftChild(iter.node()->leftChild().node());
		}
		delete  iter.node();
	}
	else if (iter.node()->leftChild() != nullptr && iter.node()->rightChild() != nullptr)
	{
		auto largestIter = iter.node()->leftChild();
		while (largestIter.node()->rightChild() != nullptr)
		{
			std::cout << "L" << largestIter.node()->rightChild().node()->element() << std::endl;
			rightChild(largestIter);
		}
		auto smallestIter = iter.node()->rightChild();
		while (smallestIter.node()->leftChild() != nullptr)
		{
			std::cout << "S" << smallestIter.node()->leftChild().node()->element() << std::endl;
			leftChild(smallestIter);
		}

		if (iter.node()->element() - smallestIter.node()->element() > largestIter.node()->element() - iter.node()->element())
		{
			std::cout << "Largest" << std::endl;
			iter.node()->setElement(largestIter.node()->element());
			largestIter.node()->parent().node()->setRightChild(nullptr);
			delete largestIter.node();
		}
		else if (iter.node()->element() - smallestIter.node()->element() < largestIter.node()->element() - iter.node()->element())
		{
			std::cout << "Smallest" << std::endl;
			iter.node()->setElement(smallestIter.node()->element());
			smallestIter.node()->parent().node()->setLeftChild(nullptr);
			delete smallestIter.node();
		}
	}
}

template <typename T, typename Iterator>
Iterator & LinkedBinaryTree<T, Iterator>::begin() {
	return Iterator(m_root);	
}

template <typename T, typename Iterator>
Iterator & LinkedBinaryTree<T, Iterator>::end() {
	return m_root->parent();	
}




#include "BinaryTree.h"
#include "BinaryTreeNode.h"

#endif
