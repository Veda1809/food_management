#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
void returnfunc();

void mainmenu();

void administration();
void customer();

void addrecord();
void deleterecord();
void searchrecord();
void viewrecord();

void vegetarian();
void nonvegetarian();
void details();
void aboutus();
int getdata();

struct employee
{

	char name[30];
	int id;
	int dd; int mm; int yyyy;
	int YOJ;
	char place[20];
	float salary;
	char department[20];
	
	int quantity;
};
struct employee e;

FILE *fp,*ft,*dp,*dt;

int s;
char findrecord;
int again;
int quantity;
double total=0;
int t;

int main()
{
	mainmenu();
	return 0;
}

void mainmenu(void)
{
	system("cls");
	printf("                                 **************************************************************************\n");
	printf("                                                     WELCOME TO FOOD ORDERING MANAGEMENT\n");
	printf("                                 **************************************************************************\n\n\n");
	printf("          1. ADMINISTRATION SECTION--> \n\n          2. CUSTOMER SECTION--> \n\n          3. ABOUT US--> \n\n          4. Exit--> \n\n\n                              Enter Your Choice --->");
	int choice;
	scanf("%d",&choice);
	if(choice==1)
	{
		administration();
	}
	else if(choice==2)
	{
		customer();
	}
	else if(choice==3)
	{
		aboutus();
	}
	else if(choice==4)
	{
		system("cls");
		printf("\n\n\n");
		printf("*******************************THANK YOU**************************************\n");
		exit(0);
	}
}

void administration()
{
	system("cls");
	printf("**************************************WELCOME TO THE EMPLOYEE SECTION************************************************\n\n");
	printf("          1. Add New Record\n\n          2. Search Record\n\n          3. Delete Record\n\n          4. View Records\n\n          5. View previous orders placed\n\n          6. Back To Main Menu \n\n             Enter Your Choice --->");
	int n;
	scanf("%d",&n);
		printf("\n\n");
	int wait;
	for(wait=0;wait<=100000;wait++)
	{
		printf("\rIn progress : %d",wait/1000);
	}
	printf("\n\n");
	if(n==1)
	{
		addrecord();
	}
	else if(n==2)
	{
		searchrecord();
	}
	else if(n==3)
	{
		deleterecord();
	}
	else if(n==4)
	{
		viewrecord();
	}
	else if(n==5)
	{
		FILE *view;
		char viw;
		view = fopen("order.txt","rt");
		while((viw=fgetc(view))!=EOF)
		{
			printf("%c",viw);
		}
		fclose(view);
	}
	else if(n==6)
	{
		system("cls");
		mainmenu();
	}
	else
	{
		printf("ENTER A VALID OPTION");
		if(getch())
		administration();
	}
	
}

int checkid(int c)  //To check if the employee id exists or not
{
	rewind(fp);
	while(fread(&e,sizeof(e),1,fp)==1)
	if(e.id==c)
		return 0;  //return 0 if employee id exits
    else
		return 1; //return 1 if it doesn't
}
int getdata()
{
	printf(" Employee ID :\t");
	scanf("%d",&t);
	if(checkid(t)==0)
	{
		printf("\n\n");
		printf("\a  Employee record exists!!!\a");
		getch();
		mainmenu();
		return 0;
	}
	e.id=t;
	printf("        Employee Name : ");
	scanf("%s",e.name);
	printf("        Date Of Birth (dd/mm/yyyy) :");
	scanf("%d/%d/%d",&e.dd,&e.mm,&e.yyyy);
	printf("        Year of Joining :");
	scanf("%d",&e.YOJ);
	printf("        Place :");
	scanf("%s",e.place);
	printf("        Department :");
	scanf("%s",e.department);
	return 1;
}

void addrecord()
{
	system("cls");
	fp=fopen("record1.txt","a");
	if(getdata()==1)
	{
		fseek(fp,0,SEEK_END);
		fwrite(&e,sizeof(e),1,fp);
		fclose(fp);
		printf("\n\n");
		printf("Record successfully saved \n\n");
		printf("Do you want to add more records!?(Y / N): ");
		if(getch()=='n')
	    	administration();
		else
	    	system("cls");
	    	addrecord();
	}	
}

void deleterecord()
{
	system("cls");
    int d;
    char another='y';
    while(another=='y')  //infinite loop
    {
	system("cls");
	printf("                Enter The Employee ID to delete :");
	scanf(" %d",&d);
	fp=fopen("record1.txt","r+");
	rewind(fp);
	while(fread(&e,sizeof(e),1,fp)==1)
	{
	    if(e.id==d) //checking if the employee id exists
	    {
			printf("\n\n");
			printf("                               .....................Employee record available....................\n\n");
			printf("               Employee Name : %s\n\n",e.name);
			printf("               Employee's Date of Birth : %d/%d/%d\n\n",e.dd,e.mm,e.yyyy);
			findrecord='t';
	    }
	}
	if(findrecord!='t')
	{
	    printf("                                    .........................Employee record unavailable..........................\n\n");
	    if(getch())
	    administration();
	}
	if(findrecord=='t' )
	{
	    printf("Do you want to delete the record ? (Y/N) ");
	    if(getch()=='y')
	    {
			ft=fopen("test1.txt","w");  //temporary file to delete
			rewind(fp);
			while(fread(&e,sizeof(e),1,fp)==1)
			{
		    	if(e.id!=d)
		    	{
					fseek(ft,0,SEEK_CUR);
					fwrite(&e,sizeof(e),1,ft); // copying the entire data to a temporary , expect the one which needs to be deleted
		    	}                              
			}
			fclose(ft);
			fclose(fp);
			remove("record1.txt");
			rename("test1.txt","record1.txt");
			fp=fopen("record1.txt","r");    
			if(findrecord=='t')
			{
		    	printf("        THE RECORD IS SUCCESSFULLY DELETED.\n\n");
		    	printf("        Do you want to delete another account ? (Y/N) : ");
			}
	    }
		else
		administration();
		fflush(stdin);
		another=getch();
	}
}
administration();
}

