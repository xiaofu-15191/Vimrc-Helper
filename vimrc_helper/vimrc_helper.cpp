#include "vimrc_helper.h"
vimrc_helper::vimrc_helper(QWidget *parent):QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("Vimrc Helper");
	this->setFont(QFont("Fira Code, Microsoft Yahei"));
	//this->setWindowIcon(QIcon(":/vimrc_helper/icons/vimrc_helper_icon.png"));
	layout=new QGridLayout();
	main_init();
	open_file();
	this->resize(750,450);
	ui.centralWidget->setLayout(layout);
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
	syntax_on=new SwitchButton(nullptr);
	status_on=new SwitchButton(nullptr);
	mouse_on=new SwitchButton(nullptr);
	cursorline_on=new SwitchButton(nullptr);
	description_syntax=new QLabel("语法高亮");
	description_status=new QLabel("状态栏");
	description_mouse=new QLabel("兼容鼠标");
	description_cursorline=new QLabel("高亮当前行");
	layout->addWidget(description_syntax,0,0,1,1);
	layout->addWidget(syntax_on,0,1,1,1);
	layout->addWidget(description_status,0,2,1,1);
	layout->addWidget(status_on,0,3,1,1);
	layout->addWidget(description_mouse,1,0,1,1);
	layout->addWidget(mouse_on,1,1,1,1);
	layout->addWidget(description_cursorline,1,2,1,1);
	layout->addWidget(cursorline_on,1,3,1,1);
	layout->setHorizontalSpacing(10);
	layout->setVerticalSpacing(10);
	layout->setContentsMargins(10,10,10,10);
	layout->setColumnStretch(0,1);
	layout->setColumnStretch(1,1);
	layout->setColumnStretch(2,1);
	layout->setColumnStretch(3,1);
	//layout->setColumnStretch(4,1);
	layout->setRowStretch(0,1);
	layout->setRowStretch(1,1);
	//layout->setRowStretch(2,2);
	//layout->setRowStretch(3,2);
	//layout->setRowStretch(4,2);
	//layout->setRowStretch(5,2);
	//layout->setRowStretch(6,1);
}
void vimrc_helper::open_file()
{
	#if _WIN32
	QString input_path=QFileDialog::getOpenFileName(nullptr,"打开vimrc文件","C:/Users","_vimrc");
	#else
	QString input_path=QFileDialog::getOpenFileName(nullptr,"打开vimrc文件","~/",".vimrc");
	#endif
	if(input_path.size()<5) return;
	for(int i=0;i<input_path.size();i++)
		file_path[i]=input_path[i].toLatin1();
	path_view();
}
void vimrc_helper::path_view()
{
	this->setWindowTitle(QString(file_path)+" - Vimrc Helper");
}