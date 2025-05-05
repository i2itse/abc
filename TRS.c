// TRANSLATION
 
void translation(){
  for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                  if (i == j) {
                        t[i][j] = 1;
                  } else {
                        t[i][j] = 0;
                  }
              }
          }
          printf("Enter the translation distance (tx,ty): ");
          scanf("%f%f", &xf, &yf);
          t[0][2] = xf;
          t[1][2] = yf;
          mul(input, t, output, v);
 
}
 
//ROTATION
 
void Rotation(){
 float o;
 int xr,yr;
 printf("Enter the fixed point (xr,yr): ");
            scanf("%d%d", &xr, &yr);
            printf("Enter the angle in degrees: ");
            scanf("%f", &o);
            radian=o*M_PI/180;
            r[0][0] = cos(o);
            r[0][1] = -sin(o);
            r[0][2] = xr * (1 - cos(o)) + yr * sin(o);
            r[1][0] = sin(o);
            r[1][1] = cos(o);
            r[1][2] = yr * (1 - cos(o)) - xr * sin(o);
            r[2][0] = 0;
            r[2][1] = 0;
            r[2][2] = 1;
            mul(input, r, output, v);
}
 
//SCALING
 
void Scaling(){
    int sx,sy;
    for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (i == j) {
                        s[i][j] = 1;
                    } else {
                        s[i][j] = 0;
                    }
                }
            }
            printf("Enter the scaling (sx,sy): ");
            scanf("%d%d", &sx, &sy);
            s[0][0] = sx;
            s[1][1] = sy;
            printf("Enter the fixed point (xf,yf): ");
            scanf("%f%f", &xf, &yf);
            s[0][2] = xf * (1 - sx);
            s[1][2] = yf * (1 - sx);
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    printf("%f\t", s[i][j]);
                }
                printf("\n");
            }
            mul(input, s, output, v);
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < v; j++) {
                    printf("%f\t", output[i][j]);
                }
                printf("\n");
            }
}