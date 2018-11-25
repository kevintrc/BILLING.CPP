#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<time.h>
#include<dos.h>
#include<fstream.h>

void head();

void loadpercent(){
	for(int i=0;i<11;i++){
		gotoxy(60,24);
		cout<<"loading "<<i*10<<"%";delay(400-(i*15))  ;
		clrscr();
}
}

/////////////////////////////////////////////////////////////////////
void loadanime(char a[],char b=' '){
	cout<<endl<<"\t\t\t";
  	for(int k=100,h=0;h<30,k>4;h++,k-=4){
   		delay(k);
   		cout<<".";
  }
  delay(1000);
  cout<<"\n\t\t\t"<<b<<" "<<a;delay(1100);
}
//////////////////////////////////////////////////////////////////////////
class price
{
protected:
char model[10];
char brand[10];
float price;

public:
void displayitems();
void set();
char* retbrand()
{
return brand;
}
char* retmodel()
{
return model;
}
float retprice()
{
return price;
}
void setprice(float a)
{
price=a;
}
}pr,pri;

void price::set()
{
cout<<endl<<endl;
int x,y;x=wherex()+2;y=wherey();
gotoxy(x,y);cprintf("Enter Brand");
gotoxy(x+30,y);cprintf("Enter Model");
gotoxy(x+60,y);cprintf("Price(Rs)");
gotoxy(x,y+1);gets(brand);
gotoxy(x+30,y+1);gets(model);
gotoxy(x+60,y+1);cin>>price;
}

void price::displayitems()
{
cout<<endl;
int x,y;x=wherex()+2;y=wherey();
gotoxy(x,y);cprintf("Brand : ");
gotoxy(x+23,y);cprintf("Model : ");
gotoxy(x+53,y);cprintf("Price(Rs) : ");
gotoxy(x+8,y);puts(brand);
gotoxy(x+32,y);puts(model);
gotoxy(x+65,y);cout<<price;
}
///////////////////////////////////////////////////
class billing
{
public:
float Tprice;
int dd,dm,dy,th,tm,ts;
int quantity;
char br[10],mod[10];
void timedateset();
void timedateprint();
void timedateprinth();
void history();
void newbill();
}bill;

void billing::timedateprint()
{
timedateset();
int x=wherex();
cout<<dd<<"/"<<dm<<"/"<<dy<<"\n";gotoxy(x,wherey());cout<<th<<":"<<tm<<":"<<ts;
}

void billing::timedateprinth()
{
int x=wherex()+60;
gotoxy(x,wherey());cout<<dd<<"/"<<dm<<"/"<<dy<<"\n";gotoxy(x,wherey());cout<<th<<":"<<tm<<":"<<ts;
cout<<"\n\n";
}
void billing::history()
{
cout<<endl;
timedateprinth();
int P,x,y;x=wherex();y=wherey();
gotoxy(x,y);cprintf("Brand");
gotoxy(x+17,y);cprintf("Model");
gotoxy(x+35,y);cprintf("Quantity");
gotoxy(x+55,y);cprintf("Total Price(Rs)");
gotoxy(x,y+1);puts(br);
gotoxy(x+17,y+1);puts(mod);
gotoxy(x+35,y+1);cout<<quantity;
gotoxy(x+55,y+1);cout<<Tprice;

cout<<endl
<<"________________________________________________________________________"
<<"\n\n\n";
}
void billing::timedateset()
{
struct date d;
getdate(&d);
struct time t;
gettime(&t);
dd=d.da_day;dm=d.da_mon;dy=d.da_year;th=t.ti_hour;tm=t.ti_min;ts=t.ti_sec;
}

