#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio2.h"
#include "rlyres.h"
int main()
{
    int choice,ticket_no,tnum;
    char *pmob_no;
    char *ptrain_no;
    char *ptrain_no2;
    int *pticket_no;
    int result1,result2,result3;
    Passenger *ptr;
    add_trains();
    while(1)
    {
    choice=enterchoice();
    if(choice==9)
    {
        exit(0);
    }
     switch(choice)
     {
     case 1:
        view_trains();
        getch();
        clrscr();
        break;
     case 2:
        ptr=get_passenger_details();
        if(ptr!=NULL)
        {
            ticket_no=book_ticket(*ptr);  //pass by reference because ticket_no has garbage value initially which will change.
            if(ticket_no==-1)
            {
                textcolor(RED);
                printf("\nBooking Failed!");
            }
            else
            {
                textcolor(LIGHTGREEN);
                printf("\nTicket Booked Successfully\n\nYour Ticket Number is %d",ticket_no);
            }
            textcolor(WHITE);
            printf("\nPress any key to go back to main screen");
            getch();
            clrscr();
        }
        break;
     case 3:
        clrscr();
        tnum=accept_ticket_no();
        clrscr();
        if(tnum==0)
        {
            gotoxy(1,25);
            printf("\t\t\t\t\t\t");
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Cancelling Input...");
            getch();
            textcolor(YELLOW);
            clrscr();
        }
        view_ticket(tnum);
        break;
     case 4:
        clrscr();
        pmob_no=accept_mob_no();
        if(pmob_no!=NULL)
        {
            pticket_no=get_ticket_no(pmob_no);
            view_all_ticket(pmob_no,pticket_no);
        }
        clrscr();
        break;
     case 5:
         clrscr();
         view_all_bookings();
         break;
     case 6:
        clrscr();
        ptrain_no=accept_train_no();
        if(ptrain_no!=NULL)
        {
          view_booking(ptrain_no);
        }
        clrscr();
        break;
     case 7:
        clrscr();
        result1=accept_ticket_no() ;
        if(result1!=0)
        {
            result2=cancel_ticket(result1);
            if(result2==0)
            {
                textcolor(LIGHTRED);
                printf("\n\nSorry! No tickets booked against the ticket number %d",result1);
            }
            if(result2==1)
            {
                textcolor(LIGHTGREEN);
                printf("\n\nTicket no %d successfully cancelled.",result1);
            }
            else if(result2==2)
            {
                textcolor(LIGHTRED);
                printf("\n\nSorry! Error in cancellation.Try again");
            }
            textcolor(WHITE);
            printf("\n\nPress any key to return to main screen.");
        }
        else
        {
            gotoxy(1,25);
            printf("\t\t\t\t\t\t");
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Cancelling Input...");
            getch();
            textcolor(YELLOW);
        }
        getch();
        clrscr();
        break;
     case 8:
        clrscr();
        ptrain_no2=accept_train_no();
        if(ptrain_no2!=NULL)
        {
            result3=cancel_train(ptrain_no2);
            if(result3==0)
            {
                textcolor(LIGHTRED);
                printf("\n\nSorry!Train number %s cannot be cancelled.",ptrain_no2);
            }
            if(result3==1)
            {
                textcolor(LIGHTGREEN);
                printf("\n\nTrain no %s successfully cancelled.",ptrain_no2);
            }
            if(result3==2)
            {
                textcolor(LIGHTRED);
                printf("\n\nSorry! Error in cancellation.Try again");
            }
            textcolor(WHITE);
            printf("\n\nPress any key to return to main screen.");
        }
        else
        {
            gotoxy(1,25);
            printf("\t\t\t\t\t\t");
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Cancelling Input...");
            getch();
            textcolor(YELLOW);
        }
        getch();
        clrscr();
        break;
     default:
        textcolor(LIGHTRED);
        printf("Wrong Choice! Try Again\n");
        getch();
        clrscr();
     }
    }
    return 0;
}
