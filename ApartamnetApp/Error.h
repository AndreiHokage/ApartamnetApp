#pragma once
#include <string>
using std::string;

class Exception_Apr
{
private:
	string msg;

public:
	Exception_Apr(string msg) :msg{ msg } {

	}

	string get_msg() const
	{
		return msg;
	}
};

class LocatarError: public Exception_Apr
{
public:
	LocatarError(string msg):Exception_Apr(msg){}
};

class RepoError : public Exception_Apr
{
public:
	RepoError(string msg): Exception_Apr(msg) {}
};


class ValueError:public Exception_Apr
{
public:
	ValueError(string msg):Exception_Apr(msg){}
};

class ListError:public Exception_Apr
{

public:
	ListError(string msg) :Exception_Apr{ msg } {}

};

class FileError :public Exception_Apr
{

public:
	FileError(string msg) :Exception_Apr{ msg } {}

};

class UndoError :public Exception_Apr
{
public:
	UndoError(string msg) :Exception_Apr{ msg } {}
};

class CevaEroare :public Exception_Apr
{
public:
	CevaEroare(string msg) :Exception_Apr{ msg } {}
};
