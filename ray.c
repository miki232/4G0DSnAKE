#include "mlx/mlx.h"
#include <stdio.h>
#include "ray.h"
#include <math.h>
#include <stdlib.h>

#include    "All_Textures.ppm"
#include    "sky.ppm"
#include    "sprites.ppm"

float degToRad(float a) { return a*M_PI/180.0;}
float FixAng(float a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}
float distance(ax,ay,bx,by,ang){ return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);}

#define pi 3.1415926535
#define p2 pi/2
#define p3 3*pi/2
#define DR 0.0174533 //one degree in radians
#define GLSW 1024
#define GLSH 512
#define pixelsize 8
#define tilesize 64
//-----------------------------------STRUCs----------------------------//

typedef struct
{
    float r,g,b;
}colore; colore hrgb;

typedef struct
{
    int w,a,d,s;
}ButtonKeys; ButtonKeys Keys;


typedef struct
{
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img4;//used
    char    *addr2;//used
    void    *img;//used
    void    *img1;//used
    void    *img2;
    void    *img3;//floor
    char    *addr;
    char    *addr3;
    int     bppx;
    int     line_len;
    int     endian;
    int     bppx2;
    int     line_len2;
    int     endian2;
    int     bppx3;
    int     line_len3;
    int     endian3;
}datamlx; datamlx data;

typedef struct 
{
    int type; //static, key, enemy
    int state; //on off
    int map; //texture to show
    int x,y,z; //position
}spritess; spritess sp[4];


//------------------------------------------------------------------//
float px,py,pdx,pdy,pa; //player position
int depth[120]; 
int gameState=0, timer=0;
int mapW[]=         //wallsmap
{
    1,1,1,1,1,2,2,3,
    1,0,0,1,0,0,0,1,
    1,0,0,4,0,2,0,1,
    1,4,0,1,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,
};

int mapF[]=          //floors
{
 0,0,0,0,0,0,0,0,
 0,0,0,0,1,1,4,0,
 0,0,0,4,2,4,4,0,
 0,0,0,0,0,4,4,0,
 0,2,0,4,4,4,4,0,
 0,4,0,4,4,4,4,0,
 0,4,0,0,1,4,4,0,
 0,0,0,0,0,0,0,0,	
};

int mapC[]=          //ceiling
{
 0,0,0,0,0,0,0,0,
 0,2,2,2,0,0,0,0,
 0,2,2,2,0,0,0,0,
 0,2,2,2,0,0,0,0,
 0,1,2,1,0,0,0,0,
 0,0,2,0,0,0,0,0,
 0,0,2,1,0,0,0,0,
 0,0,0,0,0,0,0,0,	
};
int mapX=8,mapY=8,mapS=64;

void    drawPlayer()
{
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img1, px, py);
}

int color = 0x00FFFF;
////Function to draw the pixel
void    my_mlx_pixel_put(int x, int y)
{
    char    *dst;

    dst=data.addr + (y * data.line_len + x * (data.bppx / 8));
    *(unsigned int*)dst = color;
}
void    my_mlx_pixel_put2(int x, int y)
{
    char    *dst;

    dst=data.addr2 + (y * data.line_len2 + x * (data.bppx2 / 8));
    *(unsigned int*)dst = color;
}
void    my_mlx_pixel_put3(int x, int y)
{
    char    *dst;

    dst=data.addr3 + (y * data.line_len3 + x * (data.bppx3 / 8));
    *(unsigned int*)dst = color;
}
void    drawplayer2(int x, int y)
{
    int temp = y;
    while (temp <(y+16))
    {
        int tempx = x;
        while (tempx <= (x+16))
        {
            my_mlx_pixel_put2(tempx*4, temp*4);
            tempx++;
        }
        temp++;
    }
}
void     rgb(float r, float g, float b)
{
    hrgb.r = r*255;
    hrgb.g = g*255;
    hrgb.b = b*255;
}

int rgbtohex()
{
    return((int)hrgb.r<<16 | (int)hrgb.g<<8 | (int)hrgb.b);
}

