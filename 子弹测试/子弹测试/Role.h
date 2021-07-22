#pragma once
#include "Bullet.h"
#include <iostream>
#include <graphics.h>
#include <conio.h>
using namespace std;

class Role
{
public:
	Role(int id);
	int& GetX();
	int& GetY();
	int& GetImgX();
	int& GetImgY();//执行动画效果
	int& GetVX();
	int& GetVY();
	int& GetW();
	int& GetH();
	IMAGE* GetImg();
	Bullet& GetBt();
	int& GetDir();
	int& GetCenX();
	int& GetCenY();
	int& GetBSN();
	bool& GetIsWin();
private:
	int x, y;
	int img_x, img_y;
	int v_x, v_y;
	int w, h;
	IMAGE img[2];	//0：src   1：mask 
	Bullet bt;
	int dir;
	int id;
	int cen_x, cen_y;
	int bulletShootNum;
	bool isWin;
};