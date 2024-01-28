#include "Mainwindow.h"
Mainwindow::Mainwindow(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);
	init();
}
Mainwindow::~Mainwindow()
{
}
void Mainwindow::main_message()
{
	ui.stackedWidget->setCurrentIndex(0);
}
void Mainwindow::plug_open_message()
{
	ui.stackedWidget->setCurrentIndex(1);
}
void Mainwindow::shortcut_open_message()
{
	ui.stackedWidget->setCurrentIndex(2);
}
void Mainwindow::shortcut_edit_message()
{
	ui.other_editor->setReadOnly(0);
}
void Mainwindow::shortcut_unedit_message()
{
	ui.other_editor->setReadOnly(1);
}
void Mainwindow::init()
{
	file_path.clear();
	main_message();
	ui.plug_editor->setPlaceholderText("使用vim-plug管理插件，请在其中输入插件的Github仓库地址。");
	ui.preset->setChecked(1);
	ui.other_editor->setPlainText(other_preset);
	ui.other_editor->setReadOnly(1);
	//close message init
	close_message.setText("文件已修改。是否保存？");
	close_message_save=close_message.addButton("保存",QMessageBox::AcceptRole);
	close_message_unsave=close_message.addButton("不保存",QMessageBox::RejectRole);
	close_message_cancel=close_message.addButton("取消",QMessageBox::NoRole);
	//action init
	connect(ui.open_file_action,&QAction::triggered,this,&Mainwindow::open_file);
	connect(ui.save_file_action,&QAction::triggered,this,&Mainwindow::save_file);
	connect(ui.return_main_action,&QAction::triggered,this,&Mainwindow::main_message);
	connect(ui.plugin_edit_action,&QAction::triggered,this,&Mainwindow::plug_open_message);
	connect(ui.shortcut_edit_action,&QAction::triggered,this,&Mainwindow::shortcut_open_message);
	//button init
	connect(ui.general_setting_button,SIGNAL(clicked()),this,SLOT(main_message()));
	connect(ui.plug_edit_button,SIGNAL(clicked()),this,SLOT(plug_open_message()));
	connect(ui.shortcut_edit_button,SIGNAL(clicked()),this,SLOT(shortcut_open_message()));
	connect(ui.custom,SIGNAL(clicked()),this,SLOT(shortcut_edit_message()));
	connect(ui.preset,SIGNAL(clicked()),this,SLOT(shortcut_unedit_message()));
	//unsave init
	connect(ui.autochdir_on,&QCheckBox::clicked,this,&Mainwindow::file_unsave);
	connect(ui.autoread_on,&QCheckBox::clicked,this,&Mainwindow::file_unsave);
	connect(ui.cursorline_on,&QCheckBox::clicked,this,&Mainwindow::file_unsave);
	connect(ui.expandtab_on,&QCheckBox::clicked,this,&Mainwindow::file_unsave);
	connect(ui.match_on,&QCheckBox::clicked,this,&Mainwindow::file_unsave);
	connect(ui.mouse_on,&QCheckBox::clicked,this,&Mainwindow::file_unsave);
	connect(ui.noswapfile_on,&QCheckBox::clicked,this,&Mainwindow::file_unsave);
	connect(ui.no_undo_file_on,&QCheckBox::clicked,this,&Mainwindow::file_unsave);
	connect(ui.syntax_on,&QCheckBox::clicked,this,&Mainwindow::file_unsave);
	connect(ui.line_number_combobox,&QComboBox::currentIndexChanged,this,&Mainwindow::file_unsave);
	connect(ui.errorbells_combobox,&QComboBox::currentIndexChanged,this,&Mainwindow::file_unsave);
	connect(ui.tab_stop_combobox,&QComboBox::currentIndexChanged,this,&Mainwindow::file_unsave);
	connect(ui.plug_editor,&QPlainTextEdit::textChanged,this,&Mainwindow::file_unsave);
	connect(ui.other_editor,&QPlainTextEdit::textChanged,this,&Mainwindow::file_unsave);
}
void Mainwindow::open_file()
{
	total_row=0;
	total_plugin=0;
	file_path.clear();
	#if _WIN32
	file_path=QFileDialog::getOpenFileName(nullptr,"打开vimrc文件","C:/",".vimrc;;任意文件 (*.*)");
	#else
	file_path=QFileDialog::getOpenFileName(nullptr,"打开vimrc文件","/home/",".vimrc;;任意文件 (*.*)");
	#endif
	if(file_path.size()<5) return;
	vimrc_file=new QFile(file_path);
	vimrc_file->open(QFile::ReadOnly);
	if(!vimrc_file->exists()) return;
	file_reading();
	path_view();
}
void Mainwindow::file_reading()
{
	QString tmp_other="";
	while(true)
	{
		QByteArray tmp=vimrc_file->readLine();
		if(tmp.isEmpty()) break;
		str_tmp_1=tmp;
		int num=0;
		if(str_tmp_1.contains(QString(pre_command[0]))) ui.syntax_on->setChecked(1);
		else if(str_tmp_1.contains(QString(pre_command[1]))) ui.noswapfile_on->setChecked(1);
		else if(str_tmp_1.contains(QString(pre_command[2]))) ui.mouse_on->setChecked(1);
		else if(str_tmp_1.contains(QString(pre_command[3]))) ui.cursorline_on->setChecked(1);
		else if(str_tmp_1.contains(QString(pre_command[4]))) ui.match_on->setChecked(1);
		else if(str_tmp_1.contains(QString(pre_command[5]))) ui.autoread_on->setChecked(1);
		else if(str_tmp_1.contains(QString(pre_command[6]))) ui.expandtab_on->setChecked(1);
		else if(str_tmp_1.contains(QString(pre_command[7]))) ui.autochdir_on->setChecked(1);
		else if(str_tmp_1.contains(QString(pre_command[8]))) ui.no_undo_file_on->setChecked(1);
		else if(str_tmp_1.contains(QString(pre_command[9]))) ui.line_number_combobox->setCurrentIndex(0);
		else if(str_tmp_1.contains(QString(pre_command[10])))
		{
			ui.line_number_combobox->setCurrentIndex(1);
			if(str_tmp_1.contains(QString(pre_command[11]))) ui.line_number_combobox->setCurrentIndex(2);
		}
		else if(str_tmp_1.contains(QString(pre_command[11]))) ui.line_number_combobox->setCurrentIndex(2);
		else if(str_tmp_1.contains(QString(pre_command[12])))
		{
			num=0;
			for(auto k:str_tmp_1)
				if(k>='0'&&k<='9')
					num=num*10+(k.toLatin1()-'0');
			tabstop=num;
			ui.tab_stop_combobox->setCurrentIndex(1);
			switch(tabstop)
			{
				case 2:
				{
					ui.tab_stop_combobox->setCurrentIndex(0);
					break;
				}
				case 4:
				{
					ui.tab_stop_combobox->setCurrentIndex(1);
					break;
				}
				case 6:
				{
					ui.tab_stop_combobox->setCurrentIndex(2);
					break;
				}
				case 8:
				{
					ui.tab_stop_combobox->setCurrentIndex(3);
					break;
				}
				default:break;
			}
		}
		else if(str_tmp_1.contains("call plug#begin('~/.vim/plugged')"))
		{
			QString plugins="";
			while(1)
			{
				QByteArray tmp=vimrc_file->readLine();
				str_tmp_1=tmp;
				if(str_tmp_1.contains("call plug#end()")) break;
				total_plugin++;
				for(int j=0;j<str_tmp_1.size();j++)
					if(str_tmp_1[j]=='\'')
					{
						for(int k=j+1;str_tmp_1[k]!='\''&&k<str_tmp_1.size();k++) plugins+=str_tmp_1[k];
						break;
					}
				plugins+='\n';
			}
			ui.plug_editor->setPlainText(plugins);
		}
		else if(str_tmp_1.contains(QString(pre_command[13])))
		{
			ui.errorbells_combobox->setCurrentIndex(1);
			if(str_tmp_1.contains(QString(pre_command[14]))) ui.errorbells_combobox->setCurrentIndex(2);
		}
		else
			tmp_other+=str_tmp_1;
	}
	ui.other_editor->setPlainText(tmp_other);
	saved=1;
	delete vimrc_file;
}
void Mainwindow::path_view()
{
	Mainwindow::setWindowTitle(file_path+" - Vimrc-Helper");
}
void Mainwindow::save_file()
{
	if(file_path.size()<6)
	{
		#if _WIN32
		file_path=QFileDialog::getExistingDirectory(nullptr,"保存vimrc文件","C:/");
		#else
		file_path=QFileDialog::getExistingDirectory(nullptr,"保存vimrc文件","~/");
		#endif
		if(file_path.isEmpty()) return;
		if(file_path[file_path.size()-1]!='/') file_path+='/';
		file_path+=".vimrc";
		path_view();
	}
	saved=1;
	vimrc_file=new QFile(file_path);
	vimrc_file->open(QFile::WriteOnly);
	if(!vimrc_file->exists()) return;
	vimrc_file->write(vimrc_file_preset);
	vimrc_file->write("\n");
	if(ui.syntax_on->isChecked()==1)
		vimrc_file->write(pre_command[0]),vimrc_file->write("\n");
	if(ui.noswapfile_on->isChecked()==1)
		vimrc_file->write(pre_command[1]),vimrc_file->write("\n");
	if(ui.mouse_on->isChecked()==1)
		vimrc_file->write(pre_command[2]),vimrc_file->write("\n");
	if(ui.cursorline_on->isChecked()==1)
		vimrc_file->write(pre_command[3]),vimrc_file->write("\n");
	if(ui.match_on->isChecked()==1)
		vimrc_file->write(pre_command[4]),vimrc_file->write("\n");
	if(ui.autoread_on->isChecked()==1)
		vimrc_file->write(pre_command[5]),vimrc_file->write("\n");
	if(ui.expandtab_on->isChecked()==1)
		vimrc_file->write(pre_command[6]),vimrc_file->write("\n");
	if(ui.autochdir_on->isChecked()==1)
		vimrc_file->write(pre_command[7]),vimrc_file->write("\n");
	if(ui.no_undo_file_on->isChecked()==1)
		vimrc_file->write(pre_command[8]),vimrc_file->write("\n");
	switch(ui.line_number_combobox->currentIndex())
	{
		case 0:vimrc_file->write(pre_command[9]);vimrc_file->write("\n");break;
		case 1:vimrc_file->write(pre_command[10]);vimrc_file->write("\n");break;
		case 2:vimrc_file->write(pre_command[11]);vimrc_file->write("\n");break;
		default:break;
	}
	vimrc_file->write("set tabstop=");
	switch(ui.tab_stop_combobox->currentIndex())
	{
		case 0:vimrc_file->write("2\n");break;
		case 1:vimrc_file->write("4\n");break;
		case 2:vimrc_file->write("6\n");break;
		case 3:vimrc_file->write("8\n");break;
		default:break;
	}
	switch(ui.errorbells_combobox->currentIndex())
	{
		case 0:break;
		case 1:vimrc_file->write(pre_command[13]);vimrc_file->write("\n");break;
		case 2:vimrc_file->write(pre_command[14]);vimrc_file->write("\n");break;
		default:break;
	}
	QString tmp=ui.plug_editor->toPlainText();
	if(tmp.size()>5)
	{
		vimrc_file->write("call plug#begin('~/.vim/plugged')\n");
		str_tmp_1.clear();
		int num=0;
		for(auto i:tmp)
		{
			if((i>='A'&&i<='Z')||(i>='a'&&i<='z')||(i>='0'&&i<='9')||i=='\''||i=='/'||i=='.'||i=='-'||i=='_')
				str_tmp_1.push_back(i);
			else
			{
				if(str_tmp_1.size()<2)
				{
					str_tmp_1.clear();
					num=0;
					continue;
				}
				vimrc_file->write("Plug \'");
				vimrc_file->write(str_tmp_1.toUtf8());
				vimrc_file->write("\'\n");
				str_tmp_1.clear();
				num=0;
			}
		}
		if(num>0)
		{
			vimrc_file->write("Plug \'");
			vimrc_file->write(str_tmp_1.toUtf8());
			vimrc_file->write("\'\n");
			str_tmp_1.clear();
			num=0;
		}
		vimrc_file->write("call plug#end()\n");
	}
	tmp=ui.other_editor->toPlainText();
	if(tmp.size()>5)
	{
		str_tmp_2.clear();
		str_tmp_2=tmp.toLocal8Bit();
		vimrc_file->write(str_tmp_2);
	}
	delete vimrc_file;
	Mainwindow::setWindowTitle(file_path+" - Vimrc-Helper");
}
void Mainwindow::closeEvent(QCloseEvent *event)
{
	if(saved) event->accept();
	else
	{
		int result=close_message.exec();
		switch(result)
		{
			case QMessageBox::AcceptRole:
			{
				Mainwindow::save_file();
				if(!saved) event->ignore();
				break;
			}
			case QMessageBox::RejectRole:
			{
				event->accept();
				break;
			}
			case QMessageBox::NoRole:
			{
				event->ignore();
				break;
			}
			default:event->ignore();
		}
	}
}
void Mainwindow::file_unsave()
{
	saved=0;
	Mainwindow::setWindowTitle(file_path+" * - Vimrc-Helper");
}