#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

int xa,ya,xb,yb;

void Bline(int xa,int ya,int xb,int yb)
{
		int dx,dy,d;
		int c,r,f;
		
		dx = xb - xa;
		dy = yb - ya;
	
	if(abs(dx) > abs(dy))
	{
	
		d = 2 * abs(dy) - abs(dx);
		
		if(dx>0)
		{
			c=xa;
			r=ya;
			f=xb;
		}
		else
		{
			c=xb;
			r=yb;
			f=xa;
		}
		
		while(f > c)
		{
			if(d < 0)
			{
				c = c + 1;
				d= d + 2 * abs(dy);
			}
			else
			{
				c = c + 1;
				
				if(dx > 0 && dy > 0 || dx < 0 && dy < 0)
				{
					r = r + 1;
				}
				else
				{
					r = r - 1;
				}
				d = d + 2 * abs(dy) - 2 * abs(dx);
			}
			glVertex2d(c,r);			
	
		}
		
	}
	
	else
	{
		d = 2 * abs(dx) - abs(dy);
		
		if(dy>0)
		{
			c=xa;
			r=ya;
			f=yb;
		}
		else
		{
			c=xb;
			r=yb;
			f=ya;
		}
		
		while(f > r)
		{
			if(d < 0)
			{
				r = r + 1;
				d= d + 2 * abs(dx);
			}
			else
			{
				r = r + 1;
				
				if(dx > 0 && dy > 0 || dx < 0 && dy < 0)
				{
					c = c + 1;
				}
				else
				{
					c = c - 1;
				}
				d = d + 2 * abs(dx) - 2 * abs(dy);
			}
			glVertex2d(c,r);			
	
		}
	}
	
}


void Draw()
{
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_POINTS);
		
		int yinc = (yb - ya) / 4;
		int xinc = (xb - xa) / 4;
		int y=ya,x=xa;
		for(int i=0;i<=4;i++)
		{
			
			Bline(xa,y,xb,y);
			Bline(x,ya,x,yb);
			y=y+yinc;
			x=x+xinc;
		}
		
		
		glEnd();
		glFlush();
	
}

int main(int argc,char **argv)
{
		printf("\nEnter First Coordinate: ");
		scanf("%d%d",&xa,&ya);
		
		printf("\nEnter Second Coordinate: ");
		scanf("%d%d",&xb,&yb);

		glutInit(&argc,argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowPosition(0,0);
		glutInitWindowSize(640,480);
		glutCreateWindow("Bres Line");
		glClearColor(1,1,1,0);
		glColor3f(0,0,0);
		gluOrtho2D(0,640,0,480);
		glutDisplayFunc(Draw);
		glutMainLoop();
		
		return 0;
}
