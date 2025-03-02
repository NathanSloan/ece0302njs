#include "sorted_list.hpp"
#include <stdexcept>

template <typename T>
SortedList<T>::SortedList() : List<T>()
{
}

template <typename T>
SortedList<T>::SortedList(List<T> unsorted_list)
{
  List<T> my_temp_list = unsorted_list;
  for (int end = my_temp_list.getLength() - 1; end >= 0; end--)
  {
    int max = 0;
    for (int i = 1; i <= end; i++)
    {
      if (my_temp_list.getEntry(i) > my_temp_list.getEntry(max))
      {
        max = i;
      }
    }
    if (max != end)
    {
      T temp = my_temp_list.getEntry(end);
      my_temp_list.setEntry(end, my_temp_list.getEntry(max));
      my_temp_list.setEntry(max, temp);
    }
  }
  // swap the temp list, so the original list is left as it was, and the list in the sorted list is sorted
  List<T>::swap(my_temp_list);
}

template <typename T>
SortedList<T>::SortedList(const SortedList<T> &x) : List<T>(x)
{
}

template <typename T>
SortedList<T> &SortedList<T>::operator=(SortedList<T> x)
{
  List<T>::operator=(x);
  return *this;
}

template <typename T>
SortedList<T>::~SortedList()
{
  // base destructor gets called automatically
}

template <typename T>
bool SortedList<T>::isEmpty() const noexcept
{
  return List<T>::isEmpty();
}

template <typename T>
std::size_t SortedList<T>::getLength() const noexcept
{
  return List<T>::getLength();
}

template <typename T>
void SortedList<T>::insert(const T &item)
{
  size_t i = 0;
  while (i < getLength() && item > getEntry(i))
  {
    i++;
  }
  List<T>::insert(i, item);
}

template <typename T>
void SortedList<T>::remove(const T &item)
{
  if (isEmpty())
    throw std::range_error("empty list in remove");
  size_t i = 0;
  while (i != getLength() && getEntry(i) != item)
  {
    i++;
  }
  if (getEntry(i) != item)
  {
    throw std::range_error("item not found in list");
  }
  else
  {
    List<T>::remove(i);
  }
}

template <typename T>
void SortedList<T>::removeAt(std::size_t position)
{
  if (isEmpty())
    throw std::range_error("empty list in remove");
  List<T>::remove(position);
}

template <typename T>
void SortedList<T>::clear()
{
  List<T>::clear();
}

template <typename T>
T SortedList<T>::getEntry(std::size_t position) const
{
  return List<T>::getEntry(position);
}

template <typename T>
long int SortedList<T>::getPosition(const T &item)
{
  size_t i = 0;
  while (i < getLength())
  {
    if (getEntry(i) == item)
    {
      return i;
    }
    i++;
  }
  return -1;
}
