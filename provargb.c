
typedef struct
{
    int r,g,b;
}colore; colore hrgb;

void     rgb(int r, int g, int b)
{
    hrgb.r = r*255;
    hrgb.g = g*255;
    hrgb.b = b*255;
}

int rgbtohex()
{
    return(hrgb.r<<16 | hrgb.g<<8 | hrgb.b);
}


int main()
{
    int color;
    rgb(1,1,1);
    color = rgbtohex();
}