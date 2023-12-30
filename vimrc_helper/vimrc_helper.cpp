#include "vimrc_helper.h"
vimrc_helper::vimrc_helper(QWidget *parent):QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("Vimrc Helper");
	this->setFont(QFont("Fira Code, Microsoft Yahei",11));
	//this->setWindowIcon(QIcon(":/vimrc_helper/icons/vimrc_helper_icon.png"));
	main_layout=new QGridLayout();
	main_init();
	open_file();
	this->resize(520,250);
	this->setMinimumSize(520,250);	
	ui.centralWidget->setLayout(main_layout);
}
void vimrc_helper::Action_init()
{
	open_file_action=new QAction("打开vimrc文件",nullptr);
	open_file_action->setShortcut(tr("Ctrl+O"));
	edit_plug_action=new QAction("编辑插件",nullptr);
	edit_plug_action->setShortcut(tr("Ctrl+P"));
	save_file_action=new QAction("保存文件",nullptr);
	save_file_action->setShortcut(tr("Ctrl+S"));
	connect(open_file_action,&QAction::triggered,this,&vimrc_helper::open_file);
	connect(edit_plug_action,&QAction::triggered,this,&vimrc_helper::plug_edit);
	connect(save_file_action,&QAction::triggered,this,&vimrc_helper::save_file);
	file_menu->addAction(open_file_action);
	file_menu->addAction(save_file_action);
	edit_menu->addAction(edit_plug_action);
}
void vimrc_helper::SwitchButton_init()
{
	syntax_on=new SwitchButton(nullptr);
	mouse_on=new SwitchButton(nullptr);
	cursorline_on=new SwitchButton(nullptr);
	match_on=new SwitchButton(nullptr);
	autoread_on=new SwitchButton(nullptr);
	noswapfile_on=new SwitchButton(nullptr);
	expandtab_on=new SwitchButton(nullptr);
	autochdir_on=new SwitchButton(nullptr);
	no_undo_on=new SwitchButton(nullptr);
	syntax_on->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
	syntax_on->setMaximumSize(50,25);
	mouse_on->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
	mouse_on->setMaximumSize(50,25);
	cursorline_on->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
	cursorline_on->setMaximumSize(50,25);
	match_on->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
	match_on->setMaximumSize(50,25);
	autoread_on->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
	autoread_on->setMaximumSize(50,25);
	noswapfile_on->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
	noswapfile_on->setMaximumSize(50,25);
	expandtab_on->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
	expandtab_on->setMaximumSize(50,25);
	autochdir_on->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
	autochdir_on->setMaximumSize(50,25);
	no_undo_on->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
	no_undo_on->setMaximumSize(50,25);
	description_syntax=new QLabel("语法高亮");
	description_mouse=new QLabel("兼容鼠标");
	description_cursorline=new QLabel("高亮当前行");
	description_match=new QLabel("高亮括号");
	description_autoread=new QLabel("自动读取更改");
	description_noswapfile=new QLabel("关闭SWAP文件");
	description_expandtab=new QLabel("空格缩进");
	description_autochdir=new QLabel("自动切换目录");
	description_no_undo=new QLabel("关闭撤销文件");
	main_layout->addWidget(description_syntax,0,0,1,1);
	main_layout->addWidget(syntax_on,0,1,1,1);
	main_layout->addWidget(description_noswapfile,0,2,1,1);
	main_layout->addWidget(noswapfile_on,0,3,1,1);
	main_layout->addWidget(description_mouse,0,4,1,1);
	main_layout->addWidget(mouse_on,0,5,1,1);
	main_layout->addWidget(description_cursorline,1,0,1,1);
	main_layout->addWidget(cursorline_on,1,1,1,1);
	main_layout->addWidget(description_match,1,2,1,1);
	main_layout->addWidget(match_on,1,3,1,1);
	main_layout->addWidget(description_autoread,1,4,1,1);
	main_layout->addWidget(autoread_on,1,5,1,1);
	main_layout->addWidget(description_expandtab,2,0,1,1);
	main_layout->addWidget(expandtab_on,2,1,1,1);
	main_layout->addWidget(description_autochdir,2,2,1,1);
	main_layout->addWidget(autochdir_on,2,3,1,1);
	main_layout->addWidget(description_no_undo,2,4,1,1);
	main_layout->addWidget(no_undo_on,2,5,1,1);
}
void vimrc_helper::ComboBox_init()
{
	line_number_combobox=new QComboBox(nullptr);
	line_number_combobox->setFont(QFont("Fira Code, Microsoft Yahei",9));
	line_number_combobox->addItem("相对行号");
	line_number_combobox->addItem("绝对行号");
	line_number_combobox->addItem("混合行号");
	description_number=new QLabel("行号设置");
	tabstop_combobox=new QComboBox(nullptr);
	tabstop_combobox->setFont(QFont("Fira Code, Microsoft Yahei",9));
	tabstop_combobox->addItem("2");
	tabstop_combobox->addItem("4");
	tabstop_combobox->addItem("6");
	tabstop_combobox->addItem("8");
	description_tabstop=new QLabel("缩进大小");
	main_layout->addWidget(description_number,3,0,1,1);
	main_layout->addWidget(line_number_combobox,3,1,1,1);
	main_layout->addWidget(description_tabstop,3,4,1,1);
	main_layout->addWidget(tabstop_combobox,3,5,1,1);
}
void vimrc_helper::Plug_init()
{
	start_plugin_button=new QPushButton("打开插件界面");
	connect(start_plugin_button,&QPushButton::clicked,this,&vimrc_helper::plug_edit);
	main_layout->addWidget(start_plugin_button,4,0,1,6);
	//插件编辑窗体初始化
	plug_layout=new QGridLayout();
	plugin_widget=new QWidget(nullptr);
	plugin_widget->setWindowTitle("框中每一行输入一个插件的地址，格式：Github用户名/仓库名");
	plugin_editor=new QPlainTextEdit(plugin_widget);
	plugin_editor->setFont(QFont("Fira Code"));
	plug_layout->addWidget(plugin_editor,0,0,3,4);
	plug_layout->setHorizontalSpacing(10);
	plug_layout->setVerticalSpacing(10);
	plug_layout->setContentsMargins(10,10,10,10);
	plug_layout->setColumnStretch(0,1);
	plug_layout->setColumnStretch(1,1);
	plug_layout->setColumnStretch(2,1);
	plug_layout->setColumnStretch(3,1);
	plug_layout->setRowStretch(0,1);
	plug_layout->setRowStretch(1,1);
	plug_layout->setRowStretch(2,1);
	plugin_widget->setLayout(plug_layout);
	plugin_widget->resize(520,250);
	plugin_widget->setMinimumSize(520,250);
}
void vimrc_helper::main_init()
{
	//菜单栏初始化
	file_menu=this->menuBar()->addMenu(tr("文件"));
	edit_menu=this->menuBar()->addMenu(tr("编辑"));
	Action_init();
	this->menuBar()->addSeparator();
	this->menuBar()->show();
	//界面初始化
	SwitchButton_init();
	ComboBox_init();
	Plug_init();
	main_layout->setHorizontalSpacing(10);
	main_layout->setVerticalSpacing(10);
	main_layout->setContentsMargins(10,10,10,10);
	main_layout->setColumnStretch(0,1);
	main_layout->setColumnStretch(1,1);
	main_layout->setColumnStretch(2,1);
	main_layout->setColumnStretch(3,1);
	main_layout->setColumnStretch(4,1);
	main_layout->setColumnStretch(5,1);
	main_layout->setRowStretch(0,1);
	main_layout->setRowStretch(1,1);
	main_layout->setRowStretch(2,1);
	main_layout->setRowStretch(3,1);
	main_layout->setRowStretch(4,1);
}
int vimrc_helper::str_find(const char *a,const char *b,int *nxt)
{
	memset(nxt,0,sizeof(nxt));
	int len1=strlen(a+1),len2=strlen(b+1);
	int j=0;
	for(int i=2;i<=len2;i++)
	{
		while(j&&b[i]!=b[j+1]) j=nxt[j];
		if(b[i]==b[j+1]) j++;
		nxt[i]=j;
	}
	j=0;
	for(int i=1;i<=len1;i++)
	{
		while(j&&a[i]!=b[j+1]) j=nxt[j];
		if(a[i]==b[j+1]) j++;
		if(j==len2) return i-len2+1;
	}
	return -1;
}
void vimrc_helper::open_file()
{
	total_row=0;
	total_plugin=0;
	memset(file_path,0,sizeof(file_path));
	#if _WIN32
	QString input_path=QFileDialog::getOpenFileName(nullptr,"打开vimrc文件","C:/","_vimrc");
	#else
	QString input_path=QFileDialog::getOpenFileName(nullptr,"打开vimrc文件","~/",".vimrc");
	#endif
	if(input_path.size()<5) return;
	for(int i=0;i<input_path.size();i++)
		file_path[i]=input_path[i].toLatin1();
	path_view();
	freopen(file_path,"r",stdin);
	file_reading();
}
void vimrc_helper::file_reading()
{
	while(gets_s(str_tmp_1+1,100000))
	{
		int num=0;
		if(str_find(str_tmp_1,pre_command[0],char_compare_nxt)!=-1) syntax_on->checked=1;
		else if(str_find(str_tmp_1,pre_command[1],char_compare_nxt)!=-1) noswapfile_on->checked=1;
		else if(str_find(str_tmp_1,pre_command[2],char_compare_nxt)!=-1) mouse_on->checked=1;
		else if(str_find(str_tmp_1,pre_command[3],char_compare_nxt)!=-1) cursorline_on->checked=1;
		else if(str_find(str_tmp_1,pre_command[4],char_compare_nxt)!=-1) match_on->checked=1;
		else if(str_find(str_tmp_1,pre_command[5],char_compare_nxt)!=-1) autoread_on->checked=1;
		else if(str_find(str_tmp_1,pre_command[6],char_compare_nxt)!=-1) expandtab_on->checked=1;
		else if(str_find(str_tmp_1,pre_command[7],char_compare_nxt)!=-1) autochdir_on->checked=1;
		else if(str_find(str_tmp_1,pre_command[8],char_compare_nxt)!=-1) no_undo_on->checked=1;
		else if(str_find(str_tmp_1,pre_command[9],char_compare_nxt)!=-1) line_number_combobox->setCurrentIndex(0);
		else if(str_find(str_tmp_1,pre_command[10],char_compare_nxt)!=-1)
		{
			line_number_combobox->setCurrentIndex(1);
			if(str_find(str_tmp_1,pre_command[11],char_compare_nxt)!=-1) line_number_combobox->setCurrentIndex(2);
		}
		else if(str_find(str_tmp_1,pre_command[11],char_compare_nxt)!=-1) line_number_combobox->setCurrentIndex(2);
		else if(str_find(str_tmp_1,pre_command[12],char_compare_nxt)!=-1)
		{
			num=0;
			for(auto k:str_tmp_1)
				if(k>='0'&&k<='9')
					num=num*10+k-'0';
			tabstop=num;
			tabstop_combobox->setCurrentIndex(1);
			switch(tabstop)
			{
				case 2:
				{
					tabstop_combobox->setCurrentIndex(0);
					break;
				}
				case 4:
				{
					tabstop_combobox->setCurrentIndex(1);
					break;
				}
				case 6:
				{
					tabstop_combobox->setCurrentIndex(2);
					break;
				}
				case 8:
				{
					tabstop_combobox->setCurrentIndex(3);
					break;
				}
				default:break;
			}
		}
		else if(str_find(str_tmp_1," call plug#begin('~/.vim/plugged')",char_compare_nxt)!=-1)
		{
			QString plugins="";
			while(1)
			{
				gets_s(str_tmp_1+1,100000);
				int num1=strlen(str_tmp_1+1);
				if(str_find(str_tmp_1," call plug#end()",char_compare_nxt)!=-1) break;
				total_plugin++;
				int num2=0;
				memset(str_tmp_2,0,sizeof(str_tmp_2));
				if(num1<2) continue;
				for(int j=1;j<=num1;j++)
					if(str_tmp_1[j]=='\'')
					{
						for(int k=j+1;str_tmp_1[k]!='\''&&k<num1;k++)
							str_tmp_2[++num2]=str_tmp_1[k];
						break;
					}
				plugins+=(str_tmp_2+1);
				plugins+='\n';
			}
			plugin_editor->setPlainText(plugins);
		}
	}
	fclose(stdin);
}
void vimrc_helper::path_view()
{
	this->setWindowTitle(QString(file_path)+" - Vimrc Helper");
}
void vimrc_helper::plug_edit()
{
	plugin_widget->show();
}
void vimrc_helper::save_file()
{
	//FILE *must_input=fopen("r","must_input_vimrc_part.txt");
	freopen(file_path,"w",stdout);
	//char tmp_char;
	/*while(sscanf(must_input,"%c",&tmp_char)) printf("%c",tmp_char);*/
	printf("%s\n",must_input);
	if(syntax_on->checked==1) printf("%s\n",pre_command[0]);
	if(noswapfile_on->checked==1) printf("%s\n",pre_command[1]);
	if(mouse_on->checked==1) printf("%s\n",pre_command[2]);
	if(cursorline_on->checked==1) printf("%s\n",pre_command[3]);
	if(match_on->checked==1) printf("%s\n",pre_command[4]);
	if(autoread_on->checked==1) printf("%s\n",pre_command[5]);
	if(expandtab_on->checked==1) printf("%s\n",pre_command[6]);
	if(autochdir_on->checked==1) printf("%s\n",pre_command[7]);
	if(no_undo_on->checked==1) printf("%s\n",pre_command[8]);
	switch(line_number_combobox->currentIndex())
	{
		case 0:printf("%s\n",pre_command[9]);break;
		case 1:printf("%s\n",pre_command[10]);break;
		case 2:printf("%s\n",pre_command[11]);break;
		default:break;
	}
	printf(" set tabstop=");
	switch(tabstop_combobox->currentIndex())
	{
		case 0:printf("2\n");break;
		case 1:printf("4\n");break;
		case 2:printf("6\n");break;
		case 3:printf("8\n");break;
		default:break;
	}
	printf(" call plug#begin('~/.vim/plugged')\n");
	QString tmp=plugin_editor->toPlainText();
	memset(str_tmp_1,0,sizeof(str_tmp_1));
	int num=0;
	for(auto i:tmp)
	{
		char tmp_char=i.toLatin1();
		if((tmp_char>='A'&&tmp_char<='Z')||(tmp_char>='a'&&tmp_char<='z')||(tmp_char>='0'&&tmp_char<='9')||tmp_char=='\''||tmp_char=='/'||tmp_char=='.'||tmp_char=='-'||tmp_char=='_')
			str_tmp_1[++num]=tmp_char;
		else
		{
			printf("Plug \'");
			printf("%s",str_tmp_1+1);
			printf("\'\n");
			memset(str_tmp_1,0,sizeof(str_tmp_1));
			num=0;
		}
	}
	if(num>0)
	{
		printf("Plug \'");
		printf("%s",str_tmp_1+1);
		printf("\'\n");
		memset(str_tmp_1,0,sizeof(str_tmp_1));
		num=0;
	}
	printf(" call plug#end()\n");
	fclose(stdout);
}