void searchrecord()
{
	system("cls");
    int d;
    printf("                                          *****************************Search Employee Record*********************************\n\n");
    printf("                  1. Search By ID\n");
    printf("                  2. Search By Name\n\n");
    printf("                  Enter Your Choice---> ");
    fp=fopen("record1.txt","r"); //opening a file in read mode
    rewind(fp);   
    switch(getch())
    {
	  case '1':
		{
	    	system("cls");
	    	printf("                                   **************Searching record by ID****************\n\n");
	    	printf("                Enter the Employee ID : ");
	    	scanf(" %d",&d);
	    	printf("\n\n");
			printf("Searching........");
	    	while(fread(&e,sizeof(e),1,fp)==1)
	    	{
				if(e.id==d) // check if the employee record exists ; if it exists print the details
				{
		    		printf("\n\n");
					printf("...........................The record is available............................\n\n");
				    printf("       ID : %d\n\n",e.id);
				    printf("       Name : %s\n\n",e.name);
				    printf("       Date of birth :%d/%d/%d\n\n",e.dd,e.mm,e.yyyy);
				    printf("       Year Of Joining :%d\n\n",e.YOJ);
				    printf("       Department :%s\n\n",e.department);
				    printf("       Place :%s\n\n",e.place);
				    findrecord='t';
				}

	    }
	    if(findrecord!='t')  
	    {
	    	printf("\aNo Record Found\a");
	    }
	    printf("\nWanna perform another search ? (y/n)");
	    if(getch()=='y')
	    searchrecord();
	    else
	    administration();
	    break;
	}
	case '2':
	{
	    char s[15];
	    system("cls");
	    printf("                                   **********************Searching Employee by Name***************************\n\n");
	    printf("               Enter Employee Name : ");
	    scanf(" %s",s);
	    int d=0;
	    while(fread(&e,sizeof(e),1,fp)==1)
	    {
		if(strcmp(e.name,(s))==0) 
		{
		    printf("                               .........................The record is available...........................\n\n\n");
			printf("       ID : %d\n\n",e.id);
			printf("       Name : %s\n\n",e.name);
			printf("       Date OF Birth :%d/%d/%d\n\n",e.dd,e.mm,e.yyyy);
			printf("       Year Of Joining :%d\n\n",e.YOJ);
			printf("       Department :%s\n\n",e.department);
			printf("       Place :%s\n\n",e.place);
		    d++;
		}

	    }
	    if(d==0)
	    {
	    	printf("\aNo Record Found\a");
	    }
	    printf("\nWanna perform another search? (Y/N)");
	    if(getch()=='y')
	    searchrecord();
	    else
	    administration();
	    break;
	}
	default :
	getch();
	searchrecord();
    }
    fclose(fp);
}

void viewrecord() 
{
    system("cls");
    printf("                              ********************** Employee Details**********************\n\n");
    printf("     DEPARTMENT          ID          EMPLOYEE NAME          D.O.B          Y.O.J          PLACE\n\n");
    
    fp=fopen("record1.txt","r");
    while(fread(&e,sizeof(e),1,fp)==1)
    {
		printf("        %s",e.department);
		printf("        %d",e.id);
		printf("        %s",e.name);
		printf("        %d/%d/%d",e.dd,e.mm,e.yyyy);
		printf("        %d",e.YOJ);
		printf("        %s",e.place);
		printf("\n\n");
	}
      
      fclose(fp);
      returnfunc();
}

void returnfunc()
{
    {
		printf(" Press ENTER to return to main menu");
    }
    e:
    if(getch()==13) //accepts only enter 
    administration();
    else
    goto e;
}

