#pragma once
#include "Repo_locatari.h"
#include "Iterator_myvector.h"
#include "Myvector.h"

class Repo_locatari_file:public Repo_locatari
{

private:
	string file_name;
	
	Myvector < string > split_string(string S);

	void loadfromfile(); 

	void storetofile();

public: 

	Repo_locatari_file(string file_name) :Repo_locatari(), file_name{ file_name }{
		loadfromfile();
	}

	Repo_locatari_file(const Repo_locatari_file&) = delete;

	void add_locatar(const Locatar& locatar) override;

	Locatar delete_locatar(int id) override;
	Locatar update_locatar(const Locatar& locatar) override;
};

