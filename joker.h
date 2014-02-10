/*
 * 																				Header File designed for
 * 																				Digital Image Processing 
 * 																				By Durgaprasad R B110426EC                                        * /
 * */			
//This function is for finding the attributes of an image
void imattrib(char *);
//This function is for finding the writing an image to file name passed as 2nd argument
void writeimg(char * , char * ,char c,long int *, long int *);
//This function is to find the mean
void mean(char *);
//This function is to find the histogram
void histogram(char *,char *);
//This function is used to find the equalised histogram
void histeq(char *,char*);
//This function is used to blur an image
void blur(char *, int, char );
//This function does the subtraction part
void sum(char *, char *);
//This function does the unsharp masking
void unsharp(char *);