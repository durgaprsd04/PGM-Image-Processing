
/*********************************************************************************************************************************************/
/*   		                                        Header file designed as a part of Digital Image Processing   		             *
*																										             *														
*	                                                          This was designed and coded in Sublime-Text                          *																												  *																					    *	
*		                                     Topic    : Header file for image processing using a C++ Program *																																								 *																																																																						  *	
*						                                                                       By DurgaPrasad R *			                          									  B110426EC *																																																							     *
*																																																																														 *
/*********************************************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include "joker.h"
using namespace std;
/*The function given below find out  various attributes regarding an image
 * such as pixel sizes and gray  scales */
 /*String class is used for ease of handling of files */
void imattrib(char * imagename)
{              
		  char str[40],buffer[20];
		  ifstream imread	;
		  string image;
		  cout<<"\nThe image read is "<<imagename<<"\n"; 
		  imread.open(imagename);
		  getline(imread,image);
		  size_t length = image.copy(buffer,image.length(),0);
		  buffer[length]='\0';
		  //cout<<buffer<<"\n";
		  // The character is read here and the image is identified as 
		  //pgm pbm or ppm 
		  if(buffer[0]=='P')
			{
				switch(buffer[1])
					{
							case '1':
							case '4':
									cout<<"The tag is "<<buffer<<"\n";
									cout<<"File is pbm type\n";
									break;
							case '2':
							case '5':
									cout<<"The tag is "<<buffer<<"\n";
									cout<<"File is pgm type\n";
									break;
							case '3':
							case '6':
									cout<<"The tag is "<<buffer<<"\n";
									cout<<"File is ppm \n";
									break;
					};
			}     
		else
			{
				cout<<"File is not recongnized\n";
			}
			//Getting and printing all important attributes
		getline(imread,image);
	    length = image.copy(buffer,image.length(),0);
	    //ending the string with a null pointer
		buffer[length]='\0';
		//to find if there are any hashed comments                                         
		if(buffer[0]!='#')
		  {
			  cout<<"No Hashed comments\n";
			  imread.seekg(-(strlen(buffer)+1),ios::cur);
			  }
         else
           {
		     cout<<"Hashed Comment is \n";
		     cout<<buffer<<"\n";
		   }
		imread>>str;
	   cout<<"The dimensions are        ::"<<str;
	   imread>>str;
	   cout<<"*"<<str;
	   imread>>str;
	   cout<<"\nThe number of grey levels ::"<<str<<"\n";
	   imread.close();
}
/* This part of the code is designed for writing the read image to a 
 * another image . This could later be used by the functions given
 * below to compute mean 
 * and histogram*/
void writeimg(char * imname , char *im2write ,char c, long int  *p ,long int *q)
{
    string image;
    ifstream imread;
    ofstream imwrite;
	imread.open(imname);
	imwrite.open(im2write);
   char str[40],buffer[30];
   int i=0,j=0;
   long int m,n;
   // This file is designed for reading a pgm image. This could be expanded to
   // read image any image with similar formats
if (c=='g')
  { 
	  			// For reading image we use a class known as string;
	  			//The whole program is based on the function that reads 
	  			// a particular line
		            getline(imread,image);    // a single line is read
			    size_t length = image.copy(buffer,image.length(),0);
			    //now a size_t variable
			    // is defined
			    buffer[length]='\0';
			    getline(imread,image);
			    length = image.copy(buffer,image.length(),0);
			    buffer[length]='\0';
			    if(buffer[0]!='#')
		        {
			          imread.seekg(-(strlen(buffer)+1),ios::cur);
			    }
			    //Steps for creating a new image ppm
			   	imwrite<<"P2"<<"\n";
				imwrite<<"# Image Created using C++";
				imwrite<<"\n";
				imread>>str;
				imwrite<<str<<"\t";
				m=atoi(str);
				imread>>str;
				imwrite<<str<<"\t\n";
				n=atoi(str);
				imread>>str;
				imwrite<<str<<"\n";	
				*p=m;
				*q=n;	
				for (i=0;i<m;i++)
				{
					for (j=0;j<n;j++)
						{
								imread>>str;
								imwrite<<str<<"\n";
						}
				}
  }
else 

imwrite.close();
imread.close();
} 
/*The code given below calculates the mean of gray levels. The value of each 
 * gray level is added and then divided with the total number of gray levels 
 * to provide */
