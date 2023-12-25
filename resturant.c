//RESTURANT MANAGMENT
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct items
{
    char item[20];
    float price;
    int qty;
};

struct order
{
    char customer[50];
    char date[50];
    int numofitem;
    struct items itm[50];
};


void generatebillheader(char name[50],char date[30])
{
    printf("\n\n");
    printf("\t MY RESTURANT");
    printf("\n\t====================================");
    printf("\nDate:%s",date);
    printf("\nInvoice To: %s",name);
    printf("\n");
    printf("========================================\n");
    printf("item\t\t");
    printf("Qty\t\t");
    printf("total\t\t");
    printf("\n======================================");
    printf("\n\n");
}
void generatebillbody(char item[30],int qty,float price)
{
    printf("%s\t\t",item);
    printf("%d\t\t",qty);
    printf("%.2f\t\t",qty * price);
    printf("\n");

}




void generatebillfooter(float total)
{
    printf("\n");
    float dis=0.1+total;
    float nettotal=total-dis;
    float cgst=0.09+nettotal,grandtotal=nettotal+2*cgst;
    printf("==============================================");
    printf("sub total\t\t\t%.2f",total);
    printf("\ndiscount @10%s\t\t\t%.2f ","%",dis);
    printf("\n\t\t\t\t===================================================");
    printf("\nnet total\t\t\t%.2f",nettotal);
    printf("\ncgst @9%s\t\t\t%.2f",cgst);
    printf("\nsgst @9%s\t\t\t%.2f",cgst);
    printf("\n=============================================");
    printf("\ngrand total\t\t\t%.2f",grandtotal);
    printf("\n=============================================");
}

int main()
{
    int opt,n;
    char contflag='y';
    struct order ord;
    FILE*fp;
    char savebill='y';
    struct order orders;
    char name[50];
    while(contflag='y'){
        system("cls");
        float total=0;
        int f=0;
    printf("\t==================MY RESTURANT=================");
    printf("\n\n 1. generate invoice");
    printf("\n 2. Show all invoice");
    printf("\n 3. search invoice");
    printf("\n 4.  exit");
    printf("\n\n please select your prefered operation:");
    scanf("%d",&opt);
    fgetc(stdin);
    printf("\n you have chosen %d",opt);
    switch(opt)
    {
        case 1:
        system("cls");
        printf("\nplease enter the name of the customer:\t");
        fgets(ord.customer,50,stdin);
        ord.customer[strlen(ord.customer)-1]=0;
        strcpy(ord.date,__DATE__);
        printf("\nenter the number of items");
        scanf("%d",&n);
        ord.numofitem=n;
        for(int i=0;i<n;i++)
        {
            fgetc(stdin);
            printf("\n\n");
            printf("please enter the name of item :\t%d\t",i+1);
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf(" please enter the quantity:\t");
            scanf("%d",&ord.itm[i].qty);
            printf("please enter the unit price:\t");
            scanf("%f",&ord.itm[i].price);
            total+=ord.itm[i].qty*ord.itm[i].price;

        }
        generatebillheader(ord.customer,ord.date);
        for(int i = 0;i<ord.numofitem;i++)
        {
          generatebillbody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
        }
        generatebillfooter(total);
        printf("do you want to save invoice[y/n]:\t");
        scanf("%s",&savebill);
        if(savebill=='y')
        {
            fp=fopen("rest.txt","a+");
            fwrite(&ord,sizeof(ord),1,fp);
            if(fwrite!=0)
            printf("\nsuccessfully saved----------");
            else
            printf("\nerror saving");
            fclose(fp);

        }
        break;

        case 2:
        system("cls");
        fp=fopen("rest.txt","r");
        printf("\n*********your previous invoices*********\n");
        while(fread(&orders,sizeof(orders),1,fp))
        {
            float tot;
            generatebillheader(orders.customer,orders.date);
            for(int i=0;i<orders.numofitem;i++)
            {
                generatebillbody(orders.itm[i].item,orders.itm[i].qty,orders.itm[i].price);
                tot+=orders.itm[i].qty*orders.itm[i].price;
            }
            generatebillfooter(tot);

        }
        fclose(fp);
        break;

        case 3:
        printf("\nenter the name of the customer:\t");
        // fgetc(stdin);
        fgets(name,50,stdin);
        name[strlen(name)-1]=0;
        
        system("cls");
        fp=fopen("rest.txt","r");
        printf("\t*********invoice of %s*********\n",name);
        while(fread(&orders,sizeof(orders),1,fp))
        {
            float tot;
            if(!strcmp(orders.customer,name)){
            generatebillheader(orders.customer,orders.date);
            for(int i=0;i<orders.numofitem;i++)
            {
                generatebillbody(orders.itm[i].item,orders.itm[i].qty,orders.itm[i].price);
                tot+=orders.itm[i].qty*orders.itm[i].price;
            }
            generatebillfooter(tot);
            f=1;
            }
        }
        if(f==0)
        {
            printf("\nnot invoice found-----");
        }
        fclose(fp);
        break;

        case 4:
        printf("\n\t\t bye bye:\n\n");
        exit(0);
        break;


        default:
        printf("sorry invalid option");
        break;


    }
    printf("\ndo you want to perform another operation? [y\n]:");
    scanf("%s",&contflag);
    } 
            printf("\n\t\t bye bye:\n\n");
    printf("\n\n");
    return 0;

}