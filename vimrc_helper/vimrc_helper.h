#pragma once
#pragma execution_character_set("utf-8")
#include "ui_vimrc_helper.h"
#include<QtWidgets/QWidget>
#include<QtWidgets/QMainWindow>
#include<QSettings>
#include<QPushButton>
#include<QCloseEvent>
#include<QIcon>
#include<QLineEdit>
#include<QLabel>
#include<QByteArray>
#include<QDialog>
#include<QFont>
#include<QFileDialog>
#include<QTextEdit>
#include<QString>
#include<QTextBrowser>
#include<QMenu>
#include<QMenuBar>
#include<QAction>
#include<QProcess>
#include<QGridLayout>
#include<QFileDialog>
#include<QComboBox>
#include "switchbutton.h"
#include<cstring>
#include<string>
#include<cstdlib>
#include<cstdio>
class vimrc_helper : public QMainWindow
{
	Q_OBJECT

public:
	vimrc_helper(QWidget *parent = nullptr);
	char file_path[10010];
	QAction *open_file_action;
	QLabel *description_syntax,*description_status,*description_mouse,*description_cursorline,*description_match,*description_autoread,*description_tabstop;
	QGridLayout *layout;
	SwitchButton *syntax_on,*status_on,*mouse_on,*cursorline_on,*match_on,*autoread_on;
	QComboBox *tabstop;
	void main_init();
	void open_file();
	void path_view();
	Ui::vimrc_helperClass ui;

private:
};
