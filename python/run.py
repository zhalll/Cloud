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
    #cloud.CloudGenFinalRun(10)
    length = xml_parsed.scale + 1
    width = xml_parsed.scale + 1
    height = xml_parsed.scale + 1
    out_vti_path_prefix = './data/visualize_data/head-binary-zlib'
    for i in range(xml_parsed.frame):
        out_vti_path = out_vti_path_prefix + '_' + str(i) + '.vti'
        cloud.CloudGenFrameRun()
        data = cloud.GetDensityData(xml_parsed.sim_type)
        WriteVTI(length, width, height, data, out_vti_path)

    out_xml_path = 'euler_s_out.xml'
    xml_parsed.write_result_xml(out_xml_path, out_vti_path_prefix + ' .vti')
