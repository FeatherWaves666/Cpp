#pragma once
enum RoleDir
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};
enum ATTR
{
	SPACE,//�հ�
	WALL,//ǽ
	BRICK,//ש
	ROLE //��ɫ
};
const int UP = 0;			//������Ͻ�
const int DOWN = 600;		//������½�
const int LEFT_ = 0;			//��������
const int RIGHT_ = 600;		//������ҽ�
const int START_W = 366;
const int START_H = 142;
enum MAP_FORMAT
{
	MAP1, //��·���
	MAP2, //��������
	MAP3, //���˽�����
	MAP4  //�����Ƕ���
};
const int WIN_WIDTH = 1080;
const int WIN_HEIGHT = 680;
const int WALL_BRICK_SIZE = 40;
const int ROW = WIN_HEIGHT / WALL_BRICK_SIZE;
const int COL = WIN_WIDTH / WALL_BRICK_SIZE;
const int BRICK_NUM = 350;