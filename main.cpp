#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "joker.cpp"
#include "joker.h"

using namespace std;
int  main(int argc , char **argv)
 { 
 
  char highpasswindow[40]="3highpasswindow.pgm";
 	    int n;
       if( argc <2 )
    {
      printf( "No image data as input\n" );
      cout<<"Format is "<<argv[0]<<" 'image to be blurred ' \n";
      return (-1);
    }   
  
  //Smoothing
 	//Low Pass Filter
 	//Box filter
 	//with a window size 3*3	
 	/*
 	*          Pass the window size and filter type 
 	*        'b' for box filter , 'w' weighted filter ,  'g' guassian filter
 	*
    */
     //with a window size 3*3 this is for sharpening done later
     blur(argv[1],3,'b');
     cout<<"Enter the window size for box filter::\n";
     cin>>n;
     blur(argv[1],n,'b');
     cout<<"Enter the window size for box filter::\n";
     cin>>n;
     blur(argv[1],n,'w');
   //Sum of two image and sharpened image
   sharpen(argv[1]);
   imattrib(argv[1]);
   sum(argv[1],highpasswindow);
   //Unsharp masking
   unsharp(argv[1]);
   //histogram(window,window1);
   //histeq(window,moon);
   //Weighted filter
cout<<"The sharpened image is saved in SumImage.pgm\n";
	 
return(1);
}
