---
姓名：庞晓宇
学号：2020118100
---
# MySimpleShell


## 介绍
Shell或命令行解释器是操作系统的基本用户界面。你的第一个项目是编写一个简单的shell，就像你在之前的所有实验中学到的那样。详情见文件：**《操作系统实验》 实验二：DEVELOPING A SHELL**
pdf文件可能缺少部分信息，详情见md源文件


## 使用说明
Shell 既是一个连接用户和 Linux 内核的程序，又是一门管理 Linux 系统的脚本语言。
由于安全、复杂、繁琐等原因，用户不能直接接触内核（也没有必要），需要另外再开发一个程序，让用户直接使用这个程序；该程序的作用就是接收用户的操作（点击图标、输入命令），并进行简单的处理，然后再传递给内核，这样用户就能间接地使用操作系统内核了。
用户界面和命令行就是这个另外开发的程序，就是这层“代理”。在Linux下，这个命令行程序叫做 Shell。
Shell 是一个应用程序，它连接了用户和 Linux 内核，让用户能够更加高效、安全、低成本地使用 Linux 内核，这就是 Shell 的本质。
Shell 本身并不是内核的一部分，它只是站在内核的基础上编写的一个应用程序，它和 QQ、迅雷、Firefox 等其它软件没有什么区别。
然而 Shell 也有着它的特殊性，就是开机立马启动，并呈现在用户面前；用户通过 Shell 来使用 Linux，不启动 Shell 的话，用户就没办法使用 Linux。
以下是本Shell实现的一些功能以及使用说明：
1. `cd <directory>` - cd <目录>—将当前的默认目录修改为<目录>。如果<目录>参数不存在，则报告当前目录。如果目录不存在，则应该报告适当的错误。这个命令还应该更改PWD环境变量。
2. `clr` - 清空控制台。
3. `dir <directory>` - 列出目录 `<directory>` 的内容，包含文件和文件夹。
4. `environ` - 列出所有环境字符串。
5. `echo <comment>` - 在屏幕上显示 `<comment>` ，后面跟着一个新行(多个空格/制表符可以减少到一个空格)。
6. `help` - 显示所有的命令。
7. `pause` - 暂停shell的操作，这个时候无法进行其他的操作，直到按下'Enter'。
8. `quit` - 退出Shell。关闭当前程序。


## 参考
- [GitHub-Umar-Eh/Simple-Shell](https://github.com/Umar-Eh/Simple-Shell)
- [百度百科-getcwd()](https://baike.baidu.com/item/getcwd/4746955?fr=aladdin)
- [百度百科-dirent()](https://baike.baidu.com/item/dirent/2857085?fr=aladdin)
- [vs code 配置C/C++多文件编译调试（linux&windows）](https://blog.csdn.net/hzf978742221/article/details/116101789)
- [C语言中文网-chdir()](http://c.biancheng.net/cpp/html/305.html)
- [C语言中文网-Shell](http://c.biancheng.net/shell/)


<!-- By XFTXYZ -->
