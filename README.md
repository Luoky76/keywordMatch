# 简介
&emsp;&emsp;这是一个用于学习 GitHub 命令和完成软件工程第一次个人作业而创建的仓库，作业要求可见[2021秋软工实践第一次个人编程作业](https://bbs.csdn.net/topics/600574694)。

&emsp;&emsp;本工具的主要功能为计算C/C++程序中关键词的出现次数，其次还可以统计程序中完整的 if-else 组的个数。

# 使用方法
&emsp;&emsp;首先将所有文件下载并置于同一个目录下，确保计算机以正确配置 C++ 环境后可在该目录下打开命令行 ，然后输入`g++ -o keywordmatch keywordmatch.cpp`进行编译。（注：只需编译这一个文件，其余文件均为附属文件，会一同编译）编译后，可见文件夹内多了一个可执行文件 keywordmatch.exe 。将该 .exe 文件与需要计算的文件放在同一目录下，在该目录下打开命令行，输入`keywordmatch XXX.cpp 4`其中， XXX.cpp 为需要计算的文件的文件名，该程序也支持部分其它格式的文件，如 .c 、 .txt 等。最后的「 4 」为工作模式， 4 表示最完整模式，工作模式共有 1~4 四种，差别仅在于输出哪些内容。