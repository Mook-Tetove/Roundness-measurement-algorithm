#include<stdio.h> 
#include<math.h>
#define pi 3.141592

int main()

{
         int Rceliangbi;               //测量臂长度
         int Routside[360],Rinside[360];           //测量点位（外径+内径）共360个数据
         double x[360],y[360];           //拟合坐标 
         double Rpoint[360],Rmax,Rmin;
         int Rlixiang;     //拟合半径 
         double A0=0,A1=0,B0=0,B1=0,C0=0,C1=0,C2=0,D0=0,E0=0,E1=0; 
         double A=0,B=0,C=0,D=0,E=0;
         double Aw=0,Bw=0,Cw=0,Dw=0,Ew=0; 
         double a,b,c,d,e;
         double Ox,Oy,R;
         printf("please input the length of mechanical arm:"); 
         scanf("%d",&Rceliangbi);             //输入测量臂的长度 
         int i;
         for(i=0;i<360;i++)
         {
             printf("input the length of the light(360):");                    //激光测距
             scanf("%lf",&Routside[i]);          //赋值外经 
             Rinside[i]=Rceliangbi-Routside[i];           //内径计算 
             x[i]=Rinside[i]*cos(i*pi/180);
             y[i]=Rinside[i]*sin(i*pi/180); 
          }
          int k;
          for(k=0;k<360;k++)
          {
          A0=A0+x[k]*x[k]; A1=A1+x[k];
          B0=B0+x[k]*y[k]; B1=B1+y[k];
          C0=C0+x[k]*x[k]*x[k]; C1=C1+x[k]*y[k]*y[k];
          C2=C2+x[k]*x[k]+y[k]*y[k]; D0=D0+y[k]*y[k];
          E0=E0+x[k]*x[k]*y[k];
          E1=E1+y[k]*y[k]*y[k];
          }
          Aw=360*A0; 
          Bw=360*B0;
          Cw=360*C0+360*C1; 
          Dw=360*D0;
          Ew=360*E0+360*E1;
          A=Aw-A1*A1;
          B=Bw-A1*B1; 
          C=Cw-C2*A1; 
          D=Dw+B1*B1;
          E=Ew+C2*B1;
                a=(B*E-C*D)/(A*D-B*B); 
                b=(A*E-B*C)/(A*D-B*B); 
                c=-(C2+a*A1+b*B1)/360;
         Ox=-a/2; 
         Oy=-b/2; 
         d=a*a/4; 
         e=b*b/4;
                R=sqrt((a*a/4)-(b*b/4)-c); 
         int j;
         for(j=0;j<360;j++)
         {
             Rpoint[j]=sqrt((x[j]-Ox)*(x[j]-Ox)+(y[j]-Oy)*(y[j]-Oy)); 
         }
         int n;
         Rmax=Rmin=Rpoint[0]; 
         for(n=1;n<360;n++)
         {
            if(Rpoint[n]>Rmax)
               {
                    Rmax=Rpoint[n];           //最大半径
                }
            if(Rpoint[n]<Rmin)
                {
                     Rmin=Rpoint[n];           //最小半径
                 }
             } 
             printf("The fitted radius of the circle is %f\n",R); 
             printf("The max is %f\nThe min is %f\n",Rmax,Rmin);
             return 0；
          }