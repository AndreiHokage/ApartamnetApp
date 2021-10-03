#include "AppCoord.h"
#include "RepoLab.h"
#include "Repo_locatari.h"
#include "Repo_locatari_file.h"
#include <iostream>
using std::cout;
using std::cin;

void AppCoord::run() {
	
	unique_ptr<Repo> repository;

	while (true) {
		string type;
		cout << "Introdueti tipul de persistenta: ";
		cin >> type;

		if (type == "fisiere")
		{
			repository = make_unique<Repo_locatari_file>("apartament.txt");
			break;
		}
		else
			if (type == "memorie")
			{
				repository = make_unique<Repo_locatari>();
				break;
			}
			else
				if (type == "repolab")
				{
					double prob;
					cout << "Introdu probabilitatea: ";
					cin >> prob;
					cin.clear();
					repository = make_unique<RepoLab>(prob);
					break;
				}
	}
	Validator vd;
	Controller_Locatari srv{ *repository,vd };
	UI console{ srv };
	console.run();
	
}