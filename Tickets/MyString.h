#pragma once
#include <iostream>
class MyString
{
	char* str;
	size_t size;

	void copyFrom(const MyString&);
	void free();

public:
	MyString();
	MyString(const char*);
	MyString(const MyString&);
	~MyString();

	MyString& operator=(const MyString&);

	size_t getSize() const;
	const char* getString() const;
	void setString(const char*);

	void concat(const MyString&);
	//returns -1 if word is smaller, 0 if they are the same and 1 if word is bigger
	int compare(const char*); 

	friend std::ostream& operator<<(std::ostream&, const MyString&);
	friend std::istream& operator>>(std::istream&, MyString&);
};
bool operator==(const MyString&, const MyString&);