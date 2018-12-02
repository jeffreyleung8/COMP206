/*
 =================================================================================
 Name        : q2_calendar.c
 Author      : Jeffrey Leung 
 Description : Print a calendar according to the daySize and the firstDay received
 			   arguments
 =================================================================================
 */
#define NBMONTHS 12
#define NBDAYS 30
#define NBWEEKDAY 7
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //For strlen

char* formatWeekName(int daySize, char* str, int width){
}

char* formatDate(int daySize, char* str){
	//Size of the space containing the week name(+2 for the space each side)
	int size = daySize +2;

	char* newStr;
	newStr = (char*)malloc(sizeof(char)*size);

	int position = 0;
	newStr[position]= ' ';
	position++;

	for(int i=0; i< strlen(str);i++){
		newStr[position]=str[i];
		position++;
	}
	while(position < size){
		newStr[position]= ' ';
		position++;
	}
	return newStr;
}

void printSeparatorLine(int width){
	for(int i =0; i < width; i++){
		if(i == 0){
			printf("|");
		}
		else if(i+1 == width){
			printf("|\n");
		}
		else{
			printf("-");
		}
	}

}

void printMonthName(int width, char* monthName){
}

void printWeekName(int daySize,int width, char* week[]){
	printf("|");
	for(int i = 1; i <= NBWEEKDAY; i++){
		printf("%s", formatWeekName(daySize, week[i],width));
		printf("|");
	}
	printf("\n");

}

void printDay(int daySize, char* day[], int* index){
}

void printCalendar(int daySize, int firstDay, int width, char* day[], char* week[], char* monthName, int* index){
	printSeparatorLine(width);
	printMonthName(width, monthName);
	printSeparatorLine(width);
	printWeekName(daySize, width, week);
	printSeparatorLine(width);
	printDay(daySize, day, index);
}

int main(int argc, char * argv[]) {

	int daySize, firstDay;

	//1 for January, 12 for December
	char* month[]={"","January","February","March","April","May","June","July","August","September","October","November","December"};

	//1 for Sunday, 7 for Saturday
	char* week[] = {"", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

	char* day[] = {" ","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30"};
/*
 =================================================================================
 Name        : q2_calendar.c
 Author      : Jeffrey Leung 260747885
 Description : Print a calendar according to the daySize and the firstDay received
 			   arguments
 =================================================================================
 */
#define NBMONTHS 12
#define NBDAYS 30
#define NBWEEKDAY 7
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //For strlen

char* formatWeekName(int daySize, char* str, int width){
	//Size of the space containing the week name(+2 for the space each side)
	int size = daySize +2;

	char* newStr;
	newStr=(char*)malloc(sizeof(char)*size);
	
	int position = 0;
	
	newStr[position]=' ';
	position++;

	if(daySize > strlen(str)){
		for(int i =0; i< strlen(str); i++){
			newStr[position]=str[i];
			position++;
		}
	}
	else{
		for(int i =0; i< daySize; i++){
			newStr[position]=str[i];
			position++;
		}
	}

	while(position < size){ 
		newStr[position]= ' ';
		position++;
	}

	return newStr;
}

char* formatDate(int daySize, char* str){
	//Size of the space containing the week name(+2 for the space each side)
	int size = daySize +2;

	char* newStr;
	newStr = (char*)malloc(sizeof(char)*size);

	int position = 0;
	newStr[position]= ' ';
	position++;

	for(int i=0; i< strlen(str);i++){
		newStr[position]=str[i];
		position++;
	}
	while(position < size){
		newStr[position]= ' ';
		position++;
	}
	return newStr;
}

void printSeparatorLine(int width){
	
	for(int i =0; i < width; i++){
		if(i == 0){
			printf("|");
		}
		else if(i+1 == width){
			printf("|\n");
		}
		else{
			printf("-");
		}
	}

}

void printMonthName(int width, char* monthName){
	//Define the space each side of the month name
	int space1, space2;

	if((width-strlen(monthName))%2 == 0){
		space1= (width-strlen(monthName)-2)/2;
		space2= space1;
	}
	else{
		space1 = (width-strlen(monthName)-2)/2;
		space2 = space1+1;
	}

	printf("|");

	for(int i = 0; i < space1; i++){
		printf(" ");
	}

	printf("%s",monthName);

	for(int i = 0; i < space2; i++){
		printf(" ");
	}
	printf("|\n");
}

void printWeekName(int daySize,int width, char* week[]){
	printf("|");
	for(int i = 1; i <= NBWEEKDAY; i++){
		printf("%s", formatWeekName(daySize, week[i],width));
		printf("|");
	}
	printf("\n");

}

void printDay(int daySize, char* day[], int* index){
	printf("|");
	int position= 1; //Sunday
	while(position != *index ){
		printf("%s", formatDate(daySize, day[0]));
		printf("|");
		position++;
	}
	for(int i = 1; i <= NBDAYS; i++){
		if(position == 8){
			position = 1;
			printf("\n");
			printf("|");
		}
		printf("%s", formatDate(daySize, day[i]));
		printf("|");
		position++;
	}
	*index=position;
	while(position <= 7){
		printf("%s", formatDate(daySize, day[0]));
		printf("|");
		position++;
	}
	printf("\n");
}

void printCalendar(int daySize, int firstDay, int width, char* day[], char* week[], char* monthName, int* index){
	printSeparatorLine(width);
	printMonthName(width, monthName);
	printSeparatorLine(width);
	printWeekName(daySize, width, week);
	printSeparatorLine(width);
	printDay(daySize, day, index);
}

int main(int argc, char * argv[]) {

	int daySize, firstDay;

	//1 for January, 12 for December
	char* month[]={"","January","February","March","April","May","June","July","August","September","October","November","December"};

	//1 for Sunday, 7 for Saturday
	char* week[] = {"", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

	char* day[] = {" ","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30"};

	//Verify number of arguments entered
	if(argc != 3){
		printf("Wrong number of arguments");
		exit(-1);
	}
	//Check validity of arguments entered
	else {
	  sscanf(argv[1],"%d",&daySize);
	  sscanf(argv[2],"%d",&firstDay);

	  if(daySize < 2 || firstDay<1 || firstDay>7){
	  	printf("Wrong day size / first day");
	  	exit(-1);
	  }
	}
	//Total width of the calendar
	int width = (daySize+3) * 7 + 1;

	//Index for the first day of each month
	int* index;
	index = (int*)malloc(sizeof(int));
	*(index) = firstDay;

	//Print each month
	for(int i =1; i <= NBMONTHS; i++){
		printCalendar(daySize,firstDay, width, day, week,month[i], index);
	}
	printSeparatorLine(width);
	return 0;
}

	//Verify number of arguments entered
	if(argc != 3){
		printf("Wrong number of arguments");
		exit(-1);
	}
	//Check validity of arguments entered
	else {
	  sscanf(argv[1],"%d",&daySize);
	  sscanf(argv[2],"%d",&firstDay);
	}
	//Total width of the calendar
	int width = (daySize+3) * 7 + 1;

	//Index for the first day of each month
	int* index;
	index = (int*)malloc(sizeof(int));
	*(index) = firstDay;

	//Print each month
	for(int i =1; i <= NBMONTHS; i++){
		printCalendar(daySize,firstDay, width, day, week,month[i], index);
	}
	printSeparatorLine(width);
	return 0;
}