void mean(char *imageread	)
   {
	    int i,j;
		char str[40],buffer[20];
        int array[255]={0};
		ifstream imread	;
		string image;
		int num;
		double mean;
		long int M,N;
		cout<<"The image read is "<<imageread<<"\n"; 
		imread.open(imageread);
		  getline(imread,image);
		  size_t length = image.copy(buffer,image.length(),0);
		getline(imread,image);
	    length = image.copy(buffer,image.length(),0);
	    if(buffer[0]!='#')// This part is to avoid any comments if any comes
		        {
			          imread.seekg(-(strlen(buffer)+1),ios::cur);
			    }
		imread>>str;
		M=atoi(str);
	    imread>>str;
	   N=atoi(str);
	   imread>>str;   
	   //The average is calculated by finding the sum.
        for (i=0;i<int(M);i++)
						{
		      				for (j=0;j<int(N);j++)
								{
										imread>>str;
										num=atoi(str);
										array[num]++;
										mean=mean+num;
								}
						}
	cout<<"Mean of gray levels ::"<<((mean)/(M*N))<<"\n";
	}
	/*Finding histogram using simple procedure.
	 * It is calculated by using any graylevel as index of an array 
	 * then finding the maximum value and then dividing through 
	 * with the same.*/ 
void histogram(char *imageread, char *histname)
    {
	     int i,j;
		char str[40],buffer[20];
        int array[255]={0};
		ifstream imread	;
		ofstream imread1;
		string image;
		int num;
		double mean=0,max=0;
		long int M,N;
		//The image once read in loaded into file pointer
		// The read image's  attribute is used and thus.
		imread.open(imageread);
		getline(imread,image);
  size_t length = image.copy(buffer,image.length(),0);
		getline(imread,image);
  length = image.copy(buffer,image.length(),0);
  		    if(buffer[0]!='#')//This part is to avoid any comments if there is. 
		        {
			          imread.seekg(-(strlen(buffer)+1),ios::cur);
			       }
		  imread>>str;
		  M=atoi(str);
	   imread>>str;
	   N=atoi(str);
	   imread>>str;
	   //This loop is to find the number of each gray levels   
	   for (i=0;i<int(M);i++)
						{
		      				for (j=0;j<int(N);j++)
								{
										imread>>str;
										num=atoi(str);
										array[num]++;
								}
						}
	for (i=0;i<255;i++)
			{
				  
					if(array[i]>max)
					max=array[i];
			}
			
		cout<<"Maximum value in c[l]  ::"<<max<<"\n";
		for (i=0;i<255;i++)
			{
					array[i]=(double(array[i])*255)/double(max);
			       // cout<<array[i]<<"\t";This cmd is for checking purposes
			}
		
		imread.close();
		//The first stream is closed
		//A new image is opened and created for histogram
		imread1.open(histname);
		imread1<<"P1"<<"\n";
		imread1<<"# Created using C \n";
		imread1<<"255"<<"\t";
		imread1<<"255"<<"\t\n";
        //Loop for making the histogram 		
		
		for (i=255;i>0;i--)
		{
		for (j=0;j<255;j++)
		    { 
				if(i<array[j])
					{
					 imread1<<"1";
	     			 }
					else
					{
					  imread1<<"0";
				   }
     		  }
				    imread1<<"\n"; 
       }
}
 
