#include "HistogramaGUI.h"
#define DIM 300

void HistogramaGUI::paintEvent(QPaintEvent* ev) {
	QPainter p{ this };

	srand(time(0));
	int size = coscurent.size_list();
	for (int i = 0; i < size; i++)
	{
		int x = rand() % DIM + 1;
		int y = rand() % DIM + 1;
		p.drawRect(x, y, (i + 1) * 10, (i + 1) * 20);
	}
}

void HistogramaGUI::update() {
	repaint();
}