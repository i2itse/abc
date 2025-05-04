int input[2][10];
int v;
float output[2][10];
int m=0;
int xmin,ymin,xmax,ymax;
 
void leftClip(int xa,int ya,int xb,int yb)
{
    float slope=(float)(yb-ya)/(xb-xa);
    if(xa>=xmin && xb>=xmin)
    {
        output[0][m]=xb;
        output[1][m]=yb;
        m=m+1;
    }
    if(xa>=xmin && xb<xmin)
    {
        output[0][m]=xmin;
        output[1][m]=ya+slope*(xmin-xa);
        m=m+1;
    }
    if(xa<xmin && xb>=xmin)
    {
        output[0][m]=xmin;
        output[1][m]=ya+slope*(xmin-xa);
        output[0][m+1]=xb;
        output[1][m+1]=yb;
        m=m+2;
    }
}
void rightClip(int xa,int ya,int xb,int yb)
{
    float slope=(float)(yb-ya)/(xb-xa);
    if(xa<=xmax && xb<=xmax)
    {
        output[0][m]=xb;
        output[1][m]=yb;
        m=m+1;
    }
    if(xa<=xmax && xb>xmax)
    {
        output[0][m]=xmax;
        output[1][m]=ya+slope*(xmax-xa);
        m=m+1;
    }
    if(xa>xmax && xb<=xmax)
    {
        output[0][m]=xmax;
        output[1][m]=ya+slope*(xmax-xa);
        output[0][m+1]=xb;
        output[1][m+1]=yb;
        m=m+2;
    }
}
void bottomClip(int xa,int ya,int xb,int yb)
{
    float slope=(float)(yb-ya)/(xb-xa);
    if(ya>=ymin && yb>=ymin)
    {
        output[0][m]=xb;
        output[1][m]=yb;
        m=m+1;
    }
    if(ya>=ymin && yb<ymin)
    {
        output[0][m]=xa+(ymin-ya)/slope;
        output[1][m]=ymin;
        m=m+1;
    }
    if(ya<ymin && yb>=ymin)
    {
        output[0][m]=xa+(ymin-ya)/slope;
        output[1][m]=ymin;
        output[0][m+1]=xb;
        output[1][m+1]=yb;
        m=m+2;
    }
}
 
void topClip(int xa,int ya,int xb,int yb)
{
    float slope=(float)(yb-ya)/(xb-xa);
    if(ya<=ymax && yb<=ymax)
    {
        output[0][m]=xb;
        output[1][m]=yb;
        m=m+1;
    }
    if(ya<=ymax && yb>ymax)
    {
        output[0][m]=xa+(ymax-ya)/slope;
        output[1][m]=ymax;
        m=m+1;
    }
    if(ya>ymax && yb<=ymax)
    {
        output[0][m]=xa+(ymax-ya)/slope;
        output[1][m]=ymax;
        output[0][m+1]=xb;
        output[1][m+1]=yb;
        m=m+2;
    }
}