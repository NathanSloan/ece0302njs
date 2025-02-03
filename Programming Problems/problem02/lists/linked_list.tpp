#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList()
{
  head = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList()
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
LinkedList<T>::LinkedList(const LinkedList<T> &x)
{
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
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> x)
{
  swap(x);
  return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList &x)
{
  std::swap(head, x.head);
}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
  if (head == nullptr)
  {
    return true;
  }
  return false;
}

template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept
{
  size_t list_size = 0;
  Node<T> *main_position = head;
  while (main_position != nullptr)
  {
    main_position = main_position->getNext();
    list_size++;
  }
  return list_size;
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T &item)
{
  if (position < 0 || position > getLength())
  {
    return false;
  }

  Node<T> *item_node = new Node<T>(item);

  if (isEmpty())
  {
    head = item_node;
    return true;
  }

  if (position == 0)
  {
    item_node->setNext(head);
    head = item_node;
    return true;
  }

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

  return true;
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  if (position < 0 || position >= getLength())
  {
    return false;
  }

  Node<T> *main_position = head;
  Node<T> *previous = nullptr;
  if (position == 0)
  {
    head = main_position->getNext();
    delete main_position;
    return true;
  }

  size_t i = 0;
  while (main_position != nullptr && i < position)
  {
    previous = main_position;
    main_position = main_position->getNext();
    i++;
  }
  previous->setNext(main_position->getNext());
  delete main_position;

  return true;
}

template <typename T>
void LinkedList<T>::clear()
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
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  if (position < 0 || position >= getLength())
  {
    return T();
  }

  Node<T> *main_position = head;
  size_t i = 0;
  while (main_position != nullptr && i < position)
  {
    main_position = main_position->getNext(); // traverse the list
    i++;
  }
  return main_position->getItem();
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T &newValue)
{
  if (position < 0 || position >= getLength())
  {
    return;
  }

  Node<T> *main_position = head;
  size_t i = 0;
  while (main_position != nullptr && i < position)
  {
    main_position = main_position->getNext(); // traverse the list
    i++;
  }
  main_position->setItem(newValue);
}
