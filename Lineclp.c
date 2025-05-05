#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int xmin, xmax, ymin, ymax;

struct ver {
    float x, y;
    int outcode[4];
} p1, p2, orig1, orig2;

int Round(float a) {
    return (int)(a + 0.5);
}

void ddaline(int xa, int ya, int xb, int yb) {
    int dx = xb - xa;
    int dy = yb - ya;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xinc = dx / (float)steps;
    float yinc = dy / (float)steps;
    float x = xa, y = ya;

    for (int i = 0; i <= steps; i++) {
        glVertex2i(Round(x), Round(y));
        x += xinc;
        y += yinc;
    }
}

void calculate(struct ver *p) {
    for (int j = 0; j < 4; j++) p->outcode[j] = 0;

    if (p->x < xmin) p->outcode[3] = 1;  // Left
    if (p->x > xmax) p->outcode[2] = 1;  // Right
    if (p->y < ymin) p->outcode[1] = 1;  // Bottom
    if (p->y > ymax) p->outcode[0] = 1;  // Top

    for (int k = 0; k < 4; k++) printf("%d", p->outcode[k]);
}

void windowcliping() {
    calculate(&p1);
    printf("\n");
    calculate(&p2);

    orig1 = p1;
    orig2 = p2;

    int flag1 = 0;
    for (int i = 0; i < 4; i++) {
        if (p1.outcode[i] == 1 || p2.outcode[i] == 1) {
            flag1 = 1;
            break;
        }
    }

    if (flag1 == 0) {
        printf("\nFully Accepted");
    } else {
        int flag2 = 0;
        for (int j = 0; j < 4; j++) {
            if (p1.outcode[j] == 1 && p2.outcode[j] == 1) {
                flag2 = 1;
                break;
            }
        }

        if (flag2 == 1) {
            printf("\nRejected");
            return; // Don't draw
        } else {
            printf("\nPartially Accepted");
            float m = (orig2.y - orig1.y) / (orig2.x - orig1.x);
            printf(" | Slope: %f", m);

            if (p1.outcode[0]) { p1.y = ymax; p1.x = orig1.x + (ymax - orig1.y) / m; }
            if (p1.outcode[1]) { p1.y = ymin; p1.x = orig1.x + (ymin - orig1.y) / m; }
            if (p1.outcode[2]) { p1.x = xmax; p1.y = orig1.y + m * (xmax - orig1.x); }
            if (p1.outcode[3]) { p1.x = xmin; p1.y = orig1.y + m * (xmin - orig1.x); }

            if (p2.outcode[0]) { p2.y = ymax; p2.x = orig2.x + (ymax - orig2.y) / m; }
            if (p2.outcode[1]) { p2.y = ymin; p2.x = orig2.x + (ymin - orig2.y) / m; }
            if (p2.outcode[2]) { p2.x = xmax; p2.y = orig2.y + m * (xmax - orig2.x); }
            if (p2.outcode[3]) { p2.x = xmin; p2.y = orig2.y + m * (xmin - orig2.x); }
        }
    }

    printf("\nNew coordinates: (%.2f, %.2f) -> (%.2f, %.2f)", p1.x, p1.y, p2.x, p2.y);

    ddaline(Round(p1.x), Round(p1.y), Round(p2.x), Round(p2.y));
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window in blue
    glColor3f(0, 0, 1);
    glBegin(GL_POINTS);
    ddaline(xmin, ymin, xmax, ymin);
    ddaline(xmax, ymin, xmax, ymax);
    ddaline(xmax, ymax, xmin, ymax);
    ddaline(xmin, ymax, xmin, ymin);
    glEnd();

    // Draw original line in RED
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    ddaline(Round(p1.x), Round(p1.y), Round(p2.x), Round(p2.y));
    glEnd();

    // Wait a bit (optional)


    // Draw clipped line in BLACK
    glColor3f(0, 0, 0);
    glBegin(GL_POINTS);
    windowcliping();
    glEnd();

    glFlush();
}

int main(int argc, char **argv) {
    printf("Enter the window (xmin ymin xmax ymax): ");
    scanf("%d%d%d%d", &xmin, &ymin, &xmax, &ymax);

    printf("Enter the coordinates of the line (x1 y1 x2 y2): ");
    scanf("%f%f%f%f", &p1.x, &p1.y, &p2.x, &p2.y);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Cohen-Sutherland Window Clipping");
    glClearColor(1, 1, 1, 0);
    gluOrtho2D(0, 640, 0, 480);
    glutDisplayFunc(Draw);
    glutMainLoop();

    return 0;
}

