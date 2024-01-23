#pragma once

#include <QMainWindow>
#include "ui_shortcut_son_widget_class.h"

class shortcut_son_widget_class : public QMainWindow
{
	Q_OBJECT

public:
	shortcut_son_widget_class(QWidget *parent = nullptr);
	~shortcut_son_widget_class();

private:
	Ui::shortcut_son_widget_classClass ui;
};
