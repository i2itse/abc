#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int xc,yc,r;
int h;
int Round(float a){
return (int)(a+0.5); 
}
void BCIR(int xc,int yc,int r){
int x=0,y=r,d=3-2*r;
do{
glVertex2d(xc+x,yc+y);
glVertex2d(xc+y,yc+x);
glVertex2d(xc-x,yc+y);
glVertex2d(xc+y,yc-x);
glVertex2d(xc+x,yc-y);
glVertex2d(xc-y,yc+x);
glVertex2d(xc-x,yc-y);
glVertex2d(xc-y,yc-x);
if(d<0){
x+=1;
d=d+4*x+6;
}else{
x=x+1;
y=y-1;
d=d+4*x-4*y+10;
}

}while(y>=x);


}
void Draw(){
glClear(GL_COLOR_BUFFER_BIT);
glBegin(GL_POINTS);
BCIR(xc,yc,r);
BCIR(xc+2*r,yc,r);
BCIR(xc-2*r,yc,r);
BCIR(xc-r,yc+h,r);
BCIR(xc+r,yc+h,r);
BCIR(xc-r,yc-h,r);
BCIR(xc+r,yc-h,r);
BCIR(xc,yc,2*r);

glEnd();
glFlush();
}
int main(int argc,char **argv){
printf("Enter the center coordinates:");
scanf("%d%d",&xc,&yc);
printf("Enter Radius:");
scanf("%d",&r);
h=sqrt(3*r*r);
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowPosition(0,0);
glutInitWindowSize(640,480);
glutCreateWindow("Assignment 1");
glClearColor(1,1,1,0);
glColor3f(0,0,0);
gluOrtho2D(0,640,0,480);
glutDisplayFunc(Draw);
glutMainLoop();

return 0;
}
