	/*
	 =================================================================================
	 Name        : q1_julia_explorer.c
	 Author      : Jeffrey Leung 
	 Description : Read file and print in stdout. Print the appropriate variable
	 			   when read the tags "#A#" and "#B#"
	 =================================================================================
	 */
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	int main(int argc, char * argv[]) {
		
		float a,b;
		char s;

		//Verify number of arguments entered
		if(argc != 4){
			printf("Wrong number of arguments");
			exit(-1);
		}
		else {
		 //Check float a
		  if(sscanf(argv[2],"%f",&a)!=1){
		  	printf("Error: Bad float arguments");
		  	exit(-1);
		  }
		 //Check float b
		  if(sscanf(argv[3],"%f",&b) != 1){
		  	printf("Error: Bad float arguments");
		  	exit(-1);
		  }
		 // Open file
		  FILE* fp = fopen(argv[1], "r");
		  if (fp == NULL){
		  		printf("Error: Bad file");
		  		exit(-1);
		  }

		  //Read file and print in stdout
		  do{
			s = getc(fp);

			//Check for the tags and replace by the appropriate variable
			if(s == '#'){
				s=getc(fp);
				if(s =='A'){
					if((s=getc(fp))=='#'){
						printf("%.6f",a );
					}
				}
				if(s == 'B'){
					if((s=getc(fp))=='#'){
						printf("%.6f",b );
					}
				}
			}
			else if(s == EOF){
				break;
			}
			else{
				printf("%c",s);
			}	
		}
		while(s!=EOF);
		
		fclose(fp);

		}	
		return 0;
	}

