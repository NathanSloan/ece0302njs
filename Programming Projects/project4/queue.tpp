#include "queue.hpp"

template <typename T, typename L>
void Queue<T, L>::enqueue(const T &item)
{
  internal_list.insert(internal_list.getLength(), item);
}

template <typename T, typename L>
void Queue<T, L>::dequeue()
{
  if (internal_list.getLength() == 0)
    throw std::out_of_range("Index is out of range (0)");
  else
    internal_list.remove(0);
}

template <typename T, typename L>
T Queue<T, L>::peekFront()
{
  if (internal_list.getLength() == 0)
    throw std::out_of_range("Index is out of range (0)");
  else
    return internal_list.getEntry(0);
}

template <typename T, typename L>
bool Queue<T, L>::isEmpty() const
{
  return internal_list.isEmpty();
}
