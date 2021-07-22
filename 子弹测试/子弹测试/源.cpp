#include "Bullet.h"
#include "head.h"
#include "Role.h"
#include <cmath>
#include <ctime>
#include "Start.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
void MAP_1();
void MAP_2();
void MAP_3();
void MAP_4();
int map[ROW][COL];
int map_flags;
IMAGE gather;
IMAGE img[3];
bool endGame = false;
bool isAgain = false;
void DataGather(Role& p1, Role& p2);
void EndJudge(Role& p1, Role& p2)
{
	double length = sqrt(pow(p1.GetBt().GetCenX() - (p2.GetCenX() + p2.GetW() / 2), 2) + pow(p1.GetBt().GetCenY() - (p2.GetCenY() + p2.GetH() / 2), 2));
	if (length <= p2.GetW() && p1.GetBt().GetIsFired())
	{
		mciSendString(_T("STOP BEGIN1"), 0, 0, 0);
		Sleep(2000);
		p1.GetIsWin() = true;
		endGame = true;
	}
}
void transparentimage(int x, int y, IMAGE& src, IMAGE& mask)
{
	putimage(x, y, &mask, SRCAND);
	putimage(x, y, &src, SRCPAINT);
}
bool BtDistance(Role& tmp)
{
	double distance = sqrt(pow((tmp.GetBt().GetX() - tmp.GetX()), 2) + pow((tmp.GetBt().GetY() - tmp.GetY()), 2));
	return tmp.GetBt().GetLength() > distance;
}
void DrawPer(Role& tmp, Role& tmp_)
{
	if (map_flags == MAP1)
	{
		setbkcolor(RGB(237, 174, 89));
	}
	else if (map_flags == MAP2)
	{
		setbkcolor(RGB(186, 186, 184));
	}
	else if (map_flags == MAP3)
	{
		setbkcolor(RGB(80, 160, 1));
	}
	else
	{
		setbkcolor(RGB(45, 45, 48));
	}
	cleardevice();
	for (size_t i = 0; i < ROW; i++)
	{
		for (size_t k = 0; k < COL; k++)
		{
			switch (map[i][k])
			{
			case WALL:
				putimage(k * WALL_BRICK_SIZE, i * WALL_BRICK_SIZE, &img[0]);
				break;
			case BRICK:
				putimage(k * WALL_BRICK_SIZE, i * WALL_BRICK_SIZE, &img[1]);
				break;
			}
		}
	}
	putimage(tmp.GetX(), tmp.GetY(), tmp.GetW(), tmp.GetH(), &tmp.GetImg()[1], tmp.GetImgX() * tmp.GetW(), tmp.GetImgY() * tmp.GetH(), NOTSRCERASE);
	putimage(tmp.GetX(), tmp.GetY(), tmp.GetW(), tmp.GetH(), &tmp.GetImg()[0], tmp.GetImgX() * tmp.GetW(), tmp.GetImgY() * tmp.GetH(), SRCINVERT);
	if (tmp.GetBt().GetIsFired())
	{
		transparentimage(tmp.GetBt().GetX(), tmp.GetBt().GetY(), tmp.GetBt().GetSrc(), tmp.GetBt().GetMask());
	}

	putimage(tmp_.GetX(), tmp_.GetY(), tmp_.GetW(), tmp_.GetH(), &tmp_.GetImg()[1], tmp_.GetImgX() * tmp_.GetW(), tmp_.GetImgY() * tmp_.GetH(), NOTSRCERASE);
	putimage(tmp_.GetX(), tmp_.GetY(), tmp_.GetW(), tmp_.GetH(), &tmp_.GetImg()[0], tmp_.GetImgX() * tmp_.GetW(), tmp_.GetImgY() * tmp_.GetH(), SRCINVERT);
	if (tmp_.GetBt().GetIsFired())
	{
		transparentimage(tmp_.GetBt().GetX(), tmp_.GetBt().GetY(), tmp_.GetBt().GetSrc(), tmp_.GetBt().GetMask());
	}
}
void BtMove(Role& tmp)
{
	if (tmp.GetBt().GetIsFired() == false) // 确保子弹在身上
	{
		switch (tmp.GetBt().GetDir())
		{
		case TOP:
			tmp.GetBt().GetX() = tmp.GetX() + tmp.GetW() / 2;
			tmp.GetBt().GetY() = tmp.GetY();
			break;
		case BOTTOM:
			tmp.GetBt().GetX() = tmp.GetX() + tmp.GetW() / 2;
			tmp.GetBt().GetY() = tmp.GetY() + tmp.GetH();
			break;
		case LEFT:
			tmp.GetBt().GetX() = tmp.GetX();
			tmp.GetBt().GetY() = tmp.GetY() + tmp.GetH() / 2;
			break;
		case RIGHT:
			tmp.GetBt().GetX() = tmp.GetX() + tmp.GetW();
			tmp.GetBt().GetY() = tmp.GetY() + tmp.GetH() / 2;
			break;
		default:
			break;
		}
	}
	else if (BtDistance(tmp))
	{
		switch (tmp.GetBt().GetDir())
		{
		case TOP:
			if (map[(tmp.GetBt().GetY() - tmp.GetBt().GetVX()) / WALL_BRICK_SIZE][(tmp.GetBt().GetX()) / WALL_BRICK_SIZE] == BRICK)
			{
				tmp.GetBt().GetIsFired() = false;
				map[(tmp.GetBt().GetY() - tmp.GetBt().GetVX()) / WALL_BRICK_SIZE][(tmp.GetBt().GetX()) / WALL_BRICK_SIZE] = SPACE;
			}
			else if (map[(tmp.GetBt().GetY() - tmp.GetBt().GetVX()) / WALL_BRICK_SIZE][(tmp.GetBt().GetX()) / WALL_BRICK_SIZE] == WALL)
			{
				tmp.GetBt().GetIsFired() = false;
			}
			else
			{
				tmp.GetBt().GetY() -= tmp.GetBt().GetVY();
			}
			break;
		case BOTTOM:
			if (map[(tmp.GetBt().GetY() + tmp.GetBt().GetVX()) / WALL_BRICK_SIZE][(tmp.GetBt().GetX()) / WALL_BRICK_SIZE] == BRICK)
			{
				tmp.GetBt().GetIsFired() = false;
				map[(tmp.GetBt().GetY() + tmp.GetBt().GetVX()) / WALL_BRICK_SIZE][(tmp.GetBt().GetX()) / WALL_BRICK_SIZE] = SPACE;
			}
			else if (map[(tmp.GetBt().GetY() + tmp.GetBt().GetVX()) / WALL_BRICK_SIZE][(tmp.GetBt().GetX()) / WALL_BRICK_SIZE] == WALL)
			{
				tmp.GetBt().GetIsFired() = false;
			}
			else
			{
				tmp.GetBt().GetY() += tmp.GetBt().GetVY();
			}
			break;
		case LEFT:
			if (map[tmp.GetBt().GetY() / WALL_BRICK_SIZE][(tmp.GetBt().GetX() - tmp.GetBt().GetVX()) / WALL_BRICK_SIZE] == BRICK)
			{
				tmp.GetBt().GetIsFired() = false;
				map[tmp.GetBt().GetY() / WALL_BRICK_SIZE][(tmp.GetBt().GetX() - tmp.GetBt().GetVX()) / WALL_BRICK_SIZE] = SPACE;
			}
			else if (map[tmp.GetBt().GetY() / WALL_BRICK_SIZE][(tmp.GetBt().GetX() - tmp.GetBt().GetVX()) / WALL_BRICK_SIZE] == WALL)
			{
				tmp.GetBt().GetIsFired() = false;
			}
			else
			{
				tmp.GetBt().GetX() -= tmp.GetBt().GetVX();
			}
			break;
		case RIGHT:
			if (map[tmp.GetBt().GetY() / WALL_BRICK_SIZE][(tmp.GetBt().GetX() + tmp.GetBt().GetVX()) / WALL_BRICK_SIZE] == BRICK)
			{
				tmp.GetBt().GetIsFired() = false;
				map[tmp.GetBt().GetY() / WALL_BRICK_SIZE][(tmp.GetBt().GetX() + tmp.GetBt().GetVX()) / WALL_BRICK_SIZE] = SPACE;
			}
			else if (map[tmp.GetBt().GetY() / WALL_BRICK_SIZE][(tmp.GetBt().GetX() + tmp.GetBt().GetVX()) / WALL_BRICK_SIZE] == WALL)
			{
				tmp.GetBt().GetIsFired() = false;
			}
			else
			{
				tmp.GetBt().GetX() += tmp.GetBt().GetVX();
			}
			break;
		default:
			break;
		}
	}
	else
	{
		tmp.GetBt().GetIsFired() = false;
	}
}
void RoleMove(Role& tmp, Role& tmp_)
{
	Sleep(80);
	if (GetAsyncKeyState(VK_UP)) 
	{
		tmp.GetDir() = TOP;
		tmp.GetImgY() = 1;
		tmp.GetImgX()++;
		if (tmp.GetImgX() >= 3)
		{
			tmp.GetImgX() = 0;
		}
		if ((map[(tmp.GetY() - tmp.GetVX()) / WALL_BRICK_SIZE][tmp.GetX() / WALL_BRICK_SIZE] == SPACE  
			&& map[(tmp.GetY() - tmp.GetVX()) / WALL_BRICK_SIZE][(tmp.GetX() + tmp.GetW()) / WALL_BRICK_SIZE] == SPACE)
			|| (map[(tmp.GetY() - tmp.GetVX()) / WALL_BRICK_SIZE][tmp.GetX() / WALL_BRICK_SIZE] == ROLE  
				&& map[(tmp.GetY() - tmp.GetVX()) / WALL_BRICK_SIZE][(tmp.GetX() + tmp.GetW()) / WALL_BRICK_SIZE] == ROLE))
		{
			tmp.GetY() -= tmp.GetVX();
		}
	}
	if (GetAsyncKeyState(VK_DOWN)) 
	{
		tmp.GetDir() = BOTTOM;

		tmp.GetImgY() = 0;
		tmp.GetImgX()++;
		if (tmp.GetImgX() >= 3)
		{
			tmp.GetImgX() = 0;
		}
		if ((map[(tmp.GetY() + tmp.GetH() + tmp.GetVX()) / WALL_BRICK_SIZE][tmp.GetX() / WALL_BRICK_SIZE] == SPACE  
			&& map[(tmp.GetY() + tmp.GetH() + tmp.GetVX()) / WALL_BRICK_SIZE][(tmp.GetX() + tmp.GetW()) / WALL_BRICK_SIZE] == SPACE)
			|| (map[(tmp.GetY() + tmp.GetH() + tmp.GetVX()) / WALL_BRICK_SIZE][tmp.GetX() / WALL_BRICK_SIZE] == ROLE
				&& map[(tmp.GetY() + tmp.GetH() + tmp.GetVX()) / WALL_BRICK_SIZE][(tmp.GetX() + tmp.GetW()) / WALL_BRICK_SIZE] == ROLE))
		{
			tmp.GetY() += tmp.GetVX();
		}
	}
	if (GetAsyncKeyState(VK_LEFT)) 
	{
		tmp.GetDir() = LEFT;

		tmp.GetImgY() = 2;
		tmp.GetImgX()++;
		if (tmp.GetImgX() >= 3)
		{
			tmp.GetImgX() = 0;
		}
		if ((map[tmp.GetY() / WALL_BRICK_SIZE][(tmp.GetX() - tmp.GetVX()) / WALL_BRICK_SIZE] == SPACE  
			&& map[(tmp.GetY() + tmp.GetH()) / WALL_BRICK_SIZE][(tmp.GetX() - tmp.GetVX()) / WALL_BRICK_SIZE] == SPACE)
			|| (map[tmp.GetY() / WALL_BRICK_SIZE][(tmp.GetX() - tmp.GetVX()) / WALL_BRICK_SIZE] == ROLE
				&& map[(tmp.GetY() + tmp.GetH()) / WALL_BRICK_SIZE][(tmp.GetX() - tmp.GetVX()) / WALL_BRICK_SIZE] == ROLE))
		{
			tmp.GetX() -= tmp.GetVX();
		}
	}
	if (GetAsyncKeyState(VK_RIGHT)) 
	{
		tmp.GetDir() = RIGHT;

		tmp.GetImgY() = 5;
		tmp.GetImgX()++;
		if (tmp.GetImgX() >= 3)
		{
			tmp.GetImgX() = 0;
		}
		if ((map[tmp.GetY() / WALL_BRICK_SIZE][(tmp.GetX() + tmp.GetW() + tmp.GetVX()) / WALL_BRICK_SIZE] == SPACE  
			&& map[(tmp.GetY() + tmp.GetH()) / WALL_BRICK_SIZE][(tmp.GetX() + tmp.GetW() + tmp.GetVX()) / WALL_BRICK_SIZE] == SPACE)
			|| (map[tmp.GetY() / WALL_BRICK_SIZE][(tmp.GetX() + tmp.GetW() + tmp.GetVX()) / WALL_BRICK_SIZE] == ROLE
				&& map[(tmp.GetY() + tmp.GetH()) / WALL_BRICK_SIZE][(tmp.GetX() + tmp.GetW() + tmp.GetVX()) / WALL_BRICK_SIZE] == ROLE))
		{
			tmp.GetX() += tmp.GetVX();
		}
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		tmp.GetBSN()++;
		tmp.GetBt().GetIsFired() = true;
	}



	if (GetAsyncKeyState(0x57))
	{
		tmp_.GetDir() = TOP;
		tmp_.GetImgY() = 1;
		tmp_.GetImgX()++;
		if (tmp_.GetImgX() >= 3)
		{
			tmp_.GetImgX() = 0;
		}
		if ((map[(tmp_.GetY() - tmp_.GetVX()) / WALL_BRICK_SIZE][tmp_.GetX() / WALL_BRICK_SIZE] == SPACE
			&& map[(tmp_.GetY() - tmp_.GetVX()) / WALL_BRICK_SIZE][(tmp_.GetX() + tmp_.GetW()) / WALL_BRICK_SIZE] == SPACE)
			|| (map[(tmp_.GetY() - tmp_.GetVX()) / WALL_BRICK_SIZE][tmp_.GetX() / WALL_BRICK_SIZE] == ROLE
				&& map[(tmp_.GetY() - tmp_.GetVX()) / WALL_BRICK_SIZE][(tmp_.GetX() + tmp_.GetW()) / WALL_BRICK_SIZE] == ROLE))
		{
			tmp_.GetY() -= tmp_.GetVX();
		}
	}
	if (GetAsyncKeyState(0x53))
	{
		tmp_.GetDir() = BOTTOM;

		tmp_.GetImgY() = 0;
		tmp_.GetImgX()++;
		if (tmp_.GetImgX() >= 3)
		{
			tmp_.GetImgX() = 0;
		}
		if ((map[(tmp_.GetY() + tmp_.GetH() + tmp_.GetVX()) / WALL_BRICK_SIZE][tmp_.GetX() / WALL_BRICK_SIZE] == SPACE
			&& map[(tmp_.GetY() + tmp_.GetH() + tmp_.GetVX()) / WALL_BRICK_SIZE][(tmp_.GetX() + tmp_.GetW()) / WALL_BRICK_SIZE] == SPACE)
			|| (map[(tmp_.GetY() + tmp_.GetH() + tmp_.GetVX()) / WALL_BRICK_SIZE][tmp_.GetX() / WALL_BRICK_SIZE] == ROLE
				&& map[(tmp_.GetY() + tmp_.GetH() + tmp_.GetVX()) / WALL_BRICK_SIZE][(tmp_.GetX() + tmp_.GetW()) / WALL_BRICK_SIZE] == ROLE))
		{
			tmp_.GetY() += tmp_.GetVX();
		}
	}
	if (GetAsyncKeyState(0x41))
	{
		tmp_.GetDir() = LEFT;

		tmp_.GetImgY() = 2;
		tmp_.GetImgX()++;
		if (tmp_.GetImgX() >= 3)
		{
			tmp_.GetImgX() = 0;
		}
		if ((map[tmp_.GetY() / WALL_BRICK_SIZE][(tmp_.GetX() - tmp_.GetVX()) / WALL_BRICK_SIZE] == SPACE
			&& map[(tmp_.GetY() + tmp_.GetH()) / WALL_BRICK_SIZE][(tmp_.GetX() - tmp_.GetVX()) / WALL_BRICK_SIZE] == SPACE)
			|| (map[tmp_.GetY() / WALL_BRICK_SIZE][(tmp_.GetX() - tmp_.GetVX()) / WALL_BRICK_SIZE] == ROLE
				&& map[(tmp_.GetY() + tmp_.GetH()) / WALL_BRICK_SIZE][(tmp_.GetX() - tmp_.GetVX()) / WALL_BRICK_SIZE] == ROLE))
		{
			tmp_.GetX() -= tmp_.GetVX();
		}
	}
	if (GetAsyncKeyState(0x44))
	{
		tmp_.GetDir() = RIGHT;

		tmp_.GetImgY() = 5;
		tmp_.GetImgX()++;
		if (tmp_.GetImgX() >= 3)
		{
			tmp_.GetImgX() = 0;
		}
		if ((map[tmp_.GetY() / WALL_BRICK_SIZE][(tmp_.GetX() + tmp_.GetW() + tmp_.GetVX()) / WALL_BRICK_SIZE] == SPACE
			&& map[(tmp_.GetY() + tmp_.GetH()) / WALL_BRICK_SIZE][(tmp_.GetX() + tmp_.GetW() + tmp_.GetVX()) / WALL_BRICK_SIZE] == SPACE)
			|| (map[tmp_.GetY() / WALL_BRICK_SIZE][(tmp_.GetX() + tmp_.GetW() + tmp_.GetVX()) / WALL_BRICK_SIZE] == ROLE
				&& map[(tmp_.GetY() + tmp_.GetH()) / WALL_BRICK_SIZE][(tmp_.GetX() + tmp_.GetW() + tmp_.GetVX()) / WALL_BRICK_SIZE] == ROLE))
		{
			tmp_.GetX() += tmp_.GetVX();
		}
	}
	if (GetAsyncKeyState(VK_RETURN))
	{
		tmp_.GetBSN()++;
		tmp_.GetBt().GetIsFired() = true;
	}
}
void GameInit()
{
	
	//初始化前后两列
	for (int i = 0; i < ROW; i++)
	{
		map[i][0] = map[i][COL - 1] = WALL;
	}
	//初始化上下两行
	for (size_t i = 0; i < COL; i++)
	{
		map[0][i] = map[ROW - 1][i] = WALL;
	}
	if (map_flags == MAP1)
	{
		MAP_1();
	}
	else if (map_flags == MAP2)
	{
		MAP_2();
	}
	else if (map_flags == MAP3)
	{
		MAP_3();
	}
	else
	{
		MAP_4();
	}
}
void Game(Role& p1, Role& p2)
{
	mciSendString(_T("open ./音效/背景1.mp3 alias BEGIN1"), 0, 0, 0);
	mciSendString(_T("play BEGIN1 repeat"), 0, 0, 0);
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	setbkcolor(WHITE);
	cleardevice();
	GameInit();
	BeginBatchDraw();
	while (1)
	{
		DrawPer(p1, p2);
		EndJudge(p1, p2);
		EndJudge(p2, p1);
		if (endGame)
		{
			break;
		}
		FlushBatchDraw();
		cleardevice();
		p1.GetBt().ChangePer(p1);
		p1.GetCenX() = p1.GetX() + p1.GetW() / 2;
		p1.GetCenY() = p1.GetY() + p1.GetH() / 2;
		p2.GetBt().ChangePer(p2);
		p2.GetCenX() = p2.GetX() + p2.GetW() / 2;
		p2.GetCenY() = p2.GetY() + p2.GetH() / 2;
		RoleMove(p1, p2);
		if (p1.GetBt().GetIsFired() == true)
		{
			BtMove(p1);
		}
		if (p2.GetBt().GetIsFired() == true)
		{
			BtMove(p2);
		}
	}
	EndBatchDraw();//必须加
	mciSendString(_T("close BEGIN1"), NULL, 0, 0);

	closegraph();
}
void StartUp()
{
	mciSendString(_T("open ./音效/背景.mp3 alias BEGIN"), 0, 0, 0);
	mciSendString(_T("play BEGIN repeat"), 0, 0, 0);
	Start st;
	initgraph(RIGHT_, DOWN);
	setbkcolor(WHITE);
	cleardevice();
	putimage(0, 0, &st.GetSkin());
	transparentimage(st.GetStartX(), st.GetstartY(), st.GetStart()[0], st.GetStart()[1]);

	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.mkLButton && (msg.x <= st.GetStartX() + START_W && msg.x >= st.GetStartX()) && (msg.y >= st.GetstartY() && msg.y <= st.GetstartY() + START_H))
			{
				cleardevice();
				transparentimage(st.GetStartX(), st.GetstartY(), st.GetStart()[0], st.GetStart()[1]);
				Sleep(50);
				st.GetIsOn() = true;
			}
		}
		if (st.GetIsOn())
		{
			break;
		}
	}
	mciSendString(_T("close BEGIN"), NULL, 0, 0);
	closegraph();
}
void SelectMap()
{
	mciSendString(_T("open ./音效/背景.mp3 alias BEGIN"), 0, 0, 0);
	mciSendString(_T("play BEGIN repeat"), 0, 0, 0);
	initgraph(RIGHT_, DOWN);
	IMAGE selection;
	loadimage(&selection, _T("./Colt/选择地图/选择.png"));
	putimage(0, 0, &selection);
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.mkLButton && (msg.y <= 150 && msg.y >= 0))
			{
				map_flags = MAP1;
				break;

			}
			else if (msg.mkLButton && (msg.y <= 300 && msg.y > 150))
			{
				map_flags = MAP3;
				break;

			}
			else if (msg.mkLButton && (msg.y <= 450 && msg.y > 300))
			{
				map_flags = MAP4;
				break;

			}
			else if (msg.mkLButton && (msg.y <= 600 && msg.y > 450))
			{
				map_flags = MAP2;
				break;
			}
		}
	}
	mciSendString(_T("close BEGIN"), NULL, 0, 0);
	closegraph();
}
void DataGather(Role& p1, Role& p2)
{
	initgraph(RIGHT_, DOWN);
	loadimage(&gather, _T("./Colt/汇总/1.jpeg"));
	int cnt = 0;
	if (p1.GetIsWin() && p2.GetIsWin())
	{
		const char a[] = "  No Winner  ";
		int len = strlen(a);
		while (1)
		{
			putimage(0, 0, &gather);
			settextcolor(BLACK);
			settextstyle(20, 0, _T("隶书"));
			setbkmode(TRANSPARENT);
			settextcolor(RGB(0, 0, 0));
			TCHAR p1_[5];
			outtextxy(0, 100, _T("Player1发射子弹统计："));
			_stprintf_s(p1_, _T("%d"), p1.GetBSN());
			outtextxy(150, 125, p1_);
			outtextxy(0, 150, _T("Player2发射子弹统计："));
			_stprintf_s(p1_, _T("%d"), p2.GetBSN());
			outtextxy(150, 175, p1_);
			settextstyle(50, 0, _T("隶书"));

			for (int i = 0; i < len; i++)
			{
				if (cnt + i < len)
				{
					outtextxy(500, 100 + i * 50, a[i + cnt]);
				}
				else
				{
					outtextxy(500, 100 + i * 50, a[i + cnt - len]);
				}
			}
			Sleep(500);
			if (cnt < len)
			{
				cnt++;
			}
			else
			{
				cnt = 0;
			}
			if (GetAsyncKeyState(VK_SPACE))
			{
				isAgain = true;
				return;
			}
			if (GetAsyncKeyState(0x1B))
			{
				return;
			}
		}
	}
	else if (p1.GetIsWin() && !p2.GetIsWin())
	{

		const char a[] = "  Winner: Player1  ";
		int len = strlen(a);
		while (1)
		{
			settextcolor(BLACK);
			settextstyle(20, 0, _T("隶书"));
			setbkmode(TRANSPARENT);
			settextcolor(RGB(0, 0, 0));
			putimage(0, 0, &gather);
			TCHAR p1_[5];
			outtextxy(0, 100, _T("Player1发射子弹统计："));
			_stprintf_s(p1_, _T("%d"), p1.GetBSN());
			outtextxy(150, 125, p1_);
			outtextxy(0, 150, _T("Player2发射子弹统计："));
			_stprintf_s(p1_, _T("%d"), p2.GetBSN());
			outtextxy(150, 175, p1_);
			settextstyle(50, 0, _T("隶书"));

			for (int i = 0; i < len; i++)
			{
				if (cnt + i < len)
				{
					outtextxy(500, 100 + i * 50, a[i + cnt]);
				}
				else
				{
					outtextxy(500, 100 + i * 50, a[i + cnt - len]);
				}
			}
			Sleep(500);
			if (cnt < len)
			{
				cnt++;
			}
			else
			{
				cnt = 0;
			}
			if (GetAsyncKeyState(VK_SPACE))
			{
				isAgain = true;
				return;
			}
			if (GetAsyncKeyState(0x1B))
			{
				return;
			}
		}
	}
	else if (!p1.GetIsWin() && p2.GetIsWin())
	{
		const char a[] = "  Winner: Player2  ";
		int len = strlen(a);
		while (1)
		{
			settextcolor(BLACK);
			settextstyle(20, 0, _T("隶书"));
			setbkmode(TRANSPARENT);
			settextcolor(RGB(0, 0, 0));
			putimage(0, 0, &gather);
			TCHAR p1_[5];
			outtextxy(0, 100, _T("Player1发射子弹统计："));
			_stprintf_s(p1_, _T("%d"), p1.GetBSN());
			outtextxy(150, 125, p1_);
			outtextxy(0, 150, _T("Player2发射子弹统计："));
			_stprintf_s(p1_, _T("%d"), p2.GetBSN());
			outtextxy(150, 175, p1_);
			settextstyle(50, 0, _T("隶书"));

			for (int i = 0; i < len; i++)
			{
				if (cnt + i < len)
				{
					outtextxy(500, 100 + i * 50, a[i + cnt]);
				}
				else
				{
					outtextxy(500, 100 + i * 50, a[i + cnt - len]);
				}
			}
			Sleep(500);
			if (cnt < len)
			{
				cnt++;
			}
			else
			{
				cnt = 0;
			}
			if (GetAsyncKeyState(VK_SPACE))
			{
				isAgain = true;
				return;
			}
			if (GetAsyncKeyState(0x1B))
			{
				return;
			}
		}
	}
	else
	{
		const char a[] = "  No Winner  ";
		int len = strlen(a);
		while (1)
		{
			settextcolor(BLACK);
			settextstyle(20, 0, _T("隶书"));
			setbkmode(TRANSPARENT);
			settextcolor(RGB(0, 0, 0));
			putimage(0, 0, &gather);
			TCHAR p1_[5];
			outtextxy(0, 100, _T("Player1发射子弹统计："));
			_stprintf_s(p1_, _T("%d"), p1.GetBSN());
			outtextxy(150, 125, p1_);
			outtextxy(0, 150, _T("Player2发射子弹统计："));
			_stprintf_s(p1_, _T("%d"), p2.GetBSN());
			outtextxy(150, 175, p1_);
			settextstyle(50, 0, _T("隶书"));

			for (int i = 0; i < len; i++)
			{
				if (cnt + i < len)
				{
					outtextxy(500, 100 + i * 50, a[i + cnt]);
				}
				else
				{
					outtextxy(500, 100 + i * 50, a[i + cnt - len]);
				}
			}
			Sleep(500);
			if (cnt < len)
			{
				cnt++;
			}
			else
			{
				cnt = 0;
			}
			if (GetAsyncKeyState(VK_SPACE))
			{
				isAgain = true;
				return;
			}
			if (GetAsyncKeyState(0x1B))
			{
				return;
			}
		}
	}
	closegraph();
}
int main()
{
	Role p1(1), p2(2);

	StartUp();
	again:
	SelectMap();
	Game(p1, p2);
	DataGather(p1, p2);
	if (isAgain == true)
	{
		goto again;
	}
	return 0;
}

