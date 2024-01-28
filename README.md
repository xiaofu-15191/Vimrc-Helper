# Vimrc-Helper

用于编辑vimrc文件的图形化工具，采用Qt6开发。

## 说明

### 启动

Windows：下载Release中的对应压缩包，解压后即可打开。

Linux：下载压缩包，解压后找到``Vimrc-Helper``，右键属性，勾选“允许作为程序运行”，在终端中输入``./Vimrc-Helper``即可打开。

### 使用

选项对应的vim script配置代码如下：

|vimrc_helper中选项名称|vim script(vimrc)设置代码|
| ------------ | ------------------ |
| 语法高亮     | ``syntax on``      |
| 关闭SWAP文件 | ``set noswapfile`` |
| 兼容鼠标     | ``set mouse=a``    |
| 高亮当前行   | ``set cursorline`` |
| 高亮括号     | ``set showmatch``  |
| 自动读取更改 | ``set autoread``   |
| 空格缩进（默认使用tab缩进） | ``set expandtab``  |
| 自动切换目录 | ``set autochdir``  |
| 关闭撤销文件 | ``set noundofile`` |
| 绝对行号 | ``set number`` |
| 相对行号 | ``set relativenumber`` |
| 混合行号 | ``set number relativenumber`` |
| 缩进大小设置 | ``set tabstop=[2,4,6,8]`` |
| 不响铃（默认响铃，如在普通模式下按<kbd>Esc</kbd>） | ``set noeb`` |
| 响铃时闪烁屏幕 | ``set vb`` |

插件使用 vim-plug 管理，需要将附带的plug.vim（也可自行上网查找）放在你的 ``.vim/autoload`` 文件夹中，如Linux下的 ``~/.vim/autoload`` 文件夹。

插件设置中需在编辑框中写入插件的作者Github用户名/仓库名，如图（新版有略微不同，但是同理）：

![](https://kkgithub.com/xiaofu-15191/blog-img/blob/main/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-01-17%20162725.png?raw=true)

其他设置适用于高级玩家，可参考 [additions.md](additions.md)。其中的内容将会被直接加入.vimrc文件中。

## 编译

### Windows

安装好Qt6环境，使用VS2022打开项目文件夹或Qt Creator打开文件夹中的CMakeLists.txt即可直接编译。

### Linux

首先，保证你的``build-essential``、``libxcb-xinerama0``、``libxcb-cursor0``、``libxcb*``、``libglu1-mesa-dev``、``libglu1-mesa-dev``、``freeglut3-dev``包已安装。（如果使用wayland环境，还需``libwayland-cursor0``、``libwayland*``包）

然后，安装Qt6环境，使用``Qt Creator``打开Vimrc-Helper文件夹中的CMakeLists.txt，编译项目。

