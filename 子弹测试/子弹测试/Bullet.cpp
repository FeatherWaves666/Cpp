#include "Role.h"
#include "Bullet.h"
#include "head.h"
extern enum RoleDir;
Bullet::Bullet()
{
	this->v_x = 25;
	this->v_y = 25;
	this->isFired = false;
	this->length = 3 * 40;
	this->h = 5;
	this->w = 5;
	this->cen_x = this->x + this->w / 2;
	this->cen_y = this->y + this->h / 2;
	loadimage(&this->src, _T("./src.png"));
	loadimage(&this->mask, _T("./mask.png"));
}
int& Bullet::GetX()
{
	return this->x;
}
int& Bullet::GetY()
{
	return this->y;
}
int& Bullet::GetVX()
{
	return this->v_x;
}
int& Bullet::GetVY()
{
	return this->v_y;
}
IMAGE& Bullet::GetSrc()
{
	return this->src;
}
IMAGE& Bullet::GetMask()
{
	return this->mask;
}
int& Bullet::GetDir()
{
	return this->dir;
}
int& Bullet::GetLength()
{
	return this->length;
}
bool& Bullet::GetIsFired()
{
	return this->isFired;
}
void Bullet::ChangePer(Role& player)
{
	this->cen_x = this->x + this->w / 2;
	this->cen_y = this->y + this->h / 2;
	if (this->isFired == false)
	{
		this->dir = player.GetDir();
		switch (player.GetDir())
		{
		case TOP:
			this->x = player.GetX() + player.GetW() / 2;
			this->y = player.GetY();
			break;
		case BOTTOM:
			this->x = player.GetX() + player.GetW() / 2;
			this->y = player.GetY() + player.GetH();
			break;
		case LEFT:
			this->x = player.GetX();
			this->y = player.GetY() + player.GetH() / 2;
			break;
		case RIGHT:
			this->x = player.GetX() + player.GetW();
			this->y = player.GetY() + player.GetH() / 2;
			break;
		default:
			break;
		}
	}
}
int& Bullet::GetH()
{
	return this->h;
}
int& Bullet::GetW()
{
	return this->w;
}
int& Bullet::GetCenX()
{
	return this->cen_x;
}
int& Bullet::GetCenY()
{
	return this->cen_y;
}