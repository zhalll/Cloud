#pragma once

#include<iostream>
#include<vector>
#include<string>

//�Ѿ�Ĭ�����񳤶�Ϊ1
#define GRID_LENGTH 1
//�жϸ������Ƿ�������ʵ���ֵ
#define MATERIAL_MIN 1e-6

/*�Ƿ����������������*/
//��ʼ���������/��С�¶�
#define MAX_AMBIENT_TEMP 25.0
#define MIN_AMBIENT_TEMP 5.0
//��ʼ������ˮ���ܶ�
#define INIT_VAPOR_DENSITY 1.0f
//��ʼ������ˮ���¶�
#define INIT_MATERIAL_TEMP 15.0
//��ʼ������ˮ���������ٶ�
#define INIT_VELOCITY_W 0.3

class CloudEulerGen
{
public:
	CloudEulerGen(const std::vector<int>& arg, const float epsilon);
	~CloudEulerGen();

	//ֱ�����ɶ�Ӧ���������ս��(�������д���)
	void CloudGenFinalRun(int times);
	//����demoչʾÿ֡����()
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
	int mode_flag_;   //����ģʽ(0-��,1-�ƣ�Ĭ���̣�)

	/* ������ָ���Ĳ��� */
	int n_;  //ģ��ռ��С(�������߽�)
	int start_x_;  //����Դ��ʼx����
	int end_x_;  //����Դ����x����
	int start_y_;  //����Դ��ʼy����
	int end_y_;  //����Դ����y����
	int noise_type_;  //��������
	float epsilon_;  //��������ϵ��
	/*------------------*/

	float init_vapor_density_;  //��ʼ��ˮ���ܶ�
	float init_material_temp_;  //��ʼ�������¶�
	float init_velocity_w_;  //��ʼ���������ٶ�

	int size_;
	float dt_;   //ʱ�䲽��
	int frame_count_;   //���ڼ�¼���е��ڼ�֡

	std::vector<float> velocity_u_;   //x�����ٶ�
	std::vector<float> velocity_v_;   //y�����ٶ�
	std::vector<float> velocity_w_;   //z�����ٶ�
	std::vector<float> vapor_density_;  //ˮ���ܶ�
	std::vector<float> cloud_density_;  //���ܶ�
	std::vector<float> ambient_temp_;  //�����¶�
	std::vector<float> material_temp_;  //�����¶�

	//�ռ���ά����λ��ת��һά��������
	const int Position(int i, int j, int k);
	//�����ٶȳ�
	void GetVelocity();
	//�����ܶȳ�
	void GetDensity();
	//�߽����(value:���ƵĶ�����  velocity_project_flag:�ٶ�ͶӰ���(0-���ǣ�1-x�ᣬ2-y�ᣬ3-z��)
	void BoundaryCondition(std::vector<float>& value, const int velocity_project_flag);
	//Advectƽ��(Ҫƽ��������������һ֡��ֵ������Ҫ������������ٶ�)
	void Advect(std::vector<float>& value, const std::vector<float>& pre_value, const std::vector<float>& velocity_u, const std::vector<float>& velocity_v, const std::vector<float>& velocity_w);
	//��˹���¶�����
	void GaussSeidelIteration(std::vector<float>& p, const std::vector<float>& div);
	//ProjectͶӰ
	void Project();
	//AddBouyancySmoke�̸���
	void AddBouyancySmoke();
	//AddBouyancyCloud�̸���
	void AddBouyancyCloud();
	//VorticityConfinement��������
	void VorticityConfinement();
	//PhaseTransitionCloud�����
	void PhaseTransitionCloud();
	//CorrectTimestepʱ�䲽������(�Ƿ����)
	void CorrectTimestep();
	//SourceControlԴ����
	void SourceControl();
	//NoneNoise������Դ
	void NoneNoise();
	//GaussNoise��˹����Դ
	void GaussNoise();
};

