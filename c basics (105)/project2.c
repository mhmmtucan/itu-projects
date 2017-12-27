//
//  Muhammet UÇAN ucanmu@itu.edu.tr
//  150140707.c
//  Homework2
//

#include <stdio.h>
#include <stdlib.h>

// function prototypes
void mid_rng(long long*number);
void lsd_rng(long long*number);
long take_samples(long long);
char print_histogram(int);


int main() {
    
    unsigned int menu,range1=0,range2=0,range3=0,range4=0,range5=0;
    int num_samples;
    long long seed,temp;
    
    printf("Which PRNG Algorithm?\n1. MID-PRNG\n2. LSD-PRNG\n");
    scanf("%u",&menu);
    while(menu!=1 && menu!=2) {
        printf("Enter a valid menu number\n1. MID-PRNG\n2. LSD-PRNG\n");
        scanf("%u",&menu);
    }
    
    
        
    printf("Enter the seed\n");
    if (menu==1)
        scanf("%lld",&seed);
    else if(menu==2) {
        scanf("%lld",&seed);
        while (seed%5==0 || seed%2==0) {
            printf("Enter new seed that is neither even nor ends in a 5\n");
            scanf("%lld",&seed);
        }
    }
        
    printf("Enter Number of Samples\n");
    scanf("%i",&num_samples);
    
    while ((num_samples-(range1+range2+range3+range4+range5))!=0) {
        int i;
        for (i=1; i<=num_samples; i++) {
            
            if(menu==1) mid_rng(&seed);
            else lsd_rng(&seed);
            
            
            temp=take_samples(seed);
            
            if (1<=temp && temp<=100)
                range1++;
            else if (101<=temp && temp<=200)
                range2++;
            else if (201<=temp && temp<=300)
                range3++;
            else if (301<=temp && temp<=400)
                range4++;
            else if (401<=temp && temp<=500)
                range5++;
            if ((num_samples-(range1+range2+range3+range4+range5))==0)
                break;
            
        }
    } // end of while in order to make sure that num_sample has genarated
    
    
    menu==1 ? printf("%d random numbers were generated by using MID-PRNG:\n",num_samples) : printf("%d random numbers were generated by using LSD-PRNG:\n",num_samples);
    
    printf("   1..100:");
    print_histogram(range1*100/num_samples);
    printf("%d%c\n",range1*100/num_samples,37);
    
    printf(" 101..200:");
    print_histogram(range2*100/num_samples);
    printf("%d%c\n",range2*100/num_samples,37);
    
    printf(" 201..300:");
    print_histogram(range3*100/num_samples);
    printf("%d%c\n",range3*100/num_samples,37);
    
    printf(" 301..400:");
    print_histogram(range4*100/num_samples);
    printf("%d%c\n",range4*100/num_samples,37);
    
    printf(" 401..500:");
    print_histogram(range5*100/num_samples);
    printf("%d%c\n",range5*100/num_samples,37);
    
    return 0;
} // end of main

void mid_rng(long long*number) {
    long square = *number * *number;
    
    if (square>=1000000000)  // 10 digit
        *number=(square/1000)%100000;
    else if(square>=100000000) // 9 digit
        *number=(square/100)%100000;
    else if(square>=10000000) // 8 digit
        *number=(square/100)%100000;
    else if(square>=1000000) // 7 digit
        *number=(square/10)%100000;
    else if(square>=100000) // 6 digit
        *number=square/10;
    else *number=*number;
        
} // end of mid_rng

void lsd_rng(long long*number) {
    *number = (*number * 73)%100000;
} // end of lsd_rng

long take_samples(long long a) {
    a=(a%500)+1;
    return a;
} // end of take_samples

char print_histogram(int a) {
    int i;
    for (i = 1; i <= a; i++)
        printf("*");
    return 0;
}