void MAP_1()
{
	map_flags = MAP1;
	loadimage(&img[0], _T("./images/MAP_1/wall_墙.jpg"));
	loadimage(&img[1], _T("./images/MAP_1/brick_砖.jpg"));
	map[1][4] = WALL; map[1][22] = WALL;
	map[2][5] = WALL; map[2][1] = WALL;
	map[3][6] = WALL; map[3][20] = WALL;
	map[4][3] = WALL; map[4][7] = WALL; map[4][19] = WALL; map[4][24] = WALL;
	map[5][4] = WALL; map[5][8] = WALL; map[5][9] = WALL; map[5][10] = WALL; map[5][11] = WALL; map[5][12] = WALL; map[5][13] = WALL; map[5][14] = WALL; map[5][15] = WALL; map[5][16] = WALL; map[5][17] = WALL; map[5][18] = WALL; map[5][23] = WALL;
	map[6][5] = WALL; map[6][9] = WALL; map[6][15] = WALL; map[6][22] = WALL;
	map[7][6] = WALL;
	map[8][7] = WALL; map[8][13] = WALL; map[8][19] = WALL;
	map[9][20] = WALL;
	map[10][4] = WALL; map[10][11] = WALL; map[10][17] = WALL; map[10][21] = WALL;
	map[11][3] = WALL; map[11][8] = WALL; map[11][9] = WALL; map[11][10] = WALL; map[11][11] = WALL; map[11][12] = WALL; map[11][13] = WALL; map[11][14] = WALL; map[11][15] = WALL; map[11][16] = WALL; map[11][17] = WALL; map[11][18] = WALL; map[11][23] = WALL;
	map[12][2] = WALL; map[12][7] = WALL; map[12][19] = WALL; map[12][23] = WALL;
	map[13][1] = WALL; map[13][6] = WALL; map[13][20] = WALL;
	map[14][5] = WALL; map[14][21] = WALL;
	map[15][4] = WALL; map[15][22] = WALL;
	for (int i = 0; i < BRICK_NUM; i++)
	{
		int r = rand() % ROW;//5%2=1   7%2=1
		int c = rand() % COL;
		if (map[r][c] == SPACE)
		{
			map[r][c] = BRICK;
		}
	}
}

