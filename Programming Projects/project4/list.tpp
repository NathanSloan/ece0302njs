#include "list.hpp"

template <typename T>
List<T>::List()
{
  head = nullptr;
  length = 0;
}

template <typename T>
List<T>::~List()
{
  Node<T> *position = head;
  Node<T> *next = nullptr;

  while (position != nullptr)
  {
    next = position->getNext();
    delete position;
    position = next;
  }
}

template <typename T>
List<T>::List(const List<T> &x)
{
  head = nullptr;
  length = 0;

  if (x.head != nullptr)
  {
    // Copy the first node
    head = new Node<T>(x.head->getItem());
    Node<T> *currentNew = head;
    Node<T> *currentOriginal = x.head->getNext();
    length++;

    // Copy the rest
    while (currentOriginal != nullptr)
    {
      Node<T> *newNode = new Node<T>(currentOriginal->getItem());
      currentNew->setNext(newNode);
      currentNew = newNode;
      currentOriginal = currentOriginal->getNext();
      length++;
    }
  }
}

template <typename T>
List<T> &List<T>::operator=(List<T> x)
{
  swap(x);
  return *this;
}

template <typename T>
void List<T>::swap(List<T> &x)
{
  std::swap(head, x.head);
  std::swap(length, x.length);
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  return length == 0;
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  return length;
}

template <typename T>
void List<T>::insert(std::size_t position, const T &item)
{
  if (position < 0 || position > getLength())
    throw std::range_error("outside of range of linked list");
  else
  {
    // insert at 0
    if (position == 0)
    {
      Node<T> *newNode = new Node<T>(item, head);
      head = newNode;
    }
    else
    {
      Node<T> *currentNode = head;
      for (int count = 0; count < position - 1; count++)
        currentNode = currentNode->getNext();

      Node<T> *newNode = new Node<T>(item, currentNode->getNext());
      currentNode->setNext(newNode);
    }

    length++;
  }
}

template <typename T>
void List<T>::remove(std::size_t position)
{
  if (position < 0 || position >= getLength())
    throw std::range_error("outside of range of linked list");
  else
  {
    // remove at 0
    if (position == 0)
    {
      Node<T> *newHead = head;
      head = newHead->getNext();
      delete newHead;
    }
    else
    {
      Node<T> *currentNode = head;
      Node<T> *previousNode = nullptr;
      for (int count = 0; count < position; count++)
      {
        previousNode = currentNode;
        currentNode = currentNode->getNext();
      }

      previousNode->setNext(currentNode->getNext());
      delete currentNode;
    }

    length--;
  }
}

template <typename T>
void List<T>::clear()
{
  while (head != nullptr)
  {
    Node<T> *iter = head;
    head = iter->getNext();
    delete iter;
  }
  length = 0;
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  if (position < 0 || position >= getLength())
    throw std::range_error("outside of range of linked list");
  else
  {
    Node<T> *currentNode = head;
    for (int count = 0; count < position; count++)
      currentNode = currentNode->getNext();

    return currentNode->getItem();
  }
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T &newValue)
{
  if (position < 0 || position >= getLength())
    throw std::range_error("outside of range of linked list");
  else
  {
    Node<T> *currentNode = head;
    for (int count = 0; count < position; count++)
      currentNode = currentNode->getNext();

    currentNode->setItem(newValue);
  }
}
