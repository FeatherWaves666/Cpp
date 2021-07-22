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
	SPACE,//空白
	WALL,//墙
	BRICK,//砖
	ROLE //角色
};
const int UP = 0;			//界面的上界
const int DOWN = 600;		//界面的下界
const int LEFT_ = 0;			//界面的左界
const int RIGHT_ = 600;		//界面的右界
const int START_W = 366;
const int START_H = 142;
enum MAP_FORMAT
{
	MAP1, //狭路相逢
	MAP2, //革命街垒
	MAP3, //命运交响曲
	MAP4  //生死角斗场
};
const int WIN_WIDTH = 1080;
const int WIN_HEIGHT = 680;
const int WALL_BRICK_SIZE = 40;
const int ROW = WIN_HEIGHT / WALL_BRICK_SIZE;
const int COL = WIN_WIDTH / WALL_BRICK_SIZE;
const int BRICK_NUM = 350;