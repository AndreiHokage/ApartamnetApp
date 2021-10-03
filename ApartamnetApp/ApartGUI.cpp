#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <qlist.h>
#include <string>
#include "ApartGUI.h"
#include "Error.h"

void ApartGUI::initGUI() {

	setLayout(lyMAIN);
	QPalette pal = palette();
	QColor color = { "#cc9900" };
	pal.setColor(QPalette::Window, color);
	setAutoFillBackground(true);
	setPalette(pal);


	QHBoxLayout* cosly = new QHBoxLayout();
	btncos = new QPushButton("Cart");
	btn_readcart = new QPushButton("CartReadOnly");
	cosly->addWidget(btn_readcart);
	cosly->addStretch(30);
	cosly->addWidget(btncos);
	
	lyMAIN->addLayout(cosly);

	QHBoxLayout* lymain = new QHBoxLayout(); 
	lyMAIN->addLayout(lymain);

	QVBoxLayout* ly_left = new QVBoxLayout;
	list = new QListWidget; 
	ly_left->addWidget(list);

	QHBoxLayout* line_box1 = new QHBoxLayout; 

	sortname = new QPushButton("SortByName");
	sortname->setStyleSheet("background-color:#999966");
	sortspr = new QPushButton("SortBySurface");
	sortspr->setStyleSheet("background-color:#666633");
	sorttmp = new QPushButton("SortBySprType");
	sorttmp->setStyleSheet("background-color:#33331a");

	line_box1->addWidget(sortname);
	line_box1->addWidget(sortspr);
	line_box1->addWidget(sorttmp);

	ly_left->addLayout(line_box1);
	
	lymain->addLayout(ly_left);

	QVBoxLayout* ly_right = new QVBoxLayout; 

	QFormLayout* form = new QFormLayout; 
	txtid = new QLineEdit;
	txtspr = new QLineEdit;
	txtnume = new QLineEdit;
	txttip = new QLineEdit;
	form->addRow(tr("Id:"), txtid);
	form->addRow(tr("Suprafata:"), txtspr);
	form->addRow(tr("Nume proprietar:"), txtnume);
	form->addRow(tr("Tip apartament:"), txttip); 

	ly_right->addLayout(form);

	QHBoxLayout* line1 = new QHBoxLayout();
	btnadd = new QPushButton("Add"); 
	btnupd = new QPushButton("Update");
	btndel = new QPushButton("Delete");
	btnsearch = new QPushButton("Search");

	line1->addWidget(btnadd);
	line1->addWidget(btnupd);
	line1->addWidget(btndel);
	line1->addWidget(btnsearch);
	
	ly_right->addLayout(line1);

	QHBoxLayout* line2 = new QHBoxLayout();
	fltrtip = new QPushButton("FiltreByType");
	fltrspr = new QPushButton("FiltreBySurface");

	line2->addWidget(fltrtip);
	line2->addWidget(fltrspr);

	ly_right->addLayout(line2);

	lymain->addLayout(ly_right);

	QVBoxLayout* cl3 = new QVBoxLayout;
	tbl = new QTableWidget(1, 4, this);
	tbl->setItem(0, 0, new QTableWidgetItem("Nr_Apartament"));
	tbl->setItem(0, 1, new QTableWidgetItem("Suprafata"));
	tbl->setItem(0, 2, new QTableWidgetItem("Nume prorietar"));
	tbl->setItem(0, 3, new QTableWidgetItem("Tip"));
	cl3->addWidget(tbl);

	QHBoxLayout* hz3 = new QHBoxLayout;
	btnundo = new QPushButton("Undo"); 
	hz3->addWidget(btnundo);

	cl3->addLayout(hz3);
	lymain->addLayout(cl3);

}

void ApartGUI::connect() {
	QObject::connect(btnadd, &QPushButton::clicked, this, &ApartGUI::add_locatar);
	QObject::connect(list, &QListWidget::itemSelectionChanged, this, &ApartGUI::selectcapturelist);
	QObject::connect(btnupd, &QPushButton::clicked, this, &ApartGUI::update_locatar);
	QObject::connect(btndel, &QPushButton::clicked, this, &ApartGUI::delete_locatar);
	QObject::connect(btnsearch, &QPushButton::clicked, this, &ApartGUI::search);
	QObject::connect(sortname, &QPushButton::clicked, this, [&]() {
		Myvector < Locatar > v = srv.sortbyname(); 
		reload(v);
		});
	QObject::connect(sortspr, &QPushButton::clicked, this, [&]() {
		Myvector < Locatar > v = srv.sortbyspr();
		reload(v);
		});
	QObject::connect(sorttmp, &QPushButton::clicked, this, [&]() {
		Myvector < Locatar > v = srv.sortbytypespr();
		reload(v);
		});
	QObject::connect(fltrtip, &QPushButton::clicked, this, &ApartGUI::filtrebytype);
	QObject::connect(fltrspr, &QPushButton::clicked, this, &ApartGUI::filtrebyspr);
	QObject::connect(btncos, &QPushButton::clicked, this, [&]() {
		CosGUI* wndcos=new CosGUI{ srv.get_coscurent() };
		wndcos->show();
		});
	QObject::connect(btnundo, &QPushButton::clicked, this, &ApartGUI::undo);
	QObject::connect(btn_readcart, &QPushButton::clicked, this, [this]() {
		HistogramaGUI* wndhisto = new HistogramaGUI{ srv.get_coscurent() };
		wndhisto->show();
		});
}

