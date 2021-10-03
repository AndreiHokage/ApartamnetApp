#include <QtWidgets/qformlayout.h>
#include "ApartGUI.h" 

#define SPC1 5

void CosGUI::initGUI() {
	this->setLayout(lymain);

	QVBoxLayout* cl1 = new QVBoxLayout();
	tbl = new QTableWidget(1,4,this); 
	tbl->setItem(0, 0,new QTableWidgetItem( "Nr_Apartament" ));
	tbl->setItem(0, 1, new QTableWidgetItem("Suprafata"));
	tbl->setItem(0, 2, new QTableWidgetItem("Nume proprietar"));
	tbl->setItem(0, 3, new QTableWidgetItem("Tip"));
	cl1->addWidget(tbl);
	lymain->addLayout(cl1);

	QVBoxLayout* cl2 = new QVBoxLayout; 
	txtid = new QLineEdit();
	txtrand = new QLineEdit();
	txtexp = new QLineEdit();

	QFormLayout* form21 = new QFormLayout(); 
	QVBoxLayout* cl21 = new QVBoxLayout;
	form21->addRow(tr("Id:"), txtid);
	btn_addcart = new QPushButton("Add_Cart");
	cl21->addLayout(form21); 
	cl21->addWidget(btn_addcart); 
	cl21->addStretch(SPC1);

	QFormLayout* form22 = new QFormLayout(); 
	QVBoxLayout* cl22 = new QVBoxLayout;
	btn_randcart = new QPushButton("Random Cart");
	form22->addRow(tr("Nr de generari"), txtrand);
	cl22->addLayout(form22);
	cl22->addWidget(btn_randcart);
	cl22->addStretch(SPC1);
	
	QFormLayout* form23 = new QFormLayout();
	QVBoxLayout* cl23 = new QVBoxLayout;
	btn_exp = new QPushButton("Export CSV");
	form23->addRow(tr("Nume fisier CSV"), txtexp);
	cl23->addLayout(form23);
	cl23->addWidget(btn_exp);
	cl23->addStretch(SPC1);

	QHBoxLayout* btn2pr = new QHBoxLayout;
	btn_emptycart = new QPushButton("Empty_Cart");
	btn2pr->addWidget(btn_emptycart);

	cl2->addLayout(cl21);
	cl2->addLayout(cl22);
	cl2->addLayout(cl23);
	cl2->addLayout(btn2pr);

	lymain->addLayout(cl2);
}

void CosGUI::connect() {
	coscurent.addsubsriber(this);

	QObject::connect(btn_addcart, &QPushButton::clicked, this, &CosGUI::add_cart);
	QObject::connect(btn_emptycart, &QPushButton::clicked, this, &CosGUI::empty_cart);
	QObject::connect(btn_randcart, &QPushButton::clicked, this, &CosGUI::random_cart);
	QObject::connect(btn_exp, &QPushButton::clicked, this, &CosGUI::export_csvcart);
}

void CosGUI::update() {
	reload(coscurent.get_all_list());
}

void CosGUI::add_cart() {
	bool ok = 0; 
	int apart = txtid->text().toInt(&ok); 
	if (ok == false)
	{
		QMessageBox::warning(this, "Warning", "Id ul trebe sa fie numeric!\n"); 
		clearedit();
		return;
	}
	
	try {
		coscurent.add_list(apart); 
		reload(coscurent.get_all_list());
	}
	catch (const RepoError& e)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
	clearedit();
}

void CosGUI::reload(const Myvector < Locatar >& v) {
	tbl->setRowCount(1); 
	for (const Locatar& locatar : v)
	{
		tbl->insertRow(tbl->rowCount());
		int row = tbl->rowCount() - 1;
		tbl->setItem(row, 0, new QTableWidgetItem(QString::number(locatar.get_apart())));
		tbl->setItem(row, 1, new QTableWidgetItem(QString::number(locatar.get_spr())));
		tbl->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(locatar.get_nume_pr())));
		tbl->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(locatar.get_tip())));
	}
}

void CosGUI::empty_cart() {
	coscurent.goleste();
	reload(coscurent.get_all_list());
	clearedit();
}

void CosGUI::clearedit() {
	txtid->clear();
	txtrand->clear();
	txtexp->clear();
}

void CosGUI::random_cart() {
	bool ok = 0;
	int val = txtrand->text().toInt(&ok);
	if (ok == false)
	{
		QMessageBox::warning(this, "Warning", "Valoarea trebe sa fie numerica!\n");
		clearedit(); 
		return;
	}

	try {
		coscurent.random_list(val); 
		reload(coscurent.get_all_list());
	}
	catch (const ListError& e)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
	clearedit();
}

void CosGUI::export_csvcart() {
	string file_name = txtexp->text().toStdString(); 
	try {
		coscurent.export_list_file(file_name); 
		reload(coscurent.get_all_list()); 
	}
	catch (const ListError& e)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}

	clearedit();
}