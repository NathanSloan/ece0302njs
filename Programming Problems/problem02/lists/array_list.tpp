#include "array_list.hpp"

template <typename T>
ArrayList<T>::ArrayList()
{
  array_size = 0;
  my_array = (T *)malloc(array_size * sizeof(T));
}

template <typename T>
ArrayList<T>::~ArrayList()
{
  free(my_array);
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList &rhs)
{
  array_size = rhs.array_size;
  my_array = (T *)malloc(array_size * sizeof(T));
  std::memcpy(my_array, rhs.my_array, array_size * sizeof(T));
}

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(ArrayList rhs)
{
  swap(rhs);
  return *this;
}

template <typename T>
void ArrayList<T>::swap(ArrayList &rhs)
{
  std::swap(array_size, rhs.array_size);
  std::swap(my_array, rhs.my_array);
}

template <typename T>
bool ArrayList<T>::isEmpty() const noexcept
{
  return array_size == 0;
}

template <typename T>
std::size_t ArrayList<T>::getLength() const noexcept
{
  return array_size;
}

template <typename T>
bool ArrayList<T>::insert(std::size_t position, const T &item)
{
  if (position < 0 || position > array_size)
    return false;
  array_size++;
  T *temp = (T *)malloc(array_size * sizeof(item));
  for (int i = 0; i < position; i++)
    temp[i] = my_array[i];
  temp[position] = item;

  for (int i = position + 1; i < array_size; i++)
    temp[i] = my_array[i - 1];
  my_array = (T *)realloc(my_array, array_size * sizeof(item));
  std::memcpy(my_array, temp, array_size * sizeof(item));
  free(temp);
  return true;
}

template <typename T>
bool ArrayList<T>::remove(std::size_t position)
{
  if (position < 0 || position >= array_size)
    return false;
  array_size--;
  T *temp = (T *)malloc((array_size) * sizeof(T));
  int j = 0;
  for (int i = 0; i < array_size + 1; i++)
  {
    if (i == position)
      continue;
    else
    {
      *(temp + j) = *(my_array + i);
      j++;
    }
  }
  my_array = (T *)realloc(my_array, array_size * sizeof(T));
  std::memcpy(my_array, temp, array_size * sizeof(T));
  free(temp);
  return true;
}

template <typename T>
void ArrayList<T>::clear()
{
  free(my_array);
  array_size = 0;
  my_array = (T *)malloc(array_size * sizeof(T));
}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const
{
  if (position < 0 || position >= array_size)
  {
    return T();
  }
  return my_array[position];
}

template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T &newValue)
{
  if (position < 0 || position >= array_size)
  {
    return;
  }
  my_array[position] = newValue;
}