void    drawpwalls(int x, int y, int size, float shade, float ty_Off, float *ty_step, float tx, int hmt)
{
    int temp = y;
    float ty=ty_Off*(*ty_step)+hmt*32;
    while (temp <(y +size))
    {  
        float c=All_Textures[(int)(ty)*32 + (int)(tx)]*shade;
        if(hmt==0) { color=rgbtohex(); rgb(c    ,c/2.0, c/2.0);}
        if(hmt==1) { color=rgbtohex(); rgb(c    ,c    , c/2.0);}
        if(hmt==2) { color=rgbtohex(); rgb(c/2.0,c/2.0, c    );}
        if(hmt==3) { color=rgbtohex(); rgb(c/2.0,c    , c/2.0);}
        int tempx = x;
        while (tempx <= (x+8))
        {
            my_mlx_pixel_put2(tempx, temp);
            tempx++;
        }
        temp++;
        ty+=*ty_step;
    }
    //mlx_put_image_to_window(data.mlx_ptr,data.win_ptr, data.img4, 512,0 );
}

void    drawfloors(int x, int y, int size, float ra)
{
    int temp = y;
    float dy=size-(320/2.0), deg=degToRad(ra), raFix=cos(degToRad(FixAng(pa-ra)));
    float tx=px/2 +cos(deg)*158*32/dy/raFix;
    float ty=py/2 +sin(deg)*158*32/dy/raFix;
    while (temp <(y +size))
    {  
        float c=All_Textures[((int)(ty)&31)*32 + ((int)(tx)&31)]*0.7;
        rgb(c,c,c);
        color=rgbtohex();
        int tempx = x;
        while (tempx <= (x+8))
        {
            my_mlx_pixel_put3(tempx, temp);
            tempx++;
        }
        temp++;
    }
    mlx_put_image_to_window(data.mlx_ptr,data.win_ptr, data.img3, 512,100 );
}
void    drawtile(int x, int y)
{
    int temp = y;
    while (temp <(y +tilesize-1))
    {
        int tempx = x+1;
        while (tempx <= (x +tilesize-1))
        {
            my_mlx_pixel_put(tempx, temp);
            tempx++;
        }
        temp++;
    }
}
///Clear the data img pointer
void    clear()
{
    mlx_destroy_image(data.mlx_ptr, data.img4);
    data.img4 =mlx_new_image(data.mlx_ptr, 585, 322);
    data.addr2 = mlx_get_data_addr(data.img4, &data.bppx2, &data.line_len2, &data.endian2);
}

void    drawSprite()
{
    float sx=sp[0].x-px; //temp float variables
    float sy=sp[0].y-py;
    float sz=sp[0].z;
    float CS=cos(degToRad(pa)), SN=sin(degToRad(pa)); //rotate around origin
    float a=sy*CS+sx*SN; 
    float b=sx*CS-sy*SN; 
    sx=a; sy=b;
    sx=(sx*108.0/sy)+(120/2); //convert to screen x,y
    sy=(sz*108.0/sy)+( 80/2);
    int x,y;
    int scale=32*80/b;   //scale sprite based on distance
    for(x=sx-scale/2;x<sx+scale/2;x++)
    {
        for(y=0;y<scale;y++)
        {
            //printf("%d\n", sp[s].state);
            if(sx>0 && sx<120 && b<depth[x])
            {
                color = 0xF0FF00;
                int temp = y*5;
                //printf("%d  %f\n", x, sy*4.5-temp);
                while (temp <((y*5)+5))
                {  
                    int tempx = x*5;
                    while (tempx <= ((x*5)+5))
                    {
                        int ii = sy*4.5-temp;
                        if(sy*4.5-temp>=300){ ii=80;}//draw point }
                        if(tempx<0){tempx=10;}
                        my_mlx_pixel_put2(tempx, ii);
                        tempx++;
                    }
                    temp++;
                }
            }
        }
    }
}


void    drawMap2D()
{
    int x,y,xo,yo;
    for(y=0;y<mapY;y++)
    {
        for(x=0;x<mapX;x++)
        {
            xo=x*mapS; yo=y*mapS;
            if(mapW[y*mapX+x]>0){color=0xFFFFFF;}else{color = 0x0000F0;}
            drawtile(xo, yo);
            // if(mapW[y*mapX+x]==2){color=0xFF05F0;}
            //     drawtile(xo, yo);
        }
    }
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img,-0,0);
}

