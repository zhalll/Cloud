#include "CloudEulerGen.h"
#include <vector>
#include <string>
#include <fstream>

// 将密度数据保存为.vti文件(ascii形式)(length，width，height：数据场长宽高；data：密度数据；path：文件保存路径)
bool WriteVTI(int length, int width, int height, const std::vector<float>& data, const std::string& path) {
    std::ofstream file(path, std::ios::out | std::ios::trunc);
    if (file) {
        file << "<VTKFile type=\"ImageData\" version=\"1.0\" byte_order=\"";
        // 判断大小端
        int a = 1;
        char* p = reinterpret_cast<char*>(&a);
        if (*p == 1) {
            file << "LittleEndian";
        }
        else {
            file << "BigEndian";
        }
        file << "\" header_type=\"UInt64\">" << std::endl;

        file << "<ImageData WholeExtent=\"" << "0 " << length << " 0 " << width << " 0 " << height
            << "\" Origin=\"0 0 0\" Spacing=\"1.0 1.0 1.0\">" << std::endl;
        file << "<Piece Extent=\"" << "0 " << length << " 0 " << width << " 0 " << height << "\">" << std::endl;
        file << "<PointData Scalars=\"Scalars_\">" << std::endl;
        float rangeMin = 1.0f;
        float rangeMax = 0.0f;
        for(float value:data) {
            if(value < rangeMin) {
                rangeMin = value;
            }
            if(value > rangeMax) {
                rangeMax = value;
            }
        }
        file << "<DataArray type=\"Float32\" Name=\"Scalars_\" format=\"ascii\" RangeMin=\""
            << rangeMin << "\" RangeMax=\"" << rangeMax << "\">" << std::endl;
        
        for (float value : data) {
            file << value << " ";
        }

        file << "</DataArray>" << std::endl;
        file << "</PointData>" << std::endl;
        file << "<CellData>" << std::endl;
        file << "</CellData>" << std::endl;
        file << "</Piece>" << std::endl;
        file << "</ImageData>" << std::endl;
        file << "</VTKFile>" << std::endl;
        file.close();

    }
    else {
        printf("Fail to save vti file: %s!\n", path.c_str());
        return false;
    }
    return true;
}

/*
int main() {
    std::vector<int> arg(7);
    arg[0] = 0; // mode_flag_
    arg[1] = 20; // n_
    arg[2] = 1; // start_x_
    arg[3] = 1; // end_x_
    arg[4] = 10; // start_y_
    arg[5] = 10; // end_y_
    arg[6] = 0; // noise_type_
    float epsilon = 0.7;

    CloudEulerGen cloud(arg, epsilon);
    int length, width, height;
    length = cloud.GetN() + 2;
    width = cloud.GetN() + 2;
    height = cloud.GetN() + 2;
    std::vector<float> data;
    std::string path = "test.vti";

    cloud.CloudGenFinalRun(10);
    data = cloud.GetVaporDensity();
    
    if (WriteVTI(length, width, height, data, path)) {
        printf("vti文件生成成功\n");
    }
    else {
        printf("vti文件生成失败\n");
    }

    return 0;
}
*/