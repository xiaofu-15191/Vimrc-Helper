#pragma warning(disable:26495)
#pragma warning(disable:26813)
#pragma warning(disable:26498)
#pragma warning(disable:6031)
#pragma warning(disable:26498)
#include "Mainwindow.h"
Mainwindow::Mainwindow(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);
	init();
}
Mainwindow::~Mainwindow()
{
}
/*int Mainwindow::str_find(const char *a,const char *b,int *nxt)
{
	memset(nxt,0,sizeof(nxt));
	int len1=strlen(a),len2=strlen(b);
	int j=0;
	for(int i=1;i<len2;i++)
	{
		while(j&&b[i]!=b[j]) j=nxt[j];
		if(b[i]==b[j]) nxt[i+1]=++j;
		else nxt[i+1]=0;
	}
	j=0;
	for(int i=0;i<len1;i++)
	{
		while(j&&a[i]!=b[j]) j=nxt[j];
		if(a[i]==b[j]) j++;
		if(j==len2) return i-len2+1;
	}
	return -1;
}*/
/*char *gets_s(char *str,int num)
{
	if(fgets(str,num,stdin)!=0)
	{
		size_t len=strlen(str);
		if(len>0&&str[len-1]=='\n') str[len-1]=' ';
		return str;
	}
	return 0;
}*/
void Mainwindow::plug_open_message()
{
	plug_edit_window->show();
}
void Mainwindow::init()
{
	file_path.clear();
	ui.centralWidget->setWindowIcon(QIcon(":/Vimrc-Helper/icons/vimrc_helper_icon.png"));
	plug_edit_window=new plug_widget(this);
	plug_edit_window->setWindowIcon(QIcon(":/Vimrc-Helper/icons/vimrc_helper_icon.png"));
	connect(ui.open_file_action,&QAction::triggered,this,&Mainwindow::open_file);
	connect(ui.save_file_action,&QAction::triggered,this,&Mainwindow::save_file);
	connect(ui.start_plugin_button,SIGNAL(clicked()),this,SLOT(plug_open_message()));
}
void Mainwindow::open_file()
{
	total_row=0;
	total_plugin=0;
	file_path.clear();
	#if _WIN32
	file_path=QFileDialog::getOpenFileName(nullptr,"打开vimrc文件","C:/","_vimrc;;任意文件 (*.*)");
	#else
	file_path=QFileDialog::getOpenFileName(nullptr,"打开vimrc文件","/home/",".vimrc;;任意文件 (*.*)");
	#endif
	if(file_path.size()<5) return;
	path_view();
	vimrc_file=new QFile(file_path);
	vimrc_file->open(QFile::ReadOnly);
	if(!vimrc_file->exists()) return;
	file_reading();
}
void Mainwindow::file_reading()
{
	memset(origin,0,sizeof(origin));
	while(true)
	{
		QByteArray tmp=vimrc_file->readLine();
		if(tmp.isEmpty()) break;
		str_tmp_1=tmp;
		int num=0;
		if(str_tmp_1.contains(QString(pre_command[0]))) ui.syntax_on->setChecked(1),origin[0]=1;
		else if(str_tmp_1.contains(QString(pre_command[1]))) ui.noswapfile_on->setChecked(1),origin[1]=1;
		else if(str_tmp_1.contains(QString(pre_command[2]))) ui.mouse_on->setChecked(1),origin[2]=1;
		else if(str_tmp_1.contains(QString(pre_command[3]))) ui.cursorline_on->setChecked(1),origin[3]=1;
		else if(str_tmp_1.contains(QString(pre_command[4]))) ui.match_on->setChecked(1),origin[4]=1;
		else if(str_tmp_1.contains(QString(pre_command[5]))) ui.autoread_on->setChecked(1),origin[5]=1;
		else if(str_tmp_1.contains(QString(pre_command[6]))) ui.expandtab_on->setChecked(1),origin[6]=1;
		else if(str_tmp_1.contains(QString(pre_command[7]))) ui.autochdir_on->setChecked(1),origin[7]=1;
		else if(str_tmp_1.contains(QString(pre_command[8]))) ui.no_undo_file_on->setChecked(1),origin[8]=1;
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
			/*Ui_plugin_widget::plugin_editor->setPlainText(plugins);*/
			plug_edit_window->ui.plug_editor->setPlainText(plugins);
		}
		else if(str_tmp_1.contains(QString(pre_command[13])))
		{
			ui.errorbells_combobox->setCurrentIndex(1);
			if(str_tmp_1.contains(QString(pre_command[14]))) ui.errorbells_combobox->setCurrentIndex(2);
		}
	}
	saved=1;
	delete vimrc_file;
}
void Mainwindow::path_view()
{
	Mainwindow::setWindowTitle(file_path+" - Vimrc-Helper");
}
void Mainwindow::save_file()
{
	if(file_path.size()<3)
	{
		#if _WIN32
		file_path=QFileDialog::getExistingDirectory(nullptr,"保存vimrc文件","C:/");
		if(file_path[file_path.size()-1]!='/') file_path+='/';
		file_path+="_vimrc";
		#else
		file_path=QFileDialog::getExistingDirectory(nullptr,"保存vimrc文件","~/");
		if(file_path[file_path.size()-1]!='/') file_path+='/';
		file_path+=".vimrc";
		#endif
		if(file_path.size()<3) return;
		path_view();
	}
	saved=1;
	//FILE *must_input=fopen("r","must_input_vimrc_part.txt");
	vimrc_file=new QFile(file_path);
	vimrc_file->open(QFile::WriteOnly);
	//char i;
	/*while(sscanf(must_input,"%c",&i)) printf("%c",i);*/
	vimrc_file->write(must_input);
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
	QString tmp=plug_edit_window->ui.plug_editor->toPlainText();
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
	delete vimrc_file;
}
void Mainwindow::closeEvent(QCloseEvent *event)
{
	if(saved) event->accept();
	else
	{
		int result=close_message.exec();
		switch(result)
		{
			case QMessageBox::Save:
			{
				Mainwindow::save_file();
				break;
			}
			case QMessageBox::Discard:
			{
				event->accept();
				break;
			}
			case QMessageBox::Cancel:
			{
				event->ignore();
				break;
			}
			default:event->accept();
		}
	}
}
void Mainwindow::file_unsave()
{
	saved=0;
}