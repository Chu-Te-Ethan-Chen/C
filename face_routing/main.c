#include <stdio.h>
#include <stdlib.h>
#include <math.h>//using pow and sqrt
struct node{
    int number;
    float x;
    float y;
};

struct distance{
int p1;
int p2;
float d;
};
struct distance B[55]={};//distance between two point
struct distance C[22]={};//two points whose distance less than 1

struct point_position1{
int number;
int p1;
int p2;
float *p1x;
float *p1y;
float *p2x;
float *p2y;
};
struct point_position1 D[22]={};//two points whose distance less than 1 and their position

struct point_position2{
int number;
int p1;
int p2;
};
struct point_position2 E[11]={};//two points after deleting links

int main()
{
float c,d1,d2,Mx,My;//c: distance between two points, d1:dist between start point and middle point, d2:dist between check point and middle point, Mx, My: the x, y of middle point
int i,j,k,a,n,p,h;//h:counter for inside or outside the cycle
a=-1;//counter for array B
n=-1;//counter for array C, D
p=-1;//counter for array E
h=0;

FILE *fin, *fout;
    fin = fopen("node.txt","r");//open file
    if(fin==NULL)
    {
        printf("Error! File doesn't exist.");
        return 0;
    }
    int t=0;//t for total number
    fscanf(fin,"%d",&t);
struct node A[t];//initial position
        for(i=0;i<t;i++)
        {
        fscanf(fin,"%d",&A[i].number);
        fscanf(fin,"%f",&A[i].x);
        fscanf(fin,"%f",&A[i].y);
        }
    fclose(fin);

    for(j=0;j<10;j++)//step1:find distance between every two points. And remember points pair those distance are less than 1.
    {
        for(i=0;i<10-j;i++)
        {
        c=sqrt(pow(A[i+j+1].x - A[j].x, 2)+pow(A[i+j+1].y-A[j].y,2));
        a+=1;
        B[a].p1=j;
        B[a].p2=i+j+1;
        B[a].d=c;
        if(c <= 1)
            {
            n+=1;
            C[n].p1=j;
            C[n].p2=i+j+1;
            C[n].d=c;
            D[n].number=n;
            D[n].p1=j;
            D[n].p2=i+j+1;
            D[n].p1x=&A[j].x;
            D[n].p1y=&A[j].y;
            D[n].p2x=&A[i+j+1].x;
            D[n].p2y=&A[i+j+1].y;
            }

        }
    }

    for(i=0;i<22;i++)//step2:delete spare links
    {
        Mx=(*D[i].p1x+*D[i].p2x)/2;//x=(x1+x2)/2
        My=(*D[i].p1y+*D[i].p2y)/2;//y=(y1+y2)/2
        d1=sqrt(pow(Mx-*D[i].p1x,2)+pow(My-*D[i].p1y,2));//d1:dist between start point and middle point
        for(k=0;k<11;k++)//scan array A
        {
            if(k!=D[i].p1 && k!=D[i].p2)//considering points that are not start point and check point
            {
            d2=sqrt(pow(A[k].x-Mx,2)+pow(A[k].y-My,2));//d2:dist between check point and middle point
                if(d1>d2)//if there is point inside the cycle, record it
                {
                h++;
                }
            }
        }
        if(h==0)
        {
         p++;
         E[p].number=D[i].number;
         E[p].p1=D[i].p1;
         E[p].p2=D[i].p2;
        }
        h=0;//reset
    }

    fout = fopen("link.txt","w");//write
    if (fout==NULL)
    {
        printf("File creation failed.\n");
        return 0;
    }
    else
    {
        printf("File have successfully created");
        printf("\n");
        fprintf(fout,"%d\n",n+1);
        for(i=0;i<22;i++)
        {
        fprintf(fout,"%d\t",D[i].number);
        fprintf(fout,"%d\t",D[i].p1);
        fprintf(fout,"%d\n",D[i].p2);
        }
        fprintf(fout,"\n");
        fprintf(fout,"%d\n",p+1);
        for(i=0;i<11;i++)
        {
        fprintf(fout,"%d\t",E[i].number);
        fprintf(fout,"%d\t",E[i].p1);
        fprintf(fout,"%d\n",E[i].p2);
        }
        fclose(fout);
    }
return 0;
}
