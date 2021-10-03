#include "ApartamnetApp.h"
#include "Test.h"
#include "Validator.h"
#include "Repo_locatari_file.h"
#include "Controller_Locatari.h"
#include "ApartGUI.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    {
        QApplication a(argc, argv);
        Test_all test;
        test.run_all();

        Validator vd; 
        Repo_locatari_file repo{ "apartament.txt" };
        Controller_Locatari srv{ repo,vd };
        ApartGUI gui{ srv };
        gui.show();
        a.exec();
    }
    

    return 0;
}
