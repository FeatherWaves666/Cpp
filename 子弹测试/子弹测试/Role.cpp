#include "Role.h"
#include "head.h"
extern enum RoleDir;
Role::Role(int id)
{
	this->bulletShootNum = 0;
	this->dir = BOTTOM;
	this->isWin = false;
	if (id == 1)
	{
		this->x = 1 * WALL_BRICK_SIZE;
		this->y = 1 * WALL_BRICK_SIZE;
		loadimage(&this->img[0], _T("./role1_src.jpg"));
		loadimage(&this->img[1], _T("./role1_mask.jpg"));
	}
	else
	{
		this->x = 25 * WALL_BRICK_SIZE;
		this->y = 15 * WALL_BRICK_SIZE;
		loadimage(&this->img[0], _T("./images/role2_src.jpg"));
		loadimage(&this->img[1], _T("./images/role2_mask.png"));
	}
	this->v_x = 7;
	this->v_y = 7;
	this->img_x = 0;
	this->img_y = 0;
	this->h = 30;
	this->w = 30;
	this->cen_x = this->x + this->w / 2;
	this->cen_y = this->y + this->h / 2;
}
int& Role::GetX()
{
	return this->x;
}
int& Role::GetY()
{
	return this->y;
}
int& Role::GetImgX()
{
	return this->img_x;
}
int& Role::GetImgY()
{
	return this->img_y;
}
int& Role::GetVX()
{
	return this->v_x;
}
int& Role::GetVY()
{
	return this->v_y;
}
int& Role::GetW()
{
	return this->w;
}
int& Role::GetH()
{
	return this->h;
}
IMAGE* Role::GetImg()
{
	return this->img;
}
int& Role::GetDir()
{
	return this->dir;
}
Bullet& Role::GetBt()
{
	return this->bt;
}
int& Role::GetCenX()
{
	return this->cen_x;
}
int& Role::GetCenY()
{
	return this->cen_y;
}
int& Role::GetBSN()
{
	return this->bulletShootNum;
}
bool& Role::GetIsWin()
{
	return this->isWin;
}
