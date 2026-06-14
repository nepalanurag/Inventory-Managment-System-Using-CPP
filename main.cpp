#include<iostream>
#include<string.h>
#include<fstream>
#include<cstdio>
#ifdef _WIN32
#include<conio.h>
#else
#include<termios.h>
#include<unistd.h>
#endif
using namespace std;
int i,n;
ifstream fin;
ofstream fout;
fstream fio;
void disp();

// The original code used conio.h's get_key() and clear_screen(), which only
// exist on Windows. These small wrappers keep the same behaviour on
// Windows and make the program build and run on Linux/macOS too.
int get_key()
{
#ifdef _WIN32
    return get_key();
#else
    if (!isatty(STDIN_FILENO))
        return getchar(); // input is piped: no terminal settings to change
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}

void clear_screen()
{
#ifdef _WIN32
    clear_screen();
#else
    if (isatty(STDOUT_FILENO))
        system("clear");
#endif
}
class stock
{
		char name[20];
	float pr; int quant;

public:
	void get();
	void show();
    int stockcheck(char nm[30]);    
    void withd(int qty);
    void refil(int qty);
}st;
void stock::withd(int qty)
{
	if(quant>=qty)
	{
		quant-=qty;
		cout<<"\n\nStock updated.\n";
		cout<<"\n\nTotal price to be paid:"<<pr*qty;
    }
	else 
	   cout<<"\n\nInsufficient stock";
	    get_key();	
}
void stock::refil(int qty)
{
		quant+=qty;
		cout<<"\n\nStock updated.";
	    get_key();	
}
int stock::stockcheck(char nm[30])
{
	if(strcmp(nm,name)==0)
	 return 0;
	else 
	return 1;
}
void stock::get()
{
	cout<<"\nEnter the Name , the price and then the quantity\n"; 	
	cin>>name>>pr>>quant;
}

