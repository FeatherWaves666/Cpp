#pragma once
#include "head.h"
#include <graphics.h>
#include <conio.h>
#include <iostream>
using namespace std;
class Start
{
public:
	Start();
	IMAGE* GetStart();
	bool& GetIsOn();
	IMAGE& GetSkin();
	int& GetStartX();
	int& GetstartY();
private:
	IMAGE start[2];			//[0]��ʼѡ��ͼƬ
							//[1]��ʼ������ͼ
	IMAGE skin;
	bool isOn;
	int start_x;
	int start_y;
};