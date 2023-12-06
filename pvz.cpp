#include<iostream>
#include<graphics.h>
#include<cstring>
#include<vector>
#include"tools.hpp"
using namespace std;
//建立开始界面
class Start
{
public:
	IMAGE img;
	int x1, x2, y1, y2;//开始框的左上方和右下方的坐标
	string location;
	bool flag = false;
	Start(int x1, int y1, int x2, int y2, string location) :x1(x1), x2(x2), y1(y1), y2(y2), location(location) {}
};


//鼠标移动到某个位置时，通过颜色变化来指示所选位置
//x1<x2,y1<y2
bool RectangleInstruct(int x, int y, int x1, int y1, int x2, int y2, bool flag)
{
	if (x<x2 && x>x1 && y > y1 && y < y2 && flag == false)
	{
		setlinestyle(PS_SOLID, 5);
		setlinecolor(WHITE);
		rectangle(x1, y1, x2, y2);
		return true;
	}
	return false;
}

//所有的植物种类
enum floristics{wandou,xaingrikui,jianguo};

//建立关卡类
class pass
{
public:
	IMAGE img;
	string location;
	int sizex, sizey;
	void movescene(IMAGE img, LPCTSTR locaiton, int sizex, int sizey);
	void show_colume();
	pass(string location, int sizex, int sizey,vector<int> plants):location(location),sizex(sizex),sizey(sizey),plants(plants){}
	void show_plants();
	//本关植物编号的数组
	vector<int>plants;
};



//建立植物类
class plant
{
public:
	vector<IMAGE> create_img_plants(int num);
};

vector<IMAGE> plant::create_img_plants(int num)
{
	vector<IMAGE>img_plant(num);
	return img_plant;
}

//豌豆
class wan_dou:public plant
{
public:
	int order;
	wan_dou(int x):order(x){}
};

//创建豌豆对象
wan_dou wanDou(13);
//img_wandou变量储存豌豆的13张图片IMAGE指针
vector<IMAGE>img_wandou = wanDou.create_img_plants(wanDou.order);

//向日葵
class xiang_ri_kui :public plant
{

};

//坚果
class jian_guo :public plant
{

};

//导入第n关的图片
void enter(IMAGE& img, LPCTSTR location)
{
	//cleardevice();
	loadimage(&img, location,900,600);
	putimage(0, 0, &img);
}


void pass::movescene(IMAGE img, LPCTSTR location, int sizex, int sizey)
{
	//向右移动
	for (int back_x = 0; back_x >= -350; back_x -= 3)
	{
		cleardevice();
		loadimage(&img, location, sizex,sizey,1);
		putimage(back_x, 0, &img);
		FlushBatchDraw();
	}
	//停留2秒
	Sleep(2000);

	//向左移动
	for (int back_x = -350; back_x <= -190; back_x += 3)
	{
		cleardevice();
		loadimage(&img, location,sizex,sizey,1);
		putimage(back_x, 0, &img);
		FlushBatchDraw();
	}
}

void pass::show_colume()
{
	IMAGE col;
	loadimage(&col, "sucai/column.png");
	putimage(100, 0, &col);
}

void pass::show_plants()
{
	vector<IMAGE>plant(plants.size());
	for (int i = 0; i < plants.size(); i++)
	{
		char name[32];
		sprintf_s(name, sizeof(name), "sucai/%d.png", plants[i]);
		loadimage(&plant[i], name);
		putimage(182 + 56 * i , 6, &plant[i]);
	}
}

IMAGE background; // 用于保存背景的 IMAGE 对象
bool backgroundSaved = false; // 是否已保存背景

void saveBackground(int x, int y)
{
		getimage(&background, x, y, getwidth(), getheight());
}

void restoreBackground(int x, int y)
{
	putimage(x, y, &background);
}

int curx, cury;//当前选中的植物，在移动过程中的位置
int curZhiWu = 0;	//0:没有选中，1：选择了一种植物
//用户点击,实现植物放置和拖拽
bool finish = 0;
bool dragging = 0;
void userClick(int count)
{
	ExMessage msg;
	static bool status = 0;
	if (peekmessage(&msg,EX_MOUSE))
	{
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x > 182 && msg.x < 182 + 56 * count && msg.y>6 && msg.y < 96)
			{
				int index = (msg.x - 182) / 56;
				curZhiWu = index + 1;
				dragging = 1;
			}
		}
		else if (msg.message == WM_MOUSEMOVE && dragging==1)
		{
			//记录当前位置
			cleardevice();
			curx = msg.x - 28 / 2;
			cury = msg.y - 45 / 2;
			restoreBackground(0,0);
			switch (curZhiWu - 1)
			{
			case(wandou):
				drawImg(curx, cury, &img_wandou[0]);
			}

		}
		else if (msg.message == WM_LBUTTONUP&&dragging==1) 
		{
			finish = 1;
			dragging = 0;
		}
	}
}

int main()
{
	initgraph(900, 600, EX_SHOWCONSOLE);
	Start start(279, 321, 425, 395,"Logo.jpg");


	//获取鼠标信息
	ExMessage msg;
	while (true)
	{
		enter(start.img, start.location.c_str());
		if (peekmessage(&msg, EX_MOUSE))
		{
			int x = msg.x;
			int y = msg.y;
			if (RectangleInstruct(x, y, start.x1, start.y1, start.x2, start.y2, start.flag) && msg.message == WM_LBUTTONDOWN)
			{
				start.flag = true;
				/*MessageBox(NULL, "通关", "恭喜通关", MB_OK);*/
				Sleep(1000);
				break;
				//跳转到第一关
			}
			else if (!RectangleInstruct(x, y, start.x1, start.y1, start.x2, start.y2, start.flag) && start.flag)
			{
				start.flag = false;
				cleardevice();
				enter(start.img, start.location.c_str());
			}
		}
	}
	//第一关植物
	vector<int> pass1_plants = { wandou,xaingrikui,jianguo };
	//建立第一关
	pass pass1("pass1.jpg", 1250, 600, pass1_plants);
	BeginBatchDraw();
	enter(pass1.img, pass1.location.c_str());
	//场景移动
	pass1.movescene(pass1.img, pass1.location.c_str(), pass1.sizex, pass1.sizey);
	//植物卡槽
	pass1.show_colume();
	pass1.show_plants();
	
	//load第一关的植物种类
	for (int i = 0; i < pass1_plants.size(); i++)
	{
		switch (pass1_plants[i])
		{
		case(wandou):
		{
			//char name_wandou[64]存储豌豆图片地址
			char name_wandou[64];
			for (int j = 1; j <= 13; j++)
			{
				sprintf_s(name_wandou, sizeof(name_wandou), "豌豆/%d.png", j);
				loadimage(&img_wandou[j - 1], name_wandou);
			}
		}
		}
	}
	//记录第一关是否通关
	bool pass1_flag=0;

	while (!pass1_flag)
	{
		BeginBatchDraw();
		if (!dragging) {
			// 如果不是在拖拽状态，就保存整个屏幕作为背景
			saveBackground(0,0);
		}
		userClick(pass1.plants.size());

		// 如果放置结束，清除背景保存标志
		if (finish)
		{
			backgroundSaved = false;
			finish = false;
		}

		FlushBatchDraw();
	}
	system("pause");
	return 0;
}
