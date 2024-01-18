#pragma once
#pragma warning(disable:26495)
#include <QMainWindow>
#include <QPushButton>
#include "ui_plug_widget.h"

class plug_widget: public QMainWindow
{
	Q_OBJECT

public:
	plug_widget(QWidget *parent=nullptr);
	void getmassage();
	~plug_widget();
	Ui::plug_widgetClass ui;

};
