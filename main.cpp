#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ASSUMING THE NUMBER INPUTED SHALL BE SEPERATED BY SPACES
ELSE THE PROGRAM WILL READ IT AS ONLY ONE INTEGER*/
bool postFix(char str[], float *result);					//postFix Calculator
bool operation(char a,Stack s); 							//operates the given equation
float stringToFloat(char a[],int index);					//converts string to float without using atof()
bool isOperator(char a); 									//helper function to detect if it is an operator or not
bool floatORinteger(char a[]); 								//helper function to determine if it is a float or integer
void displayError(int result);								//for error display
void displayFloat(int error, float result, char str[]);		//for display with decimal
void displayInt(int error, float result,char str[]);   		//for display with normal number


int main(int argc, char** argv) {
	char str[50],nstr[50];
	float result;
	int error;
	
	//For inputing in the compiler
	printf("Seperate numbers and operators with spaces..\n ");
	printf("Input PostFix Expression: ");
	gets(str);
	strcpy(nstr,str); 	 //string is coppied to another character array because strtok will modify the string that will be passed in the function
	error=postFix(str,&result);
	if(floatORinteger(nstr)){
		displayFloat(error,result,nstr);
	}
	else{
		displayInt(error,result,nstr);
	}   
/*	
	//For direct output
	strcpy(str,"8 9 +");
	strcpy(nstr,str);
	error=postFix(str,&result);
	if(floatORinteger(nstr)){
		displayFloat(error,result,nstr);
	}
	else{
		displayInt(error,result,nstr);
	}
	printf("\n");
	strcpy(str,"9 3 - 8 2 / -");
	strcpy(nstr,str);
	error=postFix(str,&result);
	if(floatORinteger(nstr)){
		displayFloat(error,result,nstr);
	}
	else{
		displayInt(error,result,nstr);
	}
	printf("\n");
	strcpy(str,"9 3 - 8 2 / - 6 2 / +");
	strcpy(nstr,str);
	error=postFix(str,&result);
	if(floatORinteger(nstr)){
		displayFloat(error,result,nstr);
	}
	else{
		displayInt(error,result,nstr);
	}
	printf("\n");
	strcpy(str,"9.3 3 - 8 2 / - 6 2 / 3 2 * + +");
	strcpy(nstr,str);
	error=postFix(str,&result);
	if(floatORinteger(nstr)){
		displayFloat(error,result,nstr);
	}
	else{
		displayInt(error,result,nstr);
	}
	printf("\n");
	strcpy(str,"9 3 - 8 2 / *");
	strcpy(nstr,str);
	error=postFix(str,&result);
	if(floatORinteger(nstr)){
		displayFloat(error,result,nstr);
	}
	else{
		displayInt(error,result,nstr);
	}  */
	return 0;
}

bool postFix(char str[], float *result){   //evaluates the postfix calculator
	Stack s= newStack();
	float fnum;
	bool flag=0;
	char *item=strtok(str," ");
	while(item!=NULL&&flag==0){
		if(item[0]=='-'&&item[1]>='0'&&item[1]<='9'){
			fnum = stringToFloat(item,1); 				//for converting string to float numbers without using atof()
			fnum = -fnum;
//			fnum = atof(item);
			push(s,fnum);
		}
		else if(item[0]>='0'&&item[0]<='9'){
			fnum = stringToFloat(item,0); 		//for converting string to float numbers without using atof()
		//	fnum = atof(item);
			push(s,fnum);
		}
		else if(!isEmpty(s)){
			flag=operation(item[0],s);  //function evaluates the program if it does not evaule it pushes the char operator or letter 'a' for determining an invalid expression
		}
		else {
			fnum = item[0];  //if there is no operator invalid
			push(s,fnum);
			flag = 1;
		}	
		item = strtok(NULL," ");
	}
	*result = peek(s);   //peeks the last item in the stack or its answer if flag == 0, else it peeks the last item in the stack to determine the error
	pop(s);
	if(!isEmpty(s)){ //check if the stack is still not empty or not 
		flag = 1;
	}
	destroy(&s);
	return flag;
}  


bool operation(char a,Stack s){ //function evaluates the given character if stack is empty it will not proceed on evaluating but pushing the character operator
	float val1, val2,num;		// for determining if the given string is missing an operand
	bool flag = 0;
	if(isOperator(a)){
		switch(a){
			case '+':
				val1=peek(s);
				pop(s);
				if(!isEmpty(s)){
					val2=peek(s);
					pop(s);
					num = val2+val1;
					push(s,num);
				}
				else {
					num = '+';
					push(s,num);
					flag = 1;
				}
				break;
			case '-':
				val1=peek(s);
				pop(s);
				if(!isEmpty(s)){
					val2=peek(s);
					pop(s);
					num = val2-val1;
					push(s,num);
				}
				else {
					num = '-';
					push(s,num);
					flag=1;
				}
				break;
			case '*':
				val1=peek(s);
				pop(s);
				if(!isEmpty(s)){
					val2=peek(s);
					pop(s);
					num = val2*val1;
					push(s,num);
				}
				else {
					num = '*';
					push(s,num);
					flag=1;
				}
				break;
			case '/':
				val1=peek(s);
				pop(s);
				if(!isEmpty(s)){
					val2=peek(s);
					pop(s);
					num = val2/val1;
					push(s,num);
				}
				else {
					num = '/';
					push(s,num);
					flag=1;
				}
				break;	
		}
	}
	else{
		num = 'a';			//if it is not one of the character operator then it will push 'a' for condition purposese for the invalid error
		push(s,num);					// 'a' can be change into somthing else but not numbers 1 to 9 and character operators
		flag = 1;
	}
	return flag;
}
float stringToFloat(char a[],int index){  //converts string to float data type
	int i=index,point,y=1,num1=0,num2=0;
	float fnum;
	while(a[i]!='\0'){
		if(a[i]=='.'){
			point=i;
			break;
		}
		i++;
	}
	for(i=index;a[i]!='\0'&& a[i]!=' ';i++){
		if(i<point){
			num1 = num1 * 10 + ( a[i] - '0' );
		}
		else if(i == point){
			continue;
		}
		else {
			num2 =	num2 * 10 +( a[i] - '0' );
			y = y * 10;  
		}
	}
	fnum = num2 / (float) y;
	fnum+=num1;
	return fnum;
}

bool isOperator(char a){ //check if the given character is an operator or not;
	bool flag = false;
	if(a=='+'||a=='-'||a=='*'||a=='/'){
		flag = true;
	}
	return flag;
}


bool floatORinteger(char a[]){ 	// detects if the string number has a decimal or a devision operator for decimal prinitng  
	int i = 0;		// this is to determine what type of %f should be used.
	bool flag = false;
	while(a[i]!='\0'){
		if(a[i]=='.' || a[i]=='/'){
			flag = true;
			break;
		}
		i++;
	}
	return flag;
}

void displayError(int result){  //display the error if there is error. value of result is used to know what was the last number or string have been push
	if(result >=0 && result <= 9){
		printf("Missing Operator");
	}
	else if(result=='+'||result=='-'||result=='*'||result=='/'){
		printf("Missing Operand");
	}
	else {
		printf("Invalid Expression"); 
	}
}

void displayFloat(int error, float result, char str[]){ //display's with decimal value
	if(!error){
		printf("%s = %.2f",str,result);
	}
	else {
		displayError(result);
	}
}

void displayInt(int error, float result, char str[]){   //displays's without decimal value
	if(!error){
		printf("%s = %.f",str,result);
	}
	else {
		displayError(result);
	}
}
