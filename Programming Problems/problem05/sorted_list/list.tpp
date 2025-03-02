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
  length = x.length;
  head = nullptr;
  if (x.head != nullptr)
  {
    head = nullptr;
    Node<T> *x_position = x.head;
    Node<T> *main_position = nullptr;

    while (x_position != nullptr)
    {
      Node<T> *item_node = new Node<T>(x_position->getItem());

      if (head == nullptr)
      {
        head = item_node;
        main_position = head;
      }
      else
      {
        main_position->setNext(item_node);
        main_position = main_position->getNext();
      }
      x_position = x_position->getNext();
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
void List<T>::swap(List &x)
{
  std::swap(head, x.head);
  std::swap(length, x.length);
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  if (head == nullptr)
  {
    return true;
  }
  return false;
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
  {
    throw std::range_error("outside of range of linked list");
  }

  Node<T> *item_node = new Node<T>(item);

  if (isEmpty())
  {
    head = item_node;
    length++;
  }
  else if (position == 0)
  {
    item_node->setNext(head);
    head = item_node;
    length++;
  }
  else
  {
    Node<T> *main_position = head;
    Node<T> *previous = nullptr;
    size_t i = 0;
    while (main_position != nullptr && i < position)
    {
      previous = main_position;
      main_position = main_position->getNext();
      i++;
    }
    previous->setNext(item_node);
    item_node->setNext(main_position);
    length++;
  }
}

template <typename T>
void List<T>::remove(std::size_t position)
{
  if (position < 0 || position >= getLength())
  {
    throw std::range_error("outside of range of linked list");
  }

  Node<T> *main_position = head;
  Node<T> *previous = nullptr;
  if (position == 0)
  {
    head = main_position->getNext();
    delete main_position;
    length--;
  }
  else
  {
    size_t i = 0;
    while (main_position != nullptr && i < position)
    {
      previous = main_position;
      main_position = main_position->getNext();
      i++;
    }

    previous->setNext(main_position->getNext());
    delete main_position;
    length--;
  }
}

template <typename T>
void List<T>::clear()
{
  Node<T> *position = head;
  Node<T> *next = nullptr;

  while (position != nullptr)
  {
    next = position->getNext();
    delete position;
    position = next;
  }
  head = nullptr;
  length = 0;
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  if (position < 0 || position >= getLength())
  {
    throw std::range_error("outside of range of linked list");
  }

  Node<T> *main_position = head;
  size_t i = 0;
  while (main_position != nullptr && i < position)
  {
    main_position = main_position->getNext();
    i++;
  }
  return main_position->getItem();
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T &newValue)
{
  if (position < 0 || position >= getLength())
  {
    throw std::range_error("outside of range of linked list");
  }

  Node<T> *main_position = head;
  size_t i = 0;
  while (main_position != nullptr && i < position)
  {
    main_position = main_position->getNext();
    i++;
  }
  main_position->setItem(newValue);
}