void billing::newbill()
{
cout<<endl<<endl;
int P,x,y;x=wherex();y=wherey();
gotoxy(x,y);cprintf("Enter Brand");
gotoxy(x+30,y);cprintf("Enter Model");
gotoxy(x+60,y);cprintf("Quantity");
gotoxy(x,y+1);gets(br);
gotoxy(x+30,y+1);gets(mod);
gotoxy(x+60,y+1);cin>>quantity;
}
///////////////////////////////////////////////////
///////////////////////////////////////////////////////
void showrecords()
{
fstream fs;
cout<<"\nUPDATED LIST :\n";
fs.open("price.dat",ios::in|ios::binary);
fs.seekg(0,ios::beg);
while((fs.read((char*)&pr,sizeof(pr)))!=NULL)
{
pr.displayitems();
}
fs.close();
getch();
}

void addrecord()  //ADDS AND DISPLAYS ALL EXISTING RECORDS
{
clrscr();
int flag;
char count='0';
char *mod=new char[10];
char *bran=new char[10];
cout<<"\t\t\t\tADD RECORD\n";
fstream fs,ffs;

while(1)
{
	flag=0;
	fs.open("price.dat",ios::out|ios::binary|ios::app);
	ffs.open("price.dat",ios::in|ios::binary);
	count++;
	if(wherey()>18)
	{
	clrscr();
	cout<<"\t\t\t\tADD RECORD\n";
	}
	pr.set();
		strcpy(mod,pr.retmodel());
		strcpy(bran,pr.retbrand());
		ffs.seekg(0,ios::beg);
	while((ffs.read((char*)&pri,sizeof(pri)))!=NULL)
		{
		if(strcmpi(bran,pri.retbrand())==0)
		{
		if(strcmpi(mod,pri.retmodel())==0)
		{
		flag=1;
		}}}
	if(flag!=1)
	{
	fs.write((char*)&pr,sizeof(pr));fs.close();ffs.close();
	cout<<"\n Add more?(y)";if(getch()!='y')break;
	}
	else
	{
	cout<<"\n\nThis item already exists";count--;delay(900);
	fs.close();ffs.close();
	}
}

	delete mod,bran;
	loadanime("RECORD(S) ADDED",count);clrscr();

}

void deleteallrecords()
{
remove("price.dat");
loadanime("ALL RECORDS DELETED !");
delay(1500);
}

void clearlog()
{
remove("bill.dat");
loadanime("ALL TRANSACTION HISTORY DELETED !");
delay(1500);
}

void deleterecord()
{
clrscr();
int flag=0;
cout<<"\t\t\t\tDELETE RECORD\n";
char *mod=new char[10];
char *bran=new char[10];
cout<<endl;
int x,y;x=wherex()+2;y=wherey();
gotoxy(x,y);cprintf("Enter Brand");
gotoxy(x+30,y);cprintf("Enter Model");
gotoxy(x,y+1);gets(bran);
gotoxy(x+30,y+1);gets(mod);

fstream fs,temp;
fs.open("price.dat",ios::in|ios::binary);
temp.open("temp.dat",ios::out|ios::binary);
fs.seekg(0,ios::beg);
while((fs.read((char*)&pr,sizeof(pr)))!=NULL)
{
if(strcmpi(bran,pr.retbrand())==0)
{
if(strcmpi(mod,pr.retmodel())==0)
{
flag=1;
cout<<"Confirm(y)";
if(getch()=='y')
continue;
}
}
temp.write((char*)&pr,sizeof(pr));
}
fs.close();temp.close();
remove("price.dat");
rename("temp.dat","price.dat");
delete bran,mod;
fs.open("price.dat",ios::in|ios::binary);
if(flag!=1)
{cout<<"\nItem not found";delay(1600); }
else
{loadanime("RECORDS UPDATED");
clrscr();
}
fs.close();
}