void ApartGUI::selectcapturelist() {
	QList sel = list->selectedItems();

	if (sel.isEmpty())
		cleanedit();
	else
	{
		QListWidgetItem* item = sel.at(0);
		int apart = item->data(Qt::UserRole).toInt();
		const Locatar& locatar = srv.search(apart);
		txtid->setText(QString::number(locatar.get_apart()));
		txtspr->setText(QString::number(locatar.get_spr()));
		txtnume->setText(QString::fromStdString(locatar.get_nume_pr()));
		txttip->setText(QString::fromStdString(locatar.get_tip()));
	}
}


void ApartGUI::cleanedit() {
	txtid->clear();
	txtnume->clear();
	txtspr->clear();
	txttip->clear();
}

void ApartGUI::add_locatar()
{
	bool ok1,ok2;
	int apar = txtid->text().toInt(&ok1);
	int spr = txtspr->text().toInt(&ok2);
	if (ok1==false || ok2==false )
	{
		QMessageBox::warning(this, "Warning", "Valoarea trebuie sa fie numerica!\n");
		cleanedit();
		return;
	}
	string nume_pr = txtnume->text().toStdString();
	string tip = txttip->text().toStdString();
	try {
		srv.add_locatari(apar, spr, nume_pr, tip);
		//QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(tip));
		//item->setData(Qt::UserRole, apar);
		//list->addItem(item);
		reload(srv.get_all());
	}
	catch (const RepoError& e)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
	catch (const LocatarError& e)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
	cleanedit();
}

void ApartGUI::update_locatar() {

	bool ok1, ok2; 
	int apar = txtid->text().toInt(&ok1);
	int spr = txtspr->text().toInt(&ok2); 

	if (ok1 == false || ok2 == false)
	{
		QMessageBox::warning(this, "Warning", "Valoarea trebuie sa fie numerica!\n");
		cleanedit();
		return; 
	}

	string nume = txtnume->text().toStdString();
	string tip = txttip->text().toStdString(); 

	try {
		srv.update_locatari(apar, spr, nume, tip);
		reload(srv.get_all());
	}
	catch (const RepoError& e)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
	catch (const LocatarError& e)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
	cleanedit();
}

void ApartGUI::delete_locatar() {

	bool ok;
	int id = txtid->text().toInt(&ok);
	if (ok == 0)
	{
		QMessageBox::warning(this, "Warning", "Valoarea trebuie sa fie numerica!\n");
		cleanedit();
		return;
	}
	try {
		srv.delete_locatari(id);
		reload(srv.get_all());
	}
	catch (const RepoError& e)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
	cleanedit();
}

void ApartGUI::search() {
	
	bool ok;
	int id = txtid->text().toInt(&ok);
	if (ok == 0)
	{
		QMessageBox::warning(this, "Warning", "Valoarea trebuie sa fie numerica!\n");
		cleanedit();
		return;
	}

	try {
		const Locatar& locatar = srv.search(id);
		txtspr->setText(QString::number(locatar.get_spr())); 
		txtnume->setText(QString::fromStdString(locatar.get_nume_pr()));
		txttip->setText(QString::fromStdString(locatar.get_tip()));
	}
	catch (const RepoError& e)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
		cleanedit();
	}
}

void ApartGUI::filtrebytype() {
	
	string type = txttip->text().toStdString();
	Myvector < Locatar > rez = srv.filtrebytype(type); 
	const Myvector < Locatar >& v = srv.get_all();
	list->clear();
	for (const Locatar& x : v)
	{
		QListWidgetItem* tip = new QListWidgetItem(QString::fromStdString(x.get_tip()));
		tip->setData(Qt::UserRole, x.get_apart());
		for(const Locatar& y: rez)
			if (x == y)
			{
				tip->setData(Qt::BackgroundRole, QBrush{ Qt::red, Qt::SolidPattern });
				break;
			}
		list->addItem(tip);
	}
	cleanedit();
}

void ApartGUI::filtrebyspr() {
	bool ok;
	int spr = txtspr->text().toInt(&ok);
	if (ok == 0)
	{
		QMessageBox::warning(this, "Warning", "Valoarea trebuie sa fie numerica!\n");
		cleanedit();
		return;
	}
	Myvector < Locatar > rez = srv.filtrebyspr(spr);
	const Myvector < Locatar >& v = srv.get_all();
	list->clear();
	for (const Locatar& x : v)
	{
		QListWidgetItem* tip = new QListWidgetItem(QString::fromStdString(x.get_tip()));
		tip->setData(Qt::UserRole, x.get_apart());
		for (const Locatar& y : rez)
			if (x == y)
			{
				tip->setData(Qt::BackgroundRole, QBrush{ Qt::red, Qt::SolidPattern });
				break;
			}
		list->addItem(tip);
	}
	cleanedit();
}

void ApartGUI::reload(const Myvector < Locatar >& v)
{
	list->clear();
	tbl->setRowCount(1);
	for (const Locatar& x : v)
	{
		QListWidgetItem* tip = new QListWidgetItem(QString::fromStdString(x.get_tip()));
		tip->setData(Qt::UserRole, x.get_apart());
		list->addItem(tip);

		tbl->insertRow(tbl->rowCount());
		int row = tbl->rowCount() - 1;
		tbl->setItem(row, 0, new QTableWidgetItem(QString::number(x.get_apart())));
		tbl->setItem(row, 1, new QTableWidgetItem(QString::number(x.get_spr())));
		tbl->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(x.get_nume_pr())));
		tbl->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(x.get_tip())));
	}
}

void ApartGUI::undo() {
	try {
		srv.undo();
		reload(srv.get_all());
	}
	catch (const UndoError& e)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
	cleanedit();
}