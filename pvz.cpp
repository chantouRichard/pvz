#include<iostream>
#include<graphics.h>
#include<cstring>
using namespace std;
//陈涛嘿嘿
//植物类型种类
enum { wandou, xiangrikui, jianguo, plant_count };
IMAGE plant[plant_count];
void begin()
{
	IMAGE col;
	loadimage(&col, L"sucai2/column.png");
	putimage(100, 0, &col);
}
void movescene()
{
	int back_x = 0;
	int i = 0;
	for (back_x = 0; back_x >= -350; back_x -= 5)
	{
		IMAGE img;
		cleardevice();
		loadimage(&img, L"sucai/map.jpg", 1250, 600);
		putimage(back_x, 0, &img);
		FlushBatchDraw();
	}
}
void wait()
{
	int i = 0;
	for (i = 0; i < 200; i+=4)
	{
		IMAGE img;
		cleardevice();
		loadimage(&img, L"sucai/map.jpg", 1250, 600);
		putimage(-350, 0, &img);
		FlushBatchDraw();
	}
}
void moveback()
{
	int back_x;
	for (back_x = -350; back_x <= -190; back_x += 5)
	{
		IMAGE img;
		cleardevice();
		loadimage(&img, L"sucai/map.jpg", 1250, 600);
		putimage(back_x, 0, &img);
		FlushBatchDraw();
	}
}
void column_move()
{
	IMAGE col, img;
	loadimage(&col, L"sucai2/column.png");
	loadimage(&img, L"sucai/map.jpg", 1250, 600);
	int i;
	for (i = -87; i <= 0; i +=0.3)
	{
		cleardevice();
		putimage(-190, 0, &img);
		putimage(200, i, &col);
		FlushBatchDraw();
	}
}
//显示植物卡牌
class show_plant
{
public:
	show_plant()
	{
		for (i = 1; i <= plant_count; i++)
		{
			sprintf_s(name, sizeof(name), "sucai2/%d.png", i);
			loadimage(&plant[i],name);
			putimage(79 + 55 * (i - 1), 6, &plant[i]);
		}
	}
private:
	int i;
	char name[32];
};


int main()
{
	IMAGE img;
	IMAGE col;
	initgraph(900, 600, 1);
	cleardevice();
	loadimage(&img, L"sucai/map.jpg", 1250, 600);
	putimage(0, 0, &img);
	BeginBatchDraw();
	movescene();
	wait();
	moveback();
	column_move();
	EndBatchDraw();
	system("pause");
	return 0;
}
