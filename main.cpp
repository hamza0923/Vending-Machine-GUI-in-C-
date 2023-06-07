#include<graphics.h>
#include<iostream>
#include <bits/stdc++.h>
#include<cstring>
#include<string>
#include<unistd.h>
using namespace std;

#define DEFAULT_COLOR  LIGHTRED
#define HOME 100
#define ORDER 101
#define PAY 102


char Machine_Name[25]="Hamza & Co.";
//const int width=GetSystemMetrics(SM_CXSCREEN);  //[1920px] //1215
//const int height=GetSystemMetrics(SM_CYSCREEN);	//[1200px] //900
const int width=1215;	const int height=900;

int current_state=HOME;
const int Max_Order=10;		//max number of items that can be ordered at once
int order[Max_Order];			
int Total_Amount=0;

struct Menu
{
	string item;
	int price;
};
struct Button_Dimentions
{
	int left, top, right, bottom;	
};
Menu menu[12];
Button_Dimentions button[12];
int recipt_items[12];

	
//--------------------------------------------------------------Generic Functions
int percent(int Total, int Required_Percentage)
{
	return (Required_Percentage*Total)/100;
}
int average(int num1, int num2)
{
	return (num1+num2)/2;
}
int difference(int num1, int num2)
{
	return num1>num2 ? num1-num2 : num2-num1;
}
//-------------------------------------------------------------------------------
class Graphics
{
	private:
	public:
		Graphics()
		{
		}
		void home_page()
		{
			current_state=HOME;
	
			BACKGROUND:
				setfillstyle(SOLID_FILL, DEFAULT_COLOR);
				rectangle(0, 0, width, height);
				floodfill(1,1, DEFAULT_COLOR);
				
			HOME_COMPANY_NAME:
				setbkcolor(DEFAULT_COLOR);
				settextstyle(BOLD_FONT, 0, percent(width/3,2));
				outtextxy(percent(width, 31), percent(height, 29), Machine_Name);
				
			ORDER_BUTTON:
				int button_size_x=percent(width, 10);
				int button_size_y=percent(height, 7);
				int ofsety=percent(height,1);
				setlinestyle(DASHED_LINE,0,average(button_size_x, button_size_y)/15);
				rectangle(percent(width, 50)-button_size_x, percent(height, 50)-button_size_y,percent(width, 50)+button_size_x,percent(height, 50)+button_size_y);	//Continue Button
				setfillstyle(SOLID_FILL, DEFAULT_COLOR);
				floodfill(percent(width, 50)-button_size_x+10,percent(height, 50)-button_size_y+10,WHITE);
				char Order[25]="ORDER";
				settextstyle(DEFAULT_FONT, 0, average(button_size_x, button_size_y)/25);		
				outtextxy(percent(width, 50)-button_size_x/2, percent(height, 50)-(button_size_y/2)+ofsety, Order);
		}
		void order_page()
		{
			current_state=ORDER;
				delay(10);
				cleardevice();
				
			ORDER_PAGE_COMPANY_NAME:
				setbkcolor(DEFAULT_COLOR);
				settextstyle(BOLD_FONT, 0, percent(width/3, 2));
				for(int i=29; i>4; i--)
				{
					outtextxy(percent(width, i), percent(height, i), Machine_Name);
					delay(100/i);
				}
				
			BUTTONS:
				int button_x, button_y, y_offset=height/6, x_offset;
				button_x=width/4;
				button_y=height/6;
				
				int button_size_x=percent(width, 10);
				int button_size_y=percent(height, 7);
				int button_offset_x=percent(width,14);
				int button_offset_y=percent(height,9);
				x_offset=button_size_x/2;
				int x=0;
				
				for(int i=0; i<3; i++)
				{
					for(int j=0; j<4; j++)
					{
						button[x].left=button_size_x-x_offset; button[x].top=button_size_y+y_offset; button[x].right=button_x-x_offset; button[x].bottom=button_y+y_offset;
						rectangle(button[x].left, button[x].top, button[x].right, button[x].bottom);		//buttons
						setfillstyle(SOLID_FILL, DEFAULT_COLOR);
						floodfill(button[x].left+10,button[x].top+10,WHITE);
						//sorting contents for buttons
						string str=menu[x].item;
						int item_lenght=sizeof(str);
						char item[item_lenght];
						strcpy(item, str.c_str());
						char price[10];
						sprintf(price, "Rs:%d/-", menu[x].price);					
						
						//printing contents on the buttons
						settextstyle(BOLD_FONT, 0 , average(percent(width, 10),percent(height, 7))/25);
						outtextxy((button_x-x_offset)-button_offset_x, (button_y+y_offset)-button_offset_y, item);	//items
						settextstyle(BOLD_FONT, 0 , average(percent(width, 10),percent(height, 7))/35);
						outtextxy((button_x-x_offset)-button_offset_x, (button_y+y_offset)-button_offset_y+(average(percent(width, 10),percent(height, 7))/3), price); //price
						x++;
						
						button_x=button_x+width/4;
						button_size_x=button_size_x+width/4;
					}
					button_x=width/4;
					button_size_x=percent(width, 10);
					button_y=button_y+height/6;
					button_size_y=button_size_y+height/6;
					delay(100);
				}
			
			TOTAL_AMOUNT_DISPLAY:
				int display_size_x=percent(width, 25);
				int display_size_y=percent(width, 7);
				
				setfillstyle(SOLID_FILL, BLACK);
				bar(width-percent(width,5)-display_size_x,percent(height,5),width-percent(width, 5), percent(height,5)+display_size_y);
				setcolor(GREEN);
				setlinestyle(USERBIT_LINE, average(button_size_x, button_size_y)/20,average(button_size_x, button_size_y)/40);
				rectangle(width-percent(width,5)-display_size_x,percent(height,5),width-percent(width, 5), percent(height,5)+display_size_y);	
			
			CONTINUE_TO_PAY_BUTTON:	
				button_size_x=percent(width, 25);
				button_size_y=percent(width, 7);
				
				setcolor(WHITE);
				setlinestyle(SOLID_LINE, 0, average(button_size_x, button_size_y)/30);
				rectangle(width-percent(width,5)-button_size_x,height-percent(height,5),width-percent(width, 5), height-percent(height,5)-button_size_y);	
				cout<<width-percent(width,5)-button_size_x<<", "<<height-percent(height,5)<<", "<<width-percent(width, 5)<<", "<<height-percent(height,5)-button_size_y<<endl;
				
				//height-percent(height,5)-button_size_y		top
				//height-percent(height,5)						bottom
				//width-percent(width,5)-button_size_x			left
				//width-percent(width, 5)						right
				
				char text[20]="Continue to Pay";
				settextstyle(BOLD_FONT, 0, percent(width/10, 3)+1);
				outtextxy(width-percent(width,5)-button_size_x+10, height-percent(height,5)-button_size_y+26, text);	
		}
		
