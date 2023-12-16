#pragma once
#pragma execution_character_set("utf-8")
#pragma warning(disable:6031)
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
#include<qsizepolicy.h>
#include "switchbutton.h"
#include<cstring>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<vector>
const char pre_command[100][100]={" syntax on"," set noswapfile"," set mouse=a"," set cursorline"," set showmatch"," set autoread"," set expandtab"," set autochdir"};
class vimrc_helper : public QMainWindow
{
	Q_OBJECT

public:
	vimrc_helper(QWidget *parent = nullptr);
	FILE *FILE_IN;
	int total_row=0,char_compare_nxt[100010];
	char file_path[10010],str_tmp[100010];
	std::vector<char>file[10010];
	QAction *open_file_action;
	QLabel *description_syntax,*description_mouse,*description_cursorline,*description_match,*description_autoread,*description_tabstop,*description_noswapfile,*description_expandtab,*description_autochdir;
	QGridLayout *layout;
	SwitchButton *syntax_on,*mouse_on,*cursorline_on,*match_on,*autoread_on,*noswapfile_on,*expandtab_on,*autochdir_on;
	QComboBox *tabstop;
	void main_init();
	void open_file();
	void path_view();
	void file_reading();
	int str_find(const char *,const char *,int *);
	Ui::vimrc_helperClass ui;

private:
};
