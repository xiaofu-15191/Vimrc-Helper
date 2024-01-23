#pragma once
#include<QtWidgets/QMainWindow>
#include<QAction>
#include<QWidget>
#include<QFileDialog>
#include<QChar>
#include<QFile>
#include<QMessageBox>
#include<QCloseEvent>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include "plug_widget.h"
#include "ui_Mainwindow.h"
const char pre_command[100][100]={"syntax on","set noswapfile","set mouse=a","set cursorline","set showmatch","set autoread","set expandtab","set autochdir","set noundofile","set relativenumber","set number","set number relativenumber","set tabstop=","set vb","set noeb"};
const char must_input[2000]={R"(set nocompatible
filetype plugin on
source $VIMRUNTIME/vimrc_example.vim
source $VIMRUNTIME/mswin.vim
if &diffopt !~# 'internal'
  set diffexpr=MyDiff()
endif
function MyDiff()
  let opt = '-a --binary '
  if &diffopt =~ 'icase' | let opt = opt . '-i ' | endif
  if &diffopt =~ 'iwhite' | let opt = opt . '-b ' | endif
  let arg1 = v:fname_in
  if arg1 =~ ' ' | let arg1 = '"' . arg1 . '"' | endif
  let arg1 = substitute(arg1, '!', '\!', 'g')
  let arg2 = v:fname_new
  if arg2 =~ ' ' | let arg2 = '"' . arg2 . '"' | endif
  let arg2 = substitute(arg2, '!', '\!', 'g')
  let arg3 = v:fname_out
  if arg3 =~ ' ' | let arg3 = '"' . arg3 . '"' | endif
  let arg3 = substitute(arg3, '!', '\!', 'g')
  if $VIMRUNTIME =~ ' '
	if &sh =~ '\<cmd'
	  if empty(&shellxquote)
		let l:shxq_sav = ''
		set shellxquote&
	  endif
	  let cmd = '"' . $VIMRUNTIME . '\diff"'
	else
	  let cmd = substitute($VIMRUNTIME, ' ', '" ', '') . '\diff"'
	endif
  else
	let cmd = $VIMRUNTIME . '\diff'
  endif
  let cmd = substitute(cmd, '!', '\!', 'g')
  silent execute '!' . cmd . ' ' . opt . arg1 . ' ' . arg2 . ' > ' . arg3
  if exists('l:shxq_sav')
	let &shellxquote=l:shxq_sav
  endif
endfunction)"};
class Mainwindow: public QMainWindow
{
	Q_OBJECT

public:
	Mainwindow(QWidget *parent=nullptr);
	~Mainwindow();
	int total_row=0,char_compare_nxt[100010],tabstop,total_plugin=0,saved=1,origin[10],total_shortcuts=0;
	//QChar file_path[10010],str_tmp_1[100010],str_tmp_2[100010];
	QString file_path,str_tmp_1,str_tmp_2;
	QFile *vimrc_file;
	QMessageBox close_message;
	void init();
	void open_file();
	void file_reading();
	void path_view();
	void save_file();
	void closeEvent(QCloseEvent *event);
	void file_unsave();
	//int str_find(const char *,const char *,int *);
public slots:
	void plug_open_message();
private:
	Ui::MainwindowClass ui;
	plug_widget *plug_edit_window;
};