		void recipt()
		{
			cleardevice();
			RECIPT_PAGE_COMPANY_NAME:
				setcolor(WHITE);
				settextstyle(BOLD_FONT, 0, percent(width/3, 2));
				for(int i=4; i<29; i++)
				{
					cleardevice();
					outtextxy(percent(width, i), percent(height, 4), Machine_Name);
					delay(100/i);
				}
				
			RECIPT_PAPER:
				int recipt_size_x=percent(width, 20);
				int recipt_size_y=percent(height, 20);
				int recipt_lenght=0;
				setcolor(WHITE);
				setbkcolor(DEFAULT_COLOR);
				setfillstyle(SOLID_FILL, WHITE);
				for(int i=0; i<10 && order[i]!=INT_MAX; i++)
				{
					cout<<i<<endl;
					recipt_lenght=percent(height, 10)+recipt_size_y+(i+1)*(percent(height, 4));
					bar(percent(width, 38), recipt_size_y, percent(width,62), recipt_lenght);
					delay(10);
				}
				
			DEFAULT_TEXT_PRINTING:
				setcolor(BLACK);	
				setbkcolor(WHITE);
			HEADER:
				settextstyle(SIMPLEX_FONT, 0, percent(recipt_size_x/2, 4));
				settextjustify(CENTER_TEXT, TOP_TEXT);
				outtextxy(percent(width, 50),recipt_size_y+2, Machine_Name);
				
				setlinestyle(USERBIT_LINE , 20, 3);
				line(percent(width,41), recipt_size_y+percent(height, 4), percent(width,59), recipt_size_y+percent(height, 4));
			FOOTER:
				char thanks[30]="Thank You for Your";
				char purchase[10]="Purchase";
				settextstyle(TRIPLEX_SCR_FONT, 0, 1);
				settextjustify(CENTER_TEXT, BOTTOM_TEXT);
				outtextxy(percent(width, 50),recipt_lenght-23, thanks);
				outtextxy(percent(width,50), recipt_lenght-3, purchase);
				
					
				char items[6]="ITEMS";	char qty[4]="QTY"; char price[6]="PRICE";
				settextjustify(LEFT_TEXT, TOP_TEXT);
				settextstyle(SMALL_FONT, 0, percent(recipt_size_x/2, 5));
				outtextxy(percent(width, 38)+percent(recipt_size_x, 1),percent(height,6)+recipt_size_y, items);			//printing title for items
				settextjustify(RIGHT_TEXT, TOP_TEXT);
				outtextxy(percent(width, 38)+percent(recipt_size_x, 119),percent(height,6)+recipt_size_y, price);
				outtextxy(percent(width, 38)+percent(recipt_size_x, 85),percent(height,6)+recipt_size_y, qty);
			
			PURCHASED_ITEMS_PRINTING:	
				int line_space=percent(recipt_size_x, 8);
				for(int i=0; i<12; i++)
				{
					if(recipt_items[i]!=0)
					{
						string str=menu[i].item;
						int item_lenght=sizeof(str);
						char item[item_lenght];			//item
						strcpy(item, str.c_str());
						
						int p=menu[i].price;		
						char price[10];					//price
						sprintf(price, "%d/-",p);	
						int q=recipt_items[i];		
						char qty[10];					//quantity
						sprintf(qty, "%d", q);
					
						cout<<item<<"\t"<<price<<"\t"<<qty<<endl;	
						
						settextstyle(SMALL_FONT, 0, percent(recipt_size_x/3, 8));
						settextjustify(LEFT_TEXT, TOP_TEXT);
						outtextxy(percent(width, 38)+percent(recipt_size_x, 1),percent(height,6)+recipt_size_y+line_space, item);		//printing item name
						settextjustify(RIGHT_TEXT, TOP_TEXT);
						outtextxy(percent(width, 38)+percent(recipt_size_x, 119),percent(height,6)+recipt_size_y+line_space, price);	//printing price
						outtextxy(percent(width, 38)+percent(recipt_size_x, 80),percent(height,6)+recipt_size_y+line_space, qty);		//printing quantity
						line_space=line_space+percent(recipt_size_x, 8);
						delay(50);
					}
				}
				setlinestyle(SOLID_LINE, 0, 2);
				line(percent(width, 38)+2, percent(height,6)+recipt_size_y+line_space, percent(width, 62)-2, percent(height,6)+recipt_size_y+line_space);
				
				line_space=line_space+4;
				char total_amount[20];
				sprintf(total_amount, "Total:  Rs.%d/-", Total_Amount);
				settextjustify(RIGHT_TEXT, TOP_TEXT);
				outtextxy(percent(width, 38)+percent(recipt_size_x, 119),percent(height,6)+recipt_size_y+line_space, total_amount);
				
				
		}
		void button_highlight(int x, int y)
		{
			setfillstyle(SOLID_FILL, BLACK);
			floodfill(x+10,y+10,WHITE);
			delay(150);
			setfillstyle(SOLID_FILL, DEFAULT_COLOR);
			floodfill(x+10, y+10, WHITE);
		}
		void total_amount_display()
		{
			int display_size_x=percent(width, 25);
			char total_amount[10];
			sprintf(total_amount, "Rs:%d/-", Total_Amount);
			setcolor(GREEN);
			setbkcolor(BLACK);
			settextstyle(SANS_SERIF_FONT, 0, percent(width/4, 2));
			outtextxy(width-percent(width,5)-display_size_x+5,percent(height,5)+5,total_amount);
		}
		void max_order_limit_reached()
		{
			char error[30]="**max 10 items dispensible!";
			setcolor(YELLOW);
			setbkcolor(DEFAULT_COLOR);
			settextstyle(SMALL_FONT, 0, percent(width/2,1));
			outtextxy(percent(width, 75), height-percent(height,8), error);
		}
		void no_item_selected(bool flag)
		{
			char error[30]="**no item selected!";
			if(!flag)
				setcolor(DEFAULT_COLOR);
			else
				setcolor(YELLOW);
			setbkcolor(DEFAULT_COLOR);
			settextstyle(SMALL_FONT, 0, percent(width/2,1));
			outtextxy(percent(width, 75), height-percent(height,8), error);	
		}
};
class Input : public Graphics
{
	private:
	public:
		POINT cursor;
		int x_cursor, y_cursor;
		Input()
		{
			x_cursor=y_cursor=0;
		}
		bool order_button()
		{
			bool pressed=false;
			while(!pressed)
			{
				delay(1);
				GetCursorPos(&cursor);
					x_cursor=cursor.x;
					y_cursor=cursor.y-20;	//20 is the offset value for navigation bar
				int button_size_x=percent(width, 10);
				int button_size_y=percent(height, 7);
				if(GetAsyncKeyState(VK_LBUTTON) && x_cursor>percent(width, 50)-button_size_x && x_cursor<percent(width, 50)+button_size_x && y_cursor>percent(height, 50)-button_size_y && y_cursor<percent(height, 50)+button_size_y && current_state==HOME)
				{
					
					button_highlight(percent(width, 50)-button_size_x,percent(height, 50)-button_size_y);
	
					delay(50);
					pressed=true;
					break;
				}
			}
			return pressed;
		}
		
