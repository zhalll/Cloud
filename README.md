# Cloud

> 2020.11.08 使用pybind11库将C++类变换成python模块，并用python调用执行。

> 2020.11.15 编写WriteVTI函数，可以将密度数据存储到.vti文件中（ascii形式），C++和python都可调用。

> 2020.12.10 调整XmlParsing类，能解析改动后的xml文件，并输出结果xml文件。

> 2020.12.17 修改run.py，可循环输出多帧密度场的vti文件。

## 文件结构
```
Cloud
├─ CMakeLists.txt
├─ CloudEulerGen.cpp
├─ CloudEulerGen.h
├─ Gen2py.cpp
├─ README.md
├─ WriteVTI.cpp
├─ WriteVTI.h
├─ pybind11
└─ python
       ├─ euler_i.xml
       ├─ euler_s.xml
       ├─ run.py
       └─ xml_parsing.py
```
pybind11文件太多，没法上传，可以直接去https://github.com/pybind/pybind11 下载。

## 编译方法

在Ubuntu下可以按如下顺序编译执行：

### 1.编译pybind11

    cd pybind11
    mkdir build
    cd build
    cmake ..
    make check -j 4
不用管pytest和check的Error。

### 2.编译C++代码

    cd ..
    cd ..
    mkdir build
    cd build
    cmake ..
    make
可以在build文件夹下找到.so文件，将其复制到项目主目录的python文件夹下。

### 3.执行python代码
    cd ..
    cd python
    python3 run.py

