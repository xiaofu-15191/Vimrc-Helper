#pragma once

#include <QWidget>
#include "ui_shortcut_widget_class.h"

class shortcut_widget_class : public QWidget
{
	Q_OBJECT

public:
	shortcut_widget_class(QWidget *parent = nullptr);
	~shortcut_widget_class();

private:
	Ui::shortcut_widget_classClass ui;
};
