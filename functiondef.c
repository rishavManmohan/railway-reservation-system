#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <stdlib.h>
#include <errno.h>
#include "conio2.h"
#include "rlyres.h"
int enterchoice()
{
    int choice,i;
    textcolor(YELLOW);
    gotoxy(28,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    for(i=0;i<80;i++)
       printf("-");
    printf("\nSelect an Option");
    printf("\n1- View Trains");
    printf("\n2- Book Ticket");
    printf("\n3- View Ticket");
    printf("\n4- Search Ticket Number");
    printf("\n5- View All Bookings");
    printf("\n6- View Train Bookings");
    printf("\n7- Cancel Ticket");
    printf("\n8- Cancel Train");
    printf("\n9- Quit");
    printf("\n\nEnter Choice:");
    fflush(stdin);
    scanf("%d",&choice);
    return choice;
}

void add_trains()
{
    FILE *fp;
    Train alltrains[5]={
                       {"123","BPL","GWA",2110,1510},
                       {"456","BPL","DEL",3510,2250},
                       {"345","HBJ","AGR",1570,1145},
                       {"896","HBJ","MUM",4510,3370},
                       {"111","MFP","ANVT",4200,2800},
                       };
    fp=fopen("e:\\Project\\alltrains.dat","rb");
    if(fp==NULL)
    {
        fp=fopen("e:\\Project\\alltrains.dat","wb");
        fwrite(alltrains,5*sizeof(Train),1,fp);
        printf("\nFile Created And Saved.");
    }
    fclose(fp);
}
void view_trains()
{
    int i;
    printf("TRAIN NO\tFROM\tTO\tFIRST AC FARE\tSECOND AC FARE\n");
    for(i=0;i<80;i++)
        printf("-");
    Train tr;
    FILE *fp;
    fp=fopen("e:\\Project\\alltrains.dat","rb");
    while(fread(&tr,sizeof(Train),1,fp)==1)
    {
        printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
    }
    printf("\n\n\n\n");
    fclose(fp);
}
int check_train_no(char *trainno)
{
    Train tr;
    FILE *fp;
    fp=fopen("e:\\Project\\alltrains.dat","rb");
    while(fread(&tr,sizeof(Train),1,fp)==1)
    {
        if(strcmp(tr.train_no,trainno)==0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
int check_mob_no(char *pmb)
{
    if(strlen(pmb)!=10)
        return 0;
    while(*pmb!='\0')
    {
        if(isdigit(*pmb)==0)
            return 0;
        pmb++;
    }
    return 1;
}
Passenger * get_passenger_details()
{
    clrscr();
    textcolor(LIGHTGREEN);
    gotoxy(60,1);
    printf("Enter 0 to Exit");
    textcolor(YELLOW);
    gotoxy(1,1);
    static Passenger psn;
    printf("Enter Passenger's Name:");
    fflush(stdin);
    fgets(psn.p_name,20,stdin);
    char *pos1,*pos2;
    pos1=strchr(psn.p_name,'\n');
    *pos1='\0';
    if(strcmp(psn.p_name,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Reservation Cancelled");
        getch();
        textcolor(YELLOW);
        clrscr();
        return NULL;
    }

    int valid;
    printf("Enter Gender(M/F):");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.gender);
        if(psn.gender=='0')
        {
           textcolor(LIGHTRED);
           gotoxy(1,25);
           printf("\t\t\t\t\t\t\t\t");
           gotoxy(1,25);
           printf("Reservation Cancelled");
           getch();
           textcolor(YELLOW);
           clrscr();
           return NULL;
        }
        if(psn.gender!='M' && psn.gender!='F')
        {
           textcolor(LIGHTRED);
           gotoxy(1,25);
           printf("Error!Gender Should be Either M or F(in Uppercase)");
           valid=0;
           getch();
           gotoxy(19,2);
           printf("\t\t\t");
           gotoxy(19,2);
           textcolor(YELLOW);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");

    gotoxy(1,3);
    printf("Enter Train Number:");
    do
    {
        fflush(stdin);
        scanf("%s",psn.train_no);
        if(strcmp(psn.train_no,"0")==0)
        {
           textcolor(LIGHTRED);
           gotoxy(1,25);
           printf("Reservation Cancelled");
           getch();
           textcolor(YELLOW);
           clrscr();
           return NULL;
        }
        valid=check_train_no(psn.train_no);
        if(valid==0)
        {
           textcolor(LIGHTRED);
           gotoxy(1,25);
           printf("Error!Invalid Train No!");
           getch();
           gotoxy(20,3);
           printf("\t\t\t");
           gotoxy(20,3);
           textcolor(YELLOW);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");

    gotoxy(1,4);
    printf("Enter Travelling Class(First AC:F/Second AC:S):");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.p_class);
        if(psn.p_class=='0')
        {
           textcolor(LIGHTRED);
           gotoxy(1,25);
           printf("\t\t\t\t\t\t\t\t");
           gotoxy(1,25);
           printf("Reservation Cancelled");
           getch();
           textcolor(YELLOW);
           clrscr();
           return NULL;
        }
        if(psn.p_class!='F' && psn.p_class!='S')
        {
           textcolor(LIGHTRED);
           gotoxy(1,25);
           printf("Error!Travelling Class Should be Either F or S(in Uppercase)");
           valid=0;
           getch();
           gotoxy(48,4);
           printf("\t\t\t\t");
           gotoxy(48,4);
           textcolor(YELLOW);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");

    gotoxy(1,5);
    printf("Enter Address:");
    fflush(stdin);
    fgets(psn.address,30,stdin);
    pos1=strchr(psn.address,'\n');
    *pos1='\0';
    if(strcmp(psn.address,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t\t");
        gotoxy(1,25);
        printf("Reservation Cancelled");
        getch();
        textcolor(YELLOW);
        clrscr();
        return NULL;
    }

    //gotoxy(1,6);
    printf("Enter Age:");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%d",&psn.age);
        if(psn.age==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if(psn.age<0 || psn.age>125)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error!Age Should be Positive and Valid");
            valid=0;
            getch();
            gotoxy(11,6);
            printf("\t\t\t\t");
            gotoxy(11,6);
            textcolor(YELLOW);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");

    gotoxy(1,7);
    printf("Enter (10 Digit)Mobile No:");
    do
    {
        fflush(stdin);
        fgets(psn.mob_no,12,stdin);
        pos2=strchr(psn.mob_no,'\n');
        if(pos2!=NULL)
            *pos2='\0';
        if(strcmp(psn.mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid=check_mob_no(psn.mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error!Invalid Mobile no. Try Again");
            getch();
            gotoxy(27,7);
            printf("\t\t\t\t");
            gotoxy(27,7);
            textcolor(YELLOW);
        }
    }while(valid==0);
    return &psn;
}
int get_booked_ticket_count(char *train_no,char tc)
{
    FILE *fp;
    Passenger pr;
    fp=fopen("e:\\Project\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    int count=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0 && pr.p_class==tc)
            ++count;
    }
    fclose(fp);
    return count;
}

int last_ticket_no()
{
    FILE *fp;
    fp=fopen("e:\\Project\\allbokings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    if(fread(&pr,sizeof(pr),1,fp)==0)
    {
        fclose(fp);
        return 0;
    }
    fseek(fp,-1L*sizeof(pr),SEEK_END);
    fread(&pr,sizeof(pr),1,fp);
    fclose(fp);
    return pr.ticketno;
}
int book_ticket(Passenger p)
{
    int i,ticketnum;
    i=get_booked_ticket_count(p.train_no,p.p_class);
    if(i==30)
    {
        textcolor(LIGHTRED);
        printf("All seats are full in Train number %s in class %c !",p.train_no,p.p_class);
        return -1;
    }
    ticketnum=last_ticket_no()+1;
    p.ticketno=ticketnum;
    FILE *fp;
    fp=fopen("e:\\Project\\allbokings.dat","ab");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry!File cannot be opened");
        return -1;
    }
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    return ticketnum;
}
int accept_ticket_no()
{
    int ticketno,valid;
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter Ticket Number:");
    gotoxy(64,1);
    printf("Enter 0 to cancel");
    gotoxy(21,1);
    do
    {
        valid=1;
        fflush(stdin);
       scanf("%d",&ticketno);
       if(ticketno==0)
        return 0;
       if(ticketno<0)
       {
           gotoxy(1,25);
           textcolor(LIGHTRED);
           printf("Ticket Number should be Positive! Try again");
           gotoxy(21,1);
           printf("\t\t\t\t");
           gotoxy(21,1);
           textcolor(YELLOW);
       }
    }while(valid==0);
    fflush(stdin);
    return ticketno;
}
void view_ticket(ticketno)
{
    clrscr();
    if(ticketno==0)
        return;
    int i=0;
    Passenger pr;
    FILE *fp;
    fp=fopen("e://Project//allbokings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry!File Cannot be opened");
        return;
    }
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(pr.ticketno==ticketno)
        {
            clrscr();
            i=1;
            gotoxy(1,1);
            textcolor(LIGHTGREEN);
            printf("Name of Passenger:%s",pr.p_name);
            printf("\nGender:%c",pr.gender);
            printf("\nTrain number:%s",pr.train_no);
            printf("\nTravelling class(F for 1st AC-S for 2nd AC):%c",pr.p_class);
            printf("\nAddress of Passenger:%s",pr.address);
            printf("\nAge:%d",pr.age);
            printf("\nMobile Number:%s",pr.mob_no);
            printf("\nTicket Number:%d",pr.ticketno);
            textcolor(WHITE);
            printf("\n\n\nPress any key to go back to the main screen.");
            textcolor(YELLOW);
            getch();
            clrscr();
        }
    }
    fclose(fp);
    if(i==0)
    {
        gotoxy(1,25);
        textcolor(LIGHTRED);
        printf("No details of the ticket number %d found.",ticketno);
        getch();
        textcolor(YELLOW);
        clrscr();
    }
}
char * accept_mob_no()
{
    static char mob_no[12];
    char *pos;
    int valid=0;
    printf("Enter valid mobile number:");
    do
    {
        fflush(stdin);
        fgets(mob_no,12,stdin);
        pos=strchr(mob_no,'\n');
        if(pos!=NULL)
            *pos='\0';
        if(strcmp(mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling Input...");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid=check_mob_no(mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error!Invalid Mobile no. Try Again");
            getch();
            gotoxy(27,1);
            printf("\t\t\t\t");
            gotoxy(27,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return mob_no;
}
int* get_ticket_no(char *p_mob_no)
{
    FILE *fp=fopen("e:\\Project\\allbokings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry!File cannot be opened.");
        return NULL;
    }
    int count=0;
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
            ++count;
    }
    if(count==0)
    {
        fclose(fp);
        return NULL;
    }
    int *p=(int*)malloc((count+1)*sizeof(int));
    int i=0;
    rewind(fp);
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
        {
            *(p+i)=pr.ticketno;
            i++;
        }
    }
    *(p+i)=-1;
    fclose(fp);
    return p;
}
void view_all_ticket(char *pmob_no,int *pticket_no)
{
    if(pticket_no==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry!No ticket Booked against Mobile No. %s",pmob_no);
        textcolor(WHITE);
        printf("\nPress any key to go back to main menu.");
        textcolor(YELLOW);
        getch();
        return;
    }
    printf("Following are tickets booked for the mobile number %s",pmob_no);
    int i;
    printf("\n\nTICKET NUMBERS\n");
    printf("---------------------------------------------------------");
    for(i=0;*(pticket_no+i)!=-1;i++)
    {
        printf("\n%d",*(pticket_no+i));
    }
    textcolor(WHITE);
    printf("\n\n\nPress any key to return to main menu.");
    textcolor(YELLOW);
    getch();
    free(pticket_no);
}
char * accept_train_no()
{
    clrscr();
    int valid=0;
    textcolor(YELLOW);
    gotoxy(1,1);
    printf("Enter a valid Train no:");
    gotoxy(60,1);
    printf("Enter 0 to exit");
    gotoxy(24,1);
    static char trainno[10];
    do
    {
        fflush(stdin);
        scanf("%s",trainno);
        if(strcmp(trainno,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling Input...");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid=check_train_no(trainno);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error!Invalid Train no. Try Again");
            getch();
            gotoxy(24,1);
            printf("\t\t\t\t");
            gotoxy(24,1);
            textcolor(YELLOW);
        }

    }while(valid==0);
    clrscr();
    return trainno;
}

void view_booking(char *train_no)
{
    FILE *fp=fopen("e:\\Project\\allbokings.dat","rb");
    Passenger pr;
    int i=0,j,row;
    clrscr();
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(j=1;j<=80;j++)
    {
        printf("-");
    }
    row=3;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
        {
            gotoxy(1,row);
            printf("%d",pr.ticketno);
            gotoxy(17,row);
            printf("%c",pr.p_class);
            gotoxy(25,row);
            printf("%s",pr.p_name);
            gotoxy(41,row);
            printf("%c",pr.gender);
            gotoxy(49,row);
            printf("%d",pr.age);
            gotoxy(57,row);
            printf("%s",pr.mob_no);
            row++;
            i=1;
        }
    }
    if(i==0)
    {
        clrscr();
        gotoxy(1,1);
        textcolor(LIGHTRED);
        printf("No tickets were booked in train no %s!",train_no);
    }
    textcolor(WHITE);
    printf("\n\nPress any key to go back to the main screen");
    textcolor(YELLOW);
    getch();
    fclose(fp);
}
void view_all_bookings()
{
    clrscr();
    textcolor(YELLOW);
    FILE *fp=fopen("e:\\Project\\allbokings.dat","rb");
    Passenger pr;
    int j,row;
    textcolor(YELLOW);
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(j=1;j<=80;j++)
    {
        printf("-");
    }
    row=3;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        gotoxy(1,row);
        printf("%d",pr.ticketno);
        gotoxy(17,row);
        printf("%c",pr.p_class);
        gotoxy(25,row);
        printf("%s",pr.p_name);
        gotoxy(41,row);
        printf("%c",pr.gender);
        gotoxy(49,row);
        printf("%d",pr.age);
        gotoxy(57,row);
        printf("%s",pr.mob_no);
        row++;
    }
    textcolor(WHITE);
    printf("\n\nEnter any key to return to main menu.");
    getch();
    textcolor(YELLOW);
    clrscr();
}
int cancel_ticket(int ticket_no)
{
    FILE *fp=fopen("e:\\Project\\allbokings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\n\nNo Bookings done yet!");
        return -1;
    }
    FILE *fp2=fopen("e:\\Project\\temp.dat","wb");
    Passenger pr;
    int result,i=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            i=1;
        }
        else
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }
    }
    fclose(fp);
    fclose(fp2);
    if(i==0)
     {
         remove("e:\\Project\\temp.dat");
     }
    else
    {
        result=remove("e:\\Project\\allbokings.dat");
        if(result!=0)
            return 2;
        else
        {
        result=rename("e:\\Project\\temp.dat","e:\\Project\\allbokings.dat");
        if(result!=0)
            return 2;
        }
    }
    return i;
}
int cancel_train(char* train_no)
{
    FILE *fp=fopen("e:\\Project\\allbokings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\n\nNo Bookings done yet!");
        return -1;
    }
    FILE *fp2=fopen("e:\\Project\\temp.dat","wb");
    Passenger pr;
    int result,i=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
        {
            i=1;
        }
        else
            fwrite(&pr,sizeof(pr),1,fp2);
    }
    fclose(fp);
    fclose(fp2);
    if(i==0)
    {
         remove("e:\\Project\\temp.dat");
    }
    else
     {
        result=remove("e:\\Project\\allbokings.dat");
        if(result!=0)
            return 2;
        else
        {
        result=rename("e:\\Project\\temp.dat","e:\\Project\\allbokings.dat");
        if(result!=0)
            return 2;
        }
     }
     return i;
}
