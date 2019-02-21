#include<stdio.h>
#include<graphics.h>
#include <easyx.h>
#include<stdlib.h>
#include<string.h>
#define N 100
typedef struct Plane{
	char ID[10];/*�������*/
	char takeoff[20];/*��ɵص�*/
	char  land[20];//����ص�
	char data[15];//����ʱ��
	int max;//�������˿���
	int num;//�Ѿ���ռ�õ���λ��Ŀ
	int price;//�ɻ�Ʊ��
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
void printf_one(int i)   /*��ʾһ����¼�ĺ���*/
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
		printf("\n    �������   ��ɵص�  ����ص�   ���ʱ��  Ʊ��  ���˿�   ����Ʊ��\n"); 
		for(i=0;i<amount;i++) 
		{ 
			printf_one(i);  
			printf("\n"); 
		}  
		printf("\t\t�����������Ŀ¼");
	getchar();
	menu();

}
	void search_end()
	{   
		system( "cls" );//DOS����
		closegraph();
		int i,m=0; 
		airplane s; 
		printf("\n\nEnter the end Place:"); 
		scanf("%s",s.land);               
		/*����Ҫ����ĵط�*/ 
		puts("\n--------------------------------------------------------------------"); 
		printf("\n    �������   ��ɵص� ����ص�   ���ʱ��    Ʊ��  ���˿�   ����Ʊ��\n"); 
		for(i=0;i<amount;i++)  
		{ 
			if(strcmp(air[i].land,s.land)==0)  
			{ 
				m++; 
				if((m!=0)&&(m%10==0))               
					/*Ŀ���Ƿ�����ʾ*/       
				{ 
					printf("\n\nPress any key to contiune  . . .");      
					getchar();      
					puts("\n\n");      
				} 
				printf_one(i);      
				printf("\n"); 
				/*������ʾһ����¼�ĺ���*/  
			} 
		} 
		puts("\n--------------------------------------------------------------------"); 
		getchar();                         
		/*�����⽡*/  getchar();   menu(); 
	}  
	int search()                          /*����ģ��*/ 
	{
	    closegraph();
		int i,k; 
		airplane s;  k=-1; 
		system( "cls" ); //DOS��������
		printf("��ӭ������Ʊ����!\n"); 
		printf("\n������Ҫ��Ʊ����ɵص�:\n"); 
		scanf("%s",s.takeoff);              
		/*����Ҫ����ĵط�*/  
		printf("\n������Ҫ��Ʊ�Ľ���ص�:\n");  scanf("%s",s.land);  
		printf("\n������Ҫ��Ʊ�����ʱ��:\n"); 
		scanf("%s",s.data);               
		/*���������ʱ��*/  
		for(i=0;i<amount;i++)                 
			/*����Ҫ�޸ĵ�����*/ 
		{   
			if(strcmp(s.takeoff,air[i].takeoff)==0&&strcmp(s.land,air[i].land)==0&&strcmp(s.data,air[i].data)==0)   
			{ 
				k=i;                     
				/*�ҵ�Ҫ�޸ĵļ�¼*/    printf_one(k); 
				break;                 
				/*������ʾһ����¼�ĺ���*/   }  } 
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
				printf("\n���˺���Ʊ������!");  
			}         
			else   
			{
				air[i].num++; 
				printf("\n��Ʊ�ɹ�!\n");   
			} 
		}  
		else 
			printf("\n�ú��಻����!");  
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
		printf("��ӭ������Ʊ����!\n"); 
		printf("\n\n���뺽�����:"); 
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
			printf("\n��Ʊ�ɹ�!\n"); 
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
void button7_click()//�˳�
{
	closegraph();
	exit(1);
}

void menu()
{
	BUTTON bt[7];
	char buttontext[7][100] =
	{	"�����º���","�������","�����ѯ","��Ʊ","��Ʊ","����","�˳�"	};
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
		strcpy(bt[i].btn_text, buttontext[i]);//���ַ�����������ַ���������ť
		bt[i].text_color = 0xFFFFFF;//������ɫΪ��ɫ
		bt[i].status = 0;
		bt[i].click = fun[i];//����ָ��ָ���Ӧ����
	}

	drawbutton(bt, 7);//�������˵�7����ť

	MOUSEMSG m;						// ���������Ϣ
	while (true)
	{
		// ��ȡһ�������Ϣ
		while (MouseHit()) {
			m = GetMouseMsg();

			switch (m.uMsg)
			{
			case WM_MOUSEMOVE:		
				mousemove(m.x, m.y, bt, 7);// ����ƶ�����ť��ʱ���ť��status=1
				break;

			case WM_LBUTTONDOWN://�������
				lbuttondown(m.x, m.y, bt, 7);
				break;

			case WM_RBUTTONUP:
				closegraph();
				return ;				// ����Ҽ����˳�����
			}
		}
		if (redraw == 1)drawbutton(bt, 7);
		Sleep(20);
	}

	getchar();
	closegraph();

}
void drawbutton(BUTTON *bt, int n)//����Ļ�ϻ���n����ť
{
	int i = 0;
	BeginBatchDraw();         //������ͼ������˸
	for (i = 0; i < n; i++)
	{
		settextcolor(bt[i].text_color);
		setlinecolor(0x000000);            //��ť�߿���ɫ
		setfillcolor(0x000000);          //��ť���ɫΪ��ɫ
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

void mousemove(int x, int y, BUTTON *bt, int n) //����ƶ�����ť��ʱ�ı�statusֵ
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

void lbuttondown(int x, int y, BUTTON *bt, int n)  //�ڰ�ťb�ϰ������ʱ���ö�Ӧ�ĺ���b.click()
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
	cleardevice();//��������
	putimage(0, 0, &back);
	char s[10];
	InputBox(s, 5, "�����뺽����:");
	int n = atoi(s);
	if (n>N) {closegraph();printf("only 100,�����ˣ�");getchar();menu();}
	amount=n;
	for (int i = 0; i < n; i++) {
		char airID[10]="";//���溽�����
		char airtakeoff[20]="";//���溽����ɵص�
		char airland[20]="";//���溽�ཱུ��ص�
		char airdate[15]="";//���溽��ʱ��
		char airmax[10]="";//�������˿���
		char airprice[10]="";//����Ʊ��
		    InputBox(airID,10, "�����뺽����ţ�", NULL, NULL, 0, 0, false);
		strcpy(air[i].ID,airID);
			InputBox(airtakeoff,20, "��������ɵص㣺", NULL, NULL, 0, 0, false);
		strcpy(air[i].takeoff,airtakeoff);
			InputBox(airland,20, "�����뽵��ص㣺", NULL, NULL, 0, 0, false);
		strcpy(air[i].land,airland);
			InputBox(airdate,15, "�����뺽��ʱ�䣺", NULL, NULL, 0, 0, false);
		strcpy(air[i].data,airdate);
			InputBox(airmax,10, "�����뺽�����˿�����", NULL, NULL, 0, 0, false);
		air[i].max=atoi(airmax);
			InputBox(airprice, 10, "�����뺽��Ʊ�ۣ�", NULL, NULL, 0, 0, false);
		air[i].price=atoi(airprice);
         air[i].num=0;
	}
	printf("¼����Ϣ��ɣ������������������\n");

}
void main()
{
	menu();
}