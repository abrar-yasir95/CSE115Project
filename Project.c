#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#define RETURNTIME 15


char catagories[][15]={"Computer","Electrical","Literature","Novel","Civil","History"};
void returnfunc(void);
void mainmenu(void);
void addbooks(void);
void deletebooks(void);
void editbooks(void);
void searchbooks(void);
void issuebooks(void);
void viewbooks(void);
void closeapplication(void);
int  getdata();
int  checkid(int);
int t(void);

void Password();
void issuerecord();
void loaderanim();


void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

FILE *fp,*ft,*fs;


int s;
char findbook;
char password[10]={"bookforall"};

struct meroDate
{
    int mm,dd,yy;
};
struct books
{
    int id;
    char stname[20];
    char name[20];
    char Author[20];
    int quantity;
    float Price;
    int count;
    int rackno;
    char *cat;
    struct meroDate issued;
    struct meroDate duedate;
};
struct books a;
int main()

{
      Password();
      getch();
   return 0;

}
void mainmenu()

{

    system("cls");

    int i;

    printf("---MAIN MENU---\n");


    printf("1. Add Books\n");

    printf("2. Delete books\n");

    printf("3. Search Books\n");

    printf("4. Issue Books\n");

    printf("5. View Book list\n");

    printf("6. Edit Book's Record\n");

    printf("7. Close Application\n");

    printf("------------------------------------------");

    t();

    printf("Enter your choice:");
    switch(getch())
    {
        case '1':
        addbooks();
        break;
    case '2':
        deletebooks();
        break;
        case '3':
        searchbooks();
        break;
    case '4':
        issuebooks();
        break;
        case '5':
        viewbooks();
        break;
        case '6':
        editbooks();
        break;
        case '7':
        {
        system("cls");

        printf("Thanks for using the Program..");

        printf("Exiting in 5 second...........>");

        delay(5000);
        exit(0);
        }
        default:
        {

        printf("\tWrong Entry!!Please re-enter correct option");
        if(getch())
        mainmenu();
        }

    }
}
void addbooks(void)
{
    system("cls");
    int i;

    printf("---SELECT CATEGOIES---\n");


    printf("1.Programming\n");

    printf("2.Electrical\n");

    printf("3.Literature\n");

    printf("4.Novels\n");

    printf("5.Civil\n");

    printf("6.History\n");

    printf("7.Back to main menu\n");

    printf("Enter your choice:\n");
    scanf("%d",&s);
    if(s==7)

    mainmenu() ;
    system("cls");
    fp=fopen("book.txt","w");
    if(getdata()==1)
    {
    a.cat=catagories[s-1];
    fseek(fp,0,SEEK_END);
    fwrite(&a,sizeof(a),1,fp);
    fclose(fp);

    printf("The record is successfully saved\n");

    printf("Want to save another?(Y / N):");
    if(getch()=='n')
        mainmenu();
    else
        system("cls");
        addbooks();
    }
}
void deletebooks()
{
    system("cls");
    int d;
    char another='y';
    while(another=='y')  //infinite loop
    {
    system("cls");

    printf("Enter the Book ID to  delete:");
    scanf("%d",&d);
    fp=fopen("book.txt","w");
    rewind(fp);
    while(fread(&a,sizeof(a),1,fp)==1)
    {
        if(a.id==d)
        {


        printf("The book record is available\n");

        printf("Book name is %s\n",a.name);

        printf("Rack No. is %d\n",a.rackno);
        findbook='t';
        }
    }
    if(findbook!='t')
    {

        printf("No record is found to modify the search");
        if(getch())
        mainmenu();
    }
    if(findbook=='t' )
    {

        printf("Do you want to delete it?(Y/N):");
        if(getch()=='y')
        {
        ft=fopen("stock.txt","w");  //temporary file for delete
        rewind(fp);
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(a.id!=d)
            {
            fseek(ft,0,SEEK_CUR);
            fwrite(&a,sizeof(a),1,ft); //write all in tempory file except that
            }                              //we want to delete
        }
        fclose(ft);
        fclose(fp);
        remove("book.txt");
        rename("stock.txt","book.txt"); //copy all item from temporary file to fp except that
        fp=fopen("book.txt","w");    //we want to delete
        if(findbook=='t')
        {

            printf("The record is successfully deleted\n");

            printf("Delete another record?(Y/N)");
        }
        }
    else
    mainmenu();
    fflush(stdin);
    another=getch();
    }
    }

    mainmenu();
}
void searchbooks()
{
    system("cls");
    int d;
    printf("---Search Books---\n");

    printf("1.Search By ID\n");

    printf("2.Search By Name\n");

    printf("Enter Your Choice :");
    fp=fopen("book.txt","w"); //open file for reading propose
    rewind(fp);   //move pointer at the begining of file
    switch(getch())
    {
      case '1':
    {
        system("cls");

        printf("---Search Books By ID---");

        printf("Enter the book id:");
        scanf("%d",&d);

        printf("Searching........");
        while(fread(&a,sizeof(a),1,fp)==1)
        {
        if(a.id==d)
        {
            delay(2);

            printf("The Book is available\n");

            printf("ID:%d\n",a.id);


            printf("Name:%s\n",a.name);

            printf("Author:%s\n",a.Author);


            printf("Quantity:%d\n",a.quantity);


            printf("Price:Tk.%.2f\n",a.Price);

            printf("Rack No:%d\n",a.rackno);



            findbook='t';
        }

        }
        if(findbook!='t')
        {


        printf("\aNo Record Found\n");
        }

        printf("Try another search?(Y/N)");
        if(getch()=='y')
        searchbooks();
        else
        mainmenu();
        break;
    }
    case '2':
    {
        char s[15];
        system("cls");

        printf("---Search Books By Name---\n");

        printf("Enter Book Name:");
        scanf("%s",s);
        int d=0;
        while(fread(&a,sizeof(a),1,fp)==1)
        {
        if(strcmp(a.name,(s))==0) //checks whether a.name is equal to s or not
        {

            printf("The Book is available");


            printf("ID:%d\n",a.id);


            printf("Name:%s\n",a.name);


            printf("Author:%s\n",a.Author);


            printf("Quantity:%d\n",a.quantity);


            printf("Price:tk.%.2f\n",a.Price);


            printf("Rack No:%d\n",a.rackno);



            d++;
        }

        }
        if(d==0)
        {


        printf("\aNo Record Found\n");
        }

        printf("Try another search?(Y/N)");
        if(getch()=='y')
        searchbooks();
        else
        mainmenu();
        break;
    }
    default :
    getch();
    searchbooks();
    }
    fclose(fp);
}
void issuebooks(void)
{
    int t;

    system("cls");
    printf("---ISSUE SECTION---\n");

    printf("1.Issue a Book\n");

    printf("2.View Issued Book\n");

    printf("3.Search Issued Book\n");

    printf("4.Remove Issued Book\n");

    printf("Enter a Choice:");
    switch(getch())
    {
    case '1':  //issue book
    {
        system("cls");
        int c=0;
        char another='y';
        while(another=='y')
        {
            system("cls");

            printf("---Issue Book section---");

            printf("Enter the Book Id:");
            scanf("%d",&t);
            fp=fopen("book.txt","w");
            fs=fopen("Issue.txt","w");
            if(checkid(t)==0) //issues those which are present in library
            {

                 printf("The book record is available\n");

                 printf("There are %d unissued books in the library ",a.quantity);

                 printf("The name of book is %s",a.name);

                 printf("Enter student name:");
                 scanf("%s",a.stname);
                // struct dosdate_t d; //for current date
                // _dos_getdate(&d);
                // a.issued.dd=d.day;
                // a.issued.mm=d.month;
                 //a.issued.yy=d.year;

                 printf("Issued date=%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);

                 printf("The BOOK of ID %d is issued",a.id);
                 a.duedate.dd=a.issued.dd+RETURNTIME;   //for return date
                 a.duedate.mm=a.issued.mm;
                 a.duedate.yy=a.issued.yy;
                 if(a.duedate.dd>30)
                 {
                 a.duedate.mm+=a.duedate.dd/30;
                 a.duedate.dd-=30;

                 }
                 if(a.duedate.mm>12)
                 {
                a.duedate.yy+=a.duedate.mm/12;
                a.duedate.mm-=12;

                 }

                 printf("To be return:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
                 fseek(fs,sizeof(a),SEEK_END);
                 fwrite(&a,sizeof(a),1,fs);
                 fclose(fs);
                 c=1;
            }
            if(c==0)
            {

            printf("No record found\n");
            }

            printf("Issue any more(Y/N):");
            fflush(stdin);
            another=getche();
            fclose(fp);
        }

        break;
    }
    case '2':  //show issued book list
    {
        system("cls");
        int j=4;
        printf("---Issued book list---\n");


           fs=fopen("Issue.txt","w");
        while(fread(&a,sizeof(a),1,fs)==1)
        {
            printf("STUDENT NAME :%s\nCATEGORY:%s\nID:%d\nBOOK:%s\n",a.stname,a.cat,a.id,a.name);

            printf("ISSUED DATE:%d-%d-%d\n",a.issued.dd,a.issued.mm,a.issued.yy);
            printf("RETURN DATE:%d-%d-%d\n",a.duedate.dd,a.duedate.mm,a.duedate.yy);

            j++;

        }
        fclose(fs);

        returnfunc();
    }
    break;
    case '3':   //search issued books by id
    {
        system("cls");

        printf("Enter Book ID:");
        int p,c=0;
        char another='y';
        while(another=='y')
        {

            scanf("%d",&p);
            fs=fopen("Issue.txt","w");
            while(fread(&a,sizeof(a),1,fs)==1)
            {
                if(a.id==p)
                {
                    issuerecord();

                    printf("Press any key.......\n");
                    getch();
                    issuerecord();
                    c=1;
                }

            }
            fflush(stdin);
            fclose(fs);
            if(c==0)
            {

                printf("No Record Found\n");
            }

            printf("Try Another Search?(Y/N)");
            another=getch();
        }
    }
    break;
    case '4':
    {
        system("cls");
        int b;
        FILE *fg;
        char another='y';
        while(another=='y')
        {

            printf("Enter book id to remove:");
            scanf("%d",&b);
            fs=fopen("Issue.txt","w");
            while(fread(&a,sizeof(a),1,fs)==1)
            {
                if(a.id==b)
                {
                    issuerecord();
                    findbook='t';
                }
                if(findbook=='t')
                {

                    printf("Do You Want to Remove it?(Y/N)");
                    if(getch()=='y')
                    {
                        fg=fopen("record.txt","w");
                        rewind(fs);
                        while(fread(&a,sizeof(a),1,fs)==1)
                        {
                            if(a.id!=b)
                            {
                            fseek(fs,0,SEEK_CUR);
                            fwrite(&a,sizeof(a),1,fg);
                            }
                        }
                        fclose(fs);
                        fclose(fg);
                        remove("Issue.txt");
                        rename("record.txt","Issue.txt");

                        printf("The issued book is removed from list\n");

                       }

                }
                if(findbook!='t')
                {

                    printf("No Record Found!\n");
                }
            }

            printf("Delete any more?(Y/N)");
            another=getch();
        }
    }
    default:

    printf("\aWrong Entry!!");
    getch();
    issuebooks();
    break;
      }

      returnfunc();
}
void viewbooks(void)  //show the list of book persists in library
{
    int i=0,j;
    system("cls");

    printf("---|Book List|---");


    j=4;
    fp=fopen("book.txt","w");
    while(fread(&a,sizeof(a),1,fp)==1)
    {

    printf("%s\n",a.cat);

    printf("%d\n",a.id);

    printf("%s\n",a.name);

    printf("%s\n",a.Author);

    printf("%d\n",a.quantity);

    printf("%.2f\n",a.Price);

    printf("%d\n",a.rackno);
    printf("\n\n");
    j++;
    i=i+a.quantity;
      }

      printf("Total Books =%d",i);
      fclose(fp);

      returnfunc();
}
void editbooks(void)  //edit information about book
{
    system("cls");
    int c=0;
    int d,e;

    printf("---|Edit Books Section|---");
    char another='y';
    while(another=='y')
    {
        system("cls");

        printf("Enter Book Id to be edited:\n");
        scanf("%d",&d);
        fp=fopen("book.txt","w");
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(checkid(d)==0)
            {

                printf("The book is available\n");

                printf("The Book ID:%d\n",a.id);

                printf("Enter new name:\n");scanf("%s",a.name);

                printf("Enter new Author:\n");scanf("%s",a.Author);

                printf("Enter new quantity:\n");scanf("%d",&a.quantity);

                printf("Enter new price:\n");scanf("%f",&a.Price);

                printf("Enter new rackno:\n");scanf("%d",&a.rackno);

                printf("The record is modified");
                fseek(fp,ftell(fp)-sizeof(a),0);
                fwrite(&a,sizeof(a),1,fp);
                fclose(fp);
                c=1;
            }
            if(c==0)
            {

                printf("No record found\n");
            }
        }

        printf("Modify another Record?(Y/N)");
        fflush(stdin);
        another=getch() ;
    }
        returnfunc();
}
void returnfunc(void)
{
    {
    printf(" Press ENTER to return to main menu");
    }
    a:
    if(getch()==13) //allow only use of enter
    mainmenu();
    else
    goto a;
}
int getdata()
{
    int t;

    printf("Enter the Information Below\n");


    printf("Category\n");



    printf("Book ID:");

    scanf("%d",&t);
    if(checkid(t) == 0)
    {

        printf("\aThe book id already exists\a");
        getch();
        mainmenu();
        return 0;
    }
    a.id=t;

    printf("Book Name:");
    scanf("%s",a.name);

    printf("Author:");
    scanf("%s",a.Author);

    printf("Quantity:");
    scanf("%d",&a.quantity);

    printf("Price:");
    scanf("%f",&a.Price);

    printf("Rack No:");
    scanf("%d",&a.rackno);
    return 1;
}
int checkid(int t)  //check whether the book is exist in library or not
{
    rewind(fp);
    while(fread(&a,sizeof(a),1,fp)==1)
    if(a.id==t)
    return 0;  //returns 0 if book exits
      return 1; //return 1 if it not
}
int t(void) //for time
{
time_t t;
time(&t);
printf("Date and time:%s\n",ctime(&t));

return 0 ;
}

void Password(void) //for password option
{

   system("cls");
   char d[50]="Protected via Pass";
   char ch,pass[10];
   int i=0,j;
   //textbackground(WHITE);
   //textcolor(RED);

    for(j=0;j<20;j++)
    {
    delay(50);
    printf("*");
    }
    for(j=0;j<19;j++)
   {
   delay(50);
   printf("%c",d[j]);
   }
   for(j=0;j<19;j++)
   {
   delay(50);
   printf("*");
   }


   printf("\n\tEnter Password:");

   while(ch!=13)
   {
    ch=getch();

    if(ch!=13 && ch!=8){
    putch('*');
    pass[i] = ch;
    i++;
    }
   }
   pass[i] = '\0';
   if(strcmp(pass,password)==0)
   {



    printf("\nPasswords match!");

    printf("\nPress any key to continue.....\n");
    getch();
    mainmenu();
   }
   else
   {

     printf("\aPassword is incorrect!");
     getch();
     Password();
   }
}
void issuerecord()  //display issued book's information
{
         system("cls");

         printf("The Book has taken by Mr. %s\n",a.stname);

         printf("Issued Date:%d-%d-%d\n",a.issued.dd,a.issued.mm,a.issued.yy);

         printf("Returning Date:%d-%d-%d\n",a.duedate.dd,a.duedate.mm,a.duedate.yy);
}
void loaderanim()
{
int loader;
system("cls");

printf("LOADING........");
printf("\n\n");

for(loader=1;loader<20;loader++)
{
delay(100);printf("%c",219);}
}
