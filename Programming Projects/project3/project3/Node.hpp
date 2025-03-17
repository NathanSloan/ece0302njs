//   Adapted from Frank M. Carrano and Timothy M. Henry.

/** @file Node.hpp  */
#ifndef NODE_HPP
#define NODE_HPP
#include <memory>

template <class ItemType>
class Node
{
private:
	ItemType item;						  // A data item
	std::shared_ptr<Node<ItemType>> next; // Pointer to next node

public:
	Node();
	Node(const ItemType &anItem);
	Node(const ItemType &anItem, std::shared_ptr<Node<ItemType>> nextNodePtr);
	void setItem(const ItemType &anItem);
	void setNext(std::shared_ptr<Node<ItemType>> nextNodePtr);
	ItemType getItem() const;
	std::shared_ptr<Node<ItemType>> getNext() const;
}; // end Node

#include "Node.tpp"
#endif
