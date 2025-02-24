#ifndef _SORT_HPP
#define _SORT_HPP

#include "list.hpp"

template <typename T>
void quick_sort(List<T> &list, int first, int last)
{
	if (first < last)
	{
		int pivotIndex = partition(list, first, last); // Get pivot position
		quick_sort(list, first, pivotIndex - 1);	   // Sort left part
		quick_sort(list, pivotIndex + 1, last);		   // Sort right part
	}
}

template <typename T>
int partition(List<T> &list, int first, int last)
{
	T pivot = list.getEntry(last); // Choose last element as pivot
	int i = first - 1;			   // i tracks the position for smaller elements

	for (int j = first; j < last; j++)
	{
		if (list.getEntry(j) <= pivot) // Elements <= pivot should move left
		{
			i++;
			if (i != j)
			{
				T temp = list.getEntry(i);
				list.setEntry(i, list.getEntry(j));
				list.setEntry(j, temp);
			}
		}
	}

	// Place the pivot in its correct position
	i++;
	T temp = list.getEntry(i);
	list.setEntry(i, list.getEntry(last));
	list.setEntry(last, temp);

	return i; // Return pivot index
}

#endif
