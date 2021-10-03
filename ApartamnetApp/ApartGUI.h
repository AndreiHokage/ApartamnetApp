#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlistview.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qmessagebox.h>
#include "Controller_Locatari.h"
#include "Myvector.h"
#include "Iterator_myvector.h"
#include "Locatar.h"
#include "Cos.h"
#include "Observer.h"
#include "HistogramaGUI.h"

class CosGUI:public QWidget,public Observer 
{
private:
	Cos& coscurent;
	QHBoxLayout* lymain = new QHBoxLayout; 
	QTableWidget* tbl;
	QLineEdit* txtid,*txtrand,*txtexp;
	QPushButton* btn_addcart,*btn_emptycart;
	QPushButton* btn_randcart,*btn_exp;

	void initGUI();
	void connect();
	void reload(const Myvector< Locatar >& v);
	void add_cart();
	void empty_cart();
	void clearedit();
	void random_cart();
	void export_csvcart();

	void update() override;

public:
	CosGUI(Cos& cos) :QWidget(), coscurent(cos) {
		initGUI();
		connect();
	}

	~CosGUI() {
		coscurent.removesubsriber(this);
	}

};

class ApartGUI:public QWidget
{
private:
	Controller_Locatari& srv;
	QVBoxLayout* lyMAIN = new QVBoxLayout;
	QTableWidget* tbl;
	QListWidget* list; 
	QLineEdit* txtid;
	QLineEdit* txtspr;
	QLineEdit* txttip;
	QLineEdit* txtnume; 
	QPushButton* btnadd;
	QPushButton* btnupd;
	QPushButton* btndel;
	QPushButton* btnsearch,*fltrtip,*sortname,*sortspr;
	QPushButton* sorttmp,*fltrspr,*btnexit,*btn_readcart;
	QPushButton* btncos,*btnundo;

	void initGUI();
	void connect();
	void add_locatar();
	void update_locatar();
	void delete_locatar();
	void search();
	void filtrebytype();
	void filtrebyspr();
	void reload(const Myvector<Locatar>& v);
	void cleanedit();
	void selectcapturelist();
	void undo();

public:
	ApartGUI(Controller_Locatari& srv) :QWidget(), srv{ srv } {
		initGUI();
		connect();
		reload(srv.get_all());
	}


};

