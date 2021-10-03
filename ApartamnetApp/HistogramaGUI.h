#pragma once
#include <qwidget.h>
#include <qpainter.h>
#include <random>
#include <time.h>
#include "Observer.h"
#include "Cos.h"

class HistogramaGUI:public QWidget,public Observer
{
	Cos& coscurent;

public:

	HistogramaGUI(Cos& coscurent) :coscurent{ coscurent } {
		coscurent.addsubsriber(this);
	}

	void update() override;

	void paintEvent(QPaintEvent* ev) override;

	~HistogramaGUI() {
		coscurent.removesubsriber(this);
	}

};

