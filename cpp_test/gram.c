
#include <stdio.h>
//This program tells the user how much change in whole bills they  will get given a total amount of money
//The variable billsChange is an array, so only one is needed   instead of 6
 
int main() {
    int numChange = 0;
    int billsChange[] = {0, 0, 0, 0, 0, 0};
    //User inputs how much money they wish to withdraw
    printf("Please enter the amount of money you wish to withdraw: ");
    scanf("%d", &numChange);
    //Assuming the amount is > 0, 100 is subtracted from the total until it is < 100. The number of times 100 had to be subtracted is stored in billChange[5]
    while(numChange > 0) {    
	if(numChange >= 100){
	    numChange -= 100;
	    billsChange[5] ++;
	    //This process is repeated with 50,20,10,5 and 1, with the values being stored in billsChange[4],[3],[2],[1] and [0] respectively

	}else if(numChange >= 50) {
	    numChange -= 50;
	    billsChange[4] ++;
	}else if(numChange >= 20) {
	    numChange -= 20;
	    billsChange[3] ++;
	}else if(numChange >= 10) {
	    numChange -= 10;
	    billsChange[2] ++;
	}else if(numChange >= 5) {
	    numChange -= 5;
	    billsChange[1] ++;
	}else if(numChange >= 1) {
	    numChange -= 1;
	    billsChange[0] ++;
	}
    }
    //Totaly number of bills of each type is given
    printf("You recieved %d hundred(s)\n You recieved %d fifty(s)\n You recieved %d twenty(s)\n You recieved %d ten(s)\n You recieved %d five(s)\n You recieved %d one(s)\n", billsChange[5], billsChange[4], billsChange[3], billsChange[2], billsChange[1], billsChange[0]);
    return 0;
}
