#include<iostream>
#include<graphics.h>
#include<cstring>
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

//建立关卡类
class pass
{
public:
	IMAGE img;
	string location;
	int sizex, sizey;
	void movescene(IMAGE img, LPCTSTR locaiton, int sizex, int sizey);
	pass(string location, int sizex, int sizey):location(location),sizex(sizex),sizey(sizey){}

};


//导入第n关的图片
void enter(IMAGE& img, LPCTSTR location)
{
	//cleardevice();
	loadimage(&img, location,900,600);
	putimage(0, 0, &img);
}


//植物类型种类
//enum { wandou, xiangrikui, jianguo, plant_count };
//IMAGE plant[plant_count];
//void begin()
//{
//	IMAGE col;
//	loadimage(&col, L"sucai2/column.png");
//	putimage(100, 0, &col);
//}
void pass::movescene(IMAGE img, LPCTSTR location, int sizex, int sizey)
{
	//向右移动
	for (int back_x = 0; back_x >= -350; back_x -= 5)
	{
		cleardevice();
		loadimage(&img, location, sizex,sizey);
		putimage(back_x, 0, &img);
		FlushBatchDraw();
	}
	//停留2秒
	Sleep(2000);

	//向左移动
	for (int back_x = -350; back_x <= -190; back_x += 5)
	{
		cleardevice();
		loadimage(&img, location,sizex,sizey);
		putimage(back_x, 0, &img);
		FlushBatchDraw();
	}

}

////显示植物卡牌
//class show_plant
//{
//public:
//	show_plant()
//	{
//		for (i = 1; i <= plant_count; i++)
//		{
//			sprintf_s(name, sizeof(name), "sucai2/%d.png", i);
//			loadimage(&plant[i], name);
//			putimage(79 + 55 * (i - 1), 6, &plant[i]);
//		}
//	}
//private:
//	int i;
//	char name[32];
//};
//

int main()
{
	initgraph(900, 600, EX_SHOWCONSOLE);
	Start start(279, 321, 425, 395, "C:\\Users\\20443\\Desktop\\程序设计大作业\\图片素材\\Logo.jpg");


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
				Sleep(3000);
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
	pass pass1("C:\\Users\\20443\\Desktop\\程序设计大作业\\图片素材\\第一关场景图.jpg", 1250, 600);
	BeginBatchDraw();
	enter(pass1.img, pass1.location.c_str());
	pass1.movescene(pass1.img, pass1.location.c_str(), pass1.sizex, pass1.sizey);
	//column_move();
	//
		char name[32];
	cout << "hello" << endl;
	loadimage(&col, "sucai2/column.png");
	putimage(200, 0, &col);
	for (int i = 1; i <= plant_count; i++)
	{
		sprintf_s(name, sizeof(name), "sucai2/%d.png", i);
		loadimage(&plant[i-1], name);
		putimage(280 + 55 * (i - 1), 6, &plant[i-1]);
		FlushBatchDraw();
	}
	
	EndBatchDraw();
	system("pause");
	return 0;
}
