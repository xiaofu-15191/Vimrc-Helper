# 附加内容

## 前言

实际上，你可以使用 ``help manual`` 指令，在 ``usr_05.txt`` 中学习有关其他设置的内容。但是考虑别的因素，我将在这里介绍简单的 vimrc 设置。

由于这个工具实际上是给初学者(?)使用，所以我只会在这里介绍快捷键设置以及一些别的常用设置。

## 常用设置

### 打开中文编码支持

```Vim
set encoding=utf8
set fileencodings=utf8,ucs-bom,gbk,cp936,gb2312,gb18030
```

### 设置状态栏

```vim
set laststatus=2
set statusline=\ %<%F[%1*%M%*%n%R%H]%=\ %y\ %0(%{&fileformat}\ [%{(&fenc==\"\"?&enc:&fenc).(&bomb?\",BOM\":\"\")}]\ %c:%l/%L%)
```

默认会在状态栏中显示当前模式、文件名、文件格式、编码、换行格式、当前行数与在全文件中百分之几的位置。

### 设置字体（只对gvim生效）

```vim
set guifont=JetBrains_Mono:h10
```

注意 ``JetBrains_Mono`` 替换成你需要的字体名，空格使用下划线代替，大小写不敏感。

### 设置主题

将你的颜色主题放在 ``.vim/colors`` 文件夹中，使用 ``colorscheme 主题名`` 加载主题。

例如我要使用 onedark，把官方的 onedark.vim 放在 ``~/.vim/colors`` 文件夹中，使用 ``colorscheme onedark`` 加载主题。

但实际上我使用的 onedark 主题还有一个放在 autoload 中的 onedark.vim，而且放进去了也用不了，必须要作为插件安装才能用。

总之就是大部分主题都可以这么安装，特殊情况特殊考虑。

## 快捷键设置

``map {lhs} {rhs}`` 表示将按键 ``{lhs}`` 映射到 按键 ``{rhs}`` 。

例如：

``map <C-N> :tabnew<CR>`` 表示：按下 <kbd>Ctrl</kbd>+<kbd>N</kbd> 等同于按下 ``:tabnew`` （打开新标签页）然后回车。

注意第一个尖括号中，前面的大写 ``C`` 表示按下 <kbd>Ctrl</kbd> 键； 后面的 ``N`` 表示按下 <kbd>N</kbd> 键。

---

后面的内容也可以换成其他的内容，例如普通模式下的命令：

``nnoremap <tab> V>`` 表示在普通模式下按 <kbd>Tab</kbd> 键等同于在普通模式下按 ``V>`` ，即缩进本行。最前面的 ``n`` 表示 "normal"，即这个映射在普通模式下生效。``nore`` 表示非递归引用，这个很好理解（但是不会真的有人写递归的映射吧）。

---

后面的内容还可以换成函数，例如：

````
nnoremap <F9> :call CompileRunGcc()<CR>
func! CompileRunGcc()
	exec "w"
	exec '!g++ % -o %< -Wall -std=c++14'
	endfunc
````

第一行表示在普通模式下按 <kbd>F9</kbd> 执行 ``:call CompileRunGcc()`` 即调用 ``CompileRunGcc()`` 函数。第二行至第五行是这个函数的实现。``exec`` 表示命令模式，首先 ``w`` 保存文件，然后 ``!g++ % -o %< -Wall -std=c++14``。冒号后面的感叹号表示调用外部命令，接着是g++编译文件。此处的 ``%`` 表示当前文件名（包括扩展名），``%<`` 表示文件名（无扩展名）。



当然，Vim-script 函数的语法肯定不止这么简单。这里有一段 Vim-script 代码，使用 <kbd>Ctrl</kbd>+<kbd>Up</kbd>与 <kbd>Ctrl</kbd>+<kbd>Down</kbd> 上移、下移行。读者可自行理解、复制粘贴使用。

```vim
function! s:moveup_line()
	let cur_pos = getpos('.')	"获取当前光标位置
	"如果已经是最上一行，则直接返回
	if cur_pos[1] == 1
		return
	endif
	let tgt_line = cur_pos[1] - 1	"获得上一行的行号
	let tmp = getline(tgt_line)		"将上一行的内容临时存储
	call setline(tgt_line,getline(cur_pos[1]))	"将上一行的内容替换成当前行
	call setline(cur_pos[1],tmp)	"将当前行的内容替换成上一行
	let cur_pos[1] -= 1	"将当前光标的行号减1,得到目标位置"
	call setpos('.',cur_pos)	"修改当前光标位置
endfunction

function! s:movedown_line()
	let cur_pos = getpos('.')	"获取当前光标位置
	"如果已经是最底一行，则直接返回
	if cur_pos[1] == line('$')
		return
	endif
	let tgt_line = cur_pos[1] + 1	"获得下一行的行号
	let tmp = getline(tgt_line)		"将下一行的内容临时存储
	call setline(tgt_line,getline(cur_pos[1]))	"将下一行的内容替换成当前行
	call setline(cur_pos[1],tmp)	"将当前行的内容替换成下一行
	let cur_pos[1] += 1	"将当前光标的行号+1,得到目标位置"
	call setpos('.',cur_pos)	"修改当前光标位置
endfunction

function! s:moveup_multlines() range
	"获取选择范围的端点的位置信息
	let start_mark = getpos("'<")
	let end_mark = getpos("'>")
	"对代码块的位置进行判断，当已经为最顶层时，直接退出函数
	if start_mark[1] == 1
		return
	endif
	"利用getling()和setline()内置函数实现代码块整体移动
	let save_curpos = getpos('.')
	let buffer_lines = getline(start_mark[1],end_mark[1])
	call add(buffer_lines, getline(start_mark[1] - 1))
	call setline(start_mark[1]-1,buffer_lines)
	"调整选区范围和当前光标的位置
	let start_mark[1] -= 1
	let end_mark[1] -= 1
	let save_curpos[1] -= 1
	call setpos("'<",start_mark)
	call setpos("'>",end_mark)
	call setpos('.',save_curpos)
endfunction

function! s:movedown_multlines() range
	"获取选择范围的端点的位置信息
	let start_mark = getpos("'<")
	let end_mark = getpos("'>")
	"对代码块的位置进行判断，当已经为最底层时，直接退出函数
	if end_mark[1] == line('$')
		return
	endif
	"利用getling()和setline()内置函数实现代码块整体移动
	let save_curpos = getpos('.')
	let buffer_lines = [getline(end_mark[1] + 1)]
	call extend(buffer_lines, getline(start_mark[1],end_mark[1]) )
	call setline(start_mark[1],buffer_lines)
	"调整选区范围和当前光标的位置
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
```
