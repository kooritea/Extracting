将编译好的changecsv_v3.exe放在.csv、.png的同一目录下<br />
用cmd或者bat执行<br />
for /r %%i in (*.csv) do changecsv_v3.exe %%i<br />
ps:要是文件打开失败可能是路径有其他字符，尽量放在浅层路径或者没有复杂字符的路径使用<br />
之后就可以用GalPhotoAuto的<pimg>方法自动合成了