void changeprice()
{
clrscr();
cout<<"\t\t\t\tCHANGE PRICE\n";
char *mod=new char[10];
char *bran=new char[10];
char count;
float price;
int flag=0;
cout<<endl;
int x,y;x=wherex()+2;y=wherey();
gotoxy(x,y);cprintf("Enter Brand");
gotoxy(x+30,y);cprintf("Enter Model");
gotoxy(x+60,y);cprintf("New Price(Rs)");
gotoxy(x,y+1);gets(bran);
gotoxy(x+30,y+1);gets(mod);
gotoxy(x+60,y+1);cin>>price;

fstream fs("price.dat",ios::in|ios::out|ios::binary);
fs.seekg(0,ios::beg);
while((fs.read((char*)&pr,sizeof(pr)))!=NULL)
{
if(strcmpi(bran,pr.retbrand())==0)
{
if(strcmpi(mod,pr.retmodel())==0)
{
flag=1;
pr.setprice(price);break;
}
}
}
delete bran,mod;
fs.seekg(fs.tellg()-sizeof(pr));
fs.write((char*)&pr,sizeof(pr));
fs.close();
if(flag!=1)
{cout<<"\nItem not found";delay(1600); }
else
{loadanime("RECORDS UPDATED");
clrscr();

}
}

void newcustomer()
{
int flag;
fstream fs,ofs;
cout<<"\n\t\t\t BILLING\n\n";
while(1)
{
fs.open("price.dat",ios::in|ios::binary);
ofs.open("bill.dat",ios::out|ios::binary|ios::app);
flag=0;
	if(wherey()>18)
	{
	clrscr();
	cout<<"\n\t\t\t\t BILLING\n\n";
	}
bill.newbill();
fs.seekg(0,ios::beg);
while((fs.read((char*)&pr,sizeof(pr)))!=NULL)
{
if(strcmpi(bill.br,pr.retbrand())==0)
{
	if(strcmpi(bill.mod,pr.retmodel())==0)
	{
		flag=1;
		bill.Tprice=pr.retprice()*bill.quantity;
		cout<<"\n\tTotal : "<<bill.Tprice<<" Rs";
		cout<<"\tConfirm?(y)";
		if(getch()=='y')
			{
			bill.timedateset();
			ofs.write((char*)&bill,sizeof(bill));
			loadanime("PURCHASE MADE");
			}
	}
}
}
if(flag!=1)
cout<<"\nItem not found";
fs.close();
ofs.close();
cout<<"\nBuy more?(y)";
if(getch()!='y')break;
}
loadanime(" ");
}

void billhistory()
{
fstream fs("bill.dat",ios::in|ios::binary);
int count;
char ch;
while(1)
{
	count=0;
	clrscr();
	cout<<"\n\t\t\t\tRECEIPT RECORD\n\t\t\t\t_______________\n";

	if(ch=='b')
	{
	fs.close();
	fs.open("bill.dat",ios::in|ios::binary);
	fs.seekg(0,ios::beg);
	}
	else
	fs.seekg(0,ios::cur);

	while((fs.read((char*)&bill,sizeof(bill)))!=NULL)
	{
	bill.history();
	count++;
	if(count==2)break;
	}

cout<<"\n\nPress 'n' for next page\n\nPress 'b' to go to first page\n\nPress 'x' to quit";
ch=getch();
if(ch=='n'||ch=='b')
continue;
else break;
}
fs.close();
}
////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
class login
{
 char username[15];
 char password[10];

public:
 login()
 {
  strcpy(username,"admin");
  strcpy(password,"abc");
 }
 void loginn();
};
 void login::loginn()
 {
  int k=0;char uname[15],pass[10];
  for(int j=0;j<3;j++)
  {
   gotoxy(15,wherey());cprintf("\nEnter Username:");
   gotoxy(15,wherey()+1);cin.getline(uname,15);
   if(strcmp(username,uname)==0)
   {
    gotoxy(50,wherey()-2);cout<<"Enter Password:";gotoxy(50,wherey()+1);
    for(int c=0;c<10;c++)
    {
	pass[c]=getch();
	if(pass[c]=='\b')
	{
	 if(c==0)
	  c--;
	 else
	 {
	  c-=2;
	  gotoxy(wherex()-1,wherey());
	  cout<<' ';
	  gotoxy(wherex()-1,wherey());
	 }
	}
	else if(pass[c]=='\r')
	 break;
	else
	 cout<<'*';

    }
    pass[c]='\0';
    if(strcmp(password,pass)==0)
    {
	k=1;
	break;
    }
    else
	cout<<"\n\t\tInvalid password......try again\n";
   }
   else
    cout<<"\n\t\tInvalid username.......try again\n";
  }
  if(!k)
  {
   textcolor(RED+BLINK);
  gotoxy(37,wherey()); cprintf("\n\n!!INTRUDER!!");
   getch(); textcolor(WHITE);
   exit(0);
  }
 }
 void head()
{

cout<<"________________________________________________________________________________\n\n";
cout<<"\t\t\tMANAGEMENT PROGRAM FOR";textcolor(YELLOW);cprintf(" <ITSHOPNAME>   ");textcolor(WHITE);bill.timedateset();bill.timedateprint();
cout<<"\n________________________________________________________________________________\n";
}