float   dist(float ax,float ay, float bx,float by, float ang)
{
    return(sqrt((bx-ax)*(bx-ax)+(by-ay)*(by-ay)));
}
void  drawRadys3D()
{
    int p = 8;
     int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH;
    ra=FixAng(pa+30); //pa-DR*30; if(ra<0){ ra+=2*pi;} if(ra>2*pi){ ra-=2*pi;}
    for(r=0;r<120;r++)
    {
        int vmt=0,hmt=0; //vertical and horizontal map texture num
        int mv=0,mh=0;       
        //Linea verticale
        dof=0, disV=1000000;
        int temps;
        float Tan=tan(degToRad(ra));
             if (cos(degToRad(ra))> 0.001){ rx=(((int)px>>6)<<6)+64;      ry=(px-rx)*Tan+py; xo= 64; yo=-xo*Tan;} //looking left
        else if (cos(degToRad(ra))<-0.001){ rx=(((int)px>>6)<<6) -0.0001; ry=(px-rx)*Tan+py; xo=-64; yo=-xo*Tan;} //looking right
        else { rx=px; ry=py; dof=8;}  //looking straight up or down
        
        while (dof<8)
        {
            mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;
            if(mp>0 && mp<mapX*mapY && mapW[mp] >0){ vmt=mapW[mp]-1; disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py); dof = 8;}//   hit wall     
            else{  rx+=xo; ry+=yo; dof+=1;}//next  
        }
        vx=rx; vy=ry;
        //--Check Horizontal Lines--
        dof=0; disH=1000000;
        Tan=1.0/Tan;;
             if (sin(degToRad(ra))> 0.001){ ry=(((int)py>>6)<<6) -0.0001; rx=(py-ry)*Tan+px; yo=-64; xo=-yo*Tan;} //looking up
        else if (sin(degToRad(ra))<-0.001){ ry=(((int)py>>6)<<6)+64;      rx=(py-ry)*Tan+px; yo= 64; xo=-yo*Tan;} //looking down
        else { rx=px; ry=py; dof=8;} //looking straight left or right
    
        while (dof<8)
        {
            
            mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;
            if(mp>0 && mp<mapX*mapY && mapW[mp]>0){ hmt=mapW[mp]-1; disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py); dof = 8;}//   hit wall 
            else{ rx+=xo; ry+=yo; dof+=1;}//next 
        }        
        color= 0x008000;
        float shade=1;
        if(disV<disH){ hmt=vmt; shade=0.5; rx=vx; ry=vy; disH=disV; color=0xFF0000;} //if(mv==2) { color=0x0000F0;}}
        //if(disH<disV){ rx=hx; ry=hy; disT=disH; color=0xA00000;} //if(mh==2) { color=0x0000A0;}}
        //mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img2, rx, ry);
        ///----------DRAW WALL-----------------
        float ca=FixAng(pa-ra); disH=disH*cos(degToRad(ca));//pa-ra; if(ca<0){ ca+=2*pi;} if(ca>2*pi){ ca-=2*pi;} disH=disH*cos(ca); //fix fisheye
        int lineH=(mapS*322)/disH; 
        float ty_step=32.0/(float)lineH;
        float ty_Off=0;
        if(lineH>322){ ty_Off=(lineH-322)/2.0; lineH=322;} 
        depth[r]=disH;       
        float lineO=162-(lineH>>1);

        float ty=ty_Off*ty_step;// +hmt*32;
        float tx;
        if(shade==1){tx=(int)(rx/2.0)%32; if(ra>180){tx=31-tx;}}
        else        {tx=(int)(ry/2.0)%32; if(ra>90 && ra<270){ tx=31-tx;}}
        //printf("%f\n", ra);
        // drawfloors(r*8+530, lineH,lineO, ra);
        //drawpwalls(r*8+530, lineO,lineH, shade, ty_Off, &ty_step, tx, hmt);
        
        //draw Walls
        int y;
        for(y=0;y<lineH;y++)
        {
            // float c=All_Textures[(int)(ty)*32 + (int)(tx)]*shade;
            // if(hmt==0) { color=rgbtohex(); rgb(c    ,c/2.0, c/2.0);}
            // if(hmt==1) { color=rgbtohex(); rgb(c    ,c    , c/2.0);}
            // if(hmt==2) { color=rgbtohex(); rgb(c/2.0,c/2.0, c    );}
            // if(hmt==3) { color=rgbtohex(); rgb(c/2.0,c    , c/2.0);}
            int pixel=((int)ty*32+(int)tx)*3+(hmt*32*32*3);
            int red =All_Textures[pixel+0]*shade;
            int green =All_Textures[pixel+1]*shade;
            int blue =All_Textures[pixel+2]*shade;
            int tempx = r*5;
            color = (red<<16 | green <<8 | blue);
            while (tempx < ((r*5)+5))
            {
                my_mlx_pixel_put2(tempx, y+lineO);
                tempx++;
            }
            ty+=ty_step;
        }
        //draw floors
        for(y=lineO+lineH;y<322;y++)
        {
            float dy=y-(322/2.0), deg=degToRad(ra), raFix=cos(degToRad(FixAng(pa-ra)));
            tx=px/2 +cos(deg)*158*32/dy/raFix;
            ty=py/2 -sin(deg)*158*32/dy/raFix;
            int mp=mapF[(int)(ty/32.0)*mapX+(int)(tx/32.0)]*32*32;
            int pixel=(((int)(ty)&31)*32+((int)(tx)&31))*3+mp*3;
            int red =All_Textures[pixel+0]*0.7;
            int green =All_Textures[pixel+1]*0.7;
            int blue =All_Textures[pixel+2]*0.7;
            //printf("%d\n", red);
            //color = 0x000000;
            color = (red<<16 | green <<8 | blue );
            int tempx = r*5;
            while (tempx <((r*5)+5))
            {   
                
                my_mlx_pixel_put2(tempx, y);
                tempx++;
            }

            //draw ceiling
            mp=mapC[(int)(ty/32.0)*mapX+(int)(tx/32.0)]*32*32;
            // // c=All_Textures[((int)(ty)&31)*32 + ((int)(tx)&31)+mp]*0.7;
            // // rgb(c/2.0,c/1.2,c/2.0);
            // // color=rgbtohex();
            pixel=(((int)(ty)&31)*32+((int)(tx)&31))*3+mp*3;
            red =All_Textures[pixel+0];
            green =All_Textures[pixel+1];
            blue =All_Textures[pixel+2];
            //printf("%d\n", red);
            //color = 0x000000;
            color = (red<<16 | green <<8 | blue );
            tempx = r*5;
            while (tempx <= ((r*5)+5))
            {   
                if(mp>0){ my_mlx_pixel_put2(tempx, 324-y);}
                tempx++;
            }
        }
        mlx_put_image_to_window(data.mlx_ptr,data.win_ptr, data.img4, 0,0 );

        ra=FixAng(ra-0.5); 
    }
} 

