#include<GL/glut.h>
#include<stdlib.h>
#include <stdio.h>

float bcol[3];
float fcol[3];
int input[2][10];
int v,x,y,xa,ya,xb,yb;

void Bfill(int x,int y,float bcol[3],float fcol[3])
{
    float current[3];
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,current);
    if ((current[0] != bcol[0] || current[1] != bcol[1] || current[2] != bcol[2] )&& (current[0] != fcol[0] || current[1] != fcol[1] || current[2] != fcol[2] ))
    {   
        glColor3f(fcol[0],fcol[1],fcol[2]);
        glBegin(GL_POINTS);
        glVertex2d(x,y);
        glEnd();
        glFlush();
        
        Bfill(x,y+1,bcol,fcol);
        Bfill(x,y-1,bcol,fcol);
        Bfill(x+1,y,bcol,fcol);
        Bfill(x-1,y,bcol,fcol);
    }
}

int Round(float a)
{
return (int)(a+0.5);
}
void DDA(int xa,int ya,int xb,int yb)
{
int dx,dy,steps;
dx=xb-xa;
dy=yb-ya;
 if(abs(dx)>abs(dy)){
   steps=abs(dx);
 }
 else{
   steps=abs(dy);
 }
 float xinc;
 float yinc;
 float x=xa,y=ya;
 xinc=(float)dx/steps;
 yinc=(float)dy/steps;
 for(int i=0;i<steps;i++)
    {
      x=x+xinc;
      y=y+yinc;
      glVertex2d(Round(x),Round(y));
    }
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
     glColor3f(bcol[0],bcol[1],bcol[2]);
     int i;
     for (i=0;i<v-1;i++)
     {
        DDA(input[0][i],input[1][i],input[0][i+1],input[1][i+1]);
     }
        DDA(input[0][i],input[1][i],input[0][0],input[1][0]);
   /* DDA(100,100,300,100);
    DDA(300,100,300,300);
    DDA(300,300,100,300);
    DDA(100,300,100,100);*/
    glEnd();
    glFlush();
    
}
void mouse(int button,int state,int mx,int my)
{
      if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
      {
         int windowheight=glutGet(GLUT_WINDOW_HEIGHT);
         y=windowheight-my;
          x=mx;
      }
  
  int xmin = input[0][0], xmax = input[0][0];
  int ymin = input[1][0], ymax = input[1][0];

for (int i = 1; i < v; i++) {
    if (input[0][i] < xmin) xmin = input[0][i];
    if (input[0][i] > xmax) xmax = input[0][i];
    if (input[1][i] < ymin) ymin = input[1][i];
    if (input[1][i] > ymax) ymax = input[1][i];
}

if (x >= xmin && x <= xmax && y >= ymin && y <= ymax) {
    Bfill(x, y, bcol, fcol);
}
}


int main(int argc, char **argv)
{
    printf("\nEnter no of Vertices: ");
    scanf("%d",&v);
    for(int i=0;i<v;i++)
    {
        printf("\nX[%d]: ",i+1);
        scanf("%d",&input[0][i]);
      
        printf("\nY[%d]: ",i+1);
        scanf("%d",&input[1][i]);
    }
    for(int i=0;i<3;i++)
    {
        printf("\nEnter Boundry Color[%d]: ",i);
        scanf("%f",&bcol[i]);
    }
     for(int i=0;i<3;i++)
    {
        printf("\nEnter Fil Color[%d]: ",i);
        scanf("%f",&fcol[i]);
    }
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("Boundry Filling");
    glClearColor(1,1,1,0);
   
    gluOrtho2D(0,640,0,480);
    glutDisplayFunc(Draw);
    glutMouseFunc(mouse);
    glutMainLoop();
    
    return 0;
}
