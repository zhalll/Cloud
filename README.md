# Cloud
## 编译方法
在Ubuntu下可以按如下顺序编译执行：
1.编译pybind11
    cd pybind11
    mkdir build
    cd build
    cmake ..
    make check -j 4
不用管pytest和check的Error。
2.编译自己的代码
    cd ..
    cd ..
    mkdir build
    cd build
    cmake ..
    make
可以在build文件夹下找到.so文件，将其复制到项目主目录的python文件夹下。
3.执行python代码
    cd ..
    cd python
    python3 run.py
*ps. 原本的xml文件tag匹配有误，不能解析，所以对xml文件内容有改动*
