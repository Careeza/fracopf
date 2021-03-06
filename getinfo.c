#include "frac.h"

int	deal_key(int key, t_data *frac)
{
	if (key == KEY_LESS)
		frac->zoom -= 25;
	if (key == KEY_PLUS)
		frac->iter++;
	if (key == 49)
		frac->lock = frac->lock == 0 ? 1 : 0;
	if (key == KEY_UP)
		frac->position_y += (20 / frac->zoom);
	if (key == KEY_DOWN)
		frac->position_y -= (20 / frac->zoom);
	if (key == KEY_RIGHT)
		frac->position_x += (20 / frac->zoom);
	if (key == KEY_LEFT)
		frac->position_x -= (20 / frac->zoom);
	if (key == KEY_SPACE)
		exit (0);
	mlx_destroy_image(frac->mlx, frac->img);
	frac->img = mlx_new_image(frac->mlx, SCREEN_X, SCREEN_Y);
	frac->img_ptr = (int *)mlx_get_data_addr(frac->img, &key, &key, &key);
	render(frac);
	return (0);
}

#include <stdio.h>

int	funct(int x, int y, t_data *frac)
{
	if (frac->lock == 0)
	{
		frac->julia = x / 200.0  - 2.5 + ((y / 200.0 - 2.5) * I);
		render(frac);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *frac)
{
	if (button == 1 && x < 750)
	{
		frac->xmouse = x/(double)frac->zoom - (SCREEN_X
		/ (double)(frac->zoom * 2) + frac->position_x) + frac->xmouse;
		frac->ymouse = y / (double)frac->zoom - (SCREEN_Y
		/ (double)(frac->zoom * 2) + frac->position_y) + frac->ymouse;
		frac->position_y = 0;
		frac->position_x = 0;
		frac->zoom = frac->zoom * 2;
	}
	if (button == 1 && x > 750)
	{
		main_init(frac);
		frac->frac = (y < 250 ? 1 : frac->frac);
		frac->frac = (y > 250 ? 2 : frac->frac);
		frac->frac = (y > 550 ? 3 : frac->frac);
		ft_init(frac);
	}
	if (button == 2)
		frac->zoom = frac->zoom * 0.5;
	if (button == 5)
		frac->position_y -= (20 / frac->zoom);
	if (button == 4)
		frac->position_y += (20 / frac->zoom);
	if (button == 6)
		frac->position_x += (20 / frac->zoom);
	if (button == 7)
		frac->position_x -= (20 / frac->zoom);
	render(frac);
	return (0);
}
