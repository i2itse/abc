#include <GL/glut.h>
#include <math.h>

int step=5;
int Round(float a){
  return (int)(a+0.5);
}
void DDAl(int xa,int ya,int xb,int yb){
  int dx,dy,steps;
  dx=xb-xa;
  dy=yb-ya;
  if(abs(dx)>abs(dy)){
    steps=abs(dx);
  }else{
    steps=abs(dy);
  }
  float xinc,yinc,x,y;
  xinc=(float)dx/steps;
  yinc=(float)dy/steps;
  x=xa;
  y=ya;
  glVertex2d(xa,ya);
  for(int i=0;i<steps;i++){
    x=x+xinc;
    y=y+yinc;
    glVertex2d(Round(x),Round(y));
  }


}
void koch_curve(float xa,float ya,float xb,float yb,int step){
if(step==0){
  DDAl(xa,ya,xb,yb);
  return;
  }
  float x1,y1,x2,y2,dx,dy,r_dx,r_dy,x3,y3;
  x1=xa+(xb-xa)/3;
  y1=ya+(yb-ya)/3;
  x2=xa+2*(xb-xa)/3;
  y2=ya+2*(yb-ya)/3;
  dx=x2-x1;
  dy=y2-y1;
  float angle=-M_PI/3;
  r_dx=dx*cos(angle)-dy*sin(angle);
  r_dy=dx*sin(angle)+dy*cos(angle);
  x3=x1+r_dx;
  y3=y1+r_dy;
  
  
  /*glColor3f(1,0,0);
  DDAl(xa,ya,x1,y1);
  glColor3f(0,0,1);
  DDAl(x1,y1,x3,y3);
  DDAl(x3,y3,x2,y2);
  
  glColor3f(0,1,0);
  DDAl(x2,y2,xb,yb);*/
  koch_curve(xa,ya,x1,y1,step-1);
  koch_curve(x1,y1,x3,y3,step-1);
  koch_curve(x3,y3,x2,y2,step-1);
  koch_curve(x2,y2,xb,yb,step-1);

}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    //glPointSize(2);
    glBegin(GL_POINTS);
    koch_curve(100,100,400,100,step);
    koch_curve(400,100,250,400,step);
    koch_curve(250,400,100,100,step);
    //glVertex2d(100,100);
    //DDAl(100,100,400,100);
    glEnd();
    glFlush();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(1000,100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Koch Snowflake");
    glClearColor(1,1,1,0);
    glColor3f(0,0,0);
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