void customer()
{

	system("cls");
	printf("                    ************************************************\n                                      WELCOME\n                    ************************************************\n\n");
	printf(" 	1. Vegetarian\n\n               2. Non Vegetarian\n\n                 3. Back To Main Menu\n\n   Enter Your Choice  -->");
	int k;
	scanf("%d",&k);
		int wait;
	printf("In progress :");
	for(wait=0;wait<=50000;wait++) //time delay loop
	{
		printf("\rIn progress : %d",wait/500);
	}
	if(k==1)
	{
		system("cls");
		vegetarian();
	}
	else if(k==2)
	{
		system("cls");
		nonvegetarian();
	}
	else if(k==3)
	{
		system("cls");
		mainmenu();
	}
	else
	{
		printf("Please enter the correct input \n\n");
		customer();
	}
}
void vegetarian(void)
{
	int choice;
	int again;
	int quantity;
	
	double price=0;
	
	printf("                    ****************************************\n                                  VEGETARIAN MENU\n                    ****************************************\n\n");
	printf("      1. Mushroom manchurian               100/-\n      2. Noodles              60/-\n             3. Veg. Thaali            150/-\n         -->Dal\n         -->Paneer\n         -->Chapati\n         -->Rice\n         -->Papad\n      4. Back To Main Menu\n\n Enter Your Choice-->  ");
	char v;
	FILE *vmenu;
	
    vmenu=fopen("vegmenu.txt","rt");
	while((v=getc(vmenu))!=EOF)
        {
        	printf("%c",v);
		}
         fclose(vmenu);
    printf("\n\nEnter What You Want :");
	printf("\n\n");
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		total=total + 100*(quantity);
		printf("\n");
		printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			vegetarian();
		}
		else if(again==2)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
			details();
		}
	}
	else if(choice==2)
	{
		printf("Quantity :");
		scanf("%d",&quantity);
		total=total + 60*(quantity);
		printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		if(again==1)
		{
			printf("\n\n");
			vegetarian();
		}
		else if(again==2)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
			details();
		}
	}
	else if(choice==3)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		total=total + 150*(quantity);
		printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		if(again==1)
		{
			printf("\n\n");
			vegetarian();
		}
		else if(again==2)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
			details();
		}
	}
	
	else if(choice==4)
	{
		system("cls");
		customer();
	}
	else
	{
		printf("Please enter the correct input \n\n");
		if(getch())
		vegetarian();
	}
}
void nonvegetarian()
{
	int choice;
	int again;
	int quantity;
	double price=0;
	printf("                                    **********************************************\n");
	printf("                                                  Non Vegetarian Menu\n");
	printf("                                    **********************************************\n");
    printf("1.Chicken Biryani            200-\n\n2. Tandoori Chicken                  350-\n\n3. Back To Main Menu\n\n\nEnter Your Choice");
	char n;
	FILE *nmenu;
	nmenu = fopen("nonveg.txt","rt");
	while((n=getc(nmenu))!=EOF)
	{
		printf("%c",n);
	}
	printf("\n\nEnter What You Want :");
	printf("\n\n");
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("Quantity : ");
		scanf(" %d",&quantity);
		total=total + 200*(quantity);
		printf("\n");
		printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
		scanf(" %d",&again);
		if(again==1)
		{
			printf("\n\n");
			nonvegetarian();
		}
		else if(again==2)
		{
			printf("Your Total Amount Is :%.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
			details();
		}
		
	}
	else if(choice==2)
	{
		printf("Quantity :");
		scanf(" %d",&quantity);
		total=total + 350*(quantity);
		printf("\n");
		printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
		scanf(" %d",&again);
		if(again==1)
		{
			printf("\n\n");
			nonvegetarian();
		}
		else if(again==2)
		{
			printf("Your Total Amount Is :%.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
			details();
		}
	}

	else if(choice==3)
	{
		system("cls");
		customer();
	}
	else
	{
		printf("Wrong Input! Re-enter THe Correct Option\n\n");
		nonvegetarian();
	}
}
void details()
{
	char name1[20];
	char name2[20];
	long long int phone;
	char address[40];
	char landmark[30];
	printf("Please Give Your Contact Details \n");
	printf("First Name : ");
	scanf("%s",name1);
	printf("Last Name : ");
	scanf("%s",name2);
	printf("Phone : ");
	scanf("%lld",&phone);
	printf("Address : ");
	scanf("%s",address);
	printf("Landmark : ");
	scanf("%s",landmark);
	printf("\n\n");
	printf("Your Entered Details Are --->\n");
	FILE *cust;
	cust = fopen("order.txt","a");
	fprintf(cust,"Order Placed By : %s %s\nPhone number : %lld\n",name1,name2,phone);
	fclose(cust);
	printf("    -->First Name :  %s\n    -->Last Name   :  %s\n    -->Phone     :%lld \n    -->Address  :%s \n    -->Landmark  :%s \n",name1,name2,phone,address,landmark);
	printf("\n\n\n");
	printf("                       *********************************************************************************************\n");
	printf("                                             Your Order Will Be At Your Door In 30 minutes.\n");
	printf("                                                       .....THANK YOU FOR ORDERING :).....\n");
	printf("                       *********************************************************************************************\n");
	
	printf("Press any  key to go to the main menu.");
	if(getch())
	customer();
}

void aboutus()
{
	system("cls");
	printf("PEOPLE BEHIND THIS PROJECT :\n\n   -->Eshita Vyas\n\n   -->Kamil Ahmed\n\n   -->M P Spurthi\n\n   -->Vedavandhana Balla\n\n                       *****************************THANK YOU*****************************");
	printf("\n\n");
	printf("    Press Any Key To Go Back.");
	if(getch())
	mainmenu();
}
