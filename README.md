# MyDLL
同化棋的调试工具，C++实时更改生成DLL，图形界面

功能如题，这是一个用来开发同化棋算法的应用。
这个项目包含两个程序，一个是图形界面运行的主程序，源码没有放到这里，用的语言是C#，不多说，直接用就可以。

下面是重点：

另一个程序是一个Dll工程，也是我们的大作业的算法主体部分，为了跟大作业的接口一致，
我将网上的注释和函数原封不动抄下来，这样写好算法的同学只需要把自己的代码复制粘贴过来相应的位置就好了。
点开MainCode.cpp文件就可以看到了。为了便于展示，我自己已经完成了最简单的单步数量最大解的算法，可以下下来直接运行。

嗯，反正我的智商已经打不过他了~

具体的展示见根目录下的视频，25.9MB大小。
支持即时编译运行，一遍出bug了，不需要重新加载dll文件，在visual studio里改好代码按[Shift+F6]生成dll后，
直接点开始游戏，就开始新一盘游戏，并自动重新加载dll，加大开发效率。

当然，说是开发工具，其实两个人对战，或者是两个人之间的算法之间的对战也完全没有问题！
我觉得我们线下组织班里的比赛会不会好一点~只需要把dll文件拷过去，不需要担心代码的安全，而且加载灵活。

如果大家觉得这个软件还可以的话，推荐在把编译好的dll文件放到这个github上，代码不会暴露，同时增进大家算法之间的交流。

在这个网站上直接下载zip文件就可以整个下载了，但是上传需要注册账号，嫌麻烦的同学把dll发到我邮箱也可以，我会定期上传。

大作业玩儿起来！