void MAP_2()
{
	map_flags = MAP2;
	loadimage(&img[0], _T("./images/MAP_2/墙_src.png"));
	loadimage(&img[1], _T("./images/MAP_2/箱子_src.png"));
	loadimage(&img[2], _T("./images/MAP_2/箱子_mask.png"));

	map[1][4] = WALL; map[1][13] = WALL; map[1][22] = WALL;
	map[2][4] = WALL; map[2][22] = WALL;
	map[3][11] = WALL; map[3][15] = WALL;
	map[4][11] = WALL; map[4][15] = WALL;
	map[5][2] = WALL; map[5][3] = WALL; map[5][4] = WALL; map[5][5] = WALL; map[5][6] = WALL; map[5][7] = WALL; map[5][8] = WALL; map[5][24] = WALL; map[5][11] = WALL; map[5][12] = WALL; map[5][14] = WALL; map[5][15] = WALL; map[5][18] = WALL; map[5][19] = WALL; map[5][20] = WALL; map[5][21] = WALL; map[5][22] = WALL; map[5][23] = WALL;
	map[6][8] = WALL; map[6][18] = WALL;
	map[8][13] = WALL;
	map[10][8] = WALL; map[10][18] = WALL;
	map[11][2] = WALL; map[11][3] = WALL; map[11][4] = WALL; map[11][5] = WALL; map[11][6] = WALL; map[11][7] = WALL; map[11][8] = WALL; map[11][11] = WALL; map[11][24] = WALL; map[11][12] = WALL; map[11][14] = WALL; map[11][15] = WALL; map[11][18] = WALL; map[11][19] = WALL; map[11][20] = WALL; map[11][21] = WALL; map[11][22] = WALL; map[11][23] = WALL;
	map[12][11] = WALL; map[12][15] = WALL;
	map[13][11] = WALL; map[13][15] = WALL;
	map[14][4] = WALL; map[14][22] = WALL;
	map[15][4] = WALL; map[15][13] = WALL; map[15][22] = WALL;
	for (int i = 0; i < BRICK_NUM; i++)
	{
		int r = rand() % ROW;//5%2=1   7%2=1
		int c = rand() % COL;
		if (map[r][c] == SPACE)
		{
			map[r][c] = BRICK;
		}
	}
}

