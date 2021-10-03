#pragma once
#include <vector>
#include <string>
#include <QAbstractTableModel> 
#include "Locatar.h"
#include "Myvector.h"
using std::vector;
using std::string;


class MyTableView:public QAbstractTableModel
{
private:
	const Myvector < Locatar >& v;
public:
	MyTableView(const Myvector <Locatar>& v) :v{ v } {

	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return v.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 2;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		//qDebug()<<index<<" "<<role
		if (role == Qt::DisplayRole) {
			int idx = index.row();
			Locatar loc = v.at(idx);
			if (index.column() == 0)
				return QString::number(loc.get_apart());
			else
			if (index.column() == 1)
				return QString::number(loc.get_spr());
			else
			if (index.column() == 2)
				return QString::fromStdString(loc.get_nume_pr());
			else
			if (index.column() == 3)
				return QString::fromStdString(loc.get_tip());
		}
	}
};

