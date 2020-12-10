from xml_parsing import XmlParsing
from Cloud_Gen_Based_Euler import CloudEulerGen
from Cloud_Gen_Based_Euler import WriteVTI

if __name__ == '__main__':
    xml_parsed = XmlParsing('euler_i.xml')
    arg = []
    arg.append(xml_parsed.sim_type) # 模拟对象
    arg.append(xml_parsed.scale)    # 模拟空间大小(不包含边界)
    arg.append(xml_parsed.start_x)  # 发射源起始x坐标
    arg.append(xml_parsed.end_x)    # 发射源结束x坐标
    arg.append(xml_parsed.start_y)  # 发射源起始y坐标
    arg.append(xml_parsed.end_y)    # 发射源结束y坐标
    arg.append(xml_parsed.noise)    # 噪声种类

    epsilon = xml_parsed.vortex     # 涡旋抑制系数

    cloud = CloudEulerGen(arg, epsilon)
    #cloud.CloudGenFrameRun()
    cloud.CloudGenFinalRun(10)
    data = cloud.GetDensityData(xml_parsed.sim_type)
    length = xml_parsed.scale + 1
    width = xml_parsed.scale + 1
    height = xml_parsed.scale + 1
    result_vti_path = './data/visualize_data/head-binary-zlib.vti'
    WriteVTI(length, width, height, data, result_vti_path)

    out_xml_file_path = 'euler_s_out.xml'
    xml_parsed.write_result_xml(out_xml_file_path, result_vti_path)