void    drawSky()
{
    int x,y;
    for(y=0;y<40;y++)
    {
        for(x=0;x<120;x++)
        {
            int xo=(int)pa*2-x; if(xo<0){ xo+=120;} xo=xo % 120; 
            int pixel=(y*120+xo)*3;
            int red =sky[pixel+0];
            int green =sky[pixel+1];
            int blue =sky[pixel+2];
            color = (red<<16 | green <<8 | blue);
            int ytemp = y*4;
            while (ytemp<((y*4)+4))
            {
                int tempx = x*5;
                while (tempx < ((x*5)+5))
                {
                    my_mlx_pixel_put2(tempx, ytemp);
                    tempx++;
                }
                ytemp++;
            }
        }
    }
    mlx_put_image_to_window(data.mlx_ptr,data.win_ptr, data.img4, 0,0 );

}

int    display(datamlx *vosid)
{
    if (gameState==4){printf("ok\n");}
    if (Keys.a==1){ pa+=6*0.5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));}//if(pa<  0){ pa+=2*pi;} pdx=cos(pa)*5; pdy=sin(pa)*5;}
    if (Keys.d==1){ pa-=6*0.5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));} //if(pa>2*pi){ pa-=2*pi;} pdx=cos(pa)*5; pdy=sin(pa)*5;}
    
    int xo=0; if(pdx<0){ xo=-20;} else{ xo=20;}
    int yo=0; if(pdy<0){ yo=-20;} else{ yo=20;}
    int ipx=px/64.0, ipx_add_xo=(px+xo)/64.0, ipx_sub_xo=(px-xo)/64.0;
    int ipy=py/64.0, ipy_add_yo=(py+yo)/64.0, ipy_sub_yo=(py-yo)/64.0;
    if (Keys.w==1)
    {
        if(mapW[ipy*mapX        + ipx_add_xo]==0){ px+=pdx*4;}
        if(mapW[ipy_add_yo*mapX + ipx       ]==0){ py+=pdy*4;}
    }
    if (Keys.s==1)
    {
        if(mapW[ipy*mapX        + ipx_sub_xo]==0){ px-=pdx*3;}
        if(mapW[ipy_sub_yo*mapX + ipx       ]==0){ py-=pdy*3;}
    }
    clear(); 
    drawSky();
    drawRadys3D();
    drawSprite();
    
    return (0);
}

