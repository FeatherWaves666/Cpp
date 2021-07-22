#include "Start.h"
Start::Start()
{
	this->start_x = (RIGHT_ / 2) - START_W / 2;
	this->start_y = 3 * (DOWN / 4) - START_H / 2;
	this->isOn = false;
	loadimage(&this->skin, _T("./Colt/开始界面/skin.png"));
	loadimage(&this->start[0], _T("./Colt/开始界面/start_src.png"));
	loadimage(&this->start[1], _T("./Colt/开始界面/start_mask.png"));
}
IMAGE* Start::GetStart()
{
	return this->start;
}
bool& Start::GetIsOn()
{
	return this->isOn;
}
IMAGE& Start::GetSkin()
{
	return this->skin;
}
int& Start::GetStartX()
{
	return this->start_x;
}
int& Start::GetstartY()
{
	return this->start_y;
}