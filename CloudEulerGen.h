#pragma once

#include<iostream>
#include<vector>
#include<string>

//已经默认网格长度为1
#define GRID_LENGTH 1
//判断该网格是否存在物质的阈值
#define MATERIAL_MIN 1e-6

/*是否可以灵活调整？？？*/
//初始化环境最大/最小温度
#define MAX_AMBIENT_TEMP 25.0
#define MIN_AMBIENT_TEMP 5.0
//初始化地面水气密度
#define INIT_VAPOR_DENSITY 1.0f
//初始化地面水气温度
#define INIT_MATERIAL_TEMP 15.0
//初始化地面水气上升初速度
#define INIT_VELOCITY_W 0.3

class CloudEulerGen
{
public:
	CloudEulerGen(const std::vector<int>& arg, const float epsilon);
	~CloudEulerGen();

	//直接生成对应次数的最终结果(输入运行次数)
	void CloudGenFinalRun(int times);
	//用于demo展示每帧运行()
	void CloudGenFrameRun();

	const int GetModeFlag();
	const int GetN();
	const float GetVelocityU(int i, int j, int k);
	const float GetVelocityV(int i, int j, int k);
	const float GetVelocityW(int i, int j, int k);
	const float GetVaporDensity(int i, int j, int k);
	const float GetCloudDensity(int i, int j, int k);
	const std::vector<float>& GetDensityData(int mode_flag);
	const float GetAmbientTemp(int k);
	const float GetMaterialTemp(int i, int j, int k);
	const int GetFrameCount();

private:
	int mode_flag_;   //生成模式(0-烟,1-云，默认烟！)

	/* 界面须指定的参数 */
	int n_;  //模拟空间大小(不包含边界)
	int start_x_;  //发射源起始x坐标
	int end_x_;  //发射源结束x坐标
	int start_y_;  //发射源起始y坐标
	int end_y_;  //发射源结束y坐标
	int noise_type_;  //噪声种类
	float epsilon_;  //涡旋抑制系数
	/*------------------*/

	float init_vapor_density_;  //初始化水气密度
	float init_material_temp_;  //初始化物质温度
	float init_velocity_w_;  //初始化上升初速度

	int size_;
	float dt_;   //时间步长
	int frame_count_;   //用于记录运行到第几帧

	std::vector<float> velocity_u_;   //x方向速度
	std::vector<float> velocity_v_;   //y方向速度
	std::vector<float> velocity_w_;   //z方向速度
	std::vector<float> vapor_density_;  //水气密度
	std::vector<float> cloud_density_;  //云密度
	std::vector<float> ambient_temp_;  //环境温度
	std::vector<float> material_temp_;  //物质温度

	//空间三维坐标位置转化一维向量函数
	const int Position(int i, int j, int k);
	//计算速度场
	void GetVelocity();
	//计算密度场
	void GetDensity();
	//边界控制(value:控制的对象名  velocity_project_flag:速度投影标记(0-不是，1-x轴，2-y轴，3-z轴)
	void BoundaryCondition(std::vector<float>& value, const int velocity_project_flag);
	//Advect平流(要平流的量，该量上一帧的值，所需要的三个方向的速度)
	void Advect(std::vector<float>& value, const std::vector<float>& pre_value, const std::vector<float>& velocity_u, const std::vector<float>& velocity_v, const std::vector<float>& velocity_w);
	//高斯赛德尔迭代
	void GaussSeidelIteration(std::vector<float>& p, const std::vector<float>& div);
	//Project投影
	void Project();
	//AddBouyancySmoke烟浮力
	void AddBouyancySmoke();
	//AddBouyancyCloud烟浮力
	void AddBouyancyCloud();
	//VorticityConfinement涡旋限制
	void VorticityConfinement();
	//PhaseTransitionCloud云相变
	void PhaseTransitionCloud();
	//CorrectTimestep时间步长纠正(是否合理？)
	void CorrectTimestep();
	//SourceControl源控制
	void SourceControl();
	//NoneNoise无噪声源
	void NoneNoise();
	//GaussNoise高斯噪声源
	void GaussNoise();
};