		bool take_order()
		{
			bool proceed_to_pay=false;
			bool order_full=false;
			int button_size_x=percent(width, 25);
			int	button_size_y=percent(width, 7);
			int i=0;
			int o=0;
			while(!proceed_to_pay)
			{
				delay(0);
				GetCursorPos(&cursor);
					x_cursor=cursor.x;
					y_cursor=cursor.y-20;	//20 is the offset value for navigation bar
		
				if(GetAsyncKeyState(VK_LBUTTON) && x_cursor>button[0].left && x_cursor<button[0].right && y_cursor>button[0].top && y_cursor<button[0].bottom && !order_full)
				{
					button_highlight(button[0].left, button[0].top);
					order[o]=0;
					Total_Amount=Total_Amount+menu[order[o]].price;
					cout<<"Button "<<0<<": "<<button[0].left<<" , "<<button[0].top<<" , "<<button[0].right<<" , "<<button[0].bottom<<" Order: "<<menu[order[o]].item<<endl;
					o++;
					no_item_selected(false);
				}
				if(GetAsyncKeyState(VK_LBUTTON) && x_cursor>button[i].left && x_cursor<button[i].right && y_cursor>button[i].top && y_cursor<button[i].bottom && !order_full)
				{
					button_highlight(button[i].left, button[i].top);
					order[o]=i;
					Total_Amount=Total_Amount+menu[order[o]].price;
					cout<<"Button "<<i<<": "<<button[i].left<<" , "<<button[i].top<<" , "<<button[i].right<<" , "<<button[i].bottom<<" Order: "<<menu[order[o]].item<<endl;
					o++;
					no_item_selected(false);
				}
				if(GetAsyncKeyState(VK_LBUTTON) && x_cursor>width-percent(width,5)-button_size_x && x_cursor<width-percent(width, 5) && y_cursor>height-percent(height,5)-button_size_y && y_cursor<height-percent(height,5))
				{
					button_highlight(width-percent(width,5)-button_size_x, height-percent(height,5)-button_size_y);
					if(order[0]!=INT_MAX)
					{
						proceed_to_pay=true;
						break;
					}
					else
						no_item_selected(true);
				}
				if(o==10)
				{
					max_order_limit_reached();
					order_full=true;
				}
				if(i==11)
					i=0;
				i++;
				total_amount_display();
			}
			return proceed_to_pay;
		}
		
