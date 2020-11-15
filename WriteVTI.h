#pragma once

#include <vector>
#include <string>

// 将密度数据保存为.vti文件(ascii形式)(length，width，height：数据场长宽高；data：密度数据；path：文件保存路径)
bool WriteVTI(int length, int width, int height, const std::vector<float>& data, const std::string& path);