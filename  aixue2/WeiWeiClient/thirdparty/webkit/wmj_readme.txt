增加了可编辑webkit功能
这里文件放入D:\Qt\4.8.2\src\3rdparty\webkit\Source\WebKit\qt\declarative源码中
并且单独编译qt webkit模块
编译方法如：
configure.exe -webkit -nomake demos -nomake examples -nomake tools -fast -no-dsp  -no-declarative -no-scripttools  -no-directwrite  -no-declarative-debug -no-script -no-audio-backend -no-dbus  -no-phonon-backend  -no-multimedia  -no-audio-backend
qmake WebKit.pro -r -spec  D:\Qt\4.8.2\mkspecs\win32-msvc2008 
经过上面两步
现在在打开qt creator打开webkit.pro项目再编译declarative项目就没有问题了