int    ButtonDown(int key, datamlx *soid)
{
    if (key == A)
        Keys.a=1;
    if (key == D) 
        Keys.d=1;
    if (key == W) 
        Keys.w=1;
    if (key == S) 
        Keys.s=1;
    if(key==14)
    {
        int xo=0; if(pdx<0){ xo=-20;} else{ xo=25;}
        int yo=0; if(pdy<0){ yo=-20;} else{ yo=25;}
        int ipx=px/64.0, ipx_add_xo=(px+xo)/64.0;
        int ipy=py/64.0, ipy_add_yo=(py+yo)/64.0;
        if (mapW[ipy_add_yo*mapY+ipx_add_xo]==4){ mapW[ipy_add_yo*mapX+ipx_add_xo]=0;}
    }
    if (key == ESC)
        exit(0);
    return (0);
}

int    ButtonUp(int key, datamlx *soid)
{
    if (key == A)
        Keys.a=0;
    if (key == D) 
        Keys.d=0;
    if (key == W) 
        Keys.w=0;
    if (key == S) 
        Keys.s=0;
    return(0);
}

void    init()
{
    int pw=8;
    px = 150; py=400; pa=90;
    data.img = mlx_xpm_file_to_image(data.mlx_ptr, "pg.xpm", &pw, &pw);
    data.img4 =mlx_new_image(data.mlx_ptr, 585, 322);
    //data.addr = mlx_get_data_addr(data.img, &data.bppx, &data.line_len, &data.endian);
    data.addr2 = mlx_get_data_addr(data.img4, &data.bppx2, &data.line_len2, &data.endian2);
    pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));
    sp[0].type=1; sp[0].state=1; sp[0].map=0; sp[0].x=1.5*64; sp[0].y=5*64;   sp[0].z=20; //key
    sp[1].type=2; sp[1].state=1; sp[1].map=1; sp[1].x=1.5*64; sp[1].y=4.5*64; sp[1].z= 0; //light 1
    sp[2].type=2; sp[2].state=1; sp[2].map=1; sp[2].x=3.5*64; sp[2].y=4.5*64; sp[2].z= 0; //light 2
    sp[3].type=3; sp[3].state=1; sp[3].map=2; sp[3].x=2.5*64; sp[3].y=2*64;   sp[3].z=20; //enemy 
}

int main()
{
    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, 585+1,322+1, "Ray1.1");
    init();
    //display(&data);
    mlx_loop_hook(data.mlx_ptr, display, &data);
    mlx_hook(data.win_ptr, 2, 1L << 0, ButtonDown, &data);
    mlx_hook(data.win_ptr, 3, 1L << 1, ButtonUp, &data);
    mlx_loop(data.mlx_ptr);
}