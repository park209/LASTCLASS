#include"array.h"
#include <iostream>
using namespace std;
int CompareIntegers(void* one, void* other);
int main(int argc, char* argv[]) {
	Array <int> array(3);
	Long index = array.Store(0, 1);
	int object = array.GetAt(index);
	cout << object << endl;
	index = array.Store(1, 2);
	cout << array[index] << endl;
	index = array.Store(2, 3); //1 2 3
	cout << array[index] << endl;
	int key = 1;
	index = array.LinearSearchUnique(&key, CompareIntegers);
	cout << array[index] << endl;
	index = array.Insert(1, 3); // 1 3 2 3
	cout << array[index] << endl;
	Long(*indexes);
	Long count;
	key = 3;
	array.LinearSearchDuplicate(&key, &indexes, &count, CompareIntegers);
	Long i = 0;
	while (i < count)
	{
		cout << array[indexes[i]] << endl;
		i++;
	}
	if (indexes != 0)
	{
		delete[] indexes;
	}
	index = array.AppendFromFront(5); // 5 1 3 2 3
	cout << array[index] << endl;
	index = array.AppendFromRear(5); // 5 1 3 2 3 5
	cout << array[index] << endl;
	index = array.Delete(0); // 1 3 2 3 5
	if (index == -1)
	{
		cout << "삭제되었습니다." << endl;
	}
	index = array.Delete(1); // 1 2 3 5
	if (index == -1)
	{
		cout << "삭제되었습니다." << endl;
	}
	key = 1;
	index = array.BinarySearchUnique(&key, CompareIntegers);
	cout << array[index] << endl;
	index = array.Insert(2, 3); // 1 2 3 3 5
	cout << array[index] << endl;
	key = 3;
	array.BinarySearchDuplicate(&key, &indexes, &count, CompareIntegers);
	i = 0;
	while (i < count)
	{
		cout << array[indexes[i]] << endl;
		i++;
	}
	if (indexes != 0)
	{
		delete[] indexes;
	}
	index = array.DeleteFromFront(); // 2 3 3 5
	if (index == -1)
	{
		cout << "삭제되었습니다." << endl;
	}
	index = array.DeleteFromRear(); // 2 3 3
	if (index == -1)
	{
		cout << "삭제되었습니다." << endl;
	}
	index = array.Delete(2); // 2 3
	if (index == -1)
	{
		cout << "삭제되었습니다." << endl;

	}
	index = array.AppendFromRear(1); // 2 3 1
	cout << array[index] << endl;
	array.SelectionSort(CompareIntegers); // 1 2 3
	i = 0;
	while (i < array.GetLength())
	{
		cout << array[i] << endl;
		i++;
	}
	Array<int> one(4);
	index = one.Store(0, 8);
	cout << one[index] << endl;
	index = one.Store(1, 7);
	cout << one[index] << endl;
	index = one.Store(2, 6);
	cout << one[index] << endl;
	index = one.Store(3, 5); // 8 7 6 5
	cout << one[index] << endl;
	one.BubbleSort(CompareIntegers); // 5 6 7 8
	i = 0;
	while (i < one.GetLength())
	{
		cout << one[i] << endl;
		i++;
	}
	index = one.Modify(0, 9); // 9 6 7 8
	cout << one[index] << endl;
	one.InsertionSort(CompareIntegers); // 6 7 8 9
	i = 0;
	while (i < one.GetLength())
	{
		cout << one[i] << endl;
		i++;
	}
	Array<int> other(8);
	other.MergeSort(array, one, CompareIntegers); // 1 2 3 6 7 8 9
	i = 0;
	while (i < other.GetLength())
	{
		object = other.GetAt(i);
		cout << object << " ";
		i++;
	}

	other = one;
	i = 0;
	while (i < other.GetLength())
	{
		object = other.GetAt(i);
		cout << object << " ";
		i++;
	}

	other.Clear();
	return 0;
}

int CompareIntegers(void* one, void* other)
{
	int ret;
	if (*(static_cast<int*>(one)) > *(static_cast<int*>(other)))
	{
		ret = 1;
	}
	else if (*(static_cast<int*>(one)) == *(static_cast<int*>(other)))
	{
		ret = 0;
	}
	else if (*(static_cast<int*>(one)) < *(static_cast<int*>(other)))
	{
		ret = -1;
	}
	return ret;
}