#ifndef RAY_H
# define RAY_H

typedef struct s_ray
{
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img;
    void    *img2;
    void    *img3;
    void    *img4;
    void    *background;
    void    *img4s;
    int     y;
    int     x;
    int     ssa;
    char     color;
	int w,a,d,s;
}           t_ray;



typedef enum e_keys
{
	KB_PAGE_UP = 116,
	KB_PAGE_DOWN = 121,
	W = 13,
	A = 0,
	S = 1,
	D = 2,
	ESC = 53,
	PLUS = 69,
	MINUS = 78,
	RIGHT = 123,
	LEFT = 124,
	UP = 125,
	DOWN = 126,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
}	t_keys;

#endif