void histeq(char *imname,char *imname2 )
    {   
    	/*The class declared below gives the image aspects such as gray levels and all*/
		class img
			{
				public:
				int px;
				int actgry;
				int gry;
				int grye;
				int grys;	
				double cmp;
			};	
			//Two objects are declared as follows;
			img *img1,*img2;
			img1= new img[256];//memory space is required
			img2= new img[256];//memory space is required
			double diff1=0,diff2=0;
			int i,j,k=0,num,mink=0,array[256]={0};
			float diff[255]={0};
			double min;
			int M,N;//size variables for our image
			int P,Q;//size variables for reference image.
			string im1;//class string variable for eliminating lines in the read file
			char str[40],str1[40];
			ifstream image,image2;
			ofstream image1;
			image.open(imname);
			getline(image,im1);
			getline(image,im1);
			image>>str;
			M=atoi(str);
			image>>str;
			N=atoi(str);
			image>>str;
			// The loop given below gives us a read of c[l]
			for (i=0;i<M;i++)
			{
				 for(j=0;j<N;j++)
					{
					 image>>str;
					 num=atoi(str);
					 array[num]++;
				 }
			}
			image.close();
			//Now we are filling in the img1 array with important data such
			//as grays levels and cumulative probability density  (cdf)
			img1[0].px=array[0];
			img1[0].cmp=(double)(img1[0].px)/(double)(M*N);
			img1[0].gry=0;
			img1[0].actgry=0;
			img1[0].grys=0;
			img1[0].grye=0;
			//The process given above is continued and goes as follows
			for(i=1;i<256;i++)
			 {
			 img1[i].px=array[i];
			 img1[i].cmp=((double)(img1[i].px)/(double)(M*N))+(img1[i-1].cmp); 
			 img1[i].gry=i;
			 img1[i].actgry=i;
			 img1[i].grys=i;
			 img1[i].grye=i;
		  }
			 //Here specification of image using uniform probabiltiy is taking place.
			 // This block is designed for that. 
			 for(i=0;i<=255;i++)
			 {
				 for(j=0;j<=255;j++)
				 {
					 if((double)(j)*.0039>(img1[i].cmp))	
					 {
			 		 mink=j;	
			 			 break;		 		             
		    }
				 }
				 //This part is for specification using uniform probability density function
				 //code given below computes the closest gray level
				diff1=img1[i].cmp-(double)(mink-1)*(.0039);
				diff2=(double)(mink*.0039)-img1[i].cmp;	
				if(diff1>=diff2)
				img1[i].gry=mink;
				else
				img1[i].gry=mink-1;
					 
			}
			//Here each element in img1[i].gry will have the specifed grey levels 
			// Thus we could be get the specified distribution 
			//Starting with reference image
			//Here we read the image that is needed for standerdisation.
			for(i=0;i<=255;i++)
			array[i]=0;
			image.open(imname2);
			getline(image,im1);
			getline(image,im1);
			image>>str;
			P=atoi(str);
			image>>str;
			Q=atoi(str);
			image>>str;		
			for (i=0;i<P;i++)
			{
				 for(j=0;j<Q;j++)
				{
					 image>>str;
					 num=atoi(str);
					 array[num]++;
				 }
			}
			image.close();
			//That part is done.
			// Here we start with equalisation where we left off. 
			// we assign the probability density value and then calculate the corresponding grey level
			// and proceed with an equalied disribution of grey levels in variable img[i].grye
			 for(i=0;i<=255;i++)
		     {
				     img1[i].grye=double(img1[i].cmp*255);
			    }
			 //Now we go on writing that to and image file 
	   // named equalised . 
			 image1.open("equalised.pgm");
			 image1<<"P2"<<"\n";
			 image1<<"# Created using C \n ";
			 image1<<M<<"  "<<N<<"\n";
			 image1<<"255\n";
			 image.open(imname);
			 getline(image,im1);
		 	 getline(image,im1);
	 	     getline(image,im1);
			 getline(image,im1);   
			 for(i=0;i<M;i++)
			  {
				  for(j=0;j<N;j++)
				   {
					    image>>str;
				 	   num=atoi(str);
				 	   for(k=0;k<=255;k++)
				     if(img1[k].actgry==num)//here is where the assignment takes place
					      {
						       image1<<img1[k].grye;//here equalisation takes place
				       }
				     image1<<"\n";
				   }
			}
			image.close();
			image1.close();
			//Now we start with specified image histogram
			//So start with img2[] initialisation
			img2[0].px=array[0];
			img2[0].cmp=(double)(img2[0].px)/(double)(P*Q);
			img2[0].gry=0;
			img2[0].actgry=0;
			img2[0].grys=0;
			for(i=1;i<256;i++)
			 {
			   img2[i].px=array[i];
			   img2[i].cmp=((double)(img2[i].px)/(double)(P*Q))+(img2[i-1].cmp); 
			   img2[i].gry=i;
			   img2[i].actgry=i;
			   img2[i].grys=i;
		  }
		  min=0;
		  for(i=0;i<=255;i++)
			  {
				   for(j=0;j<=255;j++)
				   {
					    if((double)(img1[j].gry)*.0039>(img2[i].cmp))	
					    {
					      mink=j;	
						     break;
						   } 		             
		     }
				     // This algorithm is for the standardisation 
				    //code given below calculates the closest gray level
				   diff1=img2[i].cmp-(double)(img1[mink].gry)*(.0039);
				   diff2=(double)(img1[mink].gry)*.0039-img2[i].cmp;	
				   //cout<<min<<"  "<<mink<<" *";
				   if(diff1>=diff2)
				    {
					     for(k=min;k<=mink;k++)
					      {
					       img1[k].grys=img2[i].actgry;
				     	 }
					  min=mink;
					  //Here the theorm G(z)=s is implemented
				    }
				   else
				    {
				        for(k=min;k<=mink;k++)
             {
				          img1[k].grys=img2[i].actgry;
					        }
					    min=mink-1;
				     }
				
			  }
    //Here is what we do with uniform pdf The image is specified with uniform pdf
			// And the code is given as follows
   image.open(imname);
			getline(image,im1);
			getline(image,im1);
			getline(image,im1);
			getline(image,im1);
			image1.open("specifiedwithuniformpdf.pgm");
			image1<<"P2\n";
			image1<<"# Created using C++\n";
			image1<<M<<"  ";
			image1<<N<<"\n";
			image1<<"255"<<"\n";
			//Here the specification is done on closest approximation. 
			// The closest value is assigned as follows
			for(i=0;i<M;i++)
			{
				for(j=0;j<N;j++)
				{
					image>>str;
				 	num=atoi(str);
				 	for(k=0;k<=255;k++)
				     if(img1[k].actgry==num)
					      {
						      image1<<img1[k].gry;
				       }
				      image1<<"\n";
				}
			}
			image.close();
			image1.close();
			//Both file streams are closed and 
			//a new one is opened and a standardised image is produced as output
			image.open(imname);
			getline(image,im1);
			getline(image,im1);
			getline(image,im1);
			getline(image,im1);
			image1.open("standerdised.pgm");
			image1<<"P2\n";
			image1<<"# Created using C++\n";
			image1<<M<<"  ";
			image1<<N<<"\n";
			image1<<"255"<<"\n";
			//standardised image is written to file
			for(i=0;i<M;i++)
			{
				for(j=0;j<N;j++)
				{
					image>>str;
				 	num=atoi(str);
				 	for(k=0;k<=255;k++)
				     if(img1[k].actgry==num)
					      {
						     image1<<img1[k].grys;
				       }
				        image1<<"\n";
				}
			}
/// This is a output check  It could commented out. Error check is the reason for such a code
			 for(i=0;i<=255;i++)
			{
				cout<<img1[i].px<<"        "<<img1[i].gry<<"       "<<img1[i].actgry<<"        "<<img1[i].grys<<"      "<<img1[i].cmp<<"   "<<i<<"\n";
			}
          delete [ ] img1;
          delete [] img2;
}
void blur(char *iminput, int masksize, char type )
{
     string im1;
     ofstream imout;
     fstream imname;
     char str[40],buffer[40];
     int array[256];
     int i,j,num;
     int p,q;
     int masksum=0;
     int shift;
     int mean;
     double sum;
     //double window[3][3]={{1,2,1},{2,4,2},{1,2,1}};
     int M,N;
     int **window;
     int **imgptr,**imgptr1,**mskptr;
     imname.open(iminput);
     getline(imname,im1);
	 size_t length = im1.copy(buffer,im1.length(),0);
     buffer[length]='\0';
     getline(imname,im1);
	 length = im1.copy(buffer,im1.length(),0);
	 //ending the string with a null pointer
	 buffer[length]='\0';
   	 //to find if there are any hashed comments                                         
	 if(buffer[0]!='#')
		 {
		   //else the file pointer is kept where it was and reading begins again
 		   imname.seekg(-(strlen(buffer)+1),ios::cur);
		 }
	 //Reading image sizes
	 imname>>str;
	 M=atoi(str);
	 imname>>str;
	 N=atoi(str); 	 
	 //Reading out the gray levels
	 getline(imname,im1);
     //this allocates memory space for all the elements of the image
     imgptr= new int*[M];
     for(i=0;i<M;i++)
     {
     	imgptr[i]=new int[N];
     }
     if(type=='b')
     {
			     //this allocates space for a new image
			     imgptr1= new int*[M];
			     for(i=0;i<M;i++)
			     {
			     	imgptr1[i]=new int[N];
			     }
			     //Allocation of space for masks
			     mskptr=new int*[masksize];
			     for(i=0;i<masksize;i++)
			     {
			     	mskptr[i] = new int[masksize];
			     }
			     //Putting values to masks
			     
			     for ( i = 0; i < masksize; ++i)
			     {
			     	for ( j = 0; j < masksize; ++j)
			     	{
			     		mskptr[i][j]=1;
			     	}
			     }
			     	for ( i = 0; i < masksize; ++i)
			     	{
			     		for ( j = 0; j < masksize; ++j)
			     		{
			     			//cout<<mskptr[i][j]<<"\t";
			       		}
			       		//cout<<"\n";
			     	}
			     
			     //Reading from the image
			     for ( i = 0; i < N; ++i)
			     {
			     	for ( j = 0; j < M; ++j)
			     	{
			     		imname>>str;
			     		num=atoi(str);
			     		imgptr[j][i]=num;
			     	}
			     }
			     shift=(masksize-1)/2;
			     for(i=shift;i<(N-shift);i++)
			     {
			     	for(j=shift;j<(M-shift);j++)
			     	{
			     		mean=0;
			                for ( p = -1*shift; p <=shift; ++p)
			                {
			                	for (q = -1*shift; q <=shift; ++q)
			                	{
			                         mean=mean+(mskptr[p+shift][q+shift])*(imgptr[q+j][p+i]);
			                	}
			                }
			                imgptr1[j][i]=mean/(masksize*masksize);
			                mean=0;
			        }
			     } 

			     sprintf(str,"%d",masksize);
			     strcat(str,"window.pgm");
			     imout.open(str);
			     imout<<"P2\n";
			     imout<<"# Made in by C++\n";
			     imout<<M<<" ";
			     imout<<N<<"\n";
			     imout<<"255\n";
			     for (int i = 0; i < N; ++i)
			     {
			     	for (int j = 0; j < M; ++j)
			     	{
			     		imout<<imgptr1[j][i]<<"\n";
			     	}
			     }
     }
     if(type=='w')
     {
                 //this allocates space for a new image
			     window = new int*[masksize];
			     for(i=0;i<masksize;i++)
			     {
			     	window[i]=new int[masksize];
 				 }
 				 for(i=-(masksize/2);i<=(masksize/2);i++)
 				 	{
 				 		for(j=-(masksize/2);j<=(masksize/2);j++)
 				 		{
 				 			window[i+masksize/2][j+masksize/2]=pow(2,(masksize/2+1)-sqrt(i*i+j*j));//pow(2,masksize/2-int(sqrt(i*i+j*j)/1.414));
 				 	    }
 				 	}
 				 for(i=0;i<(masksize);i++)
 				 	{
 				 		for(j=0;j<(masksize);j++)
 				 		{
 				 			//cout<<window[i][j]<<"\t";//=pow(2,int(float(i/2)+float(j/2));
 				 	    	masksum=masksum+window[i][j];
 				 	    }
 				 	    //cout<<"\n";
 				 	}
 				 	
			     imgptr1= new int*[M];
			     for(i=0;i<M;i++)
			     {
			     	imgptr1[i]=new int[N];
			     } 
			     //Reading from the image
			     for ( i = 0; i < N; ++i)
			     {
			     	for ( j = 0; j < M; ++j)
			     	{
			     		imname>>str;
			     		num=atoi(str);
			     		imgptr[j][i]=num;
			     	}
			     }
			     shift=1;
			     for(i=masksize/2;i<(N-masksize/2);i++)
			     {
			     	for(j=masksize/2;j<(M-masksize/2);j++)
			     	{
			     		mean=0;
			                for ( p = -(masksize/2); p <=(masksize/2); ++p)
			                {
			                	for (q = -(masksize/2); q <=(masksize/2); ++q)
			                	{
			                         mean=mean+(window[p+masksize/2][q+masksize/2])*(imgptr[q+j][p+i]);
			                	}
			                }
			                imgptr1[j][i]=mean/(masksum);
			                mean=0;
			        }
			     } 
			     sprintf(str,"%d",masksize);
			     strcat(str,"weighted.pgm");
			     imout.open(str);
			     imout<<"P2\n";
			     imout<<"# Made in bjy C++\n";
			     imout<<M<<" ";
			     imout<<N<<"\n";
			     imout<<"255\n";
			     for (int i = 0; i < N; ++i)
			     {
			     	for (int j = 0; j < M; ++j)
			     	{
			     		imout<<imgptr1[j][i]<<"\n";
			     	}
			     }
    
     }
}
//Sum the images . Quite handy in many cases.
void sum(char *im1,char *im2)
{
	string str1;
	int num,i,j,max;
	char str[40],buffer[40];
	ifstream image1,image2;
	ofstream imout;
	int M,N,P,Q;
	int **imgptr1,**imgptr2,**imgptr3;
	image1.open(im1);
	image2.open(im2);
	getline(image1,str1);
	size_t length = str1.copy(buffer,str1.length(),0);
	getline(image1,str1);
    length = str1.copy(buffer,str1.length(),0);
  	if(buffer[0]!='#')//This part is to avoid any comments if there is. 
		    {
		    	image1.seekg(-(strlen(buffer)+1),ios::cur);
	        }
    image1>>str;
    M=atoi(str);
    image1>>str;
    N=atoi(str);
    getline(image2,str1);
	length = str1.copy(buffer,str1.length(),0);
	getline(image2,str1);
    length = str1.copy(buffer,str1.length(),0);
  	if(buffer[0]!='#')//This part is to avoid any comments if there is. 
		    {
		    	image2.seekg(-(strlen(buffer)+1),ios::cur);
	        }
    image2>>str;
    P=atoi(str);
    image2>>str;
    Q=atoi(str);
    getline(image2,str1);
    if((P!=M)||(Q!=N))
    {
    	cout<<"Image sizes differ\n";
        cout<<M<<N<<P<<Q;
    	return;
    }
   
    imgptr1=new int*[M];
    for ( i = 0; i < M; ++i)
    {
    	imgptr1[i]=new int[N];
    }
    imgptr2=new int*[M];
    for ( i = 0; i < M; ++i)
    {
    	imgptr2[i]=new int[N];
    }
	imgptr3=new int*[M];
    for (i = 0; i < M; ++i)
    {
    	imgptr3[i]=new int[N];
    }		  
     for(i=0;i<N;i++)
     {
     	for ( j = 0; j < M; ++j)
     	{
     		image1>>str;
     		num=atoi(str);
     		imgptr1[j][i]=num;
     	}
     }
     for(i=0;i<N;i++)
     {
     	for ( j = 0; j < M; ++j)
     	{
     		image2>>str;
     		num=atoi(str);
     		imgptr2[j][i]=num;
     	}
     }
     for ( i = 0; i < M; ++i)
     {
     	for ( j = 0; j < N; ++j)
     	{
     		
     		imgptr3[i][j]=imgptr1[i][j]+imgptr2[i][j];	
     	   				     
     	}
     }
     max=0;
     for (i = 0; i < M; ++i)
     {
         for (j = 0; j < N; ++j)
         {
         	if(imgptr3[i][j]>max)
         		max=imgptr3[i][j];
         }
     }
     for (i = 0; i < M; ++i)
     {
         for (j = 0; j < N; ++j)
         {
         	imgptr3[i][j]=double(imgptr3[i][j])*(255)/(double(max));
         }
     }
     imout.open("SumImage.pgm");
	 imout<<"P2\n";
	 imout<<"# Made in by C++\n";
	 imout<<M<<" ";
	 imout<<N<<"\n";
	 imout<<"255\n";
	 for ( i = 0; i < N; ++i)
	 {
	  	for ( j = 0; j < M; ++j)
	     	{
	     		imout<<imgptr3[j][i]<<"\n";
	     	}
	 }
}
void sharpen(char *iminput)
	{
	 string im1;
     ofstream imout;
     fstream imname;
     char str[40],buffer[40];
     int array[256];
     int i,j,num;
     int p,q;
     int shift;
     int mean;
     double sum;
     double window[3][3]={{0,-1,0},{-1,4,-1},{0,-1,0}};
     int M,N;
     int **imgptr,**imgptr1;
     imname.open(iminput);
     getline(imname,im1);
	 size_t length = im1.copy(buffer,im1.length(),0);
     buffer[length]='\0';
     getline(imname,im1);
	 length = im1.copy(buffer,im1.length(),0);
	 //ending the string with a null pointer
	 buffer[length]='\0';
   	 //to find if there are any hashed comments                                         
	 if(buffer[0]!='#')
		 {
		   //else the file pointer is kept where it was and reading begins again
 		   imname.seekg(-(strlen(buffer)+1),ios::cur);
		 }
	 //Reading image sizes
	 imname>>str;
	 M=atoi(str);
	 imname>>str;
	 N=atoi(str); 	 
	 //Reading out the gray levels
	 getline(imname,im1);
     //this allocates memory space for all the elements of the image
     imgptr= new int*[M];
     for(i=0;i<M;i++)
     {
     	imgptr[i]=new int[N];
     }
	 for(i=0;i<M;i++)
     {
     	imgptr1[i]=new int[N];
     }
             for ( i = 0; i < N; ++i)
			     {
			     	for ( j = 0; j < M; ++j)
			     	{
			     		imname>>str;
			     		num=atoi(str);
			     		imgptr[j][i]=num;
			     	}
			     }
			     for(i=1;i<(N-1);i++)
			     {
			     	for(j=1;j<(M-1);j++)
			     	{
			     		mean=0;
			                for ( p = -1; p <=1; ++p)
			                {
			                	for (q = -1; q <=1; ++q)
			                	{
			                         mean=mean+(window[p+1][q+1])*(imgptr[q+j][p+i]);
			                	}
			                }
			                imgptr1[j][i]=mean/(1);
			                mean=0;
			        }
			     } 
			     sprintf(buffer,"%d",3);
			     strcat(buffer,"highpasswindow.pgm");
			     imout.open(buffer);
			     imout<<"P2\n";
			     imout<<"# Made in by C++\n";
			     imout<<M<<" ";
			     imout<<N<<"\n";
			     imout<<"255\n";
			     for (int i = 0; i < N; ++i)
			     {
			     	for (int j = 0; j < M; ++j)
			     	{
			     		imout<<imgptr1[j][i]<<"\n";
			     	}
			     }
    
     
    }
