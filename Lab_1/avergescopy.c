#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int sum_of_digits(int num){
    int sum=0;
    num=abs(num);
    while(num>0){
        sum+=num%10;
        num/=10;
    }
    return sum;
}

const char* get_ordinal_suffix(int n){
    if(n%100>=11&&100<=13)return "th";
    switch(n%10{
        case 1: return "st";
        case 2: return "nd";
        case 3: return 
    })
}