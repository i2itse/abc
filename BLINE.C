#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int xa, ya, xb, yb;

void BLine(int xa, int ya, int xb, int yb) {
    int dx, dy, d;
    int c, r, f;
    dx = xb - xa;
    dy = yb - ya;

    if (abs(dx) > abs(dy)) {
        d = 2 * abs(dy) - abs(dx);
        if (dx > 0) {
            c = xa; r = ya; f = xb;
        } else {
            c = xb; r = yb; f = xa;
        }
        while (f > c) {
            glVertex2i(c, r);
            if (d < 0) {
                c++;
                d += 2 * abs(dy);
            } else {
                if ((dx > 0 && dy > 0) || (dx < 0 && dy < 0)) r++;
                else r--;
                c++;
                d += 2 * abs(dy) - 2 * abs(dx);
            }
        }
    } else {
        d = 2 * abs(dx) - abs(dy);
        if (dy > 0) {
            c = xa; r = ya; f = yb;
        } else {
            c = xb; r = yb; f = ya;
        }
        while (f > r) {
            glVertex2i(c, r);
            if (d < 0) {
                r++;
                d += 2 * abs(dx);
            } else {
                if ((dx > 0 && dy > 0) || (dx < 0 && dy < 0)) c++;
                else c--;
                r++;
                d += 2 * abs(dx) - 2 * abs(dy);
            }
        }
    }
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    BLine(xa, ya, xb, yb);
    

    glEnd();
    glFlush();
}

int main(int argc, char **argv) {
    printf("\nEnter the First coordinate (xa, ya): ");
    scanf("%d%d", &xa, &ya);
    printf("\nEnter the Second coordinate (xb, yb): ");
    scanf("%d%d", &xb, &yb);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham's Line Drawing");
    glClearColor(1.0, 1.0, 1.0, 0);
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(0, 640, 0, 480); // Corrected
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
