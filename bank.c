#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define TRANSACTION_DETAILS_SIZE 1000000000
int OPENING_BALANCE = 0;
int BALANCE;
char transaction_details[TRANSACTION_DETAILS_SIZE];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
FILE *w_fp;
FILE *h_fp;

void increment_account(char *user, int amount)
{
    BALANCE += amount;
    printf("Deposit:%d,User:%s, Account balance after:%d\n", amount, user, BALANCE);
}

void decrement_account(char *user, int amount)
{
    if (BALANCE - amount < 0)
    {
        printf("Withdraw:%d,User:%s, Transaction declined\n", amount, user);
    }
    else
    {
        BALANCE -= amount;
        printf("Withdraw:%d,User:%s, Account balance after:%d\n", amount, user, BALANCE);
    }
}

static void *process_wife_transactions(void *arg)
{
    int amount = 0;
 
       while(fgets(transaction_details, TRANSACTION_DETAILS_SIZE, w_fp)!=NULL){
       
        if (transaction_details[0] == 'd')
        {
            amount = atoi(&transaction_details[8]);
            pthread_mutex_lock(&mtx);
            increment_account("Wife", amount);
            pthread_mutex_unlock(&mtx);
        }
        else if (transaction_details[0] == 'w')
        {
            amount = atoi(&transaction_details[9]);
            pthread_mutex_lock(&mtx);
            decrement_account("wife", amount);
            pthread_mutex_unlock(&mtx);
        } 
        else if(transaction_details[0]=='\n'|| transaction_details[0]=='\t')
            continue;
       }
    return NULL;
}

void process_Husband_transactions(void)
{

    int amount = 0;
  
       while(fgets(transaction_details, TRANSACTION_DETAILS_SIZE, h_fp)!=NULL){
        //check for the first letter of the type of transaction
        if (transaction_details[0] == 'd')
        {
            amount = atoi(&transaction_details[8]);
            pthread_mutex_lock(&mtx);
            increment_account("Husband", amount);
            pthread_mutex_unlock(&mtx);
        }
        else if (transaction_details[0] == 'w')
        {
            amount = atoi(&transaction_details[9]);
            pthread_mutex_lock(&mtx);
            decrement_account("Husband", amount);
            pthread_mutex_unlock(&mtx);
        }
        //check for empty lines
        else if(transaction_details[0]=='\n'|| transaction_details[0]=='\t')
            continue;
       }
    return;
}

int main(int argc,char *argv[])
{
    if(argc!=4){
        printf("bank: amount file1 file2\n");
        return 1;
    }

    //check if first argument is an integer
    char *integer_arg=argv[1];
    while(*integer_arg=='0'||*integer_arg=='1'||*integer_arg=='2'||*integer_arg=='3'||*integer_arg=='4'||
          *integer_arg=='5'||*integer_arg=='6'||*integer_arg=='7'||*integer_arg=='8'||*integer_arg=='9')
          integer_arg++;

         if(*integer_arg!='\0'){
           printf("bank: amount file1 file2\n");
           return 1; 
         }
           
          
         
    OPENING_BALANCE=atoi(argv[1]);
    h_fp=fopen(argv[2],"r");
    w_fp=fopen(argv[3],"r");
    if(h_fp==NULL||w_fp==NULL){
       printf("bank:could not open file\n");
       return 1;
    }


    printf("OPENING BALANCE %d\n", OPENING_BALANCE);
    BALANCE = OPENING_BALANCE;
    pthread_t t1;
    int s = pthread_create(&t1, NULL, process_wife_transactions, NULL);
    // pthread_create returns 0 when successful

    if (s != 0)
    {
        printf("second thread failed\n");
        pthread_exit(NULL);
    }

    process_Husband_transactions();
    pthread_join(t1,NULL);
    printf("Closing balance:%d\n",BALANCE);
    return 0;
}
