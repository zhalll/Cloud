import xml.etree.ElementTree as ET

# 给输出xml文件增加缩进和换行
def indent(elem, level=0):
    i = "\n" + level*"    "
    if len(elem):
        if not elem.text or not elem.text.strip():
            elem.text = i + "    "
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
        for elem in elem:
            indent(elem, level+1)
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
    else:
        if level and (not elem.tail or not elem.tail.strip()):
            elem.tail = i


class XmlParsing:
    # 读取并解析xml文件
    def __init__(self, in_file_path):
        with open(in_file_path, 'r', encoding='UTF-8') as xml_file:
            self.in_file_path = in_file_path
            tree = ET.parse(xml_file)
            scene = tree.getroot()
            # in 'Fluid' tag 
            fluid = scene.find('Fluid')
            for elem in fluid.iter():
                tag = elem.tag
                if(tag == 'Start'):
                    start_list = list(map(int, elem.text.split()))
                    self.start_x = start_list[0]
                    self.start_y = start_list[1]
                elif(tag == 'End'):
                    end_list = list(map(int, elem.text.split()))
                    self.end_x = end_list[0]
                    self.end_y = end_list[1]
                elif(tag == 'Vortex'):
                    self.vortex = float(elem.text)
                elif(tag == 'Noise'):
                    self.noise = int(elem.text)
            # in 'Boundary' tag
            boundary = scene.find('Boundary')
            for elem in boundary.iter():
                tag = elem.tag
                if(tag == 'Scale'):
                    self.scale = int(elem.text)
            # in 'Simulation' tag
            simulation = scene.find('Simulation')
            for elem in simulation.iter():
                tag = elem.tag
                if(tag == 'SimulationMethod'):
                    self.sim_type = int(elem.text)
                elif(tag == 'Frame'):
                    self.frame = int(elem.text)
    
    # 输出结果xml文件
    def write_result_xml(self, out_xml_file_path, result_vti_path):
        with open(self.in_file_path, 'r', encoding='UTF-8') as xml_file:
            tree = ET.parse(xml_file)
            scene = tree.getroot()
            simulation_run = ET.Element('SimulationRun')
            simulation_run.set('class', '')
            simulation_run.set('name', '模拟运行结果')
            path = ET.SubElement(simulation_run, 'Path')
            path.set('class', 'String')
            path.set('name', '仿真结果路径')
            path.set('disabled', 'true')
            path.text = result_vti_path
            scene.append(simulation_run)
            indent(scene)
            tree.write(out_xml_file_path, encoding="utf-8", xml_declaration=True)



if __name__ == '__main__':
    xml_parsed = XmlParsing('euler_i.xml')
    print('起始位置(Start)：\t\t', xml_parsed.start_x, xml_parsed.start_y)
    print('结束位置(End)：    \t\t', xml_parsed.end_x, xml_parsed.end_y)
    print('涡旋抑制系数(Vortex)： \t\t', xml_parsed.vortex)
    print('源噪声(Noise)： \t\t', xml_parsed.noise)
    print('大小(Scale)：    \t\t', xml_parsed.scale)
    print('仿真类型(SimulationMethod)：\t', xml_parsed.sim_type)
    print('模拟帧数(Frame)：  \t\t', xml_parsed.frame)

    xml_parsed.write_result_xml('euler_s_test.xml', './data/visualize_data/head-binary-zlib.vti')