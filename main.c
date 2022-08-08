#include "mlx/mlx.h"
#include <stdio.h>
#include "ray.h"
#include <math.h>
#include <stdlib.h>

#define pi 3.1415926535
#define p2 pi/2
#define p3 3*pi/2
#define DR 0.0174533 //one degree in radians

float px, py, pdx,pdy,pa;//player position
int y , x;
void    drawRays(t_ray *data);

void	my_mlx_pixel_put(t_ray *data, int x, int y, int color)
{
	char	*dst;
    
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    drawSquare(float px, float py, int dms, t_ray *data, int color)
{
    
    int temp = py+1;
    while (temp <(py +dms - 1))
    {
        int tempx = px+1;
        while (tempx <= (px + dms - 1))
        {
            my_mlx_pixel_put(data, tempx, temp, color);
            tempx++;
        }
        temp++;
    }
}


void    drawPlayer(t_ray *data)
{
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img2, px, py);
}

int All_Textures[]=               //all 32x32 textures
{
 //Checkerboard
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 

 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
};

int mapX = 8,mapY=8,mapS=64;
int map[]=
{
    1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,0,2,2,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,1,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,
};

void    drawMap2D(t_ray *data)
{
    int color;
    int sx, sy, xo, yo;
    for(sy = 0; sy < mapY; sy++)
    {
        
        for (sx = 0; sx < mapX; sx++)
        {
            xo =sx*mapS; 
            yo = sy *mapS;
            if (map[sy*mapX+sx] == 1)
            {
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, xo, yo);
                //data->color = '0';
            }
            // if (map[sy*mapX+sx] == 2)
            // {
            //     mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, xo, yo);
            //     //data->color = 'F';
            // }
            //drawSquare(xo , yo , mapS, data, color);
        }
    }
    
}

#include    "wass.ppm"

int    init(t_ray *data)
{
    pdx=cos(pa)*5;
    pdy=sin(pa)*5;
    data->ssa = 0;
    data->color = '0' ;
    if (data->a == 1)
    {
        pa-=0.1;
        if (pa < 0)
        {
            pa+=2*pi;
        }
        pdx=cos(pa)*5;
        pdy=sin(pa)*5;
    }
    int xo=0; if(pdx<0){xo-=20;} else{ xo=20;}
    int yo=0; if(pdy<0){yo-=20;} else{ yo=20;}
    int ipx=px/64.0, ipx_add_xo=(px+xo)/64.0, ipx_sub_xo=(px-xo)/64.0;
    int ipy=py/64.0, ipy_add_yo=(py+yo)/64.0, ipy_sub_yo=(py-yo)/64.0;
    if (data->d == 1) 
    {
        pa+=0.1;
        if (pa > 2*pi)
        {
            pa-=2*pi;
        }
        pdx=cos(pa)*5;
        pdy=sin(pa)*5;
    }
    if (data->w == 1) 
    {
        if(map[ipy*mapX        + ipx_add_xo]==0){  px+=pdx*0.5;}
        if(map[ipy_add_yo*mapX + ipx]==0){  py+=pdy*0.5;}
    }
    if (data->s == 1) 
    {
        if(map[ipy*mapX        + ipx_sub_xo]==0){  px-=pdx*0.5;}
        if(map[ipy_sub_yo*mapX + ipx]==0){  py-=pdy*0.5;}
    }

    int x,y;
    for(y=0;y<32;y++)
    {
        for(x=0;x<32;x++)
        {
            int pixel=(y*32+x)*3;
            int red =walls[pixel+0];
            int green =walls[pixel+1];
            int blue =walls[pixel+2];
            //int xtemp = x*8;
            int ytemp = y*5;
            while (ytemp<((y*5)+5))
            {
                int xtemp = x*5;
                while (xtemp<((x*5)+5))
                {
                    my_mlx_pixel_put(data, xtemp, ytemp, (red<<16 | green <<8 | blue));
                    xtemp++;
                }
                ytemp++;
            }
        }
    }
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0,0);
    //mlx_destroy_image(data->mlx_ptr, data->img);
    //data->img = mlx_new_image(data->mlx_ptr, 60, 320);
    //data->addr= mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
    
    return (0);
}

int    ButtonDown(int key, t_ray *data)
{
    if (key == A)
        data->a=1;
    if (key == D) 
        data->d=1;
    if (key == W) 
        data->w=1;
    if (key == S) 
        data->s=1;
    if (key == ESC)
        exit(0);
    
    return (0);
}

