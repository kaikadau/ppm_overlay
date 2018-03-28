#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/* ppm_overlay.c -o ppm_overlay -lm -O3 */
/* copyright Kai Kadau 2002 */

int main (int argc, char **argv)
{

  FILE *in1, *in2, *out;
  unsigned char *p1, *p2; 
  double trans;
  int i,sx1, sx2, sy1, sy2, bgr, bgg, bgb, r1, g1, b1, r2, g2, b2;
  char buffer[85], out_name[85];  
  
  if (argc<7) {
    printf("usage ppm_overlay <pic1.ppm> <pic2.ppm> <transparencey> <bgcolor_r> <bgcolor_g> <bgcolor_b>\n");
    printf("Put on top of pic1 the pic2 (must have the same size). The transparency defines if pic2 is transparent (1) or or not (0) with respect to pic1. Every value in between gives a linear extrapolation. The pics must be in the ppm raw format (P6 in header). The background color (rgb) defines the background color of the pics which should be the same for all pics. If there is background color in the picture object, of course this is also treated as background ...\n");
 printf("\n**************************************\nppm_overlay\nCopyright 2002 by\nKai Kadau\nLos Alamos National Laboratory, U.S.A.\nkkadau@lanl.gov\n**************************************\n\n");
    exit(1);
  }

  in1 = fopen(argv[1], "r");
  if (!in1)  {
    fprintf(stderr, "Cannot open %s\n", argv[1]);
exit(1);
  }

  in2 = fopen(argv[2], "r");
  if (!in2)  {
    fprintf(stderr, "Cannot open %s\n", argv[2]);
exit(1);
  }

   strcpy(out_name,argv[2]);
   strcat(out_name,"_over_");
   strcat(out_name,argv[1]); 

   trans=atof(argv[3]);
   printf("transp.:%lf\n",trans);

   bgr=atoi(argv[4]);
   bgg=atoi(argv[5]);
   bgb=atoi(argv[6]);
   printf("bg(rgb):%d %d %d\n",bgr, bgg, bgb);

   fgets(buffer,80,in1);
   fgets(buffer,80,in1); if (buffer[0]=='#') fgets(buffer,80,in1); // some code like xv put their garbage as an extra line ... 
   sscanf(buffer,"%d %d",&sx1, &sy1);
   printf("Dim. of pic1:%dx%d\n",sx1,sy1);
   fgets(buffer,80,in1);

   /* allocate memory for p1*/
   p1=(unsigned char*)malloc(sx1*sy1*3*sizeof(unsigned char));

   fgets(buffer,80,in2);
   fgets(buffer,80,in2); if (buffer[0]=='#') fgets(buffer,80,in2); // some code like xv put their garbage as an extra line ... 
   sscanf(buffer,"%d %d",&sx2, &sy2);
   printf("Dim. of pic2:%dx%d\n",sx2,sy2);
   fgets(buffer,80,in2);

   if ((sx1!=sx2)||(sy1!=sy2)){
     printf("The dimensions of the pics are not the same. You might get unreasonable results or if the size of pic2 is smaller than pic1 the program probably will crash! But I'll let it run ...\n");
 }  
   /* allocate memory for p2*/
    p2=(unsigned char*)malloc(sx2*sy2*3*sizeof(unsigned char));

    fread(p1, 1,3*sx1*sy1,in1);
    fread(p2, 1,3*sx2*sy2,in2);

/* here comes the core */
     for(i=0;i<sx1*sy1;++i){
     
         r1=p1[3*i];
         g1=p1[3*i+1];
         b1=p1[3*i+2]; 
         r2=p2[3*i];
         g2=p2[3*i+1];
         b2=p2[3*i+2];
         if((r2==bgr)&&(g2==bgg)&&(b2==bgb)) continue;
         if((r1==bgr)&&(g1==bgg)&&(b1==bgb)){
            p1[3*i]  =r2;
            p1[3*i+1]=g2;
            p1[3*i+2]=b2; 
         } else {
            p1[3*i]  =r2-trans*(r2-r1);
            p1[3*i+1]=g2-trans*(g2-g1);
            p1[3*i+2]=b2-trans*(b2-b1);
         }      
     }

/* end of core */

    out = fopen(out_name, "w");  

    fprintf(out,"P6\n");
    fprintf(out,"%d %d\n",sx1, sy1);
    fprintf(out,"255\n");    

    fwrite(p1, 1,3*sx1*sy1,out);

    fclose(out);

    return 0;   
}
