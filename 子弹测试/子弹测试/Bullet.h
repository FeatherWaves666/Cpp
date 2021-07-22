#pragma once
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include "Bullet.h"
using namespace std;
class Role;
class Bullet
{
public:
	Bullet();
	void ChangePer(Role& player);
	int& GetX();
	int& GetY();
	int& GetVX();
	int& GetVY();
	IMAGE& GetSrc();
	IMAGE& GetMask();
	int& GetDir();
	int& GetLength();
	bool& GetIsFired();
	int& GetH();
	int& GetW();
	int& GetCenX();
	int& GetCenY();
private:
	int x, y;
	int v_x, v_y;
	bool isFired;
	IMAGE src;
	IMAGE mask;
	int length;
	int dir;
	int h, w;
	int cen_x, cen_y;
};
