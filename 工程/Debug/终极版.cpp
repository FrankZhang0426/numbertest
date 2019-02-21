#include<stdio.h>
#include<graphics.h>
#include <easyx.h>
#include<stdlib.h>
#include<string.h>
#define N 100
typedef struct Plane{
	char ID[10];/*航班代号*/
	char takeoff[20];/*起飞地点*/
	char  land[20];//降落地点
	char data[15];//航班时间
	int max;//航班最大乘客数
	int num;//已经被占用的座位数目
	int price;//飞机票价
}plane[N],airplane;
plane air;
int amount;
MOUSEMSG m;
typedef struct
{
	RECT rc;
	char btn_text[100];
	COLORREF text_color;
	void(*click)();
	int status;
}BUTTON;

int redraw = 0;

void drawbutton(BUTTON *bt, int n);
void mousemove(int x, int y, BUTTON *bt, int n);
void lbuttondown(int x, int y, BUTTON *bt, int n);
void enter();
void printf_one(int i)   /*显示一个记录的函数*/
	{ 
		printf("%11s  %10s  %6s   %6s   %6d  %6d  %6d",air[i].ID,air[i].takeoff,air[i].land,air[i].data,air[i].price,air[i].max,air[i].num); 
	} 
void menu();
void browse() 
{       
	    IMAGE back;
	    closegraph();
	    cleardevice();
		int i; 
	
		puts("\n---------------------------------------------------------------------------------"); 
		printf("\n    航班代号   起飞地点  降落地点   起飞时间  票价  最大乘客   已售票数\n"); 
		for(i=0;i<amount;i++) 
		{ 
			printf_one(i);  
			printf("\n"); 
		}  
		printf("\t\t按任意键返回目录");
	getchar();
	menu();

}
	void search_end()
	{   
		system( "cls" );//DOS清屏
		closegraph();
		int i,m=0; 
		airplane s; 
		printf("\n\nEnter the end Place:"); 
		scanf("%s",s.land);               
		/*输入要到达的地方*/ 
		puts("\n--------------------------------------------------------------------"); 
		printf("\n    航班代号   起飞地点 降落地点   起飞时间    票价  最大乘客   已售票数\n"); 
		for(i=0;i<amount;i++)  
		{ 
			if(strcmp(air[i].land,s.land)==0)  
			{ 
				m++; 
				if((m!=0)&&(m%10==0))               
					/*目的是分屏显示*/       
				{ 
					printf("\n\nPress any key to contiune  . . .");      
					getchar();      
					puts("\n\n");      
				} 
				printf_one(i);      
				printf("\n"); 
				/*调用显示一个记录的函数*/  
			} 
		} 
		puts("\n--------------------------------------------------------------------"); 
		getchar();                         
		/*按任意健*/  getchar();   menu(); 
	}  
	int search()                          /*查找模块*/ 
	{
	    closegraph();
		int i,k; 
		airplane s;  k=-1; 
		system( "cls" ); //DOS清屏函数
		printf("欢迎进入售票窗口!\n"); 
		printf("\n请输入要订票的起飞地点:\n"); 
		scanf("%s",s.takeoff);              
		/*输入要到达的地方*/  
		printf("\n请输入要订票的降落地点:\n");  scanf("%s",s.land);  
		printf("\n请输入要订票的起飞时间:\n"); 
		scanf("%s",s.data);               
		/*输入出发的时间*/  
		for(i=0;i<amount;i++)                 
			/*查找要修改的数据*/ 
		{   
			if(strcmp(s.takeoff,air[i].takeoff)==0&&strcmp(s.land,air[i].land)==0&&strcmp(s.data,air[i].data)==0)   
			{ 
				k=i;                     
				/*找到要修改的记录*/    printf_one(k); 
				break;                 
				/*调用显示一个记录的函数*/   }  } 
				if(k==-1) 
				{ 
					printf("\n\nNO exist!");  
					return -1;  
				}  
				else 
					return k; 
	} 
	void book() 
	{ 
		closegraph;
		int i;  
		i=search(); 
		if(i!=-1) 
		{ 
			if(air[i].num>=air[i].max)  
			{ 
				printf("\n该趟航班票已售完!");  
			}         
			else   
			{
				air[i].num++; 
				printf("\n订票成功!\n");   
			} 
		}  
		else 
			printf("\n该航班不存在!");  
		getchar();  
		getchar();                     
		menu();
	} 
	void back() 
	{ 
		closegraph();
		int i,k=-1; 
		airplane s;  
		system( "cls" );  
		printf("欢迎进入退票窗口!\n"); 
		printf("\n\n输入航班代号:"); 
		scanf("%s",s.ID);                      
		for(i=0;i<amount;i++)                  
		{  
			if(strcmp(s.ID,air[i].ID)==0)   
			{ 
				k=i;                      
				printf_one(k); 
				break;                  
			}  
		} 
		if(k==-1) 
		{ 
			printf("\n\nNO exist!");  
		} 
		else 
		{ 
			air[i].num--; 
			printf("\n退票成功!\n"); 
		} 
		getchar(); 
		getchar();
		menu();
	} 
	void save() 
	{   
		closegraph();
		cleardevice();
		int i,w=1;  FILE *fp;  
		if((fp=fopen("215.txt","wt"))==NULL)      
		{ 
			printf("\nCannot open file\n");  
			return ;
		} 
		for(i=0;i<amount;i++) 
			if(fwrite(&air[i],sizeof(airplane),1,fp)!=1) 
			{        
				printf("file write error\n");   w=0; 
			} 
			if(w==1)  
			{ 
				printf("file save ok!\n"); 
			} 
			fclose(fp);  
			getchar(); 
            menu();    
	}  
