#include "plug_widget.h"
#pragma warning(disable:26495)
plug_widget::plug_widget(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);
}
void plug_widget::getmassage()
{
	this->show();
}
plug_widget::~plug_widget()
{
	
}