		void take_payment()
		{
			for(int i=0; i<12; i++)
				recipt_items[i]=0;
			
			for(int i=0; i<Max_Order; i++)
			{
				int item_no=order[i];
				recipt_items[item_no]++;
			}
			recipt();
		}
};



int main()
{
	initwindow(width, height, Machine_Name);
	//------------------------------------------------------------------------------------------MENU

	menu[0].item="LAYS";	menu[1].item="KURKURY";	menu[2].item="SALANTY";	menu[3].item="OREO";
	menu[0].price=80;		menu[1].price=50;		menu[2].price=50;		menu[3].price=50;
	
	menu[4].item="NIMKO";	menu[5].item="COCOMO";	menu[6].item="STING";	menu[7].item="COCACOLA";
	menu[4].price=60;		menu[5].price=60;		menu[6].price=120;		menu[7].price=50;
	
	menu[8].item="PRINCE";	menu[9].item="JUICE";	menu[10].item="WATER";	menu[11].item="TRIDANT";
	menu[8].price=40;		menu[9].price=70;		menu[10].price=50;		menu[11].price=300;
	
	for(int i=0; i<Max_Order; i++)
	{
		order[i]=INT_MAX;
	}
	//-----------------------------------------------------------------------------------------------
	
	Graphics display;
	Input input_event;
	
	display.home_page();

	if(input_event.order_button() && current_state==HOME)
	{
		display.order_page();
	}
	if(current_state==ORDER)
	{
		if(input_event.take_order())
			{
				current_state=PAY;
			}
	}
	if(current_state==PAY)
	{
		input_event.take_payment();
	}
	getch();
}		