#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int xa,ya,xb,yb;
int v;
int tr[3][3],input[3][10],output[3][10];

void mul(int input[3][10], int tr[3][3], int output[3][10], int v)
{ 
     for(int i=0;i<3;i++)
    {
        for(int j=0;j<v;j++)
        {  
            output[i][j]=0;
            for(int k=0; k<3;k++)
            {
                output[i][j] += tr[i][k] * input[k][j];
            }
        }
    }
}

void Matrix()
{
    printf("\nEnter no of Records: ");
    scanf("%d",&v);
   //INput MAtrix 
    for(int i=0;i<v;i++)
    {
        printf("\nX[%d]: ",i);
        scanf("%d",&input[0][i]);
        printf("\nY[%d]: ",i);
        scanf("%d",&input[1][i]);
        input[2][i]=1;
    }
    printf("\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<v;j++)
        {
            printf("\t%d",input[i][j]);
        }
        printf("\n");
    }
    
    //Translation MAtrix
    int tx,ty;
    printf("\nEnter tx: ");
    scanf("%d",&tx);
    
    printf("\nEnter ty: ");
    scanf("%d",&ty);
    for(int i=0;i<3;i++)
    {
      for(int j=0;j<3;j++)
      {
          if(i==j)
          {
            tr[i][j]=1;
          }
          else
          {
            tr[i][j]=0;
          }
      }
    }
    tr[0][2]=tx;
    tr[1][2]=ty;
     printf("\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("\t%d",tr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //output matrix
    mul(input,tr,output,v);
    
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<v;j++)
        {
            printf("\t%d",output[i][j]);
        }
        printf("\n");
    }
    
}

int ROUND(float a)
{
    return (int) (a+0.5);
}

void DDAL(int xa,int ya,int xb, int yb)
{
    int dx,dy,steps;
    dx=xb-xa;
    dy=yb-ya;
    
    if(abs(dx)>abs(dy))
    {
        steps=abs(dx);
    }
    else
    {
        steps=abs(dy);
    }
    
    glVertex2d(xa,ya);
    float xinc,yinc;
    xinc=(float)dx/steps;
    yinc=(float)dy/steps;
    
    float x=xa,y=ya;
    for(int i=0;i<steps;i++)
    {
        x=x+xinc;
        y=y+yinc;
        glVertex2d(ROUND(x),ROUND(y));
    }
}

void Draw()
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for(i=0;i<v-1;i++)
    {
        DDAL(input[0][i],input[1][i],input[0][i+1],input[1][i+1]);
    }
        DDAL(input[0][i],input[1][i],input[0][0],input[1][0]);
    glEnd();
    glFlush();
    
    usleep(500000);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for(i=0;i<v-1;i++)
    {
        DDAL(output[0][i],output[1][i],output[0][i+1],output[1][i+1]);
    }
        DDAL(output[0][i],output[1][i],output[0][0],output[1][0]);
    glEnd();
    glFlush();
}


int main(int argc,char **argv)
{
    Matrix();
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("Translation");
    glClearColor(1,1,1,0);
    glColor3f(0,0,0);
    gluOrtho2D(0,640,0,480);
    glutDisplayFunc(Draw);
    glutMainLoop();
    
    return 0;
}
