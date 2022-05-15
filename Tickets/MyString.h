#pragma once
#include <iostream>
class MyString
{
	char* str;
	size_t size;

	void copyFrom(const MyString& other);
	void free();

public:
	MyString();
	MyString(const char* string);
	MyString(const MyString& other);
	MyString(MyString&& other);
	~MyString();

	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other);

	size_t getSize() const;
	const char* getString() const;
	void setString(const char* string);

	void concat(const MyString& other);

	//returns -1 if word is smaller, 0 if they are the same and 1 if word is bigger
	int compare(const char* word); 

	friend std::ostream& operator<<(std::ostream& stream, const MyString& string);
	friend std::istream& operator>>(std::istream& stream, MyString& string);
};
bool operator==(const MyString& lhs, const MyString& rhs);