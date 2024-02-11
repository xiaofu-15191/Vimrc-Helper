#pragma once
#include<QtWidgets/QMainWindow>
#include<QAction>
#include<QWidget>
#include<QFileDialog>
#include<QChar>
#include<QFile>
#include<QMessageBox>
#include<QCloseEvent>
#include<QPushButton>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include "ui_Mainwindow.h"
const char pre_command[100][100]={"syntax on","set noswapfile","set mouse=a","set cursorline","set showmatch","set autoread","set expandtab","set autochdir","set noundofile","set relativenumber","set number","set number relativenumber","set tabstop=","set vb","set noeb"};
const char vimrc_file_preset[150]={R"(set nocompatible
filetype plugin on
source $VIMRUNTIME/vimrc_example.vim
source $VIMRUNTIME/mswin.vim)"};
const char other_preset[3000]={R"(
set laststatus=2
set statusline=\ %<%F[%1*%M%*%n%R%H]%=\ %y\ %0(%{&fileformat}\ [%{(&fenc==\"\"?&enc:&fenc).(&bomb?\",BOM\":\"\")}]\ %c:%l/%L%
map <C-N> :tabnew<CR>
map <C-W> :tabclose<CR>
map <C-S> :w<CR>
function! s:moveup_line()
	let cur_pos = getpos('.')
	if cur_pos[1] == 1
		return
	endif
	let tgt_line = cur_pos[1] - 1
	let tmp = getline(tgt_line)
	call setline(tgt_line,getline(cur_pos[1]))
	call setline(cur_pos[1],tmp)
	let cur_pos[1] -= 1
	call setpos('.',cur_pos)
endfunction

function! s:movedown_line()
	let cur_pos = getpos('.')
	if cur_pos[1] == line('$')
		return
	endif
	let tgt_line = cur_pos[1] + 1
	let tmp = getline(tgt_line)
	call setline(tgt_line,getline(cur_pos[1]))
	call setline(cur_pos[1],tmp)
	let cur_pos[1] += 1
	call setpos('.',cur_pos)
endfunction

function! s:moveup_multlines() range
	let start_mark = getpos("'<")
	let end_mark = getpos("'>")
	if start_mark[1] == 1
		return
	endif
	let save_curpos = getpos('.')
	let buffer_lines = getline(start_mark[1],end_mark[1])
	call add(buffer_lines, getline(start_mark[1] - 1))
	call setline(start_mark[1]-1,buffer_lines)
	let start_mark[1] -= 1
	let end_mark[1] -= 1
	let save_curpos[1] -= 1
	call setpos("'<",start_mark)
	call setpos("'>",end_mark)
	call setpos('.',save_curpos)
endfunction

function! s:movedown_multlines() range
	let start_mark = getpos("'<")
	let end_mark = getpos("'>")
	if end_mark[1] == line('$')
		return
	endif
	let save_curpos = getpos('.')
	let buffer_lines = [getline(end_mark[1] + 1)]
	call extend(buffer_lines, getline(start_mark[1],end_mark[1]) )
	call setline(start_mark[1],buffer_lines)
	let start_mark[1] += 1
	let end_mark[1] += 1
	let save_curpos[1] += 1
		call setpos("'<",start_mark)
	call setpos("'>",end_mark)
	call setpos('.',save_curpos)
endfunction

noremap <silent> <C-k> :call <SID>moveup_line()<CR>
noremap <silent> <C-j> :call <SID>movedown_line()<CR>
inoremap <silent> <C-k> <ESC>:call <SID>moveup_line()<CR>a
inoremap <silent> <C-j> <ESC>:call <SID>movedown_line()<CR>a
vnoremap <silent> <C-k> :call <SID>moveup_multlines()<CR>gv 
vnoremap <silent> <C-j> :call <SID>movedown_multlines()<CR>gv
)"};
class Mainwindow: public QMainWindow
{
	Q_OBJECT

public:
	Mainwindow(QWidget *parent=nullptr);
	~Mainwindow();
	int total_row=0,char_compare_nxt[100010],tabstop,total_plugin=0,saved=1,origin[10],total_shortcuts=0;
	QString file_path,str_tmp_1;
	QByteArray str_tmp_2;
	QFile *vimrc_file;
	QMessageBox close_message;
	QPushButton *close_message_save,*close_message_unsave,*close_message_cancel;
	void init();
	void open_file();
	void file_reading();
	void path_view();
	void save_file();
	void closeEvent(QCloseEvent *event);
	void file_unsave();
	//int str_find(const char *,const char *,int *);
public slots:
	void main_message();
	void plug_open_message();
	void shortcut_open_message();
	void shortcut_edit_message();
	void shortcut_unedit_message();
private:
	Ui::MainwindowClass ui;
};
