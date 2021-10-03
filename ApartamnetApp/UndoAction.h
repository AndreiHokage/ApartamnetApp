#pragma once
#include "Locatar.h"
#include "Repo_locatari.h"

//Polimorfismul funtioneaza doar cu mostenirea
class UndoAction
{

public:

	virtual void doUndo() = 0;

	virtual ~UndoAction() = default; ////!!!!!!!

};

class UndoAdauga:public UndoAction
{
private:
	Repo& repo;
	Locatar locatar;

public:
	UndoAdauga(Repo& repo, Locatar locatar) :repo{ repo }, locatar{ locatar }{

	}

	void doUndo() override;

};

class UndoSterge :public UndoAction
{
private:
	Repo& repo;
	Locatar locatar;

public:

	UndoSterge(Repo& repo,Locatar locatar):repo{repo},locatar{locatar}{}

	void doUndo() override;

};

class UndoModifica :public UndoAction
{
private:

	Repo& repo;
	Locatar locatar;

public:
	UndoModifica(Repo& repo, Locatar locatar) :repo{ repo }, locatar{ locatar }{

	}

	void doUndo() override;

};