//////////////////////////// void main ////////////////////////////////////

void main()
{
 clrscr();
 loadpercent();
 head();
 login *temp=new login;
 (*temp).loginn();delete temp;
 loadanime("ACCESS GRANTED");
 delay(200);
 xyz:

int s,vari;
char var,d,menu[][50]={"Billing","Edit Records","Quit"};
s=1;
d='1';
int p;
while(d!='\r')
{
clrscr();
 head();
 gotoxy(15,wherey()+1);textcolor(YELLOW);cprintf("SELECT CHOICE");textcolor(WHITE);
       gotoxy(60,18);cout<<"'w' for UP";
       gotoxy(60,19);cout<<"'s' for DOWN";
       gotoxy(60,20);cout<<"'Enter' to select";

       gotoxy(15,11);

for(int h=1;h<4;h++)
{
if(s==h)
{
textcolor(WHITE);
textbackground(BLUE);
}
gotoxy(15,wherey()+3);cprintf(menu[h-1]);
textcolor(WHITE);
textbackground(BLACK);
}
d=getch();
if(d=='w')
s-=1;
if(d=='s')
s+=1;
if(s==0)
s=1;
if(s==4)
s=3;
}
vari=s;

 switch(vari)
 {
  case 1:{
	    clrscr();
	    head();
	    vari=wherey();
	    gotoxy(45,15);textcolor(YELLOW);
	    cprintf("Enter option to access");textcolor(WHITE);
	    gotoxy(15,vari+5);
	    cout<<"1.NEW CUSTOMER";
	    gotoxy(15,wherey()+2);
	    cout<<"2.TRANSACTION LOG";
	    gotoxy(15,wherey()+2);
	    cout<<"3.CLEAR LOG";
	    var=getch();
	    switch(var)
		{
		case '1' : {clrscr();newcustomer();goto xyz;}
		case '2' : {clrscr();billhistory();goto xyz;}
		case '3' : {cout<<"\n\n";clearlog();goto xyz;}
		default  : goto xyz;
		}
	   }

  case 2:{
	    clrscr();head();
	    vari=wherey();
	    gotoxy(55,15);textcolor(YELLOW);cprintf("Enter option to acces");textcolor(WHITE);
	    gotoxy(15,vari+2);cout<<"1.ADD RECORD";
	    gotoxy(15,wherey()+2);cout<<"2.DELETE RECORD";
	    gotoxy(15,wherey()+2);cout<<"3.CHANGE PRICE";
	    gotoxy(15,wherey()+2);cout<<"4.VIEW EXISTING RECORDS";
	    gotoxy(15,wherey()+2);cout<<"5.DELETE ALL EXISTING RECORDS";
	    var=getch();
	    switch(var)
		{
		case '1' : {clrscr();addrecord();showrecords();goto xyz;}
		case '2' : {clrscr();deleterecord();showrecords();goto xyz;}
		case '3' : {clrscr();changeprice();showrecords();goto xyz;}
		case '4' : {clrscr();showrecords();goto xyz;}
		case '5' : {cout<<"\n\n";deleteallrecords();goto xyz;}
		default  : goto xyz;
		}

	    }

  case 3:{
		 clrscr();head();
		 cout<<"\n\t\t\t\tenter y to exit";var=getch();
		 if(var=='y')
		 exit(0);
		 else
		 goto xyz;
	   }
 }

}