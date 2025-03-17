//   Adapated from Frank M. Carrano and Timothy M. Henry.

/** ADT Stack implementation.
	@file Stack.cpp */

#include <iostream>
#include <cstddef>
#include "Stack.hpp"
#include "Node.hpp"

template <class ItemType>
Stack<ItemType>::Stack()
{
	currentSize = 0;
	headPtr = nullptr;
} // end default constructor

template <class ItemType>
Stack<ItemType>::~Stack()
{
	// no destructor needs to be called, due to smart pointers automatically deallocating
} // end destructor

template <class ItemType>
bool Stack<ItemType>::isEmpty() const
{
	return currentSize == 0;
} // end isEmpty

template <class ItemType>
int Stack<ItemType>::size() const
{
	return currentSize;
} // end size

template <class ItemType>
bool Stack<ItemType>::push(const ItemType &newItem)
{
	std::shared_ptr<Node<ItemType>> nextNodePtr = std::make_shared<Node<ItemType>>(newItem, headPtr); // alternate code
	headPtr = nextNodePtr;																			  // New node is now first node
	currentSize++;
	return true;
} // end push

template <class ItemType>
ItemType Stack<ItemType>::peek() const
{
	if (currentSize <= 0 || headPtr == nullptr)
	{
		throw std::logic_error("Empty Stack");
	}
	return headPtr->getItem();
} // end peek

template <class ItemType>
bool Stack<ItemType>::pop()
{
	if (currentSize <= 0 || headPtr == nullptr)
	{
		return false;
	}
	// move to the next, the old is automatically deleted because of smart pointer
	headPtr = std::move(headPtr->getNext());
	currentSize--;
	return true;
} // end pop

template <class ItemType>
void Stack<ItemType>::clear()
{
	// continue to pop, until headPtr is null
	while (headPtr)
	{
		// moves headPtr until it is nullptr
		headPtr = std::move(headPtr->getNext());
	}
	currentSize = 0;
} // end clear