int    ButtonUp(int key, t_ray *data)
{
    if (key == A)
        data->a=0;
    if (key == D) 
        data->d=0;
    if (key == W) 
        data->w=0;
    if (key == S) 
        data->s=0;
    return(0);
}

void    drawLine(int gg, int ss, int enx, int eny, t_ray *data)
{
    while (ss < eny)
    {
        while (gg < enx)
        {
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, gg, ss, 0x00FF00);
            gg++;
        }
        ss++;
    }
    data->ssa = 0;
}
float   dist(float ax, float ay, float bx, float by, float ang)
{
    return (sqrt((bx-ax)*(bx-ax)+ (by-ay)*(by-ay)));
}

void    draw(int x, int lineO, int lineH, int Txt[], t_ray *data, FILE *fp)
{
    int s=0;
    int tempy = 8;
    //float ty_step=32.0/(float)lineH;
    //float   ty_off=0;
    //if (lineH>320){ty_off=(lineH-320)/2.0; lineH=320;}
    //int lineOff = 160-(lineH>>1);
    int y1 = 0;
    int x1 = 0;
    //float ty=ty_off*ty_step;
    //float tx=(int)(rx/2.0)%32;
    while (y1 < lineH)
    {
        //fprintf(fp, "%c", '"');
        //int c = All_Textures[(int)(ty)*32];
        //printf("%i %%\n", y1*100/lineH);
        //printf ("%d\n", c);
        //fprintf(fp, "%c%d%d%d%d%d%d%d%d%c%c\n", '"',Txt[c],Txt[c],Txt[c+2],Txt[c+3],Txt[c+4],Txt[c+5],Txt[c+6],Txt[c+7], '"', ',');
        fprintf(fp, "%c        %c%c\n", '"', '"', ',');
       
        // x1 = 0;
        // while (x1 < 8)
        // {
        //     mlx_pixel_put(data->mlx_ptr, data->win_ptr, x+x1, (160-hy/2)+y1, data->color);
        //     x1++;
        // }
        //fprintf(fp, "%c%c\n",'"', ',');
        //ty=ty_step;
        y1++;
    }
    fprintf(fp, "%c        %c\n};\n", '"', '"');
    fclose(fp);
   
}
//----------------------------RayCast-----Engine--------------//
void    drawRays(t_ray *data)
{
    int tt = 8;
    char Rg= '0';
    char Lg= '0';
    int r,mx,my,mp,dof; float rx,ry,ra,xo,yo,disT;
    ra = pa-DR*30; if(ra<0){ ra+=2*pi;} if(ra>2*pi){ ra-=2*pi;}
    for(r=0; r<64; r++)
    {
        //Linea Orizzontale
        dof = 0;
        int y=0;
        float disH=1000000,hx=px,hy=py;
        float aTan=-1/tan(ra);
        if (ra>pi){ry = (((int)py>>6)<<6)-0.0001; rx=(py-ry)*aTan+px; yo=-64; xo=-yo*aTan;} //looking up
        if (ra<pi){ry = (((int)py>>6)<<6)+64;     rx=(py-ry)*aTan+px; yo= 64; xo=-yo*aTan;} //looking down
        if (ra == 0 || ra==pi) { rx=px; ry=py; dof=8;} //looking straight left or right
        while (dof<8)
        {
            
            mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;
            //if (mp>0 && mp<mapX*mapY && map[mp] > 1) { hx=rx; hy=ry; disH=dist(px,py,hx,hy,ra); dof = 8; data->color = 'F';} 
            if(mp>0 && mp<mapX*mapY && map[mp] == 1){ hx=rx; hy=ry; disH=dist(px,py,hx,hy,ra); dof = 8; data->color ='0'; data->ssa=0;}//   hit wall       
            if(mp>0 && mp<mapX*mapY && map[mp] ==2){ hx=rx; hy=ry; disH=dist(px,py,hx,hy,ra);dof = 8; data->color ='F'; data->ssa=1; data->ssa=1;}
            else{ rx+=xo; ry+=yo; dof+=1;}//next 
            //if(mp>0 && mp<mapX*mapY && map[mp] ==2){printf("%d", map[mp]);}
        }
        //mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img2, rx, ry);
        
        //Linea verticale
        dof = 0;
        int temps;
        float disV=1000000,vx=px,vy=py;
        float nTan=-tan(ra);
        if (ra>p2 && ra<p3){rx = (((int)px>>6)<<6)-0.0001; ry=(px-rx)*nTan+py; xo=-64; yo=-xo*nTan;} //looking left
        if (ra<p2 || ra>p3){rx = (((int)px>>6)<<6)+64;     ry=(px-rx)*nTan+py; xo= 64; yo=-xo*nTan;} //looking right
        if (ra == 0 || ra==pi) { rx=px; ry=py; dof=8;} //looking straight up or down
        while (dof<8)
        {
            mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;
            //if (mp>0 && mp<mapX*mapY && map[mp] > 1) {vx=rx; vy=ry; disV=dist(px,py,vx,vy,ra);dof = 8 ; data->color = 'F';} 
            if(mp>0 && mp<mapX*mapY && map[mp] ==1){ vx=rx; vy=ry; disV=dist(px,py,vx,vy,ra);dof = 8; data->color ='0'; data->ssa=0;}//   hit wall
            if(mp>0 && mp<mapX*mapY && map[mp] ==2){ vx=rx; vy=ry; disV=dist(px,py,vx,vy,ra);dof = 8; data->color ='F'; data->ssa=1;}      
            else{   rx+=xo; ry+=yo; dof+=1;}//next  
            //if(mp>0 && mp<mapX*mapY && map[mp] ==2){printf("%d", map[mp]);}
        }
        if (disV<disH){ rx=vx; ry=vy; disT=disV; Rg = 'A';}  
        if (disH<disV){ rx=hx; ry=hy; disT=disH; Rg = 'F'; }
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img3, rx, ry);
        //--Draw 3D Walls--
        float ca=pa-ra; if(ca<0){ ca+=2*pi;} if(ca>2*pi){ ca-=2*pi;} disT=disT*cos(ca);//fix fisheye
        float lineH=(mapS*320)/disT; if (lineH>320){lineH=320;}
        float lineO=160-lineH/2;
        //mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img4s, (r*8+512), (-lineH)); 
        //mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img4s, (r*8+512), (lineH+lineO));
        //------**--**Crea un file.xpm "dinamico", ogni volta che un frame è richiesto,
        //----- cambiando l'altezza in corrispondenza della distanza del "Muro", definito
        //-----dalla variabile lineH
        //----Non è il miglior modo per farlo ma ha un refresh accettabile
        //---In questo modo è difficile applicare delle texture, o c'è da studiarci un pò
        //FILE * fp;
        //printf("%d", mp);
        
        //fp = fopen ("file.xpm", "w");
        //fprintf(fp, "/* XPM */\n static char *dddsuca[] = {\n");
        //fprintf(fp, "%c%d %d %d %d %c%c\n", '"', 8, (int)lineH, 1, 1, '"', ',');
        //fprintf(fp, "%c c #%c%d%d%d%c%d%c%c\n", '"', Rg,0,0,0,data->color,0, '"', ','); //for red text
        //fprintf(fp, "%c1  c #%d%d%d%d%d%d%c%c\n", '"', 8,0,8,0,8,0, '"', ',');
        //fprintf(fp, "%c0  c #%c%c%c%c%c%c%c%c\n", '"', 'F','F','F','F','F','F', '"', ',');
        //fprintf(fp, "/* pixels */\n");
        //draw(r*8+512, (int)lineO, (int)lineH, All_Textures, data, fp);
        //printf("%d\n", map[r]);
        //drawSquare(r*8+512, ry, lineH, data, 0xFFFFFF);
        //printf("%d\n", (int)lineH);
        temps = (int)lineH;
        data->gliss = r+512;
        //data->img4 = mlx_xpm_file_to_image(data->mlx_ptr, "file.xpm", &tt, &temps);
        //mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img4, (r*8+512), (lineO));
        //mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img4s, (r*8+512), (lineH+lineO));
        ra+=DR; if(ra<0){ ra+=2*pi;} if(ra>2*pi){ ra-=2*pi;}
        //data->ssa = 0;
    }
    
    //printf("\n");
}

