#pragma once
#pragma execution_character_set("utf-8")
#pragma warning(disable:6031)
#pragma warning(disable:6262)
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
#include<QPlainTextEdit>
#include<QString>
#include<QTextBrowser>
#include<QMenu>
#include<QMenuBar>
#include<QAction>
#include<QProcess>
#include<QGridLayout>
#include<QFileDialog>
#include<QComboBox>
#include<QSizePolicy>
#include<QLine>
#include<QMessageBox>
#include<QCheckBox>
#include<cstring>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<vector>
const char pre_command[100][100]={"syntax on","set noswapfile","set mouse=a","set cursorline","set showmatch","set autoread","set expandtab","set autochdir","set noundofile","set relativenumber","set number","set number relativenumber","set tabstop=","set vb","set vb t_vb="};
const char must_input[2000]={R"(set nocompatible
filetype plugin on

" Vim with all enhancements
source $VIMRUNTIME/vimrc_example.vim

" Remap a few keys for Windows behavior
source $VIMRUNTIME/mswin.vim

" Use the internal diff if available.
" Otherwise use the special 'diffexpr' for Windows.
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
class vimrc_helper : public QMainWindow
{
	Q_OBJECT

public:
	vimrc_helper(QWidget *parent = nullptr);
	FILE *FILE_IN;
	int total_row=0,char_compare_nxt[100010],tabstop,total_plugin=0,saved=1,origin[10];
	char file_path[10010],str_tmp_1[100010],str_tmp_2[100010];
	std::vector<char>file[10010];
	QWidget *plugin_widget;
	QAction *open_file_action,*edit_plug_action,*save_file_action;
	QLabel *description_syntax,*description_mouse,*description_cursorline,*description_match,*description_autoread,*description_tabstop,*description_noswapfile,*description_expandtab,*description_autochdir,*description_no_undo,*description_number,*description_errorbells;
	QGridLayout *main_layout,*plug_layout;
	QCheckBox *syntax_on,*mouse_on,*cursorline_on,*match_on,*autoread_on,*noswapfile_on,*expandtab_on,*autochdir_on,*no_undo_on;
	QPushButton *start_plugin_button;
	QComboBox *tabstop_combobox,*line_number_combobox,*errorbells_combobox;
	QMenu *file_menu,*edit_menu;
	QPlainTextEdit *plugin_editor;
	QMessageBox close_message;
	void closeEvent(QCloseEvent *event);
	void file_unsave();
	void Action_init();
	void SwitchButton_init();
	void ComboBox_init();
	void main_init();
	void open_file();
	void path_view();
	void file_reading();
	void save_file();
	void Plug_init();
	void plug_edit();
	int str_find(const char *,const char *,int *);
    Ui::vimrc_helper ui;

private:
};
