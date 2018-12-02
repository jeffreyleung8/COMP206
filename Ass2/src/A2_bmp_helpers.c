/* FILE: A2_bmp_helpers.c is where you will code your answers for Assignment 2.
 *
 * Each of the functions below can be considered a start for you.
 *
 * You should leave all of the code as is, except for what's surrounded
 * in comments like "REPLACE EVERTHING FROM HERE... TO HERE.
 *
 * The assignment document and the header A2_bmp_headers.h should help
 * to find out how to complete and test the functions. Good luck!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

int bmp_open( char* bmp_filename,        unsigned int *width,
              unsigned int *height,      unsigned int *bits_per_pixel,
              unsigned int *padding,     unsigned int *data_size,
              unsigned int *data_offset, unsigned char** img_data ){

  //Open file
  FILE *bmpfile = fopen(bmp_filename, "rb");

  //Read B and M characters into chars
  char b ,m;
  fread(&b,1,1,bmpfile);
  fread(&m,1,1,bmpfile);

  //Read file size
  unsigned int overallFileSize;
  fread(&overallFileSize, 1, sizeof(unsigned int), bmpfile);

  //Close file and re-open it at the beginning to read the entire content
  fclose(bmpfile);
  bmpfile = fopen(bmp_filename,"rb");

  *img_data = (unsigned char*)malloc(overallFileSize*sizeof(char));

  fread(*img_data, 1, overallFileSize, bmpfile);

  *width = *(unsigned int*)(*img_data+18);
  *height = *(unsigned int*)(*img_data+22);
  *bits_per_pixel = *(unsigned int*)(*img_data+28);

  *padding= 4-((((*width)*(*bits_per_pixel))/8)%4);
  if(*padding == 4){ (*padding) = 0; }

  *data_size = overallFileSize;
  *data_offset=*(unsigned int*)(*img_data+10);

  return 0;
}

// We've implemented bmp_close for you. No need to modify this function
void bmp_close( unsigned char **img_data ){

  if( *img_data != NULL ){
    free( *img_data );
    *img_data = NULL;
  }
}

int bmp_mask( char* input_bmp_filename, char* output_bmp_filename,
              unsigned int x_min, unsigned int y_min, unsigned int x_max, unsigned int y_max,
              unsigned char red, unsigned char green, unsigned char blue )
{
  unsigned int img_width;
  unsigned int img_height;
  unsigned int bits_per_pixel;
  unsigned int data_size;
  unsigned int padding;
  unsigned int data_offset;
  unsigned char* img_data = NULL;

  int open_return_code = bmp_open( input_bmp_filename, &img_width, &img_height, &bits_per_pixel, &padding, &data_size, &data_offset, &img_data );

  if( open_return_code ){ printf( "bmp_open failed. Returning from bmp_mask without attempting changes.\n" ); return -1; }

  //Create new image(memory allocation)
  unsigned char* new_img = (unsigned char*)malloc((data_size )*sizeof(unsigned char));

  // //Copy the input to the new image
  memcpy(new_img,img_data,data_size);

  unsigned int num_colors = bits_per_pixel/8;

  for(unsigned int y= y_min; y <= y_max;y++){
    for(unsigned int x= x_min; x < x_max;x++){
      new_img[ y*(img_width*num_colors+padding) + x*num_colors + 2 + data_offset] = red;
      new_img[ y*(img_width*num_colors+padding) + x*num_colors + 1 + data_offset] = green;
      new_img[ y*(img_width*num_colors+padding) + x*num_colors + 0 + data_offset] = blue;
    }    
  }

  //Open output file
  FILE* outputFile = fopen(output_bmp_filename, "w");
  fwrite(new_img, sizeof(char), data_size, outputFile);
  bmp_close(&img_data);
  bmp_close(&new_img);
  fclose(outputFile);

  return 0;
}

int bmp_collage( char* bmp_input1, char* bmp_input2, char* bmp_result, int x_offset, int y_offset ){

  unsigned int img_width1;
  unsigned int img_height1;
  unsigned int bits_per_pixel1;
  unsigned int data_size1;
  unsigned int padding1;
  unsigned int data_offset1;
  unsigned char* img_data1    = NULL;

  int open_return_code = bmp_open( bmp_input1, &img_width1, &img_height1, &bits_per_pixel1, &padding1, &data_size1, &data_offset1, &img_data1 );

  if( open_return_code ){ printf( "bmp_open failed for %s. Returning from bmp_collage without attempting changes.\n", bmp_input1 ); return -1; }

  unsigned int img_width2;
  unsigned int img_height2;
  unsigned int bits_per_pixel2;
  unsigned int data_size2;
  unsigned int padding2;
  unsigned int data_offset2;
  unsigned char* img_data2    = NULL;

  open_return_code = bmp_open( bmp_input2, &img_width2, &img_height2, &bits_per_pixel2, &padding2, &data_size2, &data_offset2, &img_data2 );

  if( open_return_code ){ printf( "bmp_open failed for %s. Returning from bmp_collage without attempting changes.\n", bmp_input2 ); return -1; }

  //Determining the width and the height of new collage
  unsigned int new_width;
  unsigned int new_height;

  if(x_offset >= 0){
    if(img_width2 + x_offset > img_width1){
      new_width = img_width2 + x_offset;
    }
    else{
      new_width = img_width1;
    }
  }
  if(x_offset < 0){
    if(img_width2 < img_width1 || (img_width2 - img_width1) < abs(x_offset)){
      new_width = img_width1 + abs(x_offset);
    }
    else{
      new_width = img_width2;
    }
  }

  if(y_offset >= 0){
    if(img_height2 + y_offset > img_height1){
      new_height = img_height2 + y_offset;
    }
    else{
      new_height = img_height1;
    }
  }
  if(y_offset < 0){
    if(img_height2 < img_height1 || (img_height2 - img_height1) < abs(y_offset)){
      new_height = img_height1 + abs(y_offset);
    }
    else{
      new_height = img_height2;
    }
  }
  
  //Assuming the bits per pixel is 24 for the new image (bits_per_pixel1 == bits_per_pixel2==24)
  unsigned int new_bits_per_pixel = bits_per_pixel1 ;

  unsigned int new_padding = 4-((((new_width)*(new_bits_per_pixel))/8)%4);
  if(new_padding == 4){ (new_padding) = 0; }

  unsigned int new_size = data_offset1 + (new_width*(new_bits_per_pixel/8) + new_padding) * new_height;
  
  unsigned char* new_img = (unsigned char*)malloc(new_size);

  memcpy(new_img,img_data1,data_offset1);
  
  //Header update
  memcpy(new_img+2, &new_size,4);
  memcpy(new_img+18, &new_width,4);
  memcpy(new_img+22, &new_height,4);

  unsigned int img_one_start_col;
  unsigned int img_one_start_row;
  unsigned int img_two_start_col;
  unsigned int img_two_start_row;

  if(x_offset >= 0){
    img_one_start_col = 0;
    img_two_start_col = x_offset;
   
  }
  else if (x_offset < 0){
    img_one_start_col = abs(x_offset);
    img_two_start_col = 0;
  }

  if(y_offset >= 0){
    img_one_start_row = 0;
    img_two_start_row = y_offset;
  }
   
  else if(y_offset < 0){
    img_one_start_row = abs(y_offset);
    img_two_start_row = 0;
  }
 
  unsigned int img_one_end_col = img_one_start_col + img_width1;
  unsigned int img_one_end_row = img_one_start_row + img_height1;
  unsigned int img_two_end_col = img_two_start_col + img_width2;
  unsigned int img_two_end_row = img_two_start_row + img_height2;

  unsigned int new_num_colors = new_bits_per_pixel/8;
  unsigned int num_colors1 = bits_per_pixel1/8;
  unsigned int num_colors2 = bits_per_pixel2/8;

  //Indexes for image_1 and image_2
  unsigned int img_two_x = 0;
  unsigned int img_two_y = 0;
  unsigned int img_one_x = 0;
  unsigned int img_one_y = 0;

  //Copying first image into canvas
  for(unsigned int y = 0; y <= new_height;y++){ //horizontal
    for(unsigned int x = 0; x <= new_width; x++){ //vertical
      if(y >= img_one_start_row  && y < img_one_end_row  && x >= img_one_start_col  && x < img_one_end_col ){
        //Copy pixels of image_two into verticle horizontal indexes of new canvas
        new_img[ y*(new_width*new_num_colors+new_padding) + x*new_num_colors + 2 + data_offset1] = img_data1[ img_one_y*(img_width1*num_colors1+padding1) + img_one_x*num_colors1 + 2 + data_offset1];
        new_img[ y*(new_width*new_num_colors+new_padding) + x*new_num_colors + 1 + data_offset1] = img_data1[ img_one_y*(img_width1*num_colors1+padding1) + img_one_x*num_colors1 + 1 + data_offset1];
        new_img[ y*(new_width*new_num_colors+new_padding) + x*new_num_colors + 0 + data_offset1] = img_data1[ img_one_y*(img_width1*num_colors1+padding1) + img_one_x*num_colors1 + 0 + data_offset1];
        img_one_x++;
        if(img_one_x == img_width1){
          img_one_y++;
          img_one_x = 0;
        }
        if(img_one_y == img_height1){
          break;
        }
      
      }
    }
  }
  //Copying second image into canvas
  for(unsigned int y = 0; y <= new_height;y++){ //horizontal
    for(unsigned int x = 0; x <= new_width; x++){ //vertical
      if(y >= img_two_start_row  && y < img_two_end_row && x >= img_two_start_col  && x < img_two_end_col){
        //Copy pixels of image_two into verticle horizontal indexes of new canvas
        new_img[ y*(new_width*new_num_colors+new_padding) + x*new_num_colors + 2 + data_offset1] = img_data2[ img_two_y*(img_width2*num_colors2+padding2) + img_two_x*num_colors2 + 2 + data_offset2];
        new_img[ y*(new_width*new_num_colors+new_padding) + x*new_num_colors + 1 + data_offset1] = img_data2[ img_two_y*(img_width2*num_colors2+padding2) + img_two_x*num_colors2 + 1 + data_offset2];
        new_img[ y*(new_width*new_num_colors+new_padding) + x*new_num_colors + 0 + data_offset1] = img_data2[ img_two_y*(img_width2*num_colors2+padding2) + img_two_x*num_colors2 + 0 + data_offset2];
        img_two_x++;
        if(img_two_x == img_width2){
          img_two_y++;
          img_two_x = 0;
        }
        if(img_one_y == img_height2){
          break;
        }
      }
    }
  }

  bmp_close(&img_data1);
  bmp_close(&img_data2);
  FILE* resultFile = fopen(bmp_result, "w");
  fwrite(new_img, sizeof(char), new_size, resultFile);
  fclose(resultFile);
  return 0;
}
