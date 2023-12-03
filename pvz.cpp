#include<iostream>
#include<graphics.h>
#include<cstring>
using namespace std;
//建立关卡类
class Start
{
public:
	IMAGE img;
	int x1, x2, y1, y2;//开始框的左上方和右下方的坐标
	string location;
	bool flag = false;
	Start(int x1, int y1, int x2, int y2, string location) :x1(x1), x2(x2), y1(y1), y2(y2),location(location){}
};

//class pass
//{
//private:
//	IMAGE img;
//};


//鼠标移动到某个位置时，通过颜色变化来指示所选位置
//x1<x2,y1<y2
bool RectangleInstruct(int x, int y,int x1,int y1,int x2,int y2,bool flag)
{
	if (x<x2 && x>x1 && y>y1 && y<y2&&flag==false)
	{
		cout << "flag: " << flag;
		setlinestyle(PS_SOLID, 5);
		setlinecolor(WHITE);
		rectangle(x1, y1, x2, y2);
		return true;
	}
	return false;
}

//导入第n关的图片
void enter(IMAGE& img, LPCTSTR location)
{
	//cleardevice();
	loadimage(&img, location);
	putimage(0, 0, &img);
}


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
	initgraph(900, 600, EX_SHOWCONSOLE);
	Start start(279,321,425,395,"C:\\Users\\20443\\Desktop\\程序设计大作业\\图片素材\\Logo.jpg");


	//获取鼠标信息
	ExMessage msg;
	while (true)
	{
		
		enter(start.img, start.location.c_str());
		if (peekmessage(&msg, EX_MOUSE))
		{
			int x = msg.x;
			int y = msg.y;
			if (RectangleInstruct(x, y, start.x1, start.y1, start.x2, start.y2,start.flag)&&msg.message==WM_LBUTTONDOWN)
			{
				start.flag = true;
				MessageBox(NULL, "通关", "恭喜通关", MB_OK);
				break;
			}
			else if (!RectangleInstruct(x, y, start.x1, start.y1, start.x2, start.y2, start.flag) && start.flag)
			{
				start.flag = false;
				cleardevice();
				enter(start.img, start.location.c_str());
			}
		}
	}

	//开始游戏矩形框的选择
	getchar();
	return 0;
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

