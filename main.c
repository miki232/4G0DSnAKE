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

void    drawSquare(float px, float py, int dms, t_ray *data, int color)
{
    int temp = py+1;
    while (temp <(py +dms - 1))
    {
        int tempx = px+1;
        while (tempx <= (px + dms - 1))
        {
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, tempx, temp, color);
            tempx++;
        }
        temp++;
    }
}

void    draw(int x, int y, int hy, t_ray *data, FILE *fp)
{
    int tempy = y;
    int y1 = 0;
    int x1 = 0;
    while (y1 < hy)
    {
        //printf("%i %%\n", y1*100/hy);
        fprintf(fp, "%c        %c%c\n", '"', '"', ',');
        // x1 = 0;
        // while (x1 < 8)
        // {
        //     mlx_pixel_put(data->mlx_ptr, data->win_ptr, x+x1, (160-hy/2)+y1, data->color);
        //     x1++;
        // }
        y1++;
    }
    fprintf(fp, "%c        %c\n};\n", '"', '"');
    fclose(fp);
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
 //Brick
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
};

int mapX = 8,mapY=8,mapS=64;
int map[]=
{
    1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,0,1,0,0,0,1,
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
            if (map[sy*mapX+sx] == 2)
            {
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, xo, yo);
                //data->color = 'F';
            }
            //drawSquare(xo , yo , mapS, data, color);
        }
    }
    
}
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

    
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    //mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->background, (512), (0));
    drawMap2D(data);
    drawPlayer(data);
    //data->ssa = 0;
    drawRays(data);
    data->ssa = 0;
   
    // y = 0;
    // while(y<512)
    // {
    //     x = 0;
    //     while(x<1024)
    //     {
    //         mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x808080);
    //         x++;
    //     }
    //     y++;
    // }    
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
//----------------------------RayCast-----Engine--------------//
void    drawRays(t_ray *data)
{
    int tt = 8;
    char Rg= '0';
    char Lg= '0';
    int r,mx,my,mp,dof; float rx,ry,ra,xo,yo,disT;
    ra = pa-DR*30; if(ra<0){ ra+=2*pi;} if(ra>2*pi){ ra-=2*pi;}
    for(r=0; r<60; r++)
    {
        //Linea Orizzontale
        dof = 0;
        float disH=1000000,hx=px,hy=py;
        float aTan=-1/tan(ra);
        if (ra>pi){ry = (((int)py>>6)<<6)-0.0001; rx=(py-ry)*aTan+px; yo=-64; xo=-yo*aTan;} //looking up
        if (ra<pi){ry = (((int)py>>6)<<6)+64;     rx=(py-ry)*aTan+px; yo= 64; xo=-yo*aTan;} //looking down
        if (ra == 0 || ra==pi) { rx=px; ry=py; dof=8;} //looking straight left or right
        while (dof<8)
        {
            mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;
            //if (mp>0 && mp<mapX*mapY && map[mp] > 1) { hx=rx; hy=ry; disH=dist(px,py,hx,hy,ra); dof = 8; data->color = 'F';} 
            if(mp>0 && mp<mapX*mapY && map[mp] == 1){ hx=rx; hy=ry; disH=dist(px,py,hx,hy,ra); dof = 8; data->color ='0';}//   hit wall       
            
            else{ rx+=xo; ry+=yo; dof+=1;}//next  
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
            if(mp>0 && mp<mapX*mapY && map[mp] ==1){ vx=rx; vy=ry; disV=dist(px,py,vx,vy,ra);dof = 8; data->color ='0';}//   hit wall
                  
            else{   rx+=xo; ry+=yo; dof+=1;}//next  
        }
        if (disV<disH){ rx=vx; ry=vy; disT=disV; Rg = 'A';}  
        if (disH<disV){ rx=hx; ry=hy; disT=disH; Rg = 'F'; }
        //mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img3, rx, ry);
        //--Draw 3D Walls--
        float ca=pa-ra; if(ca<0){ ca+=2*pi;} if(ca>2*pi){ ca-=2*pi;} disT=disT*cos(ca);//fix fisheye
        float lineH=(mapS*320)/disT; if (lineH>320){lineH=320;}
        float lineO=160-lineH/2;
        //mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img4s, (r*8+512), (-lineH)); 
        //mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img4s, (r*8+512), (lineH+lineO));
        int y;
        FILE * fp;
        fp = fopen ("file.xpm", "w");
        fprintf(fp, "/* XPM */\n static char *dddsuca[] = {\n");
        fprintf(fp, "%c%d %d %d %d %c%c\n", '"', 8, (int)lineH, 1, 1, '"', ',');
        fprintf(fp, "%c c #%c%d%d%d%c%d%c%c\n", '"', Rg,0,0,0,data->color,0, '"', ',');
        fprintf(fp, "/* pixels */\n");
        draw(r*4+512, 320, (int)lineH, data, fp);
        temps = (int)lineH;
        data->img4 = mlx_xpm_file_to_image(data->mlx_ptr, "file.xpm", &tt, &temps);
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img4, (r*8+512), (lineO));
        //mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img4s, (r*8+512), (lineH+lineO));
        ra+=DR; if(ra<0){ ra+=2*pi;} if(ra>2*pi){ ra-=2*pi;}
        //data->ssa = 0;
    }   
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
    data.img = mlx_xpm_file_to_image(data.mlx_ptr, "wall.xpm", &pss, &pss);
    //data.img4s = mlx_xpm_file_to_image(data.mlx_ptr, "wll.xpm", &w, &h1);
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