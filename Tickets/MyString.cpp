#include <iostream>
#include "MyString.h"
#pragma warning(disable:4996)

void MyString::free()
{
	delete[] str;
}

void MyString::copyFrom(const MyString& other)
{
	size = other.size;
	str = new char[size + 1];
	strcpy(str, other.str);
}

MyString::MyString()
{
	str = new char[1];
	str[0] = '\0';
	size = 0;
}

MyString::MyString(const char* string)
{
	size = strlen(string);
	str = new char[size + 1];
	strcpy(str, string);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString::~MyString()
{
	free();
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

size_t MyString::getSize() const
{
	return size;
}

const char* MyString::getString() const
{
	return str;
}

void MyString::setString(const char* string)
{
	free();
	size = strlen(string);
	str = new char[size + 1];
	strcpy(str, string);
}

void MyString::concat(const MyString& other)
{
	char* result = new char[size + other.size + 1];

	strcpy(result, str);
	strcat(result, other.str);

	free();
	str = result;
	size += other.size;
}

int MyString::compare(const char* word)
{
	int diff = strcmp(str, word);
	if (diff == 0)
		return 0;
	else if (diff == -1)
		return -1;
	else if (diff == 1)
		return 1;
}

std::ostream& operator<<(std::ostream& stream, const MyString& string)
{
	stream << string.str;
	return stream;
}

std::istream& operator>>(std::istream& stream, MyString& string)
{
	char input[256];
	stream.getline(input, 255);
	string.setString(input);
	return stream;
}