void unsharp(char *iminput)
{
	string str1;
	int num,i,j,max;
	char str[40],buffer[40];
	ifstream image1,image2;
	ofstream imout;
	int M,N,P,Q;
	int **imgptr1,**imgptr2,**imgptr3;
	image1.open(iminput);
	getline(image1,str1);
	size_t length = str1.copy(buffer,str1.length(),0);
	getline(image1,str1);
    length = str1.copy(buffer,str1.length(),0);
  	if(buffer[0]!='#')//This part is to avoid any comments if there is. 
		    {
		    	image1.seekg(-(strlen(buffer)+1),ios::cur);
	        }
    image1>>str;
    M=atoi(str);
    image1>>str;
    N=atoi(str);
    image2.open("3window.pgm");
    getline(image2,str1);
	length = str1.copy(buffer,str1.length(),0);
	getline(image2,str1);
    length = str1.copy(buffer,str1.length(),0);
  	if(buffer[0]!='#')//This part is to avoid any comments if there is. 
		    {
		    	image2.seekg(-(strlen(buffer)+1),ios::cur);
	        }
    image2>>str;
    P=atoi(str);
    image2>>str;
    Q=atoi(str);
    getline(image2,str1);
    if((P!=M)||(Q!=N))
    {
    	cout<<"An error occured while unsharp masking\n";
        cout<<M<<N<<P<<Q;
    	return;
    }
   
    imgptr1=new int*[M];
    for ( i = 0; i < M; ++i)
    {
    	imgptr1[i]=new int[N];
    }
    imgptr2=new int*[M];
    for ( i = 0; i < M; ++i)
    {
    	imgptr2[i]=new int[N];
    }
	imgptr3=new int*[M];
    for (i = 0; i < M; ++i)
    {
    	imgptr3[i]=new int[N];
    }		  
     for(i=0;i<N;i++)
     {
     	for ( j = 0; j < M; ++j)
     	{
     		image1>>str;
     		num=atoi(str);
     		imgptr1[j][i]=num;
     	}
     }
     for(i=0;i<N;i++)
     {
     	for ( j = 0; j < M; ++j)
     	{
     		image2>>str;
     		num=atoi(str);
     		imgptr2[j][i]=num;
     	}
     }
     for ( i = 0; i < M; ++i)
     {
     	for ( j = 0; j < N; ++j)
     	{
     		
     		imgptr3[i][j]=(imgptr1[i][j]-imgptr2[i][j])+255;	
     	   				     
     	}
     }
     max=0;
     for (i = 0; i < M; ++i)
     {
         for (j = 0; j < N; ++j)
         {
         	   if(imgptr3[i][j]>max)
         		max=imgptr3[i][j];
         }
     }
     for (i = 0; i < M; ++i)
     {
         for (j = 0; j < N; ++j)
         {
         	imgptr3[i][j]=double(imgptr3[i][j])*(255)/(double(max));
         }
     }  

     imout.open( "UnsharpImage.pgm");
	 imout<<"P2\n";
	 imout<<"# Made in by C++\n";
	 imout<<M<<" ";
	 imout<<N<<"\n";
	 imout<<"255\n";
	 for ( i = 0; i < N; ++i)
	 {
	  	for ( j = 0; j < M; ++j)
	     	{
	     		imout<<imgptr3[j][i]<<"\n";
	     	}
	 }
}