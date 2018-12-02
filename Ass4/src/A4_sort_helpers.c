#include "A4_sort_helpers.h"
#define   BUF_SIZE   100
// Function: read_all()
// Provided to read an entire file, line by line.
// No need to change this one.
void read_all( char *filename ){

    FILE *fp = fopen( filename, "r" );
    int curr_line = 0;

    while( curr_line < MAX_NUMBER_LINES &&
           fgets( text_array[curr_line], MAX_LINE_LENGTH, fp ) )
    {
        curr_line++;
    }

    text_array[curr_line][0] = '\0';
    fclose(fp);
}

// Function: read_all()
// Provided to read only the lines of a file staring with first_letter.
// No need to change this one.
void read_by_letter( char *filename, char first_letter ){

    FILE *fp = fopen( filename, "r" );
    int curr_line = 0;
    text_array[curr_line][0] = '\0';

    while( fgets( text_array[curr_line], MAX_LINE_LENGTH, fp ) ){
        if( text_array[curr_line][0] == first_letter ){
            curr_line++;
        }

        if( curr_line == MAX_NUMBER_LINES ){
            sprintf( buf, "ERROR: Attempted to read too many lines from file.\n" );
            write( 1, buf, strlen(buf) );
            break;
        }
    }

    text_array[curr_line][0] = '\0';
    fclose(fp);
}

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q1.
void sort_words( ){
  int i = 1;
    while( text_array[i][0] != '\0' ){
        char temp[MAX_LINE_LENGTH];
        strcpy(temp, text_array[i]);
        int j = i - 1;
        while (j >= 0 && (strcmp(text_array[j],temp) > 0 )){
            strcpy(text_array[j+1], text_array[j]);
            j=j-1;
        }
        strcpy(text_array[j+1], temp);
        i++;
    }

}
sem_t * sem_array[32];

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q2.
int initialize( ){
    // Remove the current place-holder code, and write your own.
    // sprintf(buf, "Initializing.\n"  );
    // write(1, buf, strlen(buf));
    char * buffer;
    buffer = (char*)malloc(BUF_SIZE);
    int i;
    for(i = 0 ; i < 26; i++){
      sprintf(buffer, "SEM_%c",'a'+ i );
    //  printf("%s\n",buffer );
      sem_unlink(buffer);
      if(i == 0){
        sem_array[i]=sem_open( buffer , O_CREAT, 0666, 1 );
      }
      else{
        sem_array[i]=sem_open( buffer , O_CREAT, 0666, 0 );
      }
    }
    sem_array[26] = sem_open( "sem_parent" , O_CREAT, 0666, 0 );
    return 0;
}

// YOU MUST COMPLETE THIS FUNCTION FOR Q2 and Q3.
int process_by_letter( char* input_filename, char first_letter ){

    int i = first_letter - 'a';
    sem_wait(sem_array[i]);
    FILE * f = fopen("temp_file.txt","a");
    if(f == NULL){
      sprintf(buf, "Error: could not open file");
      write(1, buf, strlen(buf));
      return -1;
    }
    read_by_letter( input_filename, first_letter );
    sort_words( );
    int k = 0;
    while( text_array[k][0] != '\0' ){
        fprintf(f, "%s", text_array[k]);
        k++;
    }
    fclose(f);
    //sprintf( buf, "This process will sort the letter %c.\n",  first_letter );
    //write(1,buf,strlen(buf));
    sem_post(sem_array[i+1]);

    return 0;
}

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q2 and Q3.
int finalize( ){

    sem_wait(sem_array[26]);
    FILE * f = fopen("temp_file.txt","r");
    if(f == NULL){
      sprintf(buf, "Error: could not sort");
      write(1, buf, strlen(buf));
      return -1;
    }
    char str [MAX_LINE_LENGTH];
    while(!feof(f)){
      strcpy(str,"\0");
      fgets(str, MAX_LINE_LENGTH, f);
      sprintf(buf, "%s", str);
      write(1, buf, strlen(buf));
    }

    fclose(f);
    sprintf( buf, "Sorting complete!\n" );
    write( 1, buf, strlen(buf) );
    int ret = remove("temp_file.txt");

    if(ret == 0) {
      //File deleted successfully
      return 0;
    } else {
      //File not deleted
      return -1;
    }

}