void MAP_3()
{
	map_flags = MAP3;
	loadimage(&img[0], _T("./images/MAP_3/树.png"));
	loadimage(&img[1], _T("./images/MAP_3/stone.png"));
	for (int i = 3; i <= 23; i++) {
		map[3][i] = WALL;
		map[13][i] = WALL;
	}
	for (int i = 3; i <= 20; i++) {
		map[6][i] = WALL;
	}
	for (int i = 6; i <= 23; i++) {
		map[10][i] = WALL;
	}
	for (int i = 4; i <= 9; i++) {
		map[i][23] = WALL;
	}
	for (int i = 7; i <= 12; i++) {
		map[i][3] = WALL;
	}
	map[8][13] = WALL;
	for (int i = 0; i < BRICK_NUM; i++)
	{
		int r = rand() % ROW;//5%2=1   7%2=1
		int c = rand() % COL;
		if (map[r][c] == SPACE)
		{
			map[r][c] = BRICK;
		}
	}
}

void MAP_4()
{
	map_flags = MAP4;
	loadimage(&img[0], _T("./images/MAP_4/墙.gif"));
	loadimage(&img[1], _T("./images/MAP_4/障碍.png"));
	for (int i = 3; i <= 11; i++) {
		map[3][i] = WALL;
		map[13][i] = WALL;
	}
	for (int i = 15; i <= 23; i++) {
		map[3][i] = WALL;
		map[13][i] = WALL;
	}
	for (int i = 4; i <= 6; i++) {
		map[i][3] = WALL;
		map[i][23] = WALL;
	}
	for (int i = 10; i <= 12; i++) {
		map[i][3] = WALL;
		map[i][23] = WALL;
	}
	map[5][5] = WALL; map[5][6] = WALL; map[5][20] = WALL; map[5][21] = WALL;
	map[11][5] = WALL; map[11][6] = WALL; map[11][20] = WALL; map[11][21] = WALL;

	map[6][9] = WALL; map[6][17] = WALL; map[10][9] = WALL; map[10][17] = WALL; map[8][13] = WALL;
	map[5][13] = WALL; map[11][13] = WALL;
	for (int i = 0; i < BRICK_NUM; i++)
	{
		int r = rand() % ROW;//5%2=1   7%2=1
		int c = rand() % COL;
		if (map[r][c] == SPACE)
		{
			map[r][c] = BRICK;
		}
	}
}
//遗憾：开始的时候，应该把用一个RoleS类装两个角色类ROLE变成双人，目的是实现添加人物简单，缺点是定型了