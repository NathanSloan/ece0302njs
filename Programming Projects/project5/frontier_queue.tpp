#include "frontier_queue.hpp"

// TODO implement the member functions here

template <typename T>
State<T> frontier_queue<T>::pop()
{
  if (queue.empty())
  {
    throw std::out_of_range("Queue is empty");
  }
  State<T> returnVal = queue.front();
  std::swap(queue.front(), queue.back());
  queue.pop_back();

  /*
  parent(i) = (i - 1) / 2
  left child(i) = 2 * i + 1
  right child(i) = 2 * i + 2
  */
  std::size_t index = 0;
  while (true)
  {
    std::size_t left_child = 2 * index + 1;
    std::size_t right_child = 2 * index + 2;
    std::size_t current_child = index;

    if (left_child < queue.size() && queue[left_child].getFCost() < queue[current_child].getFCost())
    {
      current_child = left_child;
    }
    if (right_child < queue.size() && queue[right_child].getFCost() < queue[current_child].getFCost())
    {
      current_child = right_child;
    }

    if (current_child == index)
    {
      break;
    }
    else
    {
      std::swap(queue[index], queue[current_child]);
      index = current_child;
      ;
    }
  }

  return returnVal;
}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur)
{
  State<T> newState(p, cost, heur);
  queue.push_back(newState);

  /*
  parent(i) = (i - 1) / 2
  left child(i) = 2 * i + 1
  right child(i) = 2 * i + 2
  */
  int index = 0;
  while (true)
  {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int checkChild = index;

    if (leftChild < queue.size())
    {
      if (queue[leftChild].getFCost() < queue[index].getFCost())
        checkChild = leftChild;
    }
    else if (rightChild < queue.size())
    {
      if (queue[rightChild].getFCost() < queue[index].getFCost())
        checkChild = rightChild;
    }
    if (checkChild != index)
    {
      std::swap(queue[index], queue[checkChild]);
      index = checkChild;
    }
    else
    {
      break;
    }
  }
}

template <typename T>
bool frontier_queue<T>::empty()
{
  return queue.empty();
}

template <typename T>
bool frontier_queue<T>::contains(const T &p)
{
  for (int i = 0; i < queue.size(); i++)
  {
    if (queue[i].getValue() == p)
    {
      return true;
    }
  }
  return false;
}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost)
{
  for (int i = 0; i < queue.size(); i++)
  {
    if (queue[i].getValue() == p)
    {
      if (cost < queue[i].getPathCost())
      {
        queue[i].updatePathCost(cost);

        int index = 0;
        while (true)
        {
          int leftChild = 2 * index + 1;
          int rightChild = 2 * index + 2;
          int checkChild = index;

          if (leftChild < queue.size() && queue[leftChild].getFCost() < queue[index].getFCost())
            checkChild = leftChild;
          else if (rightChild < queue.size() && queue[rightChild].getFCost() < queue[index].getFCost())
            checkChild = rightChild;

          if (checkChild != index)
          {
            std::swap(queue[index], queue[checkChild]);
            index = checkChild;
          }
          else
            break;
        }
      }
    }
  }
}
