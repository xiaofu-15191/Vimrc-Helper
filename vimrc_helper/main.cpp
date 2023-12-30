#pragma warning(disable:6031)
//#pragma warning(disable:6262)
#include "vimrc_helper.h"
#include<QtWidgets/QApplication>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	vimrc_helper w;
	w.show();
	return a.exec();
}