void button1_click()
{	
	enter();
}
void button2_click()
{
	browse();
}
void button3_click()
{	
	search_end();
}
void button4_click()
{	
	book();
}
void button5_click()
{
	back();
}
void button6_click()
{
    save();
}
void button7_click()//退出
{
	closegraph();
	exit(1);
}

void menu()
{
	BUTTON bt[7];
	char buttontext[7][100] =
	{	"输入新航班","浏览航班","航班查询","订票","退票","保存","退出"	};
	void(*fun[7])() = { button1_click,button2_click,button3_click,button4_click,button5_click ,button6_click,button7_click};
	IMAGE back;
	loadimage(&back, "background.jpg", 640, 480);
	initgraph(640, 480);
	cleardevice();
	setorigin(0, 0);
	putimage(0, 0, &back);
	for (int i = 0; i < 7; i++)
	{
		bt[i].rc.left = 270;
		bt[i].rc.top = 40+i*60;
		bt[i].rc.right = 370;
		bt[i].rc.bottom = bt[i].rc.top+30;
		strcpy(bt[i].btn_text, buttontext[i]);//将字符串数组里的字符串赋给按钮
		bt[i].text_color = 0xFFFFFF;//字体颜色为白色
		bt[i].status = 0;
		bt[i].click = fun[i];//函数指针指向对应函数
	}

	drawbutton(bt, 7);//绘制主菜单7个按钮

	MOUSEMSG m;						// 定义鼠标消息
	while (true)
	{
		// 获取一条鼠标消息
		while (MouseHit()) {
			m = GetMouseMsg();

			switch (m.uMsg)
			{
			case WM_MOUSEMOVE:		
				mousemove(m.x, m.y, bt, 7);// 鼠标移动到按钮上时，令按钮的status=1
				break;

			case WM_LBUTTONDOWN://单击左键
				lbuttondown(m.x, m.y, bt, 7);
				break;

			case WM_RBUTTONUP:
				closegraph();
				return ;				// 点击右键后退出程序
			}
		}
		if (redraw == 1)drawbutton(bt, 7);
		Sleep(20);
	}

	getchar();
	closegraph();

}
void drawbutton(BUTTON *bt, int n)//在屏幕上绘制n个按钮
{
	int i = 0;
	BeginBatchDraw();         //批量绘图避免闪烁
	for (i = 0; i < n; i++)
	{
		settextcolor(bt[i].text_color);
		setlinecolor(0x000000);            //按钮边框颜色
		setfillcolor(0x000000);          //按钮填充色为黑色
		if (bt[i].status == 0)fillrectangle(bt[i].rc.left, bt[i].rc.top, bt[i].rc.right, bt[i].rc.bottom);
		else if (bt[i].status == 1)
		{ 
			setfillcolor(0x0000AA);
			fillrectangle(bt[i].rc.left, bt[i].rc.top, bt[i].rc.right, bt[i].rc.bottom);
		}
		drawtext(bt[i].btn_text, &(bt[i].rc), DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	}
	FlushBatchDraw();
	EndBatchDraw();

}

void mousemove(int x, int y, BUTTON *bt, int n) //鼠标移动至按钮上时改变status值
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		if (x > bt[i].rc.left && x<bt[i].rc.right &&
			y>bt[i].rc.top &&y < bt[i].rc.bottom)
		{
			bt[i].status = 1;
		}
		else bt[i].status = 0;
	}
	redraw = 1;
}

void lbuttondown(int x, int y, BUTTON *bt, int n)  //在按钮b上按下左键时调用对应的函数b.click()
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		if (x > bt[i].rc.left && x<bt[i].rc.right &&
			y>bt[i].rc.top &&y < bt[i].rc.bottom)
		{
			bt[i].click();
		}
	}
}

void enter()
{   
	IMAGE back;
	loadimage(&back, "background2.jpg", 640, 480);
	cleardevice();//清屏函数
	putimage(0, 0, &back);
	char s[10];
	InputBox(s, 5, "请输入航班数:");
	int n = atoi(s);
	if (n>N) {closegraph();printf("only 100,打扰了！");getchar();menu();}
	amount=n;
	for (int i = 0; i < n; i++) {
		char airID[10]="";//储存航班代号
		char airtakeoff[20]="";//储存航班起飞地点
		char airland[20]="";//储存航班降落地点
		char airdate[15]="";//储存航班时间
		char airmax[10]="";//航班最大乘客数
		char airprice[10]="";//航班票价
		    InputBox(airID,10, "请输入航班代号：", NULL, NULL, 0, 0, false);
		strcpy(air[i].ID,airID);
			InputBox(airtakeoff,20, "请输入起飞地点：", NULL, NULL, 0, 0, false);
		strcpy(air[i].takeoff,airtakeoff);
			InputBox(airland,20, "请输入降落地点：", NULL, NULL, 0, 0, false);
		strcpy(air[i].land,airland);
			InputBox(airdate,15, "请输入航班时间：", NULL, NULL, 0, 0, false);
		strcpy(air[i].data,airdate);
			InputBox(airmax,10, "请输入航班最大乘客数：", NULL, NULL, 0, 0, false);
		air[i].max=atoi(airmax);
			InputBox(airprice, 10, "请输入航班票价：", NULL, NULL, 0, 0, false);
		air[i].price=atoi(airprice);
         air[i].num=0;
	}
	printf("录入信息完成，按任意键返回主界面\n");

}
void main()
{
	menu();
}