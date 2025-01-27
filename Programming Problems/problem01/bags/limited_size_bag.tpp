#include "limited_size_bag.hpp"

// Constructor
template <typename T>
LimitedSizeBag<T>::LimitedSizeBag() : size(0) {}

// Add an item to the bag
template <typename T>
bool LimitedSizeBag<T>::add(const T &item)
{
  if (size >= maxsize)
  {
    return false; // Bag is full
  }
  items[size++] = item;
  return true;
}

// Remove an item from the bag
template <typename T>
bool LimitedSizeBag<T>::remove(const T &item)
{
  for (std::size_t i = 0; i < size; ++i)
  {
    if (items[i] == item)
    {
      items[i] = items[--size]; // Replace with the last item and decrease size
      return true;
    }
  }
  return false; // Item not found
}

// Check if the bag is empty
template <typename T>
bool LimitedSizeBag<T>::isEmpty() const
{
  return size == 0;
}

// Get the current size of the bag
template <typename T>
std::size_t LimitedSizeBag<T>::getCurrentSize() const
{
  return size;
}

// Clear the bag contents
template <typename T>
void LimitedSizeBag<T>::clear()
{
  size = 0;
}

// Count how many times an item occurs in the bag
template <typename T>
std::size_t LimitedSizeBag<T>::getFrequencyOf(const T &item) const
{
  std::size_t count = 0;
  for (std::size_t i = 0; i < size; ++i)
  {
    if (items[i] == item)
    {
      ++count;
    }
  }
  return count;
}

// Check if an item is in the bag
template <typename T>
bool LimitedSizeBag<T>::contains(const T &item) const
{
  for (std::size_t i = 0; i < size; ++i)
  {
    if (items[i] == item)
    {
      return true;
    }
  }
  return false;
}
