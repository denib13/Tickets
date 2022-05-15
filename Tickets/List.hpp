#include <fstream>
#include "Event.h"
template <typename T>
class List
{
	T* data;
	size_t count;
	size_t capacity;

	void free();
	void copyFrom(const List& other);
	void resize();
	size_t findElement(const T& element) const;
public:
	friend class TicketCenter;
	friend class Event;

	List();
	List(const List& other);
	List(List&& other);
	~List();

	List& operator=(const List& other);
	List& operator=(List&& other);
	T& operator[](size_t index) const;

	size_t getCount() const;

	void add(const T& object);
	void removeAtIndex(size_t index);
};

template<typename T>
void List<T>::resize()
{
	capacity *= 2;

	T* newArr = new T [capacity];
	for (size_t i = 0; i < count; i++)
	{
		newArr[i] = data[i];
	}

	free();
	data = newArr;
}

template<typename T>
void List<T>::free()
{
	delete[] data;
}

template<typename T>
void List<T>::copyFrom(const List<T>& other)
{
	count = other.count;
	capacity = other.capacity;

	data = new T [capacity];
	for (size_t i = 0; i < count; i++)
	{
		data[i] = other.data[i];
	}
}

template<typename T>
size_t List<T>::findElement(const T& element) const
{
	for (size_t i = 0; i < count; i++)
	{
		if (data[i] == element)
			return i;
	}
	return -1;
}

template<typename T>
List<T>::List()
{
	count = 0;
	capacity = 1;
	data = new T[capacity];
}

template<typename T>
List<T>::List(const List<T>& other)
{
	copyFrom(other);
}

template<typename T>
List<T>::List(List<T>&& other)
{
	count = other.count;
	capacity = other.capacity;
	data = other.data;

	other.data = nullptr;
}

template<typename T>
List<T>::~List()
{
	free();
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
List<T>& List<T>::operator=(List<T>&& other)
{
	if (this != &other)
	{
		free();
		count = other.count;
		capacity = other.capacity;
		data = other.data;

		other.data = nullptr;
	}
	return *this;
}

template<typename T>
T& List<T>::operator[](size_t index) const
{
	if(0 <= index && index < count)
		return data[index];
}

template<typename T>
size_t List<T>::getCount() const
{
	return count;
}

template<typename T>
void List<T>::add(const T& object)
{
	if (capacity == count)
		resize();

	data[count++] = object;
}

template<typename T>
void List<T>::removeAtIndex(size_t index)
{
	if (0 <= index && index < count)
	{
		T* newArray = new T[count - 1];
		for (size_t i = 0; i < index; i++)
		{
			newArray[i] = data[i];
		}
		for (size_t i = index + 1; i < count; i++)
		{
			newArray[i - 1] = data[i];
		}
		free();
		data = newArray;
		count--;

	}
	else
		throw std::exception("Index out of range!");
}
