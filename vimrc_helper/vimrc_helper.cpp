#include "vimrc_helper.h"
vimrc_helper::vimrc_helper(QWidget *parent):QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("Vimrc Helper");
	this->setFont(QFont("Fira Code, Microsoft Yahei",11));
	//this->setWindowIcon(QIcon(":/vimrc_helper/icons/vimrc_helper_icon.png"));
	layout=new QGridLayout();
	main_init();
	open_file();
	this->resize(450,200);
	this->setMinimumSize(450,200);
	ui.centralWidget->setLayout(layout);
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
	smartindent_on=new SwitchButton(nullptr);
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
	smartindent_on->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
	smartindent_on->setMaximumSize(50,25);
	description_syntax=new QLabel("语法高亮");
	description_mouse=new QLabel("兼容鼠标");
	description_cursorline=new QLabel("高亮行");
	description_match=new QLabel("高亮括号");
	description_autoread=new QLabel("读取更改");
	description_noswapfile=new QLabel("关闭SWAP");
	description_expandtab=new QLabel("空格缩进");
	description_autochdir=new QLabel("切换目录");
	description_smartindent=new QLabel("新行缩进");
	layout->addWidget(description_syntax,0,0,1,1);
	layout->addWidget(syntax_on,0,1,1,1);
	layout->addWidget(description_noswapfile,0,2,1,1);
	layout->addWidget(noswapfile_on,0,3,1,1);
	layout->addWidget(description_mouse,0,4,1,1);
	layout->addWidget(mouse_on,0,5,1,1);
	layout->addWidget(description_cursorline,1,0,1,1);
	layout->addWidget(cursorline_on,1,1,1,1);
	layout->addWidget(description_match,1,2,1,1);
	layout->addWidget(match_on,1,3,1,1);
	layout->addWidget(description_autoread,1,4,1,1);
	layout->addWidget(autoread_on,1,5,1,1);
	layout->addWidget(description_expandtab,2,0,1,1);
	layout->addWidget(expandtab_on,2,1,1,1);
	layout->addWidget(description_autochdir,2,2,1,1);
	layout->addWidget(autochdir_on,2,3,1,1);
	layout->addWidget(description_smartindent,2,4,1,1);
	layout->addWidget(smartindent_on,2,5,1,1);
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
	layout->addWidget(description_number,3,0,1,1);
	layout->addWidget(line_number_combobox,3,1,1,1);
	layout->addWidget(description_tabstop,3,2,1,1);
	layout->addWidget(tabstop_combobox,3,3,1,1);
}
void vimrc_helper::main_init()
{
	//菜单栏初始化
	open_file_action=new QAction("打开vimrc文件",nullptr);
	open_file_action->setShortcut(tr("Ctrl+O"));
	connect(open_file_action,&QAction::triggered,this,&vimrc_helper::open_file);
	QMenu *file_menu=this->menuBar()->addMenu(tr("文件"));
	file_menu->addAction(open_file_action);
	this->menuBar()->addSeparator();
	this->menuBar()->show();
	//界面初始化
	SwitchButton_init();
	ComboBox_init();
	layout->setHorizontalSpacing(10);
	layout->setVerticalSpacing(10);
	layout->setContentsMargins(10,10,10,10);
	layout->setColumnStretch(0,1);
	layout->setColumnStretch(1,1);
	layout->setColumnStretch(2,1);
	layout->setColumnStretch(3,1);
	layout->setColumnStretch(4,1);
	layout->setColumnStretch(5,1);
	layout->setRowStretch(0,1);
	layout->setRowStretch(1,1);
	layout->setRowStretch(2,1);
	layout->setRowStretch(3,1);
}
int vimrc_helper::str_find(const char *a,const char *b,int *nxt)
{
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
	while(gets_s(str_tmp,100000))
	{
		total_row++;
		for(auto i:str_tmp) file[total_row].push_back(i);
	}
	for(int i=1;i<=total_row;i++)
	{
		int num=0;
		memset(str_tmp,0,sizeof(str_tmp));
		for(auto j:file[i]) str_tmp[++num]=j;
		if(str_find(str_tmp,pre_command[0],char_compare_nxt)!=-1) syntax_on->checked=1;
		else if(str_find(str_tmp,pre_command[1],char_compare_nxt)!=-1) noswapfile_on->checked=1;
		else if(str_find(str_tmp,pre_command[2],char_compare_nxt)!=-1) mouse_on->checked=1;
		else if(str_find(str_tmp,pre_command[3],char_compare_nxt)!=-1) cursorline_on->checked=1;
		else if(str_find(str_tmp,pre_command[4],char_compare_nxt)!=-1) match_on->checked=1;
		else if(str_find(str_tmp,pre_command[5],char_compare_nxt)!=-1) autoread_on->checked=1;
		else if(str_find(str_tmp,pre_command[6],char_compare_nxt)!=-1) expandtab_on->checked=1;
		else if(str_find(str_tmp,pre_command[7],char_compare_nxt)!=-1) autochdir_on->checked=1;
		else if(str_find(str_tmp,pre_command[8],char_compare_nxt)!=-1) smartindent_on->checked=1;
		else if(str_find(str_tmp,pre_command[9],char_compare_nxt)!=-1) line_number_combobox->setCurrentIndex(0);
		else if(str_find(str_tmp,pre_command[10],char_compare_nxt)!=-1) line_number_combobox->setCurrentIndex(1);
		else if(str_find(str_tmp,pre_command[11],char_compare_nxt)!=-1) line_number_combobox->setCurrentIndex(2);
		else if(str_find(str_tmp,pre_command[12],char_compare_nxt)!=-1)
		{
			num=0;
			for(auto k:str_tmp)
				if(k>='0'&&k<='9')
					num=num*10+k-'0';
			tabstop=num;
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
	}
	fclose(stdin);
}
void vimrc_helper::path_view()
{
	this->setWindowTitle(QString(file_path)+" - Vimrc Helper");
}