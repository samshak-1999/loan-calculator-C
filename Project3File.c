/**********************************************************************************************
*                                   Sam Shakeel                                               *
*                                   N01456416                                                 *
*                                   Project 3 COP 2220                                        *
*                                   Loan Calculator                                           *
***********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define UPPER_YRS_LIMIT 40
#define LOWER_YRS_LIMIT 3
#define INTEREST_UPPER_LIMIT 25
#define INTEREST_LOWER_LIMIT 1
#define PRINCIPAL_UPPER_LIMIT 2000000
#define PRINCIPAL_LOWER_LIMIT 5000

void computemonthlypayment(int term, double loan, float apr, double* mntPmt);
void Loan_Term(int*);
void Interest_Rate(float*);
void Loan_Amount(float*);

int main(void) {

  FILE* fp;
  fp = fopen("loan.txt", "w");


  char saveToFile;
  float Arr[480][4];
  int i;
  int j;
  int years_Term;
  float total_Interest;
  float total_Amount;
  double required_MonthlyPayments;

  double monthlyInterestPayment;
  double interestRatePercentage;
  double paidMonthlyPayment;

  double totalLoanCost = 0;
  double totalPaidInterest = 0;
  double totalPaidPrincipal = 0;

  Loan_Term(&years_Term);
  Interest_Rate(&total_Interest);
  Loan_Amount(&total_Amount);

  interestRatePercentage = (total_Interest / 12.0) / (100.0);
  computemonthlypayment(years_Term, total_Amount, total_Interest, &required_MonthlyPayments);

  printf("\n");
  printf("|_Month__|_Int_____|__Princ____|__Balance__|\n");




    for (i = 0; i < years_Term * 12; i++)
        {

    monthlyInterestPayment = total_Amount * interestRatePercentage; //interest paid monthly
    paidMonthlyPayment = required_MonthlyPayments - monthlyInterestPayment;
    total_Amount = total_Amount - paidMonthlyPayment;


    printf("|%5.3d\t |", i+1);  //month
    Arr[i][0] =  i+1;

    printf("%7.2f  |", monthlyInterestPayment);
    Arr[i][1] = monthlyInterestPayment;

    printf("%7.2f    |",paidMonthlyPayment); // principle
    Arr[i][2] =  paidMonthlyPayment;

    printf(" %8.2f  |\n", total_Amount);
    Arr[i][3] =  total_Amount;

    totalPaidPrincipal = totalPaidPrincipal + paidMonthlyPayment;
    totalPaidInterest = totalPaidInterest + monthlyInterestPayment;

  }

    totalLoanCost = totalPaidInterest + totalPaidPrincipal;

    printf("\n");
    printf("The total loan cost for this loan is: $ %6.2f \n", totalLoanCost);
    printf("The total interest for this loan is: $ %6.2f \n", totalPaidInterest);
    printf("The total principle for this loan is: $ %6.2f \n", totalPaidPrincipal);
    printf("\n");

    printf("Would you like to this to a file, Enter 'Y' or 'y' to save or 'N' to exit: ");
    scanf(" %c", &saveToFile);

        if((saveToFile == 'Y') || (saveToFile == 'y')){
            fprintf(fp,"|_Month__|_Int_____|__Princ____|__Balance__|\n");
            for(i = 0; i < years_Term * 12; i++)
                {
                    fprintf(fp, "| %3.1f\t |", Arr[i][0]);
                    fprintf(fp, "%7.2f  |" , Arr[i][1]);
                    fprintf(fp, "%7.2f    |", Arr[i][2]);
                    fprintf(fp, " %8.2f  |\n", Arr[i][3]);
                }
        fprintf(fp,"The total loan cost for this loan is: $ %6.2f \n", totalLoanCost);
        fprintf(fp,"The total interest for this loan is: $ %6.2f \n", totalPaidInterest);
        fprintf(fp,"The total principle for this loan is: $ %6.2f \n", totalPaidPrincipal);
        }

  return 0;
}



void Interest_Rate(float* userInput){
  float period;
  do{
  printf("Enter in the interest rate (1 to 25) for this loan or zero to quit: ");
  scanf(" %f", &period);
        if(period == 0){
            printf("You have chosen to exit the program\n");
        }
        else if ((period > INTEREST_UPPER_LIMIT) || (period < INTEREST_LOWER_LIMIT))
        {
             printf("You have entered an out of range value, enter a value again from 1 to 25 percent.\n");
        }
        else
        break;

  }while(period);

  *userInput = period;

  return;
}

void Loan_Amount(float* totalAmount){
  float principal;

  do{
  printf("Enter in the total amount of the loan (5 thousand to 2 million) or zero to quit: ");
  scanf(" %f",&principal);
        if(principal == 0){
            printf("You have chosen to exit the program\n");
        }
        else if ((principal > PRINCIPAL_UPPER_LIMIT) || (principal < PRINCIPAL_LOWER_LIMIT)){
            printf("You have entered an out of range value, enter a value again from 5 thousand to 2 million. \n");
        }
        else
            break;

  }while(principal);

  *totalAmount = principal;

  return ;

}


void computemonthlypayment(int term, double loan, float apr, double* mntPmt)
{
  int T = term * 12; //convert to months
  float mntRate = (apr / 12.0)/(100.0);//interest rate per month
  double base = 1 + mntRate;
  *mntPmt = loan * ((mntRate * pow(base,T)) / (pow(base,T) - 1));
  return;
}

void Loan_Term(int* userEntry)
{
  int term = 0;

  do{
    printf("Enter in the number of years (3 to 40) for this loan or zero to quit: ");
    scanf("%d", &term);
            if(term == 0){
                    printf("You have chosen to exit the program\n");
                        }
            else if((term > UPPER_YRS_LIMIT) || (term < LOWER_YRS_LIMIT)){
                    printf("You have entered an out of range value, enter a value again from 3 to 40 years.\n");
                    }
            else
                break;

  }while(term);

  *userEntry = term;

  return;
}
