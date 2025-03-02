#include "sorted_list.hpp"
#include <stdexcept>

template <typename T>
SortedList<T>::SortedList(): List<T>()
{
}

template <typename T>
SortedList<T>::SortedList(List<T> unsorted_list) 
{
  // TODO
}

template <typename T>
SortedList<T>::SortedList(const SortedList<T> & x):
  List<T>(x)
{
}

template <typename T>
SortedList<T>& SortedList<T>::operator=(SortedList<T> x)
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
void SortedList<T>::insert(const T& item)
{
  // TODO
}

template <typename T>
void SortedList<T>::remove(const T& item)
{  
  // TODO
}

template <typename T>
void SortedList<T>::removeAt(std::size_t position)
{  
  // TODO
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
long int SortedList<T>::getPosition(const T& item)
{
  // TODO
  return 0;
}
