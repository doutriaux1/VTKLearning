#include <math.h>
#include <stdio.h>
#include <stdlib.h>


FILE *fperr;/* input, output, and error for scripts */
typedef struct Gpoint {
  float x;
  float y;
} Gpoint;

void gp(int npts, Gpoint *pts) {
  int i;
  for (i=0;i<npts;i++) {
    fprintf(fperr,"%f, %f\n",pts[i].x,pts[i].y);
  }
}
void gsfais(int i) {};

void gpl(int npts, Gpoint *pts) {
  fprintf(fperr,"line\n");
  gp(npts,pts);
}
void gfa(int npts, Gpoint *pts) {
  fprintf(fperr,"poly\n");
  gp(npts,pts);
}
int main() {
  int		i, j, k,k1,n, mtype;
  int 		opwk, *pwk;
  float   	x, y, s,tempx,tempy,startx,starty;
  float		PI_V=3.14159265358979323846;
  float	   	add_angle, angle1, angle2;//,myx[30],myy[30];
  Gpoint  	xseg[8000],xseg1[100],xseg2[100], xseg3[100],xseg4[100],xseg5[100],xseg6[100],plus1[2], star1[3], cros1[2];
  Gpoint  	plus2[2], star2[3], cros2[2];
  Gpoint  	star3[3];
  double Vma_tab_size;
  int GSOLID;
  GSOLID=0;
  char fnm[64];


  Gpoint pe;
  int npts;

  npts = 1;
  pe.x = 0.;
    pe.y = 0.;
  float	        x1,y1,xcent,ycent,p,r;


  /* Draw the marker */
  Vma_tab_size = 100.;
  for (mtype=0;mtype<203;mtype++) {
    sprintf(fnm,"marker%.2i.txt",mtype);
    fprintf(stderr,"File name is: %s\n",fnm);
    fperr = fopen(fnm,"w");
    switch (mtype) {

      case 0:
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/1000;
          n = 20; add_angle = PI_V/n ; 
          for(k = 0; k <= 2*n; k++){
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          gpl(41, xseg);
        }
        break;




      case 1:
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          n=20;
          add_angle = PI_V/n;
          angle1 = 0; 
          j = 0,k = 0;
          s = Vma_tab_size/1000;
          for(k = 0; k <= 2*n; k++){  
            angle1= k*add_angle;
            if(k==31){     
              xseg[j].x = tempx; 
              xseg[j].y = tempy-(Vma_tab_size*0.001);
              j++;
              xseg[j].x = tempx;
              xseg[j].y = tempy;
              j++;
            }
            tempx = xseg[j].x = x + s*cos(angle1);  
            tempy = xseg[j].y = y + s*sin(angle1); 
            j++;
          }
          gpl(43,xseg);
        }
        break;

      case 2:
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          n=20;
          add_angle = PI_V/n;
          angle1 = 0; 
          j = 0,k = 0;
          s = Vma_tab_size/1000;
          for(k = 0; k <= 2*n; k++){   
            angle1 = k*add_angle;
            tempx = xseg[j].x = x + s*cos(angle1);  
            tempy = xseg[j].y = y + s*sin(angle1); 
            j++;
            if(k==0 || k==20){ 
              if(k==0){  
                xseg[j].x = tempx + (Vma_tab_size*0.001); }
              if(k==20) {
                xseg[j].x = tempx- (Vma_tab_size*0.001); }
              xseg[j].y = tempy;
              j++;
              xseg[j].x = tempx;
              xseg[j].y = tempy;
              j++;
            }


          }
          gpl(45,xseg);
        }
        break;

      case 3:
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          n=20;
          add_angle = PI_V/n;
          angle1 = 0; 
          j = 0,k = 0;
          s = Vma_tab_size/1000;


          for(k = 0; k <= 2*n; k++){ 
            angle1 = k*add_angle;
            tempx = xseg[j].x = x + s*cos(angle1);
            tempy = xseg[j].y = y + s*sin(angle1); 
            j++;			
            if(k==10 ){    
              xseg[j].x = tempx; 
              xseg[j].y = tempy + (Vma_tab_size*0.001);
              j++;
              xseg[j].x = tempx;
              xseg[j].y = tempy;
              j++;
            }
          }
          gpl(43,xseg);
        }
        break;

      case 4:
        for (i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0,k=0;
          s = Vma_tab_size/1000;
          xseg[j].x = x;
          tempy = xseg[j].y = y;
          j++;
          xseg[j].x = x;
          xseg[j].y = y-(Vma_tab_size*0.001); 
          j++;
          for (k = 0; k <= 17; k+= 1){
            xseg[j].x = x + k*Vma_tab_size*0.0001; 
            xseg[j].y = y + 1*sin(k)*Vma_tab_size*0.0001; 
            j++;
          }
          gpl(19,xseg);
        }
        break;  


      case 5:
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; 
          j = 0,k = 0;
          s = Vma_tab_size/1000;
          // for w05
          for ( k=0; k <= 6; k += 1){
            xseg[j].x = x + k*Vma_tab_size*0.0001; 
            xseg[j].y = y + (sin(k))*Vma_tab_size*0.0001; 
            j++;
          }

          for (k = 6; k >= 0; k -= 1){
            xseg[j].x = x + k*Vma_tab_size*0.0001;
            xseg[j].y = y + (1*sin(-1*k))*Vma_tab_size*0.0001; 
            j++;
          }


          gpl(14,xseg);
        }
        break;





        //w06
      case 6:
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; 
          j = 0,k=0;
          s = Vma_tab_size/1000;
          n=20;
          add_angle=PI_V/n ; 
          for( k = 0; k < n + (n/2); k++) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          y = y - Vma_tab_size*0.002;
          add_angle = PI_V/n ; 
          for( k = n/2; k >-(n); k--) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          gpl(60,xseg);
        }
        break;





        // w07
      case 7:
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          angle1 = 0; 
          j = 0,k=0;
          s = Vma_tab_size/1000;

          // code for "S" in symbol w07
          n=20;
          add_angle=PI_V/n ;
          for( k = 0; k <n + (n/2); k++) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }

          y = y - Vma_tab_size*0.002;
          add_angle = PI_V/n ;
          for( k = n/2; k >-(n); k--){
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }

          gpl(60,xseg);



          // code for "|" i.e cross vertical arrow in symbol w07

          x = pe.x;
          y = pe.y;                             
          j = 0;
          tempx = xseg1[j].x = x;
          tempy = xseg1[j].y = y + Vma_tab_size*0.002;
          j++;

          // code for up arrow

          xseg1[j].x = xseg1[j-1].x - Vma_tab_size*0.0006;
          xseg1[j].y = xseg1[j-1].y - Vma_tab_size*0.0006;
          j++;

          xseg1[j].x = tempx;
          xseg1[j].y = tempy;
          j++;

          xseg1[j].x = xseg1[j-1].x + Vma_tab_size*0.0006;
          xseg1[j].y = xseg1[j-1].y - Vma_tab_size*0.0006;
          j++;

          //code for vetical line

          xseg1[j].x = tempx;
          xseg1[j].y = tempy;
          j++;
          xseg1[j].x = tempx;
          xseg1[j].y = tempy - (Vma_tab_size*0.006);
          j++;
          gpl(6,xseg1);

        }
        break;



      case 8:
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0,k = 0;
          s = Vma_tab_size/1000;
          //w08

          // code for first ring
          n = 20;
          add_angle=PI_V/n ; 
          for(k = n/2; k < (2*n)-2; k++) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            if(k== (2*n-(n/2))){
              tempx = xseg[j].x;
              tempy = xseg[j].y;
            }
            j++;
          }
          gpl(28,xseg);

          //code for second ring		
          n = 20;
          x = tempx;
          y = tempy;
          j = 0;
          for(k = 3; k<(2*n-(n/8)); k++){
            angle2 = k*add_angle;
            xseg1[j].x = x + s*cos(angle2);
            xseg1[j].y = y + s*sin(angle2);
            if ( k== (2*n-(n/2))){
              startx = xseg1[j].x;
              starty = xseg1[j].y;
            }
            j++;
          }
          gpl(35,xseg1);

          //code for third ring
          n = 20;
          x = startx;
          y = starty;
          j = 0;
          for(k = 3; k<(2*n-(n/4)); k++) {
            angle2 = k*add_angle;
            xseg2[j].x = x + s*cos(angle2);
            xseg2[j].y = y + s*sin(angle2);
            j++;
          }
          gpl(32,xseg2);


        }
        break;




      case 9:
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0,k = 0;


          //w09
          //code for "S"
          n = 20;
          add_angle = PI_V/n ;
          for(k = 0; k<n+(n/2); k++) {
            angle1 = k*add_angle;
            xseg[j].x =x + s*cos(angle1);
            xseg[j].y =y + s*sin(angle1);
            j++;
          }
          tempx = xseg[j-1].x;
          tempy = xseg[j-1].y;
          y = y - Vma_tab_size*0.002;
          add_angle = PI_V/n ;
          for( k = n/2; k >-(n); k--) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          gpl(60,xseg);

          //code for horizontal right hand arrow mark         

          {         
            x = pe.x;
            y = pe.y;
            j = 0;
            startx = xseg1[j].x = tempx - Vma_tab_size*0.002;
            starty = xseg1[j].y = tempy;
            j++;
            xseg1[j].x = tempx + Vma_tab_size*0.002;
            xseg1[j].y = tempy;
            j++;

            xseg1[j].x = xseg1[j-1].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-1].y - Vma_tab_size*0.0006;
            j++;


            xseg1[j].x = xseg1[j-2].x;
            xseg1[j].y = xseg1[j-2].y;
            j++;
            xseg1[j].x = xseg1[j-3].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-3].y + Vma_tab_size*0.0006;
            j++;
            gpl(5,xseg1);
          }

          //code for right bracket in w09
          {
            x = tempx;
            y = tempy;
            add_angle = PI_V/24;
            angle1 = 0; angle2 = add_angle;
            j = 0;

            //code for right down bracket
            for (k = 0; k < 8; k++) {
              xseg[j].x = x + Vma_tab_size*0.0025*cos(angle1);
              xseg[j].y = y - Vma_tab_size*0.0025*sin(angle1);
              ++j;
              angle1 += add_angle;
            }
            gpl(8, xseg);

            //code for right up bracket
            angle1 = 0;
            j=0;
            for (k = 0; k < 8; k++) {
              xseg2[j].x = x + Vma_tab_size*0.0025*cos(angle1);
              xseg2[j].y = y + Vma_tab_size*0.0025*sin(angle1);
              ++j;
              angle1 += add_angle;
            }  
            gpl(8, xseg2);

          }

          //code for left bracket in w09
          {
            x =  tempx;
            y = tempy ;
            j = 0;
            n = 20;
            add_angle = (PI_V/n) ;
            angle2 = 0;

            //code for left down bracket
            for(k = 0; k < 7; k++) {
              xseg3[j].x = x - Vma_tab_size*0.0025*cos(angle2);
              xseg3[j].y = y + Vma_tab_size*0.0025*sin(angle2);
              ++j;
              angle2 += add_angle;
            }             
            gpl(7,xseg3);

            //code for left down bracket
            j = 0;
            angle2 = 0;
            add_angle = (PI_V/n) ;
            for(k = 0; k < 7; k++) {
              xseg4[j].x = x - Vma_tab_size*0.0025*cos(angle2);
              xseg4[j].y = y - Vma_tab_size*0.0025*sin(angle2);
              ++j;
              angle2 += add_angle;
            }             
            gpl(7,xseg4);

          }      



        }
        break;


      case 10:
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0, k = 0;
          s = Vma_tab_size/1000;
          //w10

          {
            j = 0;
            xseg[j].x = x;
            tempy = xseg[j].y = y - Vma_tab_size*0.0005;
            j++;
            xseg[j].x = x + Vma_tab_size*0.0025;
            xseg[j].y = tempy;
            j++;
            gpl(2,xseg);
          }
          {
            k=0;
            xseg1[k].x = x;
            xseg1[k].y = y;
            k++;
            xseg1[k].x = x + Vma_tab_size*0.0025;
            xseg1[k].y = y;
            k++;
            gpl(2,xseg1);
          }
        }
        break;



      case 11:
        for (i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0,k=0;
          s = Vma_tab_size/1000;
          //w11

          // code for upper first part of line
          {
            j = 0;
            xseg[j].x = x;
            tempy = xseg[j].y = y - Vma_tab_size*0.0005;
            j++;
            xseg[j].x = x + Vma_tab_size*0.0010;
            xseg[j].y = tempy;
            j++;
            gpl(2,xseg);
          }

          //code for upper second part of line
          {
            k = 0;
            tempx = xseg1[k].x = x + Vma_tab_size*0.0015 ;
            tempy = xseg1[k].y = y - Vma_tab_size*0.0005;
            k++;
            xseg1[k].x = tempx + Vma_tab_size*0.0010;
            xseg1[k].y = tempy;
            k++;
            gpl(2,xseg1);
          }

          //code for lower first part of line
          {
            j = 0;
            xseg2[j].x = x;
            tempy = xseg2[j].y = y;
            j++;
            xseg2[j].x = x + Vma_tab_size*0.0010;
            xseg2[j].y = tempy;
            j++;
            gpl(2,xseg2);
          }

          //code for lower second part of line
          {
            k = 0;
            tempx = xseg3[k].x = x + Vma_tab_size*0.0015;
            xseg3[k].y = y;
            k++;
            xseg3[k].x = tempx + Vma_tab_size*0.0010;
            xseg3[k].y = y;
            k++;
            gpl(2,xseg3);
          }

        }
        break;




      case 12:
        for (i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0,k=0;
          s = Vma_tab_size/1000;
          //w12

          // code for upper first part of line
          {
            j = 0;
            xseg[j].x = x;
            tempy = xseg[j].y = y + Vma_tab_size*0.0005;
            j++;
            xseg[j].x = x + Vma_tab_size*0.0010;
            xseg[j].y = tempy;
            j++;
            gpl(2,xseg);
          }

          //code for upper second part of line
          {
            k = 0;
            tempx = xseg1[k].x = x + Vma_tab_size*0.0015 ;
            tempy = xseg1[k].y = y + Vma_tab_size*0.0005;
            k++;
            xseg1[k].x = tempx + Vma_tab_size*0.0010;
            xseg1[k].y = tempy;
            k++;
            gpl(2,xseg1);
          }

          //code for lower line
          {
            j = 0;
            xseg2[j].x = x;
            tempy = xseg2[j].y = y;
            j++;
            xseg2[j].x = x + 2*Vma_tab_size*0.0010 + Vma_tab_size*0.0005;
            xseg2[j].y = tempy;
            j++;
            gpl(2,xseg2);
          }
        }
        break;



        //w13
      case 13:
        for (i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0,k = 0;
          s = Vma_tab_size/1000;
          xseg[j].x = x;
          tempy = xseg[j].y = y;
          j++;

          // code for left down line
          xseg[j].x = x - Vma_tab_size*0.0010;
          xseg[j].y = y - Vma_tab_size*0.0010;
          j++;

          // code for right down line
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          // code for arrow
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y  - Vma_tab_size*0.0020;
          j++;

          xseg[j].x = xseg[j-1].x;
          xseg[j].y = xseg[j-1].y + Vma_tab_size*0.0003;
          j++;


          xseg[j].x = xseg[j-2].x;
          xseg[j].y = xseg[j-2].y;
          j++;

          xseg[j].x = xseg[j-3].x-Vma_tab_size*0.0004;
          xseg[j].y = xseg[j-3].y;
          j++;

          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          gpl(8,xseg);
        }
        break;





        //w14
      case 14:
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/1000;
          n=20;
          add_angle=PI_V/n ; 
          // start of solid circle
          gsfais(GSOLID);
          for( k = 0; k <= 2*n; k++){
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
            if( k == 10) {
              tempx = xseg[j].x;
              tempy = xseg[j].y + 0.01;
            }
          }
          gfa(41, xseg);
          // end of solid circle


          //code for right bracket in w09

          add_angle = PI_V/n;
          angle1 = 0; angle2 = 0;
          j = 0;

          for ( k = 0; k < 12; k++) {
            angle2 += add_angle;
            if ( k >= 4) {
              xseg1[j].x = x - Vma_tab_size*0.0015*cos(angle2);
              xseg1[j].y = y - Vma_tab_size*0.0015*sin(angle2);
              j++;
            }
          }
          gpl(8, xseg1);

          angle2 = 0;
          j=0;
          for ( k = 0; k < 8; k++) {
            angle2 += add_angle;
            if ( k >= 4){
              xseg2[j].x = x +Vma_tab_size*0.0015*cos(angle2);
              xseg2[j].y = y - Vma_tab_size*0.0015*sin(angle2);
              j++;
            }
          }
          gpl(4, xseg2);

        }
        break;



        //w15

      case 15:


        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n=20;
          add_angle=PI_V/n ; 

          // start of solid circle
          gsfais(GSOLID);
          for( k = 0; k <= 2*n; k++){
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
            if(k == 10) {
              tempx = xseg[j].x;
              tempy = xseg[j].y + 0.01;
            }
          }
          gfa(41, xseg);

          //right side open bracket 
          add_angle = PI_V/n;
          angle1 = 0; 
          angle2 = 0;
          j = 0;
          x=x+Vma_tab_size*0.0025;

          for ( k = 0; k <(n+5); k++) {
            angle2 += add_angle;
            if ( k >= 15) {
              xseg1[j].x = x + Vma_tab_size*0.0015*cos(angle2);
              xseg1[j].y = y + Vma_tab_size*0.0015*sin(angle2);
              j++;
            }
          }
          gpl(10, xseg1);

          //left side open bracket 	 
          angle2 = 0;
          j = 0;
          x = x - Vma_tab_size*0.0050;
          for ( k = 0; k <n-5; k++) {
            angle2 += add_angle;
            if ( k >= 5){
              xseg2[j].x = x + Vma_tab_size*0.0015*sin(angle2);
              xseg2[j].y = y + Vma_tab_size*0.0015*cos(angle2);
              j++;
            }
          }
          gpl(10, xseg2);


        }
        break;





        //w16
      case 16:


        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n=20;
          add_angle=PI_V/n ; 

          // start of solid circle
          gsfais(GSOLID);
          for( k = 0; k<=2*n; k++){
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
            if( k== 10) {
              tempx = xseg[j].x;
              tempy = xseg[j].y + 0.01;
            }
          }
          gfa(41, xseg);

          //right side open bracket 
          add_angle = PI_V/n;
          angle1 = 0; angle2 = 0;
          j = 0;
          for ( k = 0; k <n-5; k++) {
            angle2 += add_angle;
            if ( k >= 5) {
              xseg2[j].x = x + Vma_tab_size*0.0015*sin(angle2);
              xseg2[j].y = y + Vma_tab_size*0.0015*cos(angle2);
              j++;
            }
          }
          gpl(10, xseg2);

          //left side open bracket 	 
          angle2 = 0;
          j = 0;
          for ( k = 0; k <(n+5); k++) {
            angle2 += add_angle;
            if ( k >= 15) {
              xseg1[j].x = x + Vma_tab_size*0.0015*cos(angle2);
              xseg1[j].y = y + Vma_tab_size*0.0015*sin(angle2);
              j++;
            }
          }
          gpl(10, xseg1);

        }
        break;





        //w17
      case 17:

        // its part of w13 and other few lines
        for ( i = 0; i < npts; i++) {
          startx =   x = pe.x;
          starty =   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0,k = 0;
          s = Vma_tab_size/1000;

          //code for w13
          j = 0;
          xseg[j].x = x;
          tempy = xseg[j].y = y;
          j++;

          // code for left down line
          tempx = xseg[j].x = x - Vma_tab_size*0.0010;
          tempy = xseg[j].y = y - Vma_tab_size*0.0010;
          j++;

          // code for right down line
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y -  Vma_tab_size*0.0020;
          j++;

          // code for arrow
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y -  Vma_tab_size*0.0020;
          j++;

          xseg[j].x = xseg[j-1].x;
          xseg[j].y = xseg[j-1].y + Vma_tab_size*0.0003;
          j++;

          xseg[j].x = xseg[j-2].x;
          xseg[j].y = xseg[j-2].y;
          j++;

          xseg[j].x = xseg[j-3].x - Vma_tab_size*0.0004;
          xseg[j].y = xseg[j-3].y;
          j++;

          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y -  Vma_tab_size*0.0020;
          j++;

          gpl(8,xseg);

          // code for top horizontal line
          j = 0;
          xseg1[j].x = x; 
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x - Vma_tab_size*0.0024;
          xseg1[j].y = y;
          j++;

          // code for vertical line
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y - Vma_tab_size*0.002;
          j++;
          gpl(4,xseg1);



          //right side close bracket 
          x = tempx + Vma_tab_size*0.0015;
          y = tempy;  //x,y adjustment to draw bracket
          n = 20;
          add_angle = PI_V/n;
          angle1 = 0; angle2 = 0;
          j = 0;

          for ( k = 0; k < n-4; k++) {
            angle2 += add_angle;
            if ( k >= 3) {
              xseg2[j].x = x + Vma_tab_size*0.0015*sin(angle2);
              xseg2[j].y = y + Vma_tab_size*0.0015*cos(angle2);
              j++;
            }
          }
          gpl(13, xseg2);

          //left side open bracket 	 
          angle2 = 0;
          j = 0;
          x = tempx - Vma_tab_size*0.0015;
          y = tempy; //x,y adjustment to draw bracket
          for ( k = 0; k <(n+6); k++) {
            angle2 += add_angle;
            if ( k >= 13) {
              xseg1[j].x = x +Vma_tab_size*0.0015*cos(angle2);
              xseg1[j].y = y + Vma_tab_size*0.0015*sin(angle2);
              j++;
            }
          }
          gpl(13, xseg1);

        }

        break;



        //w18
      case 18:


        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          j = 0,k = 0;

          xseg[j].x = x;
          xseg[j].y = y + Vma_tab_size*0.001;
          j++;

          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.0015;
          j++;

          xseg[j].x = x;
          xseg[j].y = y; j++;

          xseg[j].x = x + Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.0015;
          j++;

          xseg[j].x = x ;
          xseg[j].y = y + Vma_tab_size*0.001;
          j++;
          gpl(5, xseg);


        }
        break;




        //w19
      case 19:


        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          j = 0,k = 0;
          s = Vma_tab_size/1000;

          // code for left square open bracket
          xseg[j].x = x;
          xseg[j].y = y;
          j++;
          xseg[j].x = x + Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.001;
          j++;	

          tempx = xseg[j].x = x + Vma_tab_size*0.001;
          tempy = xseg[j].y = y + Vma_tab_size*0.005;
          j++;

          xseg[j].x = tempx - Vma_tab_size*0.001;
          xseg[j].y = tempy + Vma_tab_size*0.001;
          j++;

          gpl(4, xseg);

          x = x + Vma_tab_size*0.004; // gap between two vetical lines
          j = 0;

          // code for right square open bracket
          xseg1[j].x = x;
          xseg1[j].y=y;
          j++;

          xseg1[j].x = x - Vma_tab_size*0.001;
          xseg1[j].y = y + Vma_tab_size*0.001;
          j++;

          startx = xseg1[j].x = x - Vma_tab_size*0.001;
          starty = xseg1[j].y = y + Vma_tab_size*0.005;
          j++;

          xseg1[j].x = startx + Vma_tab_size*0.001;
          xseg1[j].y = starty + Vma_tab_size*0.001;
          j++;

          gpl(4, xseg1);


        }
        break;



        //w20
      case 20:

        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n=20;
          add_angle=PI_V/n ; 

          // start of solid circle 
          gsfais(GSOLID);
          for( k = 0; k <=2*n; k++) {

            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
            if( k == n+(n/2)) {
              tempx=x;
              tempy=y;
            }

          }
          gfa(41, xseg);

          //start of solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size/3000;
          j = 0;

          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--) {	
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;

          }
          s = Vma_tab_size/1500;
          for( k =-(n/2); k < n/4; k++) {
            angle1 = k*add_angle;
            xseg1[j].x = x + Vma_tab_size/1500*cos(angle1);
            xseg1[j].y = y + Vma_tab_size/2500*sin(angle1);
            j++;
          }

          gfa(35, xseg1);

          // code for right side line
          y = tempy - Vma_tab_size*0.0015;

          x = tempx + Vma_tab_size*0.0005;

          j = 0;
          xseg1[j].x = x; 
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001; 
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001; 
          xseg1[j].y = y + Vma_tab_size*0.003; 
          j++;

          xseg1[j].x = x ;
          xseg1[j].y = y + Vma_tab_size*0.003; 
          j++;
          gpl(4, xseg1);

        }
        break;





        //w21
      case 21:


        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          angle1 = 0; 
          j = 0,k = 0;
          s = Vma_tab_size/2000;

          y = y + Vma_tab_size*0.001; // setting centered circle position

          // start of solid circle
          gsfais(GSOLID);                                                   
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
            if( k == 10) {
              tempx = xseg[j].x;
              tempy = xseg[j].y + 0.01;
            }
          }
          gfa(41, xseg);

          // end of solid circle

          // code for right side line
          y = y - Vma_tab_size*0.0015;

          x = x + Vma_tab_size*0.0005;

          j = 0;
          xseg1[j].x = x ;
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001; 
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001;
          xseg1[j].y = y + Vma_tab_size*0.003; 
          j++;

          xseg1[j].x = x;
          xseg1[j].y = y + Vma_tab_size*0.003;
          j++;
          gpl(4, xseg1);

        }
        break;





        //w22
      case 22:

        // start of  star
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;

        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          j = 0,k = 0;
          y = y + Vma_tab_size*0.001; // setting centered star position

          xseg[0].x = x + star1[0].x;
          xseg[0].y = y + star1[0].y;
          xseg[1].x = x + star1[1].x;
          xseg[1].y = y + star1[1].y;
          gpl(2, xseg);

          xseg[0].x = x + star2[0].x;
          xseg[0].y = y + star2[0].y;
          xseg[1].x = x + star2[1].x;
          xseg[1].y = y + star2[1].y;
          gpl(2, xseg);

          xseg[0].x = x + star3[0].x;
          xseg[0].y = y + star3[0].y;
          xseg[1].x = x + star3[1].x;
          xseg[1].y = y + star3[1].y;
          gpl(2, xseg);

          // end of  star

          // code for right side line
          y = y - Vma_tab_size*0.0015;
          x = x + Vma_tab_size*0.001;

          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001; 
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001;
          xseg1[j].y = y + Vma_tab_size*0.003;
          j++;

          xseg1[j].x = x;
          xseg1[j].y = y + Vma_tab_size*0.003;
          j++;
          gpl(4, xseg1);

        }
        break;





        //w23
      case 23:


        // start of  star
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;

        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          j = 0,k=0;
          y=y+Vma_tab_size*0.001; // setting star position

          xseg[0].x = x + star1[0].x;
          xseg[0].y = y + star1[0].y;
          xseg[1].x = x + star1[1].x;
          xseg[1].y = y + star1[1].y;
          gpl(2, xseg);

          xseg[0].x = x + star2[0].x;
          xseg[0].y = y + star2[0].y;
          xseg[1].x = x + star2[1].x;
          xseg[1].y = y + star2[1].y;
          gpl(2, xseg);

          xseg[0].x = x + star3[0].x;
          xseg[0].y = y + star3[0].y;
          xseg[1].x = x + star3[1].x;
          xseg[1].y = y + star3[1].y;
          gpl(2, xseg);

          // end of  star

          // start of solid circle

          y = y + Vma_tab_size*0.003; // setting circle position
          gsfais(GSOLID); 
          s = Vma_tab_size/1500;                                                 
          n=20;
          add_angle=PI_V/n ; 
          for( k=0; k <=2*n; k++) {
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
            if( k == 10) {
              tempx = xseg2[j].x;
              tempy = xseg2[j].y + 0.01;
            }
          }
          gfa(41, xseg2);

          // end of solid circle


          // code for right side line
          y = y - Vma_tab_size*0.0045;
          x = x + Vma_tab_size*0.001;
          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001;
          xseg1[j].y = y ;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001;
          xseg1[j].y = y + Vma_tab_size*0.006; 
          j++;

          xseg1[j].x = x;
          xseg1[j].y = y + Vma_tab_size*0.006; 
          j++;

          gpl(4, xseg1);

        }
        break;




        //w24
      case 24:


        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          angle1 = 0; 
          j = 0,k = 0;
          s = Vma_tab_size/1000;
          n=20;
          add_angle=PI_V/n ; 
          for( k = 0; k <n + (n/2); k++) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*sin(angle1);
            xseg[j].y = y + s*cos(angle1);
            j++;
          }

          x = x - Vma_tab_size*0.002;
          y = y;
          add_angle = PI_V/n ; 
          for( k = n/2; k >-(n); k--) {
            angle1= k*add_angle;
            xseg[j].x = x + s*sin(angle1);
            xseg[j].y = y + s*cos(angle1);
            j++;
          } 
          gpl(60,xseg);

          // code for right side line

          x = x + Vma_tab_size*0.003;
          y = y - Vma_tab_size*0.0015;

          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001; 
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001;
          xseg1[j].y = y + Vma_tab_size*0.003;
          j++;

          xseg1[j].x = x;
          xseg1[j].y = y + Vma_tab_size*0.003; 
          j++;

          gpl(4, xseg1);


        }
        break;




        //w25
      case 25:


        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          angle1 = 0; 
          j = 0,k = 0;
          s = Vma_tab_size/1000;


          // code for invert triangle
          xseg[j].x = x;
          xseg[j].y = y + Vma_tab_size*0.001;
          j++;

          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.001;
          j++;

          xseg[j].x = x;
          xseg[j].y = y;
          j++;

          xseg[j].x = x + Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.001;
          j++;

          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y +Vma_tab_size*0.001;
          j++;

          gpl(5, xseg);


          y = y + Vma_tab_size*0.003; // setting circle position
          gsfais(GSOLID);                                                   
          n=20; 
          j = 0;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
            if(k == 10) {
              tempx = xseg2[j].x;
              tempy = xseg2[j].y + 0.01;
            }
          }
          gfa(41, xseg2);

          // end of solid circle


          // code for right side line
          y = y - Vma_tab_size*0.004;
          x = x + Vma_tab_size*0.001;

          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001; 
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001;
          xseg1[j].y = y + Vma_tab_size*0.006; 
          j++;

          xseg1[j].x = x;
          xseg1[j].y = y + Vma_tab_size*0.006; 
          j++;

          gpl(4, xseg1);



        }
        break;





        //w26
      case 26:

        // star initialization 
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;

        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          j = 0,k = 0;
          s = Vma_tab_size/1000;


          // code for invert triangle
          xseg2[j].x = x;
          xseg2[j].y = y + Vma_tab_size*0.001;
          j++;
          xseg2[j].x = x - Vma_tab_size*0.001;
          xseg2[j].y = y + Vma_tab_size*0.001;
          j++;

          xseg2[j].x = x;
          xseg2[j].y = y;
          j++;

          xseg2[j].x = x + Vma_tab_size*0.001;
          xseg2[j].y = y + Vma_tab_size*0.001;
          j++;

          xseg2[j].x = x - Vma_tab_size*0.001;
          xseg2[j].y = y + Vma_tab_size*0.001;
          j++;

          gpl(5, xseg2);

          y = y + Vma_tab_size*0.002; // setting star position
          // start of  star

          j = 0,k = 0;
          y = y + Vma_tab_size*0.001; // setting star position

          xseg[0].x = x + star1[0].x;
          xseg[0].y = y + star1[0].y;
          xseg[1].x = x + star1[1].x;
          xseg[1].y = y + star1[1].y;
          gpl(2, xseg);
          xseg[0].x = x + star2[0].x;
          xseg[0].y = y + star2[0].y;
          xseg[1].x = x + star2[1].x;
          xseg[1].y = y + star2[1].y;
          gpl(2, xseg);
          xseg[0].x = x + star3[0].x;
          xseg[0].y = y + star3[0].y;
          xseg[1].x = x + star3[1].x;
          xseg[1].y = y + star3[1].y;
          gpl(2, xseg);

          // end of  star


          // code for right side line
          y = y - Vma_tab_size*0.004;
          x = x + Vma_tab_size*0.001;

          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x + Vma_tab_size*0.001; 
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001; 
          xseg1[j].y = y + Vma_tab_size*0.006; 
          j++;

          xseg1[j].x = x;
          xseg1[j].y = y + Vma_tab_size*0.006; 
          j++;
          gpl(4, xseg1);



        }
        break;



        //w27
      case 27:


        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0,k = 0;
          s = Vma_tab_size/1000;


          // code for invert triangle
          xseg2[j].x = x;
          xseg2[j].y = y + Vma_tab_size*0.001;
          j++;
          xseg2[j].x = x - Vma_tab_size*0.001;
          xseg2[j].y = y + Vma_tab_size*0.001;
          j++;

          xseg2[j].x = x ; 
          xseg2[j].y = y;
          j++;

          xseg2[j].x = x + Vma_tab_size*0.001;
          xseg2[j].y = y + Vma_tab_size*0.001;
          j++;

          xseg2[j].x = x - Vma_tab_size*0.001;
          xseg2[j].y = y + Vma_tab_size*0.001;
          j++;
          gpl(5, xseg2);


          y = y + Vma_tab_size*0.002; // setting regular triangle [top] position
          j=0;
          xseg[j].x = x;
          xseg[j].y = y;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y; 
          j++;

          xseg[j].x = x;
          xseg[j].y = y + Vma_tab_size*0.001;
          j++;

          xseg[j].x = x + Vma_tab_size*0.001;
          xseg[j].y = y;
          j++;

          xseg[j].x = x;
          xseg[j].y = y;
          j++;
          gpl(5, xseg);


          // code for right side line
          y = y - Vma_tab_size*0.003;

          x = x + Vma_tab_size*0.0012;


          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x + Vma_tab_size*0.001; 
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001; 
          xseg1[j].y = y + Vma_tab_size*0.005;
          j++;

          xseg1[j].x = x;
          xseg1[j].y = y + Vma_tab_size*0.005; 
          j++;
          gpl(4, xseg1);



        }
        break;




        //w28
      case 28:


        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          j = 0,k = 0;
          s = Vma_tab_size/1000;

          // first horizontal line

          {
            j = 0;
            xseg[j].x = x;
            tempy = xseg[j].y = y - Vma_tab_size*0.001;
            j++;
            xseg[j].x = x + Vma_tab_size*0.004;
            xseg[j].y = tempy;
            j++;
            gpl(2,xseg);
          }


          // second horizontal line
          {
            j = 0;
            xseg2[j].x = x;
            tempy = xseg2[j].y = y;
            j++;
            xseg2[j].x = x + Vma_tab_size*0.004;
            xseg2[j].y = tempy;
            j++;
            gpl(2,xseg2);
          }


          // third horizontal line
          {
            j = 0;
            xseg3[j].x = x;
            tempy = xseg3[j].y = y + Vma_tab_size*0.001;
            j++;
            xseg3[j].x = x + Vma_tab_size*0.004;
            xseg3[j].y = tempy;
            j++;
            gpl(2,xseg3);
          }

          // code for right side line
          y = y - Vma_tab_size*0.0015;
          x = x + Vma_tab_size*0.004;

          j = 0;
          xseg1[j].x = x ;
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001;
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001; 
          xseg1[j].y = y + Vma_tab_size*0.003;
          j++;

          xseg1[j].x = x ;
          xseg1[j].y = y + Vma_tab_size*0.003;
          j++;

          gpl(4, xseg1);



        }
        break;






        //w29
      case 29:


        // code of w17
        // its part of w13 and other few lines
        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          j = 0,k = 0;
          s = Vma_tab_size/1000;

          //code for w13
          j = 0;
          xseg[j].x = x;
          tempy = xseg[j].y = y;
          j++;
          // code for left down line
          tempx = xseg[j].x = x - Vma_tab_size*0.0010;
          tempy = xseg[j].y = y - Vma_tab_size*0.0010;
          j++;
          // code for right down line
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;
          // code for arrow
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          xseg[j].x = xseg[j-1].x;
          xseg[j].y = xseg[j-1].y + Vma_tab_size*0.0003;
          j++;


          xseg[j].x = xseg[j-2].x;
          xseg[j].y = xseg[j-2].y;
          j++;

          xseg[j].x = xseg[j-3].x - Vma_tab_size*0.0004;
          xseg[j].y = xseg[j-3].y;
          j++;

          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          gpl(8,xseg);

          // code for top horizontal line
          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x - Vma_tab_size*0.0024;
          xseg1[j].y = y;
          j++;

          // code for vertical line
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y - Vma_tab_size*0.002;
          j++;

          gpl(4,xseg1);



          // code for right side line
          y = y - Vma_tab_size*0.0025;
          x = x + Vma_tab_size*0.0005;

          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x + Vma_tab_size*0.001; 
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001;
          xseg1[j].y = y + Vma_tab_size*0.003; 
          j++;

          xseg1[j].x = x ; 
          xseg1[j].y = y + Vma_tab_size*0.003; 
          j++;

          gpl(4, xseg1);


        }

        break;





        //w30

      case 30:

        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;

          angle1 = 0;
          j = 0,k = 0;

          // code of w09
          //code for "S"
          n = 20;
          add_angle = PI_V/n ;
          for( k = 0;k <n+(n/2); k++) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          tempx = xseg[j-1].x;
          tempy = xseg[j-1].y;
          y = y - Vma_tab_size*0.002;
          add_angle = PI_V/n ;
          for( k = n/2; k >-(n); k--) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }

          gpl(60,xseg);



          //code for horizontal right hand arrow mark         

          {         

            x = pe.x;
            y = pe.y;

            j = 0;
            startx = xseg1[j].x = tempx - Vma_tab_size*0.002;
            starty = xseg1[j].y = tempy; 
            j++;
            xseg1[j].x = tempx + Vma_tab_size*0.002;
            xseg1[j].y = tempy;
            j++;

            xseg1[j].x = xseg1[j-1].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-1].y - Vma_tab_size*0.0006;
            j++;

            xseg1[j].x = xseg1[j-2].x;
            xseg1[j].y = xseg1[j-2].y;
            j++;
            xseg1[j].x = xseg1[j-3].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-3].y + Vma_tab_size*0.0006;
            j++;


            gpl(5,xseg1);

          }


          // code for right side line
          y = y - Vma_tab_size*0.002;
          x = x + Vma_tab_size*0.001;

          j = 0;
          xseg2[j].x = x + Vma_tab_size*0.003; 
          xseg2[j].y = y - Vma_tab_size*0.001;
          j++;
          xseg2[j].x = x + Vma_tab_size*0.003;
          xseg2[j].y = y + Vma_tab_size*0.003;
          j++;

          gpl(2, xseg2);


        }

        break;



        //w31
      case 31:

        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          angle1 = 0; 
          j = 0, k = 0;


          // code of w09
          //code for "S"
          n = 20;
          add_angle = PI_V/n ;
          for( k = 0; k <n+(n/2); k++) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          tempx = xseg[j-1].x;
          tempy = xseg[j-1].y;
          y = y - Vma_tab_size*0.002;
          add_angle = PI_V/n ;
          for( k = n/2;k >-(n); k--) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }

          gpl(60,xseg);


          //code for horizontal right hand arrow mark         
          {         

            x = pe.x;
            y = pe.y;

            j = 0;
            startx = xseg1[j].x = tempx - Vma_tab_size*0.002;
            starty = xseg1[j].y = tempy;
            j++;

            xseg1[j].x = tempx + Vma_tab_size*0.002;
            xseg1[j].y = tempy;
            j++;

            xseg1[j].x = xseg1[j-1].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-1].y - Vma_tab_size*0.0006;
            j++;

            xseg1[j].x = xseg1[j-2].x;
            xseg1[j].y = xseg1[j-2].y;
            j++;

            xseg1[j].x = xseg1[j-3].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-3].y + Vma_tab_size*0.0006;
            j++;


            gpl(5,xseg1);

          }


        }

        break;




        //w32
      case 32:

        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          angle1 = 0; 
          j = 0, k = 0;


          // code of w09
          //code for "S"
          n = 20;
          add_angle = PI_V/n ;
          for( k = 0; k <n+(n/2); k++) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          tempx = xseg[j-1].x;
          tempy = xseg[j-1].y;
          y = y - Vma_tab_size*0.002;
          add_angle = PI_V/n ;
          for( k =n/2; k >-(n); k--) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }

          gpl(60,xseg);

          //code for horizontal right hand arrow mark         
          {         

            x = pe.x;
            y = pe.y;

            j = 0;
            startx = xseg1[j].x = tempx - Vma_tab_size*0.002;
            starty = xseg1[j].y = tempy;
            j++;

            xseg1[j].x = tempx + Vma_tab_size*0.002;
            xseg1[j].y = tempy;
            j++;

            xseg1[j].x = xseg1[j-1].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-1].y - Vma_tab_size*0.0006;
            j++;


            xseg1[j].x = xseg1[j-2].x;
            xseg1[j].y = xseg1[j-2].y;
            j++;

            xseg1[j].x = xseg1[j-3].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-3].y + Vma_tab_size*0.0006;
            j++;


            gpl(5,xseg1);

          }

          // code for right side line
          y = y - Vma_tab_size*0.002;
          j = 0;
          xseg2[j].x = x - Vma_tab_size*0.003; 
          xseg2[j].y = y - Vma_tab_size*0.001; 
          j++;

          xseg2[j].x = x - Vma_tab_size*0.003; 
          xseg2[j].y = y + Vma_tab_size*0.003; 
          j++;

          gpl(2, xseg2);


        }

        break;




        //w33
      case 33:

        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;

          angle1 = 0; 
          j = 0, k = 0;


          // code of w09
          //code for "S"
          n = 20;
          add_angle = PI_V/n ;
          for( k = 0; k <n+(n/2); k++) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          tempx = xseg[j-1].x;
          tempy = xseg[j-1].y;
          y = y - Vma_tab_size*0.002;
          add_angle = PI_V/n ;
          for( k = n/2; k >-(n); k--) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }

          gpl(60,xseg);



          //code for horizontal right hand arrow mark         

          {         

            x = pe.x;
            y = pe.y;

            j = 0;
            startx = xseg1[j].x = tempx - Vma_tab_size*0.002; 
            starty = xseg1[j].y = tempy - Vma_tab_size*0.0002;
            j++;

            xseg1[j].x = tempx + Vma_tab_size*0.002;
            xseg1[j].y = tempy - Vma_tab_size*0.0002;
            j++;

            k = 0;
            xseg2[k].x = tempx - Vma_tab_size*0.002; 
            xseg2[k].y = tempy + Vma_tab_size*0.0002;
            k++;

            xseg2[k].x = tempx + Vma_tab_size*0.002;
            xseg2[k].y = tempy + Vma_tab_size*0.0002;
            k++;

            gpl(2,xseg2);

            xseg1[j].x = xseg1[j-1].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-1].y - Vma_tab_size*0.0006;
            j++;


            xseg1[j].x = xseg1[j-2].x + Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-2].y + Vma_tab_size*0.0003;
            j++;

            xseg1[j].x = xseg1[j-3].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-3].y +Vma_tab_size*0.0008;
            j++;

            xseg1[j].x = xseg2[k-1].x;
            xseg1[j].y = xseg2[k-1].y;
            j++;


            gpl(6,xseg1);

          }


          // code for right side line
          y = y - Vma_tab_size*0.002;

          j = 0;
          xseg2[j].x = x + Vma_tab_size*0.0035;
          xseg2[j].y = y - Vma_tab_size*0.001;
          j++;
          xseg2[j].x = x + Vma_tab_size*0.0035; 
          xseg2[j].y = y + Vma_tab_size*0.003;
          j++;

          gpl(2, xseg2);



        }

        break;




        //w34
      case 34:

        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          angle1 = 0;
          j = 0, k = 0;


          // code of w09
          //code for "S"
          n = 20;
          add_angle = PI_V/n ;
          for( k = 0; k <n+(n/2); k++) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          tempx = xseg[j-1].x;
          tempy = xseg[j-1].y;
          y = y - Vma_tab_size*0.002;
          add_angle = PI_V/n ;
          for( k = n/2; k >-(n); k--) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }

          gpl(60,xseg);


          //code for horizontal right hand arrow mark         

          {         

            x = pe.x;
            y = pe.y;

            j = 0;
            startx = xseg1[j].x = tempx - Vma_tab_size*0.002;
            starty = xseg1[j].y = tempy - Vma_tab_size*0.0002;
            j++;

            xseg1[j].x = tempx + Vma_tab_size*0.002;
            xseg1[j].y = tempy - Vma_tab_size*0.0002;
            j++;

            k = 0;
            xseg2[k].x = tempx - Vma_tab_size*0.002; 
            xseg2[k].y = tempy + Vma_tab_size*0.0002;
            k++;

            xseg2[k].x = tempx + Vma_tab_size*0.002;
            xseg2[k].y = tempy + Vma_tab_size*0.0002;
            k++;

            gpl(2,xseg2);


            xseg1[j].x = xseg1[j-1].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-1].y - Vma_tab_size*0.0006;
            j++;


            xseg1[j].x = xseg1[j-2].x + Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-2].y + Vma_tab_size*0.0003;
            j++;

            xseg1[j].x = xseg1[j-3].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-3].y + Vma_tab_size*0.0008;
            j++;

            xseg1[j].x = xseg2[k-1].x;
            xseg1[j].y = xseg2[k-1].y;
            j++;


            gpl(6,xseg1);

          }


        }

        break;





        //w35

      case 35:

        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;

          angle1 = 0; 
          j = 0, k = 0;


          // code of w09
          //code for "S"
          n = 20;
          add_angle = PI_V/n ;
          for( k = 0; k <n+(n/2); k++) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          tempx = xseg[j-1].x;
          tempy = xseg[j-1].y;
          y = y - Vma_tab_size*0.002;
          add_angle = PI_V/n ;
          for( k = n/2; k >-(n); k--) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }

          gpl(60,xseg);



          //code for horizontal right hand arrow mark         

          {         

            x = pe.x;
            y = pe.y;

            j = 0;
            startx = xseg1[j].x = tempx - Vma_tab_size*0.002;
            starty = xseg1[j].y = tempy - Vma_tab_size*0.0002;
            j++;

            xseg1[j].x = tempx + Vma_tab_size*0.002;
            xseg1[j].y = tempy - Vma_tab_size*0.0002;
            j++;

            k = 0;
            xseg2[k].x = tempx - Vma_tab_size*0.002;
            xseg2[k].y = tempy + Vma_tab_size*0.0002;
            k++;

            xseg2[k].x = tempx + Vma_tab_size*0.002;
            xseg2[k].y = tempy + Vma_tab_size*0.0002;
            k++;

            gpl(2,xseg2);


            xseg1[j].x = xseg1[j-1].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-1].y - Vma_tab_size*0.0006;
            j++;


            xseg1[j].x = xseg1[j-2].x + Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-2].y + Vma_tab_size*0.0003;
            j++;

            xseg1[j].x = xseg1[j-3].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-3].y + Vma_tab_size*0.0008;
            j++;

            xseg1[j].x = xseg2[k-1].x;
            xseg1[j].y = xseg2[k-1].y;
            j++;


            gpl(6,xseg1);

          }


          // code for left side line

          y = y - Vma_tab_size*0.002;

          j = 0;
          xseg2[j].x = x - Vma_tab_size*0.003; 
          xseg2[j].y = y - Vma_tab_size*0.001;
          j++;

          xseg2[j].x = x - Vma_tab_size*0.003; 
          xseg2[j].y = y + Vma_tab_size*0.003;
          j++;

          gpl(2, xseg2);

        }

        break;




        //w36
      case 36:

        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          j = 0, k = 0;

          //code for horizontal right hand arrow mark         

          {         

            startx = xseg1[j].x = x - Vma_tab_size*0.002;
            starty = xseg1[j].y = y;
            j++;

            xseg1[j].x = x + Vma_tab_size*0.002;
            xseg1[j].y = y;
            j++;


            xseg1[j].x = xseg1[j-1].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-1].y - Vma_tab_size*0.0006;
            j++;

            xseg1[j].x = xseg1[j-2].x;
            xseg1[j].y = xseg1[j-2].y;
            j++;

            xseg1[j].x = xseg1[j-3].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-3].y + Vma_tab_size*0.0006;
            j++;

            gpl(5,xseg1);

          }


          //code for vertical down hand arrow mark         

          {   j = 0;      

            xseg[j].x = x ;
            starty = xseg[j].y = y + Vma_tab_size*0.0015;
            j++;

            xseg[j].x = x ;
            xseg[j].y = y - Vma_tab_size*0.0015;
            j++;

            xseg[j].x = xseg[j-1].x - Vma_tab_size*0.0006;
            xseg[j].y = xseg[j-1].y + Vma_tab_size*0.0006;
            j++;


            xseg[j].x = xseg[j-2].x;
            xseg[j].y = xseg[j-2].y;
            j++;

            xseg[j].x = xseg[j-3].x + Vma_tab_size*0.0006;
            xseg[j].y = xseg[j-3].y + Vma_tab_size*0.0006;
            j++; 

            xseg[j].x = xseg[j-2].x;
            xseg[j].y = xseg[j-2].y;
            j++; 

            gpl(6,xseg);

          }

        }

        break;




        //w37
      case 37:

        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          j = 0, k = 0;

          //code for horizontal right hand arrow mark         

          {         

            x = pe.x;
            y = pe.y;

            j = 0;
            startx = xseg1[j].x = x - Vma_tab_size*0.002; 
            starty = xseg1[j].y = y - Vma_tab_size*0.0002;
            j++;

            xseg1[j].x = x + Vma_tab_size*0.002;
            xseg1[j].y = y - Vma_tab_size*0.0002;
            j++;

            k = 0;
            xseg2[k].x = x - Vma_tab_size*0.002;
            xseg2[k].y = y + Vma_tab_size*0.0002;
            k++;

            xseg2[k].x = x + Vma_tab_size*0.002;
            xseg2[k].y = y + Vma_tab_size*0.0002;
            k++;

            gpl(2,xseg2);


            xseg1[j].x = xseg1[j-1].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-1].y - Vma_tab_size*0.0006;
            j++;


            xseg1[j].x = xseg1[j-2].x + Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-2].y + Vma_tab_size*0.0003;
            j++;

            xseg1[j].x = xseg1[j-3].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-3].y + Vma_tab_size*0.0008;
            j++;

            xseg1[j].x = xseg2[k-1].x;
            xseg1[j].y = xseg2[k-1].y;
            j++;


            gpl(6,xseg1);

          }

          //code for vertical down hand arrow mark         

          {  j = 0;      

            xseg[j].x = x ;
            starty = xseg[j].y = y + Vma_tab_size*0.0015;
            j++;
            xseg[j].x = x ;
            xseg[j].y = y - Vma_tab_size*0.002;
            j++;

            xseg[j].x = xseg[j-1].x - Vma_tab_size*0.0006;
            xseg[j].y = xseg[j-1].y + Vma_tab_size*0.0006;
            j++;


            xseg[j].x = xseg[j-2].x;
            xseg[j].y = xseg[j-2].y;
            j++;

            xseg[j].x = xseg[j-3].x + Vma_tab_size*0.0006;
            xseg[j].y = xseg[j-3].y + Vma_tab_size*0.0006;
            j++; 

            xseg[j].x = xseg[j-2].x;
            xseg[j].y = xseg[j-2].y;
            j++; 


            gpl(6,xseg);

          }


        }

        break;




        //w38
      case 38:

        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;

          j = 0,k = 0;

          //code for horizontal right hand arrow mark         

          {         

            startx = xseg1[j].x = x - Vma_tab_size*0.002;
            starty = xseg1[j].y = y;
            j++;

            xseg1[j].x = x + Vma_tab_size*0.002;
            xseg1[j].y = y ;
            j++;


            xseg1[j].x = xseg1[j-1].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-1].y - Vma_tab_size*0.0006;
            j++;


            xseg1[j].x = xseg1[j-2].x;
            xseg1[j].y = xseg1[j-2].y;
            j++;

            xseg1[j].x = xseg1[j-3].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-3].y + Vma_tab_size*0.0006;
            j++;


            gpl(5,xseg1);

          }



          //code for vertical up hand arrow mark         

          {   j = 0;      

            xseg[j].x = x;
            starty = xseg[j].y = y - Vma_tab_size*0.0015;
            j++;

            xseg[j].x = x;
            xseg[j].y = y + Vma_tab_size*0.0015;
            j++;

            xseg[j].x = xseg[j-1].x - Vma_tab_size*0.0006;
            xseg[j].y = xseg[j-1].y - Vma_tab_size*0.0006;
            j++;


            xseg[j].x = xseg[j-2].x;
            xseg[j].y = xseg[j-2].y;
            j++;

            xseg[j].x = xseg[j-3].x + Vma_tab_size*0.0006;
            xseg[j].y = xseg[j-3].y - Vma_tab_size*0.0006;
            j++; 

            xseg[j].x = xseg[j-2].x;
            xseg[j].y = xseg[j-2].y;
            j++; 

            gpl(6,xseg);

          }

        }

        break;





        //w39
      case 39:

        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;

          j = 0, k = 0;

          //code for horizontal right hand arrow mark         

          {         

            x = pe.x;
            y = pe.y;

            j = 0;
            startx = xseg1[j].x = x - Vma_tab_size*0.002;
            starty = xseg1[j].y = y - Vma_tab_size*0.0002;
            j++;

            xseg1[j].x = x + Vma_tab_size*0.002;
            xseg1[j].y = y - Vma_tab_size*0.0002;
            j++;

            k = 0;
            xseg2[k].x = x - Vma_tab_size*0.002;
            xseg2[k].y = y + Vma_tab_size*0.0002;
            k++;

            xseg2[k].x = x + Vma_tab_size*0.002; 
            xseg2[k].y = y + Vma_tab_size*0.0002;
            k++;

            gpl(2,xseg2);


            xseg1[j].x = xseg1[j-1].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-1].y - Vma_tab_size*0.0006;
            j++;

            xseg1[j].x = xseg1[j-2].x + Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-2].y + Vma_tab_size*0.0003;
            j++;

            xseg1[j].x = xseg1[j-3].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-3].y + Vma_tab_size*0.0008;
            j++;

            xseg1[j].x = xseg2[k-1].x;
            xseg1[j].y = xseg2[k-1].y;
            j++;


            gpl(6,xseg1);

          }

          //code for vertical up hand arrow mark         

          {   j = 0;      

            xseg[j].x = x;
            starty = xseg[j].y = y - Vma_tab_size*0.0015;
            j++;

            xseg[j].x = x ;
            xseg[j].y = y + Vma_tab_size*0.0015;
            j++;

            xseg[j].x = xseg[j-1].x - Vma_tab_size*0.0006;
            xseg[j].y = xseg[j-1].y - Vma_tab_size*0.0006;
            j++;

            xseg[j].x = xseg[j-2].x;
            xseg[j].y = xseg[j-2].y;
            j++;

            xseg[j].x = xseg[j-3].x + Vma_tab_size*0.0006;
            xseg[j].y = xseg[j-3].y - Vma_tab_size*0.0006;
            j++; 

            xseg[j].x = xseg[j-2].x;
            xseg[j].y = xseg[j-2].y;
            j++; 

            gpl(6,xseg);

          }


        }

        break;




        //w40
      case 40:

        for ( i = 0; i < npts; i++) {
          startx =   x = pe.x;
          starty =   y = pe.y;

          j = 0,k = 0;
          s = Vma_tab_size/1000;

          //first line
          {
            j = 0;
            xseg5[j].x = x;
            tempy = xseg5[j].y = y - Vma_tab_size*0.0005;
            j++;
            xseg5[j].x = x + Vma_tab_size*0.0025;
            xseg5[j].y = tempy;
            j++;
            gpl(2,xseg5);
          }

          //second line
          {
            k = 0;
            xseg1[k].x = x;
            xseg1[k].y = y;
            k++;
            xseg1[k].x = x + Vma_tab_size*0.0025;
            xseg1[k].y = y;
            k++;
            gpl(2,xseg1);
          }

          //third line
          {
            k = 0;
            xseg6[k].x = x;
            xseg6[k].y = y + Vma_tab_size*0.0005;
            k++;
            xseg6[k].x = x + Vma_tab_size*0.0025;
            xseg6[k].y = y + Vma_tab_size*0.0005;
            k++;
            gpl(2,xseg6);
          }


          //code for right bracket in w09
          {
            x = x + Vma_tab_size*0.0025;

            add_angle = PI_V/24;
            angle1 = 0; 
            j = 0;
            //code for right down bracket

            for ( k = 0; k <8; k++) {
              xseg[j].x = x + Vma_tab_size*0.001*cos(angle1);
              xseg[j].y = y - Vma_tab_size*0.001*sin(angle1);
              ++j;
              angle1 += add_angle;
            }
            gpl(8, xseg);

            //code for right up bracket
            angle1 = 0;
            j = 0;
            for ( k = 0; k <8; k++) {
              xseg2[j].x = x +Vma_tab_size*0.001*cos(angle1);
              xseg2[j].y = y + Vma_tab_size*0.001*sin(angle1);
              ++j;
              angle1 += add_angle;
            }  
            gpl(8, xseg2);

          }


          //code for left bracket in w09
          {
            x =  x - Vma_tab_size*0.0025;
            j = 0;
            n = 20;
            add_angle = (PI_V/n) ;
            angle2 = 0;

            //code for left down bracket
            for( k = 0; k <7; k++){
              xseg3[j].x = x - Vma_tab_size*0.001*cos(angle2);
              xseg3[j].y = y + Vma_tab_size*0.001*sin(angle2);
              ++j;
              angle2 += add_angle;
            }             
            gpl(7,xseg3);

            //code for left down bracket
            j = 0; angle2 = 0;

            add_angle = (PI_V/n) ;
            for( k = 0; k <7; k++){
              xseg4[j].x = x - Vma_tab_size*0.001*cos(angle2);
              xseg4[j].y = y - Vma_tab_size*0.001*sin(angle2);
              ++j;
              angle2 += add_angle;
            }             
            gpl(7,xseg4);

          }


        }
        break;




        //w41

      case 41:

        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;

          j = 0,k = 0;
          s = Vma_tab_size/1000;

          //first line - first half
          {
            j = 0;
            xseg[j].x = x;
            tempy = xseg[j].y = y + Vma_tab_size*0.0005;
            j++;
            xseg[j].x = x + Vma_tab_size*0.001;
            xseg[j].y = tempy;
            j++;
            gpl(2,xseg);
          }

          //first line - second half
          {
            j = 0;
            tempx = xseg3[j].x = x + Vma_tab_size*0.0015;
            tempy = xseg3[j].y = y + Vma_tab_size*0.0005;
            j++;
            xseg3[j].x = tempx + Vma_tab_size*0.001;
            xseg3[j].y = tempy;
            j++;
            gpl(2,xseg3);
          }

          //middle line
          {
            k = 0;
            xseg1[k].x = x;
            xseg1[k].y = y;
            k++;
            xseg1[k].x = x + Vma_tab_size*0.0025;
            xseg1[k].y = y;
            k++;
            gpl(2,xseg1);
          }

          // third line - first half
          {
            k = 0;
            xseg2[k].x = x;
            xseg2[k].y = y - Vma_tab_size*0.0005;
            k++;
            xseg2[k].x = x + Vma_tab_size*0.001;
            xseg2[k].y = y - Vma_tab_size*0.0005;
            k++;
            gpl(2,xseg2);
          }

          // third line - second half
          {
            k = 0;
            tempx = xseg4[k].x = x + Vma_tab_size*0.0015;
            xseg4[k].y = y - Vma_tab_size*0.0005;
            k++;
            xseg4[k].x = tempx + Vma_tab_size*0.001;
            xseg4[k].y = y - Vma_tab_size*0.0005;
            k++;
            gpl(2,xseg4);
          }


        }
        break;







        //w42
      case 42:

        for  ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;

          j = 0,k = 0;
          s = Vma_tab_size/1000;

          //first line - first half
          {
            j = 0;
            xseg[j].x = x;
            tempy = xseg[j].y = y + Vma_tab_size*0.0005;
            j++;
            xseg[j].x = x + Vma_tab_size*0.001;
            xseg[j].y = tempy;
            j++;
            gpl(2,xseg);
          }

          //first line - second half
          {
            j = 0;
            tempx = xseg3[j].x = x + Vma_tab_size*0.0015;
            tempy = xseg3[j].y = y+ Vma_tab_size*0.0005;
            j++;
            xseg3[j].x = tempx + Vma_tab_size*0.001;
            xseg3[j].y = tempy;
            j++;
            gpl(2,xseg3);
          }

          //middle line
          {
            k = 0;
            xseg1[k].x = x;
            xseg1[k].y = y;
            k++;
            xseg1[k].x = x +Vma_tab_size*0.0025;
            xseg1[k].y = y;
            k++;
            gpl(2,xseg1);
          }

          // third line
          {
            k = 0;
            xseg2[k].x = x;
            xseg2[k].y = y -Vma_tab_size*0.0005;
            k++;
            xseg2[k].x = x +Vma_tab_size*0.0025;
            xseg2[k].y = y - Vma_tab_size*0.0005;
            k++;
            gpl(2,xseg2);
          }

          // code for right side line
          j = 0;
          xseg4[j].x = x + Vma_tab_size*0.003;
          xseg4[j].y = y -Vma_tab_size*0.0008;
          j++;
          xseg4[j].x = x + Vma_tab_size*0.003;
          xseg4[j].y = y + Vma_tab_size*0.0008;
          j++;

          gpl(2, xseg4);

        }
        break;





        //w43
      case 43:

        for (i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;

          j = 0,k = 0;
          s = Vma_tab_size/1000;

          //first line
          {
            j = 0;
            xseg5[j].x = x;
            tempy = xseg5[j].y = y - Vma_tab_size*0.0005;
            j++;
            xseg5[j].x = x + Vma_tab_size*0.0025;
            xseg5[j].y = tempy;
            j++;
            gpl(2,xseg5);
          }

          //second line
          {
            k = 0;
            xseg1[k].x =  x;
            xseg1[k].y = y;
            k++;
            xseg1[k].x = x + Vma_tab_size*0.0025;
            xseg1[k].y = y;
            k++;
            gpl(2,xseg1);
          }

          //third line
          {
            k = 0;
            xseg6[k].x = x;
            xseg6[k].y = y + Vma_tab_size*0.0005;
            k++;
            xseg6[k].x = x + Vma_tab_size*0.0025;
            xseg6[k].y = y + Vma_tab_size*0.0005;
            k++;
            gpl(2,xseg6);
          }

          // code for right side line
          j = 0;
          xseg4[j].x = x + Vma_tab_size*0.003;
          xseg4[j].y = y - Vma_tab_size*0.0008;
          j++;
          xseg4[j].x = x + Vma_tab_size*0.003;
          xseg4[j].y = y + Vma_tab_size*0.0008;
          j++;

          gpl(2, xseg4);

        }
        break;





        //w44
      case 44:

        for (i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;

          j = 0,k = 0;
          s = Vma_tab_size/1000;

          //first line - first half
          {
            j = 0;
            xseg[j].x = x;
            tempy = xseg[j].y = y + Vma_tab_size*0.0005;
            j++;
            xseg[j].x = x + Vma_tab_size*0.001;
            xseg[j].y = tempy;
            j++;
            gpl(2,xseg);
          }

          //first line - second half
          {
            j = 0;
            tempx = xseg3[j].x = x + Vma_tab_size*0.0015;
            tempy = xseg3[j].y = y + Vma_tab_size*0.0005;
            j++;
            xseg3[j].x = tempx + Vma_tab_size*0.001;
            xseg3[j].y = tempy;
            j++;
            gpl(2,xseg3);
          }

          //middle line
          {
            k = 0;
            xseg1[k].x = x;
            xseg1[k].y = y;
            k++;
            xseg1[k].x = x + Vma_tab_size*0.0025;
            xseg1[k].y = y;
            k++;
            gpl(2,xseg1);
          }

          // third line
          {
            k = 0;
            xseg2[k].x = x;
            xseg2[k].y = y - Vma_tab_size*0.0005;
            k++;
            xseg2[k].x = x + Vma_tab_size*0.0025;
            xseg2[k].y = y - Vma_tab_size*0.0005;
            k++;
            gpl(2,xseg2);
          }

        }
        break;




        //w45
      case 45:

        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;

          j = 0,k = 0;
          s = Vma_tab_size/1000;

          //first line
          {
            j = 0;
            xseg5[j].x = x;
            tempy = xseg5[j].y = y - Vma_tab_size*0.0005;
            j++;
            xseg5[j].x = x + Vma_tab_size*0.0025;
            xseg5[j].y = tempy;
            j++;
            gpl(2,xseg5);
          }

          //second line
          {
            k = 0;
            xseg1[k].x = x;
            xseg1[k].y = y;
            k++;
            xseg1[k].x = x + Vma_tab_size*0.0025;
            xseg1[k].y = y;
            k++;
            gpl(2,xseg1);
          }

          //third line
          {
            k = 0;
            xseg6[k].x = x;
            xseg6[k].y = y + Vma_tab_size*0.0005;
            k++;
            xseg6[k].x = x + Vma_tab_size*0.0025;
            xseg6[k].y = y + Vma_tab_size*0.0005;
            k++;
            gpl(2,xseg6);
          }


        }
        break;




        //w46
      case 46:

        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;

          j = 0,k = 0;
          s = Vma_tab_size/1000;

          //first line - first half
          {
            j = 0;
            xseg[j].x = x;
            tempy = xseg[j].y = y + Vma_tab_size*0.0005;
            j++;
            xseg[j].x = x + Vma_tab_size*0.001;
            xseg[j].y = tempy;
            j++;
            gpl(2,xseg);
          }

          //first line - second half
          {
            j = 0;
            tempx = xseg3[j].x = x + Vma_tab_size*0.0015;
            tempy = xseg3[j].y = y + Vma_tab_size*0.0005;
            j++;
            xseg3[j].x = tempx + Vma_tab_size*0.001;
            xseg3[j].y = tempy;
            j++;
            gpl(2,xseg3);
          }

          //middle line
          {
            k = 0;
            xseg1[k].x = x;
            xseg1[k].y = y;
            k++;
            xseg1[k].x = x + Vma_tab_size*0.0025;
            xseg1[k].y = y;
            k++;
            gpl(2,xseg1);
          }

          // third line
          {
            k = 0;
            xseg2[k].x = x;
            xseg2[k].y = y - Vma_tab_size*0.0005;
            k++;
            xseg2[k].x = x + Vma_tab_size*0.0025;
            xseg2[k].y = y - Vma_tab_size*0.0005;
            k++;
            gpl(2,xseg2);
          }

          // code for left side line
          j = 0;
          xseg4[j].x = x - Vma_tab_size*0.0005;
          xseg4[j].y = y - Vma_tab_size*0.0008;
          j++;
          xseg4[j].x = x - Vma_tab_size*0.0005;
          xseg4[j].y = y + Vma_tab_size*0.0008; 
          j++;
          gpl(2, xseg4);

        }
        break;




        //w47
      case 47:

        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;

          j = 0,k = 0;
          s = Vma_tab_size/1000;

          //first line
          {
            j = 0;
            xseg5[j].x = x;
            tempy = xseg5[j].y = y - Vma_tab_size*0.0005;
            j++;
            xseg5[j].x = x + Vma_tab_size*0.0025;
            xseg5[j].y = tempy;
            j++;
            gpl(2,xseg5);
          }

          //second line
          {
            k = 0;
            xseg1[k].x = x;
            xseg1[k].y = y;
            k++;
            xseg1[k].x = x + Vma_tab_size*0.0025;
            xseg1[k].y = y;
            k++;
            gpl(2,xseg1);
          }

          //third line
          {
            k = 0;
            xseg6[k].x = x;
            xseg6[k].y = y + Vma_tab_size*0.0005;
            k++;
            xseg6[k].x = x + Vma_tab_size*0.0025;
            xseg6[k].y = y + Vma_tab_size*0.0005;
            k++;
            gpl(2,xseg6);
          }

          // code for left side line
          j = 0;
          xseg4[j].x = x - Vma_tab_size*0.0005;
          xseg4[j].y = y - Vma_tab_size*0.0008;
          j++;
          xseg4[j].x = x - Vma_tab_size*0.0005; 
          xseg4[j].y = y + Vma_tab_size*0.0008;
          j++;

          gpl(2, xseg4);

        }
        break;



        //w48
      case 48:

        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;

          j = 0, k = 0;
          s = Vma_tab_size/1000;

          //first base horizontal line
          {
            j = 0;
            xseg5[j].x = x;
            tempy = xseg5[j].y = y - Vma_tab_size*0.0007;
            j++;
            xseg5[j].x = x + Vma_tab_size*0.0028;
            xseg5[j].y = tempy;
            j++;
            gpl(2,xseg5);
          }

          // solid invert triangle
          {
            gsfais(GSOLID);
            k = 0;
            xseg2[k].x = x + Vma_tab_size*0.0015;
            xseg2[k].y = tempy;
            k++;
            xseg2[k].x = x + Vma_tab_size*0.001;
            xseg2[k].y = y;
            k++;
            xseg2[k].x = x + Vma_tab_size*0.002;
            xseg2[k].y = y;
            k++;
            xseg2[k].x = x + Vma_tab_size*0.0015;
            xseg2[k].y = tempy;
            k++;
            gfa(4,xseg2);
          }


          //second line
          {
            k = 0;
            xseg1[k].x = x;
            xseg1[k].y = y;
            k++;
            xseg1[k].x = x + Vma_tab_size*0.0028;
            xseg1[k].y = y;
            k++;
            gpl(2,xseg1);
          }

          //connection between second and third line
          {
            //left line
            xseg2[0].x = x + Vma_tab_size*0.001;
            xseg2[0].y = y;
            xseg2[1].x = x + Vma_tab_size*0.0005;
            xseg2[1].y = y + Vma_tab_size*0.0008;
            xseg2[2].x = x;
            xseg2[2].y = y + Vma_tab_size*0.0008;
            gpl(3,xseg2);

            //right line
            xseg4[0].x = x + Vma_tab_size*0.002;
            xseg4[0].y = y;
            xseg4[1].x = x + Vma_tab_size*0.0024;
            xseg4[1].y = y + Vma_tab_size*0.0008;
            xseg4[2].x = x + Vma_tab_size*0.0029;
            xseg4[2].y = y + Vma_tab_size*0.0008;
            gpl(3,xseg4);

          }


        }
        break;






        //w49
      case 49:

        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;

          j = 0,k=0;
          s = Vma_tab_size/1000;

          //first base horizontal line
          {
            j = 0;
            xseg5[j].x = x;
            tempy = xseg5[j].y = y - Vma_tab_size*0.0007;
            j++;
            xseg5[j].x = x + Vma_tab_size*0.0028;
            xseg5[j].y = tempy;
            j++;
            gpl(2,xseg5);
          }

          // solid invert triangle
          {
            gsfais(GSOLID);
            k = 0;
            xseg2[k].x = x + Vma_tab_size*0.0015;
            xseg2[k].y = tempy;
            k++;
            xseg2[k].x = x + Vma_tab_size*0.001;
            xseg2[k].y = y;
            k++;
            xseg2[k].x = x + Vma_tab_size*0.002;
            xseg2[k].y = y;
            k++;
            xseg2[k].x = x + Vma_tab_size*0.0015;
            xseg2[k].y = tempy;
            k++;
            gfa(4,xseg2);
          }


          //second line
          {
            k = 0;
            xseg1[k].x = x;
            xseg1[k].y = y;
            k++;
            xseg1[k].x = x + Vma_tab_size*0.0028;
            xseg1[k].y = y;
            k++;
            gpl(2,xseg1);
          }

          //connection between second and third line
          {
            //left line
            xseg2[0].x = x + Vma_tab_size*0.001;
            xseg2[0].y = y;
            xseg2[1].x = x + Vma_tab_size*0.0005;
            xseg2[1].y = y + Vma_tab_size*0.0008;
            gpl(2,xseg2);

            //right line
            xseg4[0].x = x + Vma_tab_size*0.002;
            xseg4[0].y = y;
            xseg4[1].x = x + Vma_tab_size*0.0024;
            xseg4[1].y = y + Vma_tab_size*0.0008;
            gpl(2,xseg4);

          }

          //third line
          {
            k = 0;
            xseg6[k].x = x;
            xseg6[k].y = y + Vma_tab_size*0.0008;
            k++;
            xseg6[k].x = x + Vma_tab_size*0.0028;
            xseg6[k].y = y + Vma_tab_size*0.0008;
            k++;
            gpl(2,xseg6);
          }

        }
        break;





        //w50
      case 50:

        // start of solid circle 
        gsfais(GSOLID);
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          angle1 = 0; 
          j = 0;
          s = Vma_tab_size / 1800;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
            if ( k == n+(n/2)) {
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg);

          //start of solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size/3000; 
          j = 0;
          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--){	
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size / 1500;
          for( k = -(n/2); k <n/4; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + Vma_tab_size / 1500*cos(angle1);
            xseg1[j].y = y + Vma_tab_size / 2500*sin(angle1);
            j++;
          }

          gfa(35, xseg1);
        }
        break;



        //w51
      case 51:


        // start of solid left circle 
        gsfais(GSOLID);
        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size / 1800;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <= 2*n; k++){
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
            if( k == n+(n/2)){
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg);

          //start of left solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size / 3000;
          j = 0;
          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--) {	
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size / 1500;
          for( k = -(n/2); k <n/4; k++) {
            angle1 = k*add_angle;
            xseg[j].x = x + Vma_tab_size / 1500*cos(angle1);
            xseg[j].y = y + Vma_tab_size / 2500*sin(angle1);
            j++;
          }				
          gfa(35, xseg);

          // start of solid right circle 
          x = x +  Vma_tab_size*0.0015;
          y = tempy;//position of right circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/1800;
          n =20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++) {
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
            if( k == n+(n/2)){
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg1);

          //start of right solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size / 3000;
          j = 0;
          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--) {	
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size / 1500;
          for( k = -(n/2); k <n/4; k++) {
            angle1 = k*add_angle;
            xseg1[j].x = x + Vma_tab_size / 1500*cos(angle1);
            xseg1[j].y = y + Vma_tab_size / 2500*sin(angle1);
            j++;
          }
          gfa(35, xseg1);


        }
        break;




        //w52
      case 52:


        // start of solid left circle 
        gsfais(GSOLID);
        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          angle1 = 0; 
          j = 0;
          s = Vma_tab_size / 1800;
          n =20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
            if( k == n+(n/2)) {
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg);

          //start of left solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size / 3000;
          j = 0;
          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--) {	
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size/1500;
          for( k = -(n/2); k <n/4; k++) {
            angle1 = k*add_angle;
            xseg[j].x = x + Vma_tab_size / 1500*cos(angle1);
            xseg[j].y = y + Vma_tab_size / 2500*sin(angle1);
            j++;
          }
          gfa(35, xseg);

          // start of solid right circle 
          y = tempy + Vma_tab_size*0.0018;//position of right circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size / 1800;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
            if( k == n+(n/2)) {
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg1);

          //start of right solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size / 3000;
          j = 0; 
          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--) {	
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size / 1500;
          for( k = -(n/2); k <n/4; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + Vma_tab_size / 1500*cos(angle1);
            xseg1[j].y = y + Vma_tab_size / 2500*sin(angle1);
            j++;
          }
          gfa(35, xseg1);

        }
        break;






        //w53
      case 53:


        // start of solid left circle 
        gsfais(GSOLID);
        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/1800;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
            if(k == n+(n/2)) {
              tempx = x ;
              tempy = y ;
            }
          }
          gfa(41, xseg);

          //start of left solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005; 
          s = Vma_tab_size / 3000;
          j = 0;
          gsfais(GSOLID);
          for( k = n/2; k > -(n/2); k--) {	
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size / 1500;
          for( k =-(n/2); k < n/4; k++) {
            angle1 = k*add_angle;
            xseg[j].x = x + Vma_tab_size / 1500*cos(angle1);
            xseg[j].y = y + Vma_tab_size / 2500*sin(angle1);
            j++;
          }
          gfa(35, xseg);

          // start of solid right circle 
          x = x + Vma_tab_size*0.0015;
          y = tempy;//position of right circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size / 1800;
          n =20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++) {
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
            if( k == n+(n/2)) {
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg1);

          //start of right solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005; 
          s = Vma_tab_size / 3000;
          j = 0;
          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--) {	
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size / 1500;
          for( k = -(n/2); k <n/4; k++) {
            angle1 = k*add_angle;
            xseg1[j].x = x + Vma_tab_size / 1500*cos(angle1);
            xseg1[j].y = y + Vma_tab_size / 2500*sin(angle1);
            j++;
          }
          gfa(35, xseg1);

          // start of solid top circle 
          x = tempx - Vma_tab_size*0.0008;//position of top circle
          y = tempy + Vma_tab_size*0.0015;
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size / 1800;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0 ; k <=2*n; k++) {
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
            if(k == n+(n/2)){
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg2);

          //start of top solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005; 
          s = Vma_tab_size / 3000;
          j = 0; 

          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--) {	
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size / 1500;
          for( k = -(n/2); k <n/4; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + Vma_tab_size / 1500*cos(angle1);
            xseg2[j].y = y + Vma_tab_size / 2500*sin(angle1);
            j++;
          }
          gfa(35, xseg2);

        }
        break;



        //w54
      case 54:


        // start of solid first circle 
        gsfais(GSOLID);
        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          y = y - Vma_tab_size*0.0018; //position of first circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size / 1800;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++) {  
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
            if( k == n+(n/2)){
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg);

          //start of first solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size / 3000;
          j = 0;
          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--) {	
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size/1500;
          for( k =-(n/2); k <n/4; k++) {
            angle1 = k*add_angle;
            xseg[j].x = x + Vma_tab_size / 1500*cos(angle1);
            xseg[j].y = y + Vma_tab_size / 2500*sin(angle1);
            j++;
          }
          gfa(35, xseg);

          // start of solid middle circle 
          y = pe.y;//position of middle circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/1800;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++) {
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
            if( k == n+(n/2)){
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg1);

          //start of middle solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size / 3000;
          j = 0;
          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--){	
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size / 1500;
          for(k = -(n/2); k <n/4; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + Vma_tab_size / 1500*cos(angle1);
            xseg1[j].y = y + Vma_tab_size / 2500*sin(angle1);
            j++;
          }
          gfa(35, xseg1);


          // start of solid last circle 
          y = tempy + Vma_tab_size*0.0018;//position of last circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size / 1800;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
            if( k == n+(n/2)){
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg2);

          //start of last solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size / 3000;
          j = 0;
          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--){	
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size/1500;
          for( k = -(n/2); k < n/4; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + Vma_tab_size/1500*cos(angle1);
            xseg2[j].y = y + Vma_tab_size/2500*sin(angle1);
            j++;
          }
          gfa(35, xseg2);

        }
        break;





        //w55
      case 55:


        // start of solid left circle 
        gsfais(GSOLID);
        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/1800;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0 ; k <=2*n; k++){

            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
            if( k == n+(n/2)) {
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg);

          //start of left solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size / 3000;
          j = 0;
          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--) {	
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size / 1500;
          for( k = -(n/2); k <n/4; k++) {
            angle1 = k*add_angle;
            xseg[j].x = x + Vma_tab_size / 1500*cos(angle1);
            xseg[j].y = y + Vma_tab_size / 2500*sin(angle1);
            j++;
          }
          gfa(35, xseg);

          // start of solid right circle 
          x = tempx + Vma_tab_size*0.0015;
          y = tempy;//position of right circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size / 1800;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <= 2*n; k++){

            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
            if(k == n+(n/2)){
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg1);

          //start of right solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size / 3000;
          j = 0;
          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--) {	
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size / 1500;
          for( k =-(n/2); k <n/4; k++) {
            angle1 = k*add_angle;
            xseg1[j].x = x + Vma_tab_size/1500*cos(angle1);
            xseg1[j].y = y + Vma_tab_size/2500*sin(angle1);
            j++;
          }
          gfa(35, xseg1);


          // start of solid top circle 
          x = tempx -  Vma_tab_size*0.0008;//position of top circle
          y = tempy + Vma_tab_size*0.0015;
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size / 1800;
          n=20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
            if( k == n+(n/2)) {
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg2);

          //start of top solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size / 3000;
          j = 0;
          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--) {	
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size / 1500;
          for( k =-(n/2); k <n/4; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + Vma_tab_size/1500*cos(angle1);
            xseg2[j].y = y + Vma_tab_size/2500*sin(angle1);
            j++;
          }
          gfa(35, xseg2);

          // start of solid bottom circle 
          x = tempx;//position of bottom circle
          y = tempy - Vma_tab_size*0.003;
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n = 20;
          add_angle=PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg3[j].x = x + s*cos(angle1);
            xseg3[j].y = y + s*sin(angle1);
            j++;
            if( k == n+(n/2)) {
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg3);

          //start of bottom solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size / 3000;
          j = 0;
          gsfais(GSOLID);
          for( k = n /2; k >-(n/2); k--){	
            angle1 = k*add_angle;
            xseg3[j].x = x + s*cos(angle1);
            xseg3[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size / 1500;
          for( k =-(n/2); k <n/4; k++){
            angle1 = k*add_angle;
            xseg3[j].x = x + Vma_tab_size/1500*cos(angle1);
            xseg3[j].y = y + Vma_tab_size/2500*sin(angle1);
            j++;
          }
          gfa(35, xseg3);


        }
        break;





        //w56
      case 56:


        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;

          angle1 = 0; 
          j = 0,k = 0;
          s = Vma_tab_size/1000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k < n+(n/2); k++) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*sin(angle1);
            xseg[j].y = y + s*cos(angle1);
            j++;
          }

          x = x - Vma_tab_size*0.002;
          y = y;
          add_angle = PI_V/n ; 
          for( k = n/2; k >-(n); k--){
            angle1 = k*add_angle;
            xseg[j].x = x + s*sin(angle1);
            xseg[j].y = y + s*cos(angle1);
            j++;
          } 
          gpl(60,xseg);

          //solid circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2200;
          n=20;
          add_angle=PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
            if( k == n+(n/2)){
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg1);

          //start of first solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size / 3000;
          j = 0;
          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--){	
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size / 1500;
          for( k =-(n/2); k < n/4; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + Vma_tab_size/1500*cos(angle1);
            xseg1[j].y = y + Vma_tab_size/2500*sin(angle1);
            j++;
          }
          gfa(35, xseg1);

        }
        break;



        //w57
      case 57:


        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0;
          angle2 = add_angle;
          j = 0,k = 0;
          s = Vma_tab_size/1000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0;k < n+(n/2); k++) {
            angle1 = k*add_angle;
            xseg[j].x = x + s*sin(angle1);
            xseg[j].y = y + s*cos(angle1);
            j++;
          }

          x = x - Vma_tab_size*0.002;
          y = y;
          add_angle = PI_V/n ; 
          for( k = n/2; k >-(n); k--){
            angle1 = k*add_angle;
            xseg[j].x = x + s*sin(angle1);
            xseg[j].y = y + s*cos(angle1);
            j++;
          } 
          gpl(60,xseg);

          //solid left circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2200;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
            if( k == n+(n/2)){
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg1);

          //start of left solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size / 3000;
          j = 0;
          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--){	
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size / 1500;
          for( k =-(n/2); k <n/4; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + Vma_tab_size/1500*cos(angle1);
            xseg1[j].y = y + Vma_tab_size/2500*sin(angle1);
            j++;
          }

          gfa(35, xseg1);

          // solid second circle
          x = x + Vma_tab_size*0.002;
          y = tempy;//position of second circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size / 2200;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
            if( k == n+(n/2)){
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg2);

          //start of left solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size / 3000;
          j = 0;
          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--){	
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size/1500;
          for( k = -(n/2); k < n/4; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + Vma_tab_size/1500*cos(angle1);
            xseg2[j].y = y + Vma_tab_size/2500*sin(angle1);
            j++;
          }
          gfa(35, xseg2);

        }
        break;



        //w58
      case 58:

        // start of solid bottom circle 
        gsfais(GSOLID);
        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          // start of solid top circle 
          y = y + Vma_tab_size*0.0015;//position of top circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size / 1800;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg1);


          // start comma
          //solid circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size / 1800;
          n = 20;
          add_angle = PI_V/n ;
          x = pe.x; 
          y = pe.y;
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
            if(k == n+(n/2)){
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg1);

          //start of first solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size / 3000;
          j = 0;
          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--){	
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size/1500;
          for( k =-(n/2); k <n/4; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + Vma_tab_size/1500*cos(angle1);
            xseg1[j].y = y + Vma_tab_size/2500*sin(angle1);
            j++;
          }
          gfa(35, xseg1);
        }
        break;




        //w59
      case 59:

        gsfais(GSOLID);
        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          // start top comma
          //solid circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size / 1800;
          n =20;
          add_angle = PI_V/n ;
          y = y + Vma_tab_size*0.0035;//position of top comma;
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
            if( k == n+(n/2)){
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg1);

          //start of first solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size / 3000;
          j = 0;
          gsfais(GSOLID);
          for( k = n/2; k >-(n/2); k--){	
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size/1500;
          for( k =-(n/2); k <n/4; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + Vma_tab_size/1500*cos(angle1);
            xseg1[j].y = y + Vma_tab_size/2500*sin(angle1);
            j++;
          }
          gfa(35, xseg1);

          // start of solid middle circle 
          y = pe.y;
          y = y + Vma_tab_size*0.0015;//position of middle circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size / 1800;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg1);

          // start bottom comma
          //solid circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/1800;
          n = 20;
          add_angle = PI_V/n ;
          x = pe.x; 
          y = pe.y;
          for( k = 0 ; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
            if( k == n+(n/2)){
              tempx = x;
              tempy = y;
            }
          }
          gfa(41, xseg1);

          //start of first solid comma symbol
          x = tempx - Vma_tab_size*0.0001;
          y = tempy - Vma_tab_size*0.0005;
          s = Vma_tab_size / 3000;
          j = 0;
          gsfais(GSOLID);
          for( k =n/2; k >-(n/2); k--){	
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          s = Vma_tab_size/1500;
          for( k =-(n/2); k <n/4; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + Vma_tab_size/1500*cos(angle1);
            xseg1[j].y = y + Vma_tab_size/2500*sin(angle1);
            j++;
          }
          gfa(35, xseg1);

        }
        break;




        //w60
      case 60:


        // start of solid circle 
        gsfais(GSOLID);
        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg);
        }
        break;




        //w61
      case 61:


        // start of solid left circle 
        gsfais(GSOLID);
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg);

          // start of solid right circle 
          x = x + Vma_tab_size*0.0015;//position of right circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg1);

        }
        break;





        //w62
      case 62:


        // start of solid bottom circle 
        gsfais(GSOLID);
        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0 ; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg);

          // start of solid top circle 
          y = y + Vma_tab_size*0.0015;//position of top circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++) {
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg1);

        }
        break;






        //w63
      case 63:


        // start of solid left circle 
        gsfais(GSOLID);
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          angle1 = 0; 
          j = 0;
          s = Vma_tab_size / 2000;
          n=20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg);

          // start of solid right circle 
          x = x + Vma_tab_size*0.0015;//position of right circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg1);

          // start of solid top circle 
          x = x - Vma_tab_size*0.0008;//position of top circle
          y = y + Vma_tab_size*0.001;
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg2);

        }
        break;




        //w65
      case 65:


        // start of solid left circle 
        gsfais(GSOLID);
        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg);

          // start of solid right circle 
          x = x + Vma_tab_size*0.0015;//position of right circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg1);


          // start of solid top circle 
          x = x - Vma_tab_size*0.0008;//position of top circle
          y = y + Vma_tab_size*0.001;
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg2);
          // start of solid bottom circle 

          //position of bottom circle
          y = y - Vma_tab_size*0.002;
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <= 2*n; k++){
            angle1 = k*add_angle;
            xseg3[j].x = x + s*cos(angle1);
            xseg3[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg3);


        }
        break;




        //w64
      case 64:


        // start of solid first circle 
        gsfais(GSOLID);
        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;
          y=y- Vma_tab_size*0.0012; //position of first circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n=20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg);

          // start of solid middle circle 
          y = pe.y;//position of middle circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg1);


          // start of solid last circle 
          y = y + Vma_tab_size*0.0012;//position of last circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg2);

        }
        break;





        //w66
      case 66:


        for (i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; 
          j = 0,k=0;
          s = Vma_tab_size/1000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <n+(n/2); k++){
            angle1 = k*add_angle;
            xseg[j].x = x + s*sin(angle1);
            xseg[j].y = y + s*cos(angle1);
            j++;
          }
          x = x - Vma_tab_size*0.002;
          y = y;
          add_angle = PI_V/n ; 
          for( k = n/2; k >-(n); k--){
            angle1 = k*add_angle;
            xseg[j].x = x + s*sin(angle1);
            xseg[j].y = y + s*cos(angle1);
            j++;
          } 
          gpl(60,xseg);

          //solid circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg1);

        }
        break;




        //w67
      case 67:


        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; 
          j = 0,k=0;
          s = Vma_tab_size/1000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <n+(n/2); k++){
            angle1 = k*add_angle;
            xseg[j].x = x + s*sin(angle1);
            xseg[j].y = y + s*cos(angle1);
            j++;
          }

          x = x - Vma_tab_size*0.002;
          y = y;
          add_angle = PI_V/n ; 
          for( k = n/2; k >-(n); k--){
            angle1 = k*add_angle;
            xseg[j].x = x + s*sin(angle1);
            xseg[j].y = y + s*cos(angle1);
            j++;
          } 
          gpl(60,xseg);

          //solid left circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg1);

          // solid second circle
          x = x + Vma_tab_size*0.002;//position of second circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/2000;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg2);

        }
        break;




        //w68
      case 68:


        // star initialization 
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;



        // start of solid bottom circle 
        gsfais(GSOLID);
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          // start of  star
          j = 0,k = 0;

          xseg[0].x = x + star1[0].x;
          xseg[0].y = y + star1[0].y;
          xseg[1].x = x + star1[1].x;
          xseg[1].y = y + star1[1].y;
          gpl(2, xseg);
          xseg[0].x = x + star2[0].x;
          xseg[0].y = y + star2[0].y;
          xseg[1].x = x + star2[1].x;
          xseg[1].y = y + star2[1].y;
          gpl(2, xseg);
          xseg[0].x = x + star3[0].x;
          xseg[0].y = y + star3[0].y;
          xseg[1].x = x + star3[1].x;
          xseg[1].y = y + star3[1].y;
          gpl(2, xseg);

          // end of  star


          // start of solid top circle 
          y = y+ Vma_tab_size*0.0022;//position of top circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/1500;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg1);

        }
        break;







        //w69
      case 69:


        // star initialization 
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;



        // start of solid bottom circle 
        gsfais(GSOLID);
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;


          // start of bottom star
          j = 0,k = 0;

          xseg[0].x = x + star1[0].x;
          xseg[0].y = y + star1[0].y;
          xseg[1].x = x + star1[1].x;
          xseg[1].y = y + star1[1].y;
          gpl(2, xseg);
          xseg[0].x = x + star2[0].x;
          xseg[0].y = y + star2[0].y;
          xseg[1].x = x + star2[1].x;
          xseg[1].y = y + star2[1].y;
          gpl(2, xseg);
          xseg[0].x = x + star3[0].x;
          xseg[0].y = y + star3[0].y;
          xseg[1].x = x + star3[1].x;
          xseg[1].y = y + star3[1].y;
          gpl(2, xseg);

          // end of  bottom star



          // start of solid middle circle 
          y = y + Vma_tab_size*0.0022;//position of top circle
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/1500;
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg1);


          // start of  top star
          y = y + Vma_tab_size*0.0022;//position of top star
          j = 0,k = 0;

          xseg2[0].x = x + star1[0].x;
          xseg2[0].y = y + star1[0].y;
          xseg2[1].x = x + star1[1].x;
          xseg2[1].y = y + star1[1].y;
          gpl(2, xseg2);
          xseg2[0].x = x + star2[0].x;
          xseg2[0].y = y + star2[0].y;
          xseg2[1].x = x + star2[1].x;
          xseg2[1].y = y + star2[1].y;
          gpl(2, xseg2);
          xseg2[0].x = x + star3[0].x;
          xseg2[0].y = y + star3[0].y;
          xseg2[1].x = x + star3[1].x;
          xseg2[1].y = y + star3[1].y;
          gpl(2, xseg2);
          // end of  top star

        }
        break;





        //w70
      case 70:


        // star initialization 
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;


        // start of solid bottom circle 
        gsfais(GSOLID);
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          // start of  star
          j = 0, k = 0;

          xseg[0].x = x + star1[0].x;
          xseg[0].y = y + star1[0].y;
          xseg[1].x = x + star1[1].x;
          xseg[1].y = y + star1[1].y;
          gpl(2, xseg);
          xseg[0].x = x + star2[0].x;
          xseg[0].y = y + star2[0].y;
          xseg[1].x = x + star2[1].x;
          xseg[1].y = y + star2[1].y;
          gpl(2, xseg);
          xseg[0].x = x + star3[0].x;
          xseg[0].y = y + star3[0].y;
          xseg[1].x = x + star3[1].x;
          xseg[1].y = y + star3[1].y;
          gpl(2, xseg);

          // end of   star

        }
        break;




        //w71
      case 71:


        // star initialization 
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;


        gsfais(GSOLID);
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          // start of left star
          j = 0, k = 0;

          xseg[0].x = x + star1[0].x;
          xseg[0].y = y + star1[0].y;
          xseg[1].x = x + star1[1].x;
          xseg[1].y = y + star1[1].y;
          gpl(2, xseg);
          xseg[0].x = x + star2[0].x;
          xseg[0].y = y + star2[0].y;
          xseg[1].x = x + star2[1].x;
          xseg[1].y = y + star2[1].y;
          gpl(2, xseg);
          xseg[0].x = x + star3[0].x;
          xseg[0].y = y + star3[0].y;
          xseg[1].x = x + star3[1].x;
          xseg[1].y = y + star3[1].y;
          gpl(2, xseg);

          // end of  left star


          // start of  right star
          x = x + Vma_tab_size*0.0025;//position of right star
          j = 0, k = 0;

          xseg2[0].x = x + star1[0].x;
          xseg2[0].y = y + star1[0].y;
          xseg2[1].x = x + star1[1].x;
          xseg2[1].y = y + star1[1].y;
          gpl(2, xseg2);
          xseg2[0].x = x + star2[0].x;
          xseg2[0].y = y + star2[0].y;
          xseg2[1].x = x + star2[1].x;
          xseg2[1].y = y + star2[1].y;
          gpl(2, xseg2);
          xseg2[0].x = x + star3[0].x;
          xseg2[0].y = y + star3[0].y;
          xseg2[1].x = x + star3[1].x;
          xseg2[1].y = y + star3[1].y;
          gpl(2, xseg2);

          // end of  right star


        }
        break;








        //w72
      case 72:


        // star initialization 
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;

        gsfais(GSOLID);
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          // start of bottom star
          j = 0, k = 0;

          xseg[0].x = x + star1[0].x;
          xseg[0].y = y + star1[0].y;
          xseg[1].x = x + star1[1].x;
          xseg[1].y = y + star1[1].y;
          gpl(2, xseg);
          xseg[0].x = x + star2[0].x;
          xseg[0].y = y + star2[0].y;
          xseg[1].x = x + star2[1].x;
          xseg[1].y = y + star2[1].y;
          gpl(2, xseg);
          xseg[0].x = x + star3[0].x;
          xseg[0].y = y + star3[0].y;
          xseg[1].x = x + star3[1].x;
          xseg[1].y = y + star3[1].y;
          gpl(2, xseg);

          // end of  bottom star


          // start of  top star
          y = y + Vma_tab_size*0.002;//position of right star
          j = 0, k = 0;

          xseg2[0].x = x + star1[0].x;
          xseg2[0].y = y + star1[0].y;
          xseg2[1].x = x + star1[1].x;
          xseg2[1].y = y + star1[1].y;
          gpl(2, xseg2);
          xseg2[0].x = x + star2[0].x;
          xseg2[0].y = y + star2[0].y;
          xseg2[1].x = x + star2[1].x;
          xseg2[1].y = y + star2[1].y;
          gpl(2, xseg2);
          xseg2[0].x = x + star3[0].x;
          xseg2[0].y = y + star3[0].y;
          xseg2[1].x = x + star3[1].x;
          xseg2[1].y = y + star3[1].y;
          gpl(2, xseg2);

          // end of  top star


        }
        break;






        //w73
      case 73:


        // star initialization 
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;


        gsfais(GSOLID);
        for (i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;


          // start of left star
          j = 0, k = 0;

          xseg[0].x = x + star1[0].x;
          xseg[0].y = y + star1[0].y;
          xseg[1].x = x + star1[1].x;
          xseg[1].y = y + star1[1].y;
          gpl(2, xseg);
          xseg[0].x = x + star2[0].x;
          xseg[0].y = y + star2[0].y;
          xseg[1].x = x + star2[1].x;
          xseg[1].y = y + star2[1].y;
          gpl(2, xseg);
          xseg[0].x = x + star3[0].x;
          xseg[0].y = y + star3[0].y;
          xseg[1].x = x + star3[1].x;
          xseg[1].y = y + star3[1].y;
          gpl(2, xseg);

          // end of  left star


          // start of  right star
          x = x + Vma_tab_size*0.0025;//position of right star
          j = 0, k = 0;

          xseg2[0].x = x + star1[0].x;
          xseg2[0].y = y + star1[0].y;
          xseg2[1].x = x + star1[1].x;
          xseg2[1].y = y + star1[1].y;
          gpl(2, xseg2);
          xseg2[0].x = x + star2[0].x;
          xseg2[0].y = y + star2[0].y;
          xseg2[1].x = x + star2[1].x;
          xseg2[1].y = y + star2[1].y;
          gpl(2, xseg2);
          xseg2[0].x = x + star3[0].x;
          xseg2[0].y = y + star3[0].y;
          xseg2[1].x = x + star3[1].x;
          xseg2[1].y = y + star3[1].y;
          gpl(2, xseg2);

          // end of  right star


          // start of  top star
          x = x - Vma_tab_size*0.0012;
          y = y + Vma_tab_size*0.0025;//position of top star
          j = 0, k = 0;

          xseg3[0].x = x + star1[0].x;
          xseg3[0].y = y + star1[0].y;
          xseg3[1].x = x + star1[1].x;
          xseg3[1].y = y + star1[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star2[0].x;
          xseg3[0].y = y + star2[0].y;
          xseg3[1].x = x + star2[1].x;
          xseg3[1].y = y + star2[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star3[0].x;
          xseg3[0].y = y + star3[0].y;
          xseg3[1].x = x + star3[1].x;
          xseg3[1].y = y + star3[1].y;
          gpl(2, xseg3);

          // end of  top star


        }
        break;





        //w74
      case 74:


        // star initialization 
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;




        gsfais(GSOLID);
        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          // start of bottom star
          j = 0, k = 0;

          xseg[0].x = x + star1[0].x;
          xseg[0].y = y + star1[0].y;
          xseg[1].x = x + star1[1].x;
          xseg[1].y = y + star1[1].y;
          gpl(2, xseg);
          xseg[0].x = x + star2[0].x;
          xseg[0].y = y + star2[0].y;
          xseg[1].x = x + star2[1].x;
          xseg[1].y = y + star2[1].y;
          gpl(2, xseg);
          xseg[0].x = x + star3[0].x;
          xseg[0].y = y + star3[0].y;
          xseg[1].x = x + star3[1].x;
          xseg[1].y = y + star3[1].y;
          gpl(2, xseg);

          // end of  bottom star


          // start of middle star
          y = y + Vma_tab_size*0.002;//position of middle star
          j = 0, k = 0;

          xseg2[0].x = x + star1[0].x;
          xseg2[0].y = y + star1[0].y;
          xseg2[1].x = x + star1[1].x;
          xseg2[1].y = y + star1[1].y;
          gpl(2, xseg2);
          xseg2[0].x = x + star2[0].x;
          xseg2[0].y = y + star2[0].y;
          xseg2[1].x = x + star2[1].x;
          xseg2[1].y = y + star2[1].y;
          gpl(2, xseg2);
          xseg2[0].x = x + star3[0].x;
          xseg2[0].y = y + star3[0].y;
          xseg2[1].x = x + star3[1].x;
          xseg2[1].y = y + star3[1].y;
          gpl(2, xseg2);

          // end of  middle star


          // start of  top star
          y = y + Vma_tab_size*0.002;//position of top star
          j = 0, k = 0;

          xseg3[0].x = x + star1[0].x;
          xseg3[0].y = y + star1[0].y;
          xseg3[1].x = x + star1[1].x;
          xseg3[1].y = y + star1[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star2[0].x;
          xseg3[0].y = y + star2[0].y;
          xseg3[1].x = x + star2[1].x;
          xseg3[1].y = y + star2[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star3[0].x;
          xseg3[0].y = y + star3[0].y;
          xseg3[1].x = x + star3[1].x;
          xseg3[1].y = y + star3[1].y;
          gpl(2, xseg3);

          // end of  top star

        }
        break;




        //w75
      case 75:


        // star initialization 
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;


        gsfais(GSOLID);
        for ( i = 0; i < npts; i++) {
          x = pe.x;
          y = pe.y;

          // start of left star
          j = 0, k = 0;

          xseg[0].x = x + star1[0].x;
          xseg[0].y = y + star1[0].y;
          xseg[1].x = x + star1[1].x;
          xseg[1].y = y + star1[1].y;
          gpl(2, xseg);
          xseg[0].x = x + star2[0].x;
          xseg[0].y = y + star2[0].y;
          xseg[1].x = x + star2[1].x;
          xseg[1].y = y + star2[1].y;
          gpl(2, xseg);
          xseg[0].x = x + star3[0].x;
          xseg[0].y = y + star3[0].y;
          xseg[1].x = x + star3[1].x;
          xseg[1].y = y + star3[1].y;
          gpl(2, xseg);

          // end of  left star

          // start of  right star
          x = x + Vma_tab_size*0.0025;//position of right star
          j = 0, k = 0;

          xseg2[0].x = x + star1[0].x;
          xseg2[0].y = y + star1[0].y;
          xseg2[1].x = x + star1[1].x;
          xseg2[1].y = y + star1[1].y;
          gpl(2, xseg2);
          xseg2[0].x = x + star2[0].x;
          xseg2[0].y = y + star2[0].y;
          xseg2[1].x = x + star2[1].x;
          xseg2[1].y = y + star2[1].y;
          gpl(2, xseg2);
          xseg2[0].x = x + star3[0].x;
          xseg2[0].y = y + star3[0].y;
          xseg2[1].x = x + star3[1].x;
          xseg2[1].y = y + star3[1].y;
          gpl(2, xseg2);

          // end of  right star


          // start of  top star
          x = x - Vma_tab_size*0.0012;
          y = y + Vma_tab_size*0.0025;//position of top star
          j = 0, k = 0;

          xseg3[0].x = x + star1[0].x;
          xseg3[0].y = y + star1[0].y;
          xseg3[1].x = x + star1[1].x;
          xseg3[1].y = y + star1[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star2[0].x;
          xseg3[0].y = y + star2[0].y;
          xseg3[1].x = x + star2[1].x;
          xseg3[1].y = y + star2[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star3[0].x;
          xseg3[0].y = y + star3[0].y;
          xseg3[1].x = x + star3[1].x;
          xseg3[1].y = y + star3[1].y;
          gpl(2, xseg3);

          // end of  top star


          // start of bottom star

          y = y - Vma_tab_size*0.005;//position of bottom star
          j = 0, k = 0;

          xseg4[0].x = x + star1[0].x;
          xseg4[0].y = y + star1[0].y;
          xseg4[1].x = x + star1[1].x;
          xseg4[1].y = y + star1[1].y;
          gpl(2, xseg4);
          xseg4[0].x = x + star2[0].x;
          xseg4[0].y = y + star2[0].y;
          xseg4[1].x = x + star2[1].x;
          xseg4[1].y = y + star2[1].y;
          gpl(2, xseg4);
          xseg4[0].x = x + star3[0].x;
          xseg4[0].y = y + star3[0].y;
          xseg4[1].x = x + star3[1].x;
          xseg4[1].y = y + star3[1].y;
          gpl(2, xseg4);

          // end of  bottom star


        }
        break;





        //w76
      case 76:

        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0, k = 0;

          //code for horizontal line right hand arrow mark         

          {         

            startx = xseg1[j].x = x - Vma_tab_size*0.002;
            starty = xseg1[j].y = y;
            j++;
            xseg1[j].x = x + Vma_tab_size*0.002;
            xseg1[j].y = y ;
            j++;
            xseg1[j].x = xseg1[j-1].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-1].y - Vma_tab_size*0.0006;
            j++;
            xseg1[j].x = xseg1[j-2].x;
            xseg1[j].y = xseg1[j-2].y;
            j++;
            xseg1[j].x = xseg1[j-3].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-3].y + Vma_tab_size*0.0006;
            j++;

            gpl(5,xseg1);

            //left side arrow mark	
            j = 0;
            xseg[j].x = startx;
            xseg[j].y = starty;
            j++;
            xseg[j].x = xseg[j-1].x + Vma_tab_size*0.0006;
            xseg[j].y = xseg[j-1].y - Vma_tab_size*0.0006;
            j++;
            xseg[j].x = xseg[j-2].x;
            xseg[j].y = xseg[j-2].y;
            j++;
            xseg[j].x = xseg[j-3].x + Vma_tab_size*0.0006;
            xseg[j].y = xseg[j-3].y + Vma_tab_size*0.0006;
            j++;
            gpl(4,xseg);	

          }



        }
        break;





        //w77
      case 77:


        for (i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0, k = 0;
          s = Vma_tab_size/1000;

          // setting regular triangle position
          j = 0;
          xseg[j].x = x;
          xseg[j].y = y;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y;
          j++;
          xseg[j].x = x ;
          xseg[j].y = y + Vma_tab_size*0.001;
          j++;
          xseg[j].x = x + Vma_tab_size*0.001;
          xseg[j].y = y;
          j++;
          xseg[j].x = x;
          xseg[j].y = y;
          j++;
          gpl(5, xseg);

          // horizontal line
          j = 0;
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y + Vma_tab_size*0.0005;
          j++;
          xseg1[j].x = x + Vma_tab_size*0.002;
          xseg1[j].y = y + Vma_tab_size*0.0005;
          j++;
          gpl(2, xseg1);
        }
        break;







        //w78
      case 78:

        for (i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0, k = 0;

          //code for cross mark

          //right cross line
          xseg2[j].x = x; 
          xseg2[j].y = y;
          j++;
          xseg2[j].x = x + Vma_tab_size*0.002; 
          xseg2[j].y = y + Vma_tab_size*0.002;
          j++;
          gpl(2,xseg2);

          //left cross line	
          j = 0;
          xseg3[j].x = x;
          xseg3[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg3[j].x = x + Vma_tab_size*0.002;
          xseg3[j].y = y;
          j++;
          gpl(2,xseg3);

          //code for horizontal line right hand arrow mark         
          {         
            j = 0;
            xseg1[j].x = x - Vma_tab_size*0.002; 
            xseg1[j].y = y + Vma_tab_size*0.001;
            j++;
            xseg1[j].x = x + Vma_tab_size*0.001;
            xseg1[j].y = y + Vma_tab_size*0.001;
            j++;
            xseg1[j].x = xseg1[j-1].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-1].y - Vma_tab_size*0.0002;
            j++;
            xseg1[j].x = xseg1[j-2].x;
            xseg1[j].y = xseg1[j-2].y;
            j++;
            xseg1[j].x = xseg1[j-3].x - Vma_tab_size*0.0006;
            xseg1[j].y = xseg1[j-3].y + Vma_tab_size*0.0002;
            j++;
            gpl(5,xseg1);

            //left side arrow mark	
            j = 0;
            xseg[j].x = x + Vma_tab_size*0.004;
            xseg[j].y = y + Vma_tab_size*0.001 ;
            j++;
            xseg[j].x = x + Vma_tab_size*0.001;
            xseg[j].y = y + Vma_tab_size*0.001;
            j++;
            xseg[j].x = xseg[j-1].x + Vma_tab_size*0.0006;
            xseg[j].y = xseg[j-1].y - Vma_tab_size*0.0002;
            j++;
            xseg[j].x = xseg[j-2].x;
            xseg[j].y = xseg[j-2].y;
            j++;
            xseg[j].x = xseg[j-3].x + Vma_tab_size*0.0006;
            xseg[j].y = xseg[j-3].y + Vma_tab_size*0.0002;
            j++;
            gpl(5,xseg);	

          }


        }
        break;




        //w79

      case 79:


        gsfais(GSOLID);
        for (i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; 
          j = 0,k=0;
          s = Vma_tab_size/1000;
          // start of solid circle 		
          x = x;
          y = y + Vma_tab_size*0.0004;
          angle1 = 0; 
          j = 0;
          s = Vma_tab_size/8000;//set size of circle
          n = 20;
          add_angle = PI_V/n ; 
          for( k = 0 ; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg1);	

          // setting regular triangle position
          j = 0;
          y = pe.y;
          xseg[j].x = x;
          xseg[j].y = y;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y;
          j++;
          xseg[j].x = x ;
          xseg[j].y = y + Vma_tab_size*0.001;
          j++;
          xseg[j].x = x + Vma_tab_size*0.001;
          xseg[j].y = y; 
          j++;
          xseg[j].x = x;
          xseg[j].y = y;
          j++;
          gpl(5, xseg);


        }
        break;





        //w80
      case 80:


        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0,k = 0;

          // code for invert triangle
          xseg[j].x = x; 
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x ;
          xseg[j].y = y;
          j++;
          xseg[j].x = x + Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          gpl(5, xseg);

          y = y + Vma_tab_size*0.003; // setting circle position
          gsfais(GSOLID);                                                   
          n = 20; 
          j = 0; 
          s = Vma_tab_size/2000;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg2);

          // end of solid circle

        }
        break;






        //w82
      case 82:


        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; 
          j = 0, k = 0;

          // code for invert triangle
          xseg[j].x = x;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x;
          xseg[j].y = y;
          j++;
          xseg[j].x = x + Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          gpl(5, xseg);


          y = y + Vma_tab_size*0.0028; // setting circle position
          gsfais(GSOLID);                                                   
          n = 20;
          j = 0;
          s = Vma_tab_size/2000;
          add_angle=PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg2);

          // end of solid circle

          // top most circle
          y = y + Vma_tab_size*0.0012; // setting top most circle position
          gsfais(GSOLID);                                                   
          n = 20;
          j = 0;
          s = Vma_tab_size/2000;
          add_angle=PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg1);

          // end of solid circle



        }
        break;





        //w81
      case 81:


        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; 
          j = 0, k = 0;

          // code for invert triangle
          xseg[j].x = x;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x ;
          xseg[j].y = y;
          j++;
          xseg[j].x = x + Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          gpl(5, xseg);

          // code for horizontal line inside triangle
          j = 0;
          xseg1[j].x = x - Vma_tab_size*0.0007;
          xseg1[j].y = y + Vma_tab_size*0.0014;
          j++;
          xseg1[j].x = x + Vma_tab_size*0.0007;
          xseg1[j].y = y + Vma_tab_size*0.0014;
          j++;
          gpl(2, xseg1);

          y = y + Vma_tab_size*0.003; // setting circle position
          gsfais(GSOLID);                                                   
          n = 20;
          j = 0;
          s = Vma_tab_size/2000;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg2);

          // end of solid circle

        }
        break;





        //w83
      case 83:



        // star initialization 
        s = Vma_tab_size/2000;//size of star
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;




        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; 
          j = 0, k = 0;

          // code for invert triangle
          xseg[j].x = x;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x;
          xseg[j].y = y;
          j++;
          xseg[j].x = x + Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          gpl(5, xseg);

          // start of  top star

          y = y + Vma_tab_size*0.0028;//setting star position
          j = 0, k = 0;

          xseg3[0].x = x + star1[0].x;
          xseg3[0].y = y + star1[0].y;
          xseg3[1].x = x + star1[1].x;
          xseg3[1].y = y + star1[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star2[0].x;
          xseg3[0].y = y + star2[0].y;
          xseg3[1].x = x + star2[1].x;
          xseg3[1].y = y + star2[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star3[0].x;
          xseg3[0].y = y + star3[0].y;
          xseg3[1].x = x + star3[1].x;
          xseg3[1].y = y + star3[1].y;
          gpl(2, xseg3);

          // end of  top star	

          // top most circle
          y = y+ Vma_tab_size*0.0012; // setting top most circle position
          gsfais(GSOLID);                                                   
          n = 20;
          j = 0;
          s = Vma_tab_size/2000;
          add_angle = PI_V/n ; 
          for( k =0 ; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg1[j].x = x + s*cos(angle1);
            xseg1[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg1);

          // end of solid circle

        }
        break;





        //w84
      case 84:

        // star initialization 
        s = Vma_tab_size/2000;//size of star
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;

        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; 
          j = 0, k = 0;

          // code for invert triangle
          xseg[j].x = x ;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x ;
          xseg[j].y = y ;
          j++;
          xseg[j].x = x + Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          gpl(5, xseg);

          // code for horizontal line inside triangle
          j = 0;
          xseg1[j].x = x - Vma_tab_size*0.0007;
          xseg1[j].y = y+ Vma_tab_size*0.0014;
          j++;
          xseg1[j].x = x + Vma_tab_size*0.0007;
          xseg1[j].y = y +Vma_tab_size*0.0014;
          j++;
          gpl(2, xseg1);


          // start of  top star
          y = y + Vma_tab_size*0.0028;//setting star position
          j = 0, k = 0;

          xseg3[0].x = x + star1[0].x;
          xseg3[0].y = y + star1[0].y;
          xseg3[1].x = x + star1[1].x;
          xseg3[1].y = y + star1[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star2[0].x;
          xseg3[0].y = y + star2[0].y;
          xseg3[1].x = x + star2[1].x;
          xseg3[1].y = y + star2[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star3[0].x;
          xseg3[0].y = y + star3[0].y;
          xseg3[1].x = x + star3[1].x;
          xseg3[1].y = y + star3[1].y;
          gpl(2, xseg3);

          // end of  top star	


          // top most circle
          y = y + Vma_tab_size*0.0012; // setting top most circle position
          gsfais(GSOLID);                                                   
          n = 20;
          j = 0;
          s = Vma_tab_size/2000;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg2);

          // end of solid circle


        }
        break;




        //w85
      case 85:



        // star initialization 
        s = Vma_tab_size/2000;//size of star
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;




        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          j = 0, k = 0;

          // code for invert triangle
          xseg[j].x = x;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x ;
          xseg[j].y = y ;
          j++;
          xseg[j].x = x + Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          gpl(5, xseg);


          // start of  top star
          y = y + Vma_tab_size*0.0028;//setting star position
          j = 0, k = 0;

          xseg3[0].x = x + star1[0].x;
          xseg3[0].y = y + star1[0].y;
          xseg3[1].x = x + star1[1].x;
          xseg3[1].y = y + star1[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star2[0].x;
          xseg3[0].y = y + star2[0].y;
          xseg3[1].x = x + star2[1].x;
          xseg3[1].y = y + star2[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star3[0].x;
          xseg3[0].y = y + star3[0].y;
          xseg3[1].x = x + star3[1].x;
          xseg3[1].y = y + star3[1].y;
          gpl(2, xseg3);

          // end of  top star	

        }
        break;



        //w86
      case 86:


        // star initialization 
        s = Vma_tab_size/2000;//size of star
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;




        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          j = 0, k = 0;

          // code for invert triangle
          xseg[j].x = x;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x ;
          xseg[j].y = y ;
          j++;
          xseg[j].x = x + Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          gpl(5, xseg);

          // code for horizontal line inside triangle
          j = 0;
          xseg1[j].x = x - Vma_tab_size*0.0007;
          xseg1[j].y = y + Vma_tab_size*0.0014;
          j++;
          xseg1[j].x = x + Vma_tab_size*0.0007;
          xseg1[j].y = y + Vma_tab_size*0.0014;
          j++;
          gpl(2, xseg1);


          // start of  top star
          y = y + Vma_tab_size*0.0028;//setting star position
          j = 0, k = 0;

          xseg3[0].x = x + star1[0].x;
          xseg3[0].y = y + star1[0].y;
          xseg3[1].x = x + star1[1].x;
          xseg3[1].y = y + star1[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star2[0].x;
          xseg3[0].y = y + star2[0].y;
          xseg3[1].x = x + star2[1].x;
          xseg3[1].y = y + star2[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star3[0].x;
          xseg3[0].y = y + star3[0].y;
          xseg3[1].x = x + star3[1].x;
          xseg3[1].y = y + star3[1].y;
          gpl(2, xseg3);

          // end of  top star	

        }
        break;





        //w87
      case 87:


        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          j = 0, k = 0;
          s = Vma_tab_size/1000;

          // code for invert triangle
          xseg[j].x = x;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x ; 
          xseg[j].y = y;
          j++;
          xseg[j].x = x + Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          gpl(5, xseg);


          y = y + Vma_tab_size*0.0025; // setting regular triangle [top] position
          j = 0;
          xseg2[j].x = x;
          xseg2[j].y = y;
          j++;
          xseg2[j].x = x - Vma_tab_size*0.001;
          xseg2[j].y = y;
          j++;
          xseg2[j].x = x;
          xseg2[j].y = y + Vma_tab_size*0.001;
          j++;
          xseg2[j].x = x + Vma_tab_size*0.001;
          xseg2[j].y = y ;
          j++;
          xseg2[j].x = x;
          xseg2[j].y = y;
          j++;
          gpl(5, xseg2);

        }
        break;





        //w88
      case 88:


        for (i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          j = 0, k = 0;
          s = Vma_tab_size/1000;

          // code for invert triangle
          xseg[j].x = x;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x;
          xseg[j].y = y;
          j++;
          xseg[j].x = x + Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          gpl(5, xseg);

          // code for horizontal line inside triangle
          j = 0;
          xseg1[j].x = x - Vma_tab_size*0.0007;
          xseg1[j].y = y + Vma_tab_size*0.0014;
          j++;
          xseg1[j].x = x + Vma_tab_size*0.0007;
          xseg1[j].y = y + Vma_tab_size*0.0014;
          j++;
          gpl(2, xseg1);

          y = y + Vma_tab_size*0.0025; // setting regular triangle [top] position
          j = 0;
          xseg2[j].x = x;
          xseg2[j].y = y;
          j++;
          xseg2[j].x = x - Vma_tab_size*0.001;
          xseg2[j].y = y;
          j++;
          xseg2[j].x = x;
          xseg2[j].y = y + Vma_tab_size*0.001;
          j++;
          xseg2[j].x = x + Vma_tab_size*0.001;
          xseg2[j].y = y;
          j++;
          xseg2[j].x = x;
          xseg2[j].y = y;
          j++;
          gpl(5, xseg2);

        }
        break;





        //w89
      case 89:


        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          j = 0, k = 0;
          s = Vma_tab_size/1000;

          // code for invert triangle

          xseg[j].x = x;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x;
          xseg[j].y = y;
          j++;
          xseg[j].x = x + Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          gpl(5, xseg);

          gsfais(GSOLID); 
          y = y + Vma_tab_size*0.0025; // setting regular triangle [top] position
          j = 0;
          xseg2[j].x = x;
          xseg2[j].y = y;
          j++;
          xseg2[j].x = x - Vma_tab_size*0.001;
          xseg2[j].y = y;
          j++;
          xseg2[j].x = x;
          xseg2[j].y = y + Vma_tab_size*0.001;
          j++;
          xseg2[j].x = x + Vma_tab_size*0.001;
          xseg2[j].y = y;
          j++;
          xseg2[j].x = x;
          xseg2[j].y = y;
          j++;
          gfa(5, xseg2);

        }
        break;




        //w90
      case 90:


        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          j = 0, k = 0;
          s = Vma_tab_size/1000;

          // code for invert triangle
          xseg[j].x = x;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x;
          xseg[j].y = y;
          j++;
          xseg[j].x = x + Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          gpl(5, xseg);

          // code for horizontal line inside triangle
          j = 0;
          xseg1[j].x = x - Vma_tab_size*0.0007;
          xseg1[j].y = y + Vma_tab_size*0.0014;
          j++;
          xseg1[j].x = x + Vma_tab_size*0.0007;
          xseg1[j].y = y + Vma_tab_size*0.0014;
          j++;
          gpl(2, xseg1);

          gsfais(GSOLID); 
          y = y + Vma_tab_size*0.0025; // setting regular triangle [top] position
          j = 0;
          xseg2[j].x = x;
          xseg2[j].y = y;
          j++;
          xseg2[j].x = x - Vma_tab_size*0.001;
          xseg2[j].y = y;
          j++;
          xseg2[j].x = x;
          xseg2[j].y = y + Vma_tab_size*0.001;
          j++;
          xseg2[j].x = x + Vma_tab_size*0.001;
          xseg2[j].y = y;
          j++;
          xseg2[j].x = x;
          xseg2[j].y = y;
          j++;
          gfa(5, xseg2);

        }
        break;





        //w91
      case 91:


        // code of w17
        // its part of w13 and other few lines
        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; 
          j = 0, k = 0;
          s = Vma_tab_size/1000;

          //code for w13
          j = 0;
          xseg[j].x = x;
          tempy = xseg[j].y = y;
          j++;

          // code for left down line
          tempx = xseg[j].x = x - Vma_tab_size*0.0010;
          tempy = xseg[j].y = y - Vma_tab_size*0.0010;
          j++;

          // code for right down line
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          // code for arrow
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;
          xseg[j].x = xseg[j-1].x;
          xseg[j].y = xseg[j-1].y + Vma_tab_size*0.0003;
          j++;
          xseg[j].x = xseg[j-2].x;
          xseg[j].y = xseg[j-2].y;
          j++;
          xseg[j].x = xseg[j-3].x - Vma_tab_size*0.0004;
          xseg[j].y = xseg[j-3].y;
          j++;
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          gpl(8,xseg);

          // code for top horizontal line
          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.0024;
          xseg1[j].y = y;
          j++;

          // code for vertical line
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y - Vma_tab_size*0.002;
          j++;
          gpl(4,xseg1);

          // code for right side line
          y = y - Vma_tab_size*0.0025;
          x = x + Vma_tab_size*0.0005;
          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x + Vma_tab_size*0.001; 
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x + Vma_tab_size*0.001;
          xseg1[j].y = y + Vma_tab_size*0.003;
          j++;
          xseg1[j].x = x;
          xseg1[j].y = y + Vma_tab_size*0.003;
          j++;
          gpl(4, xseg1);

          //code for solid circle
          x = x + Vma_tab_size*0.002;
          y = y + Vma_tab_size*0.0015; // setting circle position
          gsfais(GSOLID);                                                   
          n = 20;
          j =0 ;
          s = Vma_tab_size/2000;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg2);


        }

        break;





        //w92
      case 92:


        // code of w17
        // its part of w13 and other few lines
        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; 
          j = 0, k = 0;
          s = Vma_tab_size/1000;

          //code for w13
          j = 0;
          xseg[j].x = x;
          tempy = xseg[j].y = y;
          j++;

          // code for left down line
          tempx = xseg[j].x = x - Vma_tab_size*0.0010;
          tempy = xseg[j].y = y - Vma_tab_size*0.0010;
          j++;

          // code for right down line
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          // code for arrow
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          xseg[j].x = xseg[j-1].x;
          xseg[j].y = xseg[j-1].y + Vma_tab_size*0.0003;
          j++;

          xseg[j].x = xseg[j-2].x;
          xseg[j].y = xseg[j-2].y;
          j++;

          xseg[j].x = xseg[j-3].x - Vma_tab_size*0.0004;
          xseg[j].y = xseg[j-3].y;
          j++;

          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          gpl(8,xseg);

          // code for top horizontal line
          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.0024;
          xseg1[j].y = y;
          j++;

          // code for vertical line
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y - Vma_tab_size*0.002;
          j++;
          gpl(4,xseg1);

          // code for right side line
          y = y - Vma_tab_size*0.0025;
          x = x + Vma_tab_size*0.0005;

          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x + Vma_tab_size*0.001;
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001;
          xseg1[j].y = y + Vma_tab_size*0.003;
          j++;

          xseg1[j].x = x; 
          xseg1[j].y = y + Vma_tab_size*0.003; 
          j++;
          gpl(4, xseg1);

          //code for solid top circle
          x = x + Vma_tab_size*0.002;
          y = y+ Vma_tab_size*0.0022; // setting top circle position
          gsfais(GSOLID);                                                   
          n = 20;
          j = 0; 
          s = Vma_tab_size/2000;
          add_angle=PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg2);

          //end code for solid top circle


          //code for solid bottom circle

          y = y - Vma_tab_size*0.0012; // setting bottom circle position
          gsfais(GSOLID);                                                   
          n = 20;
          j = 0; 
          s = Vma_tab_size/2000;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg3[j].x = x + s*cos(angle1);
            xseg3[j].y = y+ s*sin(angle1);
            j++;
          }
          gfa(41, xseg3);

          //end for solid bottom circle

        }

        break;




        //w93
      case 93:


        // star initialization 
        s = Vma_tab_size/2000;//size of star
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;


        // code of w17
        // its part of w13 and other few lines
        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0, k = 0;
          s = Vma_tab_size/1000;

          //code for w13
          j = 0;
          xseg[j].x = x;
          tempy = xseg[j].y = y;
          j++;

          // code for left down line
          tempx = xseg[j].x = x - Vma_tab_size*0.0010;
          tempy = xseg[j].y = y - Vma_tab_size*0.0010;
          j++;

          // code for right down line
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          // code for arrow
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          xseg[j].x = xseg[j-1].x;
          xseg[j].y = xseg[j-1].y + Vma_tab_size*0.0003;j++;


          xseg[j].x = xseg[j-2].x;
          xseg[j].y = xseg[j-2].y;
          j++;
          xseg[j].x = xseg[j-3].x - Vma_tab_size*0.0004;
          xseg[j].y = xseg[j-3].y;
          j++;
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          gpl(8,xseg);

          // code for top horizontal line
          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.0024;
          xseg1[j].y = y;
          j++;

          // code for vertical line
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y - Vma_tab_size*0.002;
          j++;
          gpl(4,xseg1);


          // code for right side line
          y = y - Vma_tab_size*0.0025;
          x = x + Vma_tab_size*0.0005;
          j = 0 ;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x + Vma_tab_size*0.001;
          xseg1[j].y = y;
          j++;

          xseg1[j].x = x + Vma_tab_size*0.001;
          xseg1[j].y = y + Vma_tab_size*0.003;
          j++;

          xseg1[j].x = x;
          xseg1[j].y = y + Vma_tab_size*0.003; 
          j++;
          gpl(4, xseg1);


          // start of  top star
          x = x + Vma_tab_size*0.002;//setting star position
          y = y + Vma_tab_size*0.0022; 
          j = 0, k = 0;

          xseg3[0].x = x + star1[0].x;
          xseg3[0].y = y + star1[0].y;
          xseg3[1].x = x + star1[1].x;
          xseg3[1].y = y + star1[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star2[0].x;
          xseg3[0].y = y + star2[0].y;
          xseg3[1].x = x + star2[1].x;
          xseg3[1].y = y + star2[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star3[0].x;
          xseg3[0].y = y + star3[0].y;
          xseg3[1].x = x + star3[1].x;
          xseg3[1].y = y + star3[1].y;
          gpl(2, xseg3);

          // end of  top star


          // code for cross line

          xseg2[0].x = x + Vma_tab_size*0.0015;
          xseg2[0].y = y; 
          xseg2[1].x = x - Vma_tab_size*0.0005;
          xseg2[1].y = y - Vma_tab_size*0.001; 
          gpl(2, xseg2);

          // code for triangle
          x = x + Vma_tab_size*0.0005;
          y = y - Vma_tab_size*0.002; // setting regular triangle [top] position
          j = 0;
          xseg4[j].x = x;
          xseg4[j].y = y;
          j++;
          xseg4[j].x = x - Vma_tab_size*0.0008;
          xseg4[j].y = y; 
          j++;
          xseg4[j].x = x;
          xseg4[j].y = y + Vma_tab_size*0.0008;
          j++;
          xseg4[j].x = x + Vma_tab_size*0.0008;
          xseg4[j].y = y;
          j++;
          xseg4[j].x = x;
          xseg4[j].y = y;
          j++;
          gpl(5, xseg4);


        }

        break;






        //w94
      case 94:


        // star initialization 
        s = Vma_tab_size/2000;//size of star
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;


        // code of w17
        // its part of w13 and other few lines
        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0, k = 0;
          s = Vma_tab_size/1000;

          //code for w13
          j = 0;
          xseg[j].x = x;
          tempy = xseg[j].y = y;
          j++;

          // code for left down line
          tempx = xseg[j].x = x - Vma_tab_size*0.0010;
          tempy = xseg[j].y = y - Vma_tab_size*0.0010;
          j++;

          // code for right down line
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          // code for arrow
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          xseg[j].x = xseg[j-1].x;
          xseg[j].y = xseg[j-1].y + Vma_tab_size*0.0003;
          j++;


          xseg[j].x = xseg[j-2].x;
          xseg[j].y = xseg[j-2].y;
          j++;
          xseg[j].x = xseg[j-3].x - Vma_tab_size*0.0004;
          xseg[j].y = xseg[j-3].y;
          j++;
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          gpl(8,xseg);

          // code for top horizontal line
          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.0024;
          xseg1[j].y = y;
          j++;

          // code for vertical line
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y - Vma_tab_size*0.002;
          j++;
          gpl(4,xseg1);

          // code for right side line
          y = y- Vma_tab_size*0.0025;
          x = x + Vma_tab_size*0.0005;
          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x + Vma_tab_size*0.001;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x + Vma_tab_size*0.001;
          xseg1[j].y = y + Vma_tab_size*0.003;
          j++;
          xseg1[j].x = x;
          xseg1[j].y = y + Vma_tab_size*0.003;
          j++;
          gpl(4, xseg1);


          // start of  top star
          x = x + Vma_tab_size*0.002;//setting star position
          y = y + Vma_tab_size*0.0032; 
          j = 0, k = 0;

          xseg3[0].x = x + star1[0].x;
          xseg3[0].y = y + star1[0].y;
          xseg3[1].x = x + star1[1].x;
          xseg3[1].y = y + star1[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star2[0].x;
          xseg3[0].y = y + star2[0].y;
          xseg3[1].x = x + star2[1].x;
          xseg3[1].y = y + star2[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star3[0].x;
          xseg3[0].y = y + star3[0].y;
          xseg3[1].x = x + star3[1].x;
          xseg3[1].y = y + star3[1].y;
          gpl(2, xseg3);

          // end of  top star

          // start of  bottom star
          //setting bottom position
          y = y - Vma_tab_size*0.001; 
          j = 0, k = 0;

          xseg3[0].x = x + star1[0].x;
          xseg3[0].y = y + star1[0].y;
          xseg3[1].x = x + star1[1].x;
          xseg3[1].y = y + star1[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star2[0].x;
          xseg3[0].y = y + star2[0].y;
          xseg3[1].x = x + star2[1].x;
          xseg3[1].y = y + star2[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star3[0].x;
          xseg3[0].y = y + star3[0].y;
          xseg3[1].x = x + star3[1].x;
          xseg3[1].y = y + star3[1].y;
          gpl(2, xseg3);

          // end of  bottom star


          // code for cross line

          xseg2[0].x = x + Vma_tab_size*0.0015;
          xseg2[0].y = y; 
          xseg2[1].x = x - Vma_tab_size*0.0005;
          xseg2[1].y = y - Vma_tab_size*0.001; 
          gpl(2, xseg2);

          // code for top triangle
          x = x + Vma_tab_size*0.0005;
          y = y - Vma_tab_size*0.0015; // setting regular triangle [top] position
          j = 0;
          xseg4[j].x = x; 
          xseg4[j].y = y;
          j++;
          xseg4[j].x = x - Vma_tab_size*0.0005;
          xseg4[j].y = y;
          j++;
          xseg4[j].x = x;
          xseg4[j].y = y + Vma_tab_size*0.0008;
          j++;
          xseg4[j].x = x + Vma_tab_size*0.0008;
          xseg4[j].y = y;
          j++;
          xseg4[j].x = x;
          xseg4[j].y = y;
          j++;
          gpl(5, xseg4);

          // code for bottom triangle
          y = y - Vma_tab_size*0.001; // setting regular triangle [bottom] position
          j = 0;
          xseg4[j].x = x; 
          xseg4[j].y = y;
          j++;
          xseg4[j].x = x - Vma_tab_size*0.0008;
          xseg4[j].y = y;
          j++;
          xseg4[j].x = x ;
          xseg4[j].y = y + Vma_tab_size*0.0008;
          j++;
          xseg4[j].x = x + Vma_tab_size*0.0008;
          xseg4[j].y = y ;
          j++;
          xseg4[j].x = x;
          xseg4[j].y = y;
          j++;
          gpl(5, xseg4);

        }

        break;




        //w95
      case 95:


        // star initialization 
        s = Vma_tab_size/2000;//size of star
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;


        // code of w17
        // its part of w13 and other few lines
        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0,k = 0;
          s = Vma_tab_size/1000;

          //code for w13
          j = 0;
          xseg[j].x = x;
          tempy = xseg[j].y = y;
          j++;

          // code for left down line
          tempx = xseg[j].x = x - Vma_tab_size*0.0010;
          tempy = xseg[j].y = y - Vma_tab_size*0.0010;
          j++;

          // code for right down line
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          // code for arrow
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          xseg[j].x = xseg[j-1].x;
          xseg[j].y = xseg[j-1].y + Vma_tab_size*0.0003;
          j++;

          xseg[j].x = xseg[j-2].x;
          xseg[j].y = xseg[j-2].y;
          j++;
          xseg[j].x = xseg[j-3].x - Vma_tab_size*0.0004;
          xseg[j].y = xseg[j-3].y;
          j++;
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          gpl(8,xseg);

          // code for top horizontal line
          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.0024;
          xseg1[j].y = y;
          j++;

          // code for vertical line
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y - Vma_tab_size*0.002;
          j++;
          gpl(4,xseg1);


          //code for solid circle
          x = x - Vma_tab_size*0.002;
          y = y + Vma_tab_size*0.0008; // setting circle position
          gsfais(GSOLID);                                                   
          n = 20;
          j = 0;
          s = Vma_tab_size/2000;
          add_angle=PI_V/n ; 
          for( k = 0 ; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg2);

          // code for cross line
          xseg3[0].x = x + Vma_tab_size*0.0014;
          xseg3[0].y = y + Vma_tab_size*0.0005; 
          xseg3[1].x = x + Vma_tab_size*0.0004;
          xseg3[1].y = y - Vma_tab_size*0.0005; 
          gpl(2, xseg3);

          // start of star
          x = x + Vma_tab_size*0.002; 
          j = 0, k = 0;

          xseg3[0].x = x + star1[0].x;
          xseg3[0].y = y + star1[0].y;
          xseg3[1].x = x + star1[1].x;
          xseg3[1].y = y + star1[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star2[0].x;
          xseg3[0].y = y + star2[0].y;
          xseg3[1].x = x + star2[1].x;
          xseg3[1].y = y + star2[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star3[0].x;
          xseg3[0].y = y + star3[0].y;
          xseg3[1].x = x + star3[1].x;
          xseg3[1].y = y + star3[1].y;
          gpl(2, xseg3);

          // end of  bottom star


        }
        break;





        //w96
      case 96:


        // code of w17
        // its part of w13 and other few lines
        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          j = 0, k = 0;
          s = Vma_tab_size/1000;

          //code for w13
          j = 0;
          xseg[j].x = x;
          tempy = xseg[j].y = y;
          j++;

          // code for left down line
          tempx = xseg[j].x = x - Vma_tab_size*0.0010;
          tempy = xseg[j].y = y - Vma_tab_size*0.0010;
          j++;

          // code for right down line
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          // code for arrow
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y- Vma_tab_size*0.0020;
          j++;

          xseg[j].x = xseg[j-1].x;
          xseg[j].y = xseg[j-1].y + Vma_tab_size*0.0003;
          j++;

          xseg[j].x=xseg[j-2].x;
          xseg[j].y=xseg[j-2].y;j++;
          xseg[j].x=xseg[j-3].x-Vma_tab_size*0.0004;
          xseg[j].y=xseg[j-3].y;
          j++;
          xseg[j].x=x+Vma_tab_size*0.0001;
          xseg[j].y=y-Vma_tab_size*0.0020;
          j++;

          gpl(8,xseg);



          // code for top horizontal line
          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.0024;
          xseg1[j].y = y;
          j++;

          // code for vertical line
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y - Vma_tab_size*0.002;
          j++;
          gpl(4,xseg1);

          // code for triangle
          x = x - Vma_tab_size*0.0012;
          y = y + Vma_tab_size*0.0008; // setting regular triangle [top] position

          j = 0;
          xseg4[j].x = x;
          xseg4[j].y = y;
          j++;
          xseg4[j].x = x - Vma_tab_size*0.0005;
          xseg4[j].y = y;
          j++;
          xseg4[j].x = x;
          xseg4[j].y = y + Vma_tab_size*0.0005;
          j++;
          xseg4[j].x = x + Vma_tab_size*0.0005;
          xseg4[j].y = y;
          j++;
          xseg4[j].x = x;
          xseg4[j].y = y;
          j++;
          gpl(5, xseg4);



        }

        break;






        //w97
      case 97:



        // star initialization 
        s = Vma_tab_size/2000;//size of star
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;


        // code of w17
        // its part of w13 and other few lines
        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0,k=0;
          s = Vma_tab_size/1000;

          //code for w13
          j = 0;
          xseg[j].x = x;
          tempy = xseg[j].y = y;
          j++;

          // code for left down line
          tempx = xseg[j].x = x - Vma_tab_size*0.0010;
          tempy = xseg[j].y = y - Vma_tab_size*0.0010;
          j++;

          // code for right down line
          xseg[j].x = x;
          xseg[j].y = y - Vma_tab_size*0.0015;
          j++;

          // code for again pending left down line
          tempx = xseg[j].x = x - Vma_tab_size*0.001;
          tempy = xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          // code for arrow
          xseg[j].x = xseg[j-1].x + Vma_tab_size*0.0001;
          xseg[j].y = xseg[j-1].y + Vma_tab_size*0.0003;
          j++;
          gpl(5,xseg);

          xseg[0].x = tempx;
          xseg[0].y = tempy;
          j++;
          xseg[1].x = tempx + Vma_tab_size*0.0004;
          xseg[1].y = tempy;
          Vma_tab_size*0.0001;
          j++;
          gpl(2,xseg);

          // code for top horizontal line
          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.0024;
          xseg1[j].y = y;
          j++;

          // code for vertical line
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y - Vma_tab_size*0.002;
          j++;
          gpl(4,xseg1);


          //code for solid circle
          x = x - Vma_tab_size*0.002;
          y = y + Vma_tab_size*0.0008; // setting circle position
          gsfais(GSOLID);                                                   
          n = 20;
          j = 0;
          s = Vma_tab_size/2000;
          add_angle = PI_V/n ; 
          for( k = 0; k <=2*n; k++){
            angle1 = k*add_angle;
            xseg2[j].x = x + s*cos(angle1);
            xseg2[j].y = y + s*sin(angle1);
            j++;
          }
          gfa(41, xseg2);

          // code for cross line
          xseg3[0].x = x + Vma_tab_size*0.0014;
          xseg3[0].y = y + Vma_tab_size*0.0005; 
          xseg3[1].x = x + Vma_tab_size*0.0004;
          xseg3[1].y = y - Vma_tab_size*0.0005; 
          gpl(2, xseg3);


          // start of star
          x = x + Vma_tab_size*0.002; 
          j = 0, k = 0;

          xseg3[0].x = x + star1[0].x;
          xseg3[0].y = y + star1[0].y;
          xseg3[1].x = x + star1[1].x;
          xseg3[1].y = y + star1[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star2[0].x;
          xseg3[0].y = y + star2[0].y;
          xseg3[1].x = x + star2[1].x;
          xseg3[1].y = y + star2[1].y;
          gpl(2, xseg3);
          xseg3[0].x = x + star3[0].x;
          xseg3[0].y = y + star3[0].y;
          xseg3[1].x = x + star3[1].x;
          xseg3[1].y = y + star3[1].y;
          gpl(2, xseg3);

          // end of  bottom star


        }
        break;



        //w98
      case 98:



        // star initialization 
        s = Vma_tab_size/2000;//size of star
        star1[0].x = -s;
        star1[0].y = 0;
        star1[1].x = s;
        star1[1].y = 0;
        star2[0].x = s * 0.5;
        star2[0].y = s * 0.866;
        star2[1].x = -s * 0.5;
        star2[1].y = -s * 0.866;
        star3[0].x = s * 0.5;
        star3[0].y = -s * 0.866;
        star3[1].x = -s * 0.5;
        star3[1].y = s * 0.866;


        // code of w17
        // its part of w13 and other few lines
        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0, k = 0;

          //code for w13
          j = 0;
          xseg[j].x = x;
          tempy = xseg[j].y = y;
          j++;

          // code for left down line
          tempx = xseg[j].x = x - Vma_tab_size*0.0010;
          tempy = xseg[j].y = y - Vma_tab_size*0.0010;
          j++;

          // code for right down line
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          // code for arrow
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y -  Vma_tab_size*0.0020;
          j++;

          xseg[j].x = xseg[j-1].x;
          xseg[j].y = xseg[j-1].y + Vma_tab_size*0.0003;
          j++;

          xseg[j].x = xseg[j-2].x;
          xseg[j].y = xseg[j-2].y;
          j++;
          xseg[j].x = xseg[j-3].x - Vma_tab_size*0.0004;
          xseg[j].y = xseg[j-3].y;
          j++;
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          gpl(8,xseg);



          // code for top horizontal line
          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.0024;
          xseg1[j].y = y;
          j++;

          // code for vertical line
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y - Vma_tab_size*0.002;
          j++;
          gpl(4,xseg1);


          // code for w31
          x = x - Vma_tab_size*0.0012;
          y = y + Vma_tab_size*0.002; // setting S position


          // code of w09
          //code for "S"
          n = 20;
          s = Vma_tab_size/2000;j=0;
          add_angle = PI_V/n ;
          for( k = 0; k <n+(n/2); k++){
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }
          tempx = xseg[j-1].x;
          tempy = xseg[j-1].y;
          y = y - Vma_tab_size*0.001;
          add_angle = PI_V/n ;
          for( k = n/2; k >-(n); k--){
            angle1 = k*add_angle;
            xseg[j].x = x + s*cos(angle1);
            xseg[j].y = y + s*sin(angle1);
            j++;
          }

          gpl(60,xseg);


          //code for horizontal right hand arrow mark         
          {         
            // x = pe.x;
            y = y + Vma_tab_size*0.0025;
            j = 0;
            startx = xseg1[j].x = tempx - Vma_tab_size*0.001;
            starty = xseg1[j].y = tempy;
            j++;
            xseg1[j].x = tempx + Vma_tab_size*0.001;
            xseg1[j].y = tempy;
            j++;
            xseg1[j].x = xseg1[j-1].x - Vma_tab_size*0.0003;
            xseg1[j].y = xseg1[j-1].y - Vma_tab_size*0.0003;
            j++;
            xseg1[j].x = xseg1[j-2].x;
            xseg1[j].y = xseg1[j-2].y;
            j++;
            xseg1[j].x = xseg1[j-3].x - Vma_tab_size*0.0003;
            xseg1[j].y = xseg1[j-3].y + Vma_tab_size*0.0003;
            j++;

            gpl(5,xseg1);

          }


        }

        break;





        //w99
      case 99:


        // code of w17
        // its part of w13 and other few lines
        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0, k = 0;
          s = Vma_tab_size/1000;

          //code for w13
          j = 0;
          xseg[j].x = x;
          tempy = xseg[j].y = y;
          j++;

          // code for left down line
          tempx = xseg[j].x = x - Vma_tab_size*0.0010;
          tempy = xseg[j].y = y - Vma_tab_size*0.0010;
          j++;

          // code for right down line
          xseg[j].x = x;
          xseg[j].y = y - Vma_tab_size*0.0015;
          j++;

          // code for again pending left down line
          tempx = xseg[j].x = x - Vma_tab_size*0.001;
          tempy = xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          // code for arrow
          xseg[j].x = xseg[j-1].x + Vma_tab_size*0.0001;
          xseg[j].y = xseg[j-1].y + Vma_tab_size*0.0003;
          j++;
          gpl(5,xseg);

          xseg[0].x = tempx;
          xseg[0].y = tempy;
          j++;
          xseg[1].x =tempx +Vma_tab_size*0.0004;
          xseg[1].y =tempy;Vma_tab_size*0.0001;
          j++;
          gpl(2,xseg);



          // code for top horizontal line
          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.0024;
          xseg1[j].y = y;
          j++;

          // code for vertical line
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y - Vma_tab_size*0.002;
          j++;
          gpl(4,xseg1);


          // code for triangle
          x = x - Vma_tab_size*0.0012;
          y = y + Vma_tab_size*0.0008; // setting regular triangle [top] position

          j = 0;
          xseg4[j].x = x;
          xseg4[j].y = y;
          j++;
          xseg4[j].x = x - Vma_tab_size*0.0005;
          xseg4[j].y = y;
          j++;

          xseg4[j].x = x;
          xseg4[j].y = y + Vma_tab_size*0.0005;
          j++;
          xseg4[j].x = x + Vma_tab_size*0.0005;
          xseg4[j].y = y;
          j++;
          xseg4[j].x = x;
          xseg4[j].y = y;
          j++;
          gpl(5, xseg4);


        }
        break;




        //w200
      case 200:

        // its part of w13 and other few lines
        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0,k = 0;
          s = Vma_tab_size/1000;

          //code for w13
          j = 0;
          xseg[j].x = x;
          tempy = xseg[j].y = y;
          j++;

          // code for left down line
          tempx = xseg[j].x = x - Vma_tab_size*0.0010;
          tempy = xseg[j].y = y - Vma_tab_size*0.0010;
          j++;

          // code for right down line
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          // code for arrow
          xseg[j].x = x + Vma_tab_size*0.0001;
          xseg[j].y = y - Vma_tab_size*0.0020;
          j++;

          xseg[j].x = xseg[j-1].x;
          xseg[j].y = xseg[j-1].y + Vma_tab_size*0.0003;
          j++;

          xseg[j].x = xseg[j-2].x;
          xseg[j].y = xseg[j-2].y;
          j++;
          xseg[j].x = xseg[j-3].x - Vma_tab_size*0.0004;
          xseg[j].y = xseg[j-3].y;
          j++;
          xseg[j].x=x+Vma_tab_size*0.0001;
          xseg[j].y=y-Vma_tab_size*0.0020;
          j++;

          gpl(8,xseg);

          // code for top horizontal line
          j = 0;
          xseg1[j].x = x;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.0024;
          xseg1[j].y = y;
          j++;

          // code for vertical line
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y;
          j++;
          xseg1[j].x = x - Vma_tab_size*0.002;
          xseg1[j].y = y - Vma_tab_size*0.002;
          j++;
          gpl(4,xseg1);


        }

        break;





        //w201
      case 201:


        for ( i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0, k = 0;
          s = Vma_tab_size/1000;

          // code for invert triangle
          xseg[j].x = x;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y +Vma_tab_size*0.002;
          j++;
          xseg[j].x = x;
          xseg[j].y = y;
          j++;
          xseg[j].x = x + Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          xseg[j].x = x - Vma_tab_size*0.001;
          xseg[j].y = y + Vma_tab_size*0.002;
          j++;
          gpl(5, xseg);

        }
        break;




        //w202
      case 202:

        // slash 

        for (i = 0; i < npts; i++) {
          startx=   x = pe.x;
          starty=   y = pe.y;
          add_angle = PI_V/24;
          angle1 = 0; angle2 = add_angle;
          j = 0, k = 0;
          s = Vma_tab_size/1000;
          j = 0;
          xseg[0].x = x + Vma_tab_size*0.0005;
          xseg[0].y = y + Vma_tab_size*0.001;
          xseg[1].x = x - Vma_tab_size*0.0005;
          xseg[1].y = y - Vma_tab_size*0.001;
          gpl(2, xseg);
        }

        break;

      default:
        break;
    }
    /* Set the Line attributes back */
  }
}