int    buttons(int keycode, t_ray *data)
{
    
    return (0);
}

int main()
{
    int w = 8;
    int h =  320;
    int h1 = 16;
    int c = 512;
    int pss;
    pss = 64;
    int pw;
    pw = 10;
    t_ray data;
    py = 300;
    px = 300;

   

    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, 1024, 512, "RayCast");
    //data.img = mlx_xpm_file_to_image(data.mlx_ptr, "wall.xpm", &pss, &pss);
    data.img = mlx_new_image(data.mlx_ptr, 400, 400);
    data.addr= mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    data.img4s = mlx_xpm_file_to_image(data.mlx_ptr, "wll.xpm", &w, &h1);
    data.img2 = mlx_xpm_file_to_image(data.mlx_ptr, "pg.xpm", &pw, &pw);
    data.img3 = mlx_xpm_file_to_image(data.mlx_ptr, "dot.xpm", &pw, &pw);
    data.img4 = mlx_xpm_file_to_image(data.mlx_ptr, "wll.xpm",&h1, &h);
    //init(&data);
    //drawSquare(px, py, 8, &data);
    //mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img2, 300, 300);
    //drawPlayer(&data);
    //drawMap2D(&data);
    
    mlx_loop_hook(data.mlx_ptr, init, &data);
    mlx_hook(data.win_ptr, 2, 1L << 0, ButtonDown, &data);
    mlx_hook(data.win_ptr, 3, 1L << 1, ButtonUp, &data);
    mlx_loop(data.mlx_ptr);    
}
void    drawSprite()
{
int x,y,s;
 //if(px<sp[0].x+30 && px>sp[0].x-30 && py<sp[0].y+30 && py>sp[0].y-30){ printf("ok\n");} //pick up key 	
 //if(px<sp[3].x+30 && px>sp[3].x-30 && py<sp[3].y+30 && py>sp[3].y-30){ gameState=4;} //enemy kills

 //enemy attack
 int spx=(int)sp[3].x>>6,          spy=(int)sp[3].y>>6;          //normal grid position
 int spx_add=((int)sp[3].x+15)>>6, spy_add=((int)sp[3].y+15)>>6; //normal grid position plus     offset
 int spx_sub=((int)sp[3].x-15)>>6, spy_sub=((int)sp[3].y-15)>>6; //normal grid position subtract offset
 if(sp[3].x>px && mapW[spy*8+spx_sub]==0){ sp[3].x-=0.04;}
 if(sp[3].x<px && mapW[spy*8+spx_add]==0){ sp[3].x+=0.04;}
 if(sp[3].y>py && mapW[spy_sub*8+spx]==0){ sp[3].y-=0.04;}
 if(sp[3].y<py && mapW[spy_add*8+spx]==0){ sp[3].y+=0.04;}

 for(s=0;s<4;s++)
 {
  float sx=sp[s].x-px; //temp float variables
  float sy=sp[s].y-py;
  float sz=sp[s].z;

  float CS=cos(degToRad(pa)), SN=sin(degToRad(pa)); //rotate around origin
  float a=sy*CS+sx*SN; 
  float b=sx*CS-sy*SN; 
  sx=a; sy=b;

  sx=(sx*108.0/sy)+(120/2); //convert to screen x,y
  sy=(sz*108.0/sy)+( 80/2);

  int scale=32*80/b;   //scale sprite based on distance
  if(scale<0){ scale=0;} if(scale>120){ scale=120;}  

  //texture
  float t_x=0, t_y=31, t_x_step=31.5/(float)scale, t_y_step=32.0/(float)scale;

  for(x=sx-scale/2;x<sx+scale/2;x++)
  {
   t_y=31;
   
   for(y=0;y<scale;y++)
   {
    //printf("%d\n", sp[s].state);
    if(sp[s].state==1 && x>0 && x<120 && b<depth[x])
    {
        //printf("%d\n", x);
     int pixel=((int)t_y*32+(int)t_x)*3+(sp[s].map*32*32*3);
     int red   =sprites[pixel+0];
     int green =sprites[pixel+1];
     int blue  =sprites[pixel+2];
     color = (red<<16 | green <<8 | blue);
     if(red!=255 || green!=0 || blue!=255) //dont draw if purple
     {
        int temp = y*5;
        while (temp <((y*5)+5))
        {  
            int tempx = x*5;
            while (tempx <= ((x*5)+5))
            {
                my_mlx_pixel_put2(tempx,sy*4-temp); //draw point 
                tempx++;
            }
            temp++;
        }
            
     }
     t_y-=t_y_step; if(t_y<0){ t_y=0;}
    }
   }
   t_x+=t_x_step;
  }
 }
 //mlx_put_image_to_window(data.mlx_ptr,data.win_ptr, data.img4, 0,0 );
}