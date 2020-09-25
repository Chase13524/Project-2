#include<iostream>
#include "date.h"
using namespace std;

int main(){

     Date d1;
     bool good = false;
     while(!good){
     try{
	cout<<"Enter your favorite date: ";
	cin>>d1;
    	good = true;
     }
     catch(bad_month b1){
	b1.msg();
     }
     catch(bad_day bd1){
	bd1.msg();
     }
     }// end of while
	cout<<"I always liked " <<d1<<endl;
return 0;
}
