#include "dynamic_bag.hpp"

template <typename T>
DynamicBag<T>::DynamicBag()
    : size(0), capacity(10)
{
  items = new T[capacity];
}

template <typename T>
DynamicBag<T>::DynamicBag(const DynamicBag<T> &x)
    : size(x.size), capacity(x.capacity)
{
  items = new T[capacity];
  std::copy(x.items, x.items + size, items);
}

template <typename T>
DynamicBag<T>::~DynamicBag()
{
  delete[] items;
}

template <typename T>
DynamicBag<T> &DynamicBag<T>::operator=(DynamicBag<T> x)
{
  swap(x);
  return *this;
}

template <typename T>
void DynamicBag<T>::swap(DynamicBag<T> &x)
{
  std::swap(items, x.items);
  std::swap(size, x.size);
  std::swap(capacity, x.capacity);
}

template <typename T>
bool DynamicBag<T>::add(const T &item)
{
  if (size == capacity)
    resize();

  items[size++] = item;
  return true;
}

template <typename T>
bool DynamicBag<T>::remove(const T &item)
{
  for (std::size_t i = 0; i < size; ++i)
  {
    if (items[i] == item)
    {
      items[i] = items[size - 1];
      --size;
      return true;
    }
  }
  return false;
}

template <typename T>
bool DynamicBag<T>::isEmpty() const
{
  return size == 0;
}

template <typename T>
std::size_t DynamicBag<T>::getCurrentSize() const
{
  return size;
}

template <typename T>
bool DynamicBag<T>::contains(const T &item) const
{
  for (std::size_t i = 0; i < size; ++i)
  {
    if (items[i] == item)
      return true;
  }
  return false;
}

template <typename T>
void DynamicBag<T>::clear()
{
  size = 0;
}

template <typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T &item) const
{
  std::size_t count = 0;
  for (std::size_t i = 0; i < size; ++i)
  {
    if (items[i] == item)
      ++count;
  }
  return count;
}

template <typename T>
void DynamicBag<T>::resize()
{
  capacity *= 2;
  T *newItems = new T[capacity];
  std::copy(items, items + size, newItems);
  delete[] items;
  items = newItems;
}