void stock::show()
{
	cout<<"\n"<<name<<"\t\t\t"<<quant<<"\t\t\t"<<pr;
}
void addnew()
{
    clear_screen();
		
	disp();
	get_key();
	clear_screen();
	
	cout<<"\nEnter the No. of Products that you wish to add: ";
    cin>>n;
  if (n!=0)
    {
	fout.open("shop.dat",ios::binary|ios::app);
	for(i=0;i<n;i++)
	{
	    
		cout<<"\n\nInput the name, price and the quantity of item respectively\n\n";
	    st.get();
	    fout.write((char*)&st,sizeof(st));
        cout<<"\n\nitem updated";
		cin.get();
    }
    cout<<"\n\nStock Updated!!";
    fout.close();
    cin.get();
    clear_screen();
    disp();
}
	else
{

	fout.close();
	cin.get();
	clear_screen();
	cout<<"\n\nNo items to be added";
}
}
void withdraw()
{
	clear_screen();
	char temp[100];int qty;
	int i=0;
	long pos=0;
	disp();
	cout<<"\n\nEnter the product's name \n"<<endl;
	cin>>temp;
	cout<<"\n\nEnter quantity: \n"<<endl;
	cin>>qty;
	fio.open("shop.dat",ios::binary|ios::out|ios::in);
     while(fio)
     {
	    pos=fio.tellp();
	    fio.read((char*)&st,sizeof(st));
	    if(st.stockcheck(temp)==0)
	    {
		  
		  st.withd(qty);
		  fio.seekp(pos);
		  fio.write((char*)&st,sizeof(st));
		  i++;break;
	    }
     }
     
    
     if(i!=1)
       cout<<"\n\n!!Item not found!!";
       get_key();
     fio.close();
    cin.get();
    clear_screen();
	 disp(); 
	get_key();
}
void disp()
{
	int i=1;
	cout<<"\n==================================================================";
	cout<<"\n\n=================\tTHE STOCK ITEMS ARE\t==================";
	cout<<"\n\n==================================================================\n";
	cout<<"\n\nPARTICULARS\tSTOCK AVAILABLE\t\t\t PRICE";
	cout<<"\n\n============================================================\n";	
	 fin.open("shop.dat",ios::binary);
     while(!fin.eof())
     {
	  fin.read((char*)&st,sizeof(st));
	  if(!fin.eof())
	  {
	     if(fin.tellg()<0)
	     {	i=0; break;}
	     st.show();
	  }
     }
     if(i==0)
     {	cout<<"\n\n\t\t\t!!Empty record room!!";
	get_key();
     }
     fin.close();
    
}
void refill()
{
	clear_screen();
	char temp[100];int qty;
	int i=0;
	long pos=0;
	disp();
	cout<<"\n\nEnter the products name \n"<<endl;
	cin>>temp;
	cout<<"\n\nEnter quantity: \n"<<endl;
	cin>>qty;
	fio.open("shop.dat",ios::binary|ios::out|ios::in);
     while(fio)
     {
	    pos=fio.tellp();
	    fio.read((char*)&st,sizeof(st));
	    if(st.stockcheck(temp)==0)
	    {
		  st.refil(qty);
		  fio.seekp(pos);
		  fio.write((char*)&st,sizeof(st));
		  i++;break;
	    }
     }
     if(i!=1)
       cout<<"\n\n!!Record not found!!";
     fio.close();
    clear_screen();
    cin.get();
	 disp(); cin.get();	
}
void remove()
{
	clear_screen();	
	 int i=0;
     char temp[30];
     cout<<"\n\t\t\t\tDelete Record";
     cout<<"\n\nEnter the name of the product:";
     cin>>temp;
     fout.open("temp.dat",ios::binary);
     fin.open("shop.dat",ios::binary);
     while(!fin.eof())
     {
	  fin.read((char*)&st,sizeof(st));
	  if(!fin.eof())
	    if(st.stockcheck(temp)==0)
	    {
		  st.show();
		  cout<<"\n\n\t\tRecord deleted";
		  i++;
	    }
	    else
		  fout.write((char*)&st,sizeof(st));
     }
     if(i==0)
       cout<<"\n\n!!Record not found!!";
     fin.close();
     fout.close();
     ::remove("shop.dat");
     rename("temp.dat","shop.dat");
}
int main()
{
	char pass[10];
	int i,j;
	cout<<"\n\t\tINVENTORY MANAGEMENT SYSTEM\n";	
	cout<<"=============================================================";
	cout<<"\n\n\t\t 1.Employee Menu\n\n\t\t 2.Customer Menu\n\n\t\t";
	cout<<"\n\n==========================================================\n";
	cout<<"\n\nEnter Your Choice:";
	cin>>j;
	cin.ignore(1000, '\n'); // drop the leftover newline so it is not read as the first password character
	if(j==1)
	{
	clear_screen();
    cout<<"\n\n\n\t\tPlease enter the password: ";
	
	for(int z=0;z<3;z++)
	{
		pass[z]=get_key();
		clear_screen();
		cout<<"\n\n\n\n\n\n\n\t\t\t\t\tPlease enter the password: ";
		for(i=1;i<=(z+1);i++)
		{
			cout<<"*";
		}
	}
	pass[3]='\0'; // terminate the buffer before comparing
	if(strcmp(pass,"abc")==0)
	{
    clear_screen();
	empmenu:
	clear_screen();
	cout<<"=================================================================";
	cout<<"\n\n\t\t\t    EMPLOYEE MENU\n1. Add new product\n2. Display stock\n3. Refill\n4. Remove an item\n5. Exit:";
	cout<<"\n\n\n==========================END OF MENU=============================";
	cout<<"\n\n Enter your Choice :\t";
	cin>>i;
	if(i==1)
	{
		addnew();get_key();
	goto empmenu;
	}

	else if(i==2)
	{
		clear_screen();
	disp();get_key();goto empmenu;
	}
	else if(i==3)
	{
		refill();goto empmenu;
	}
	else if(i==4)
	{
		remove();get_key();goto empmenu;
	}
	else 
	{
		clear_screen();
	get_key();
	exit(0);
}
}
else
{
	cout<<"\n\n\nINPUT CORRECT PASSWORD!!!\n\n";
	get_key();

	exit(0);
}
	}
	if(j==2)
	{
		custmenu:
	clear_screen();
	cout<<"=================================================================";
	cout<<"\n\n\t\t\t CUSTOMER MENU\n1. Purchase\n2. Display stock\n3. Exit:";
	cout<<"\n\n\n==========================END OF MENU=============================";
	cout<<"\n\n Enter your Choice :\t";
	cin>>i;	
	if (i==1)
	{
	withdraw();get_key();goto custmenu;
	}
	else if(i==2)
	{
		clear_screen();
	disp();get_key();goto custmenu;
	}	
	else 
	{
		clear_screen();
	get_key();
	exit(0);
}	
}
	get_key();
}
