/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 10:19:44 by prastoin          #+#    #+#             */
/*   Updated: 2019/01/14 16:00:07 by fbecerri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "frac.h"

static int	ft_div3(t_complex c, int iter)
{
	t_complex	z;
	int			i;

	i = 0;
	z = 0;
	while (i < iter && cabs(z) <= 2)
	{
		z = ccos(z / c);
		i++;
	}
	return (i);
}

static int	ft_div2(t_complex z, int iter, t_complex c)
{
	int			i;

	i = 0;
	while (i < iter && cabs(z) <= 2)
	{
		z = z * z + c;
		i++;
	}
	return (i);
}

static int	ft_div(t_complex c, int iter)
{
	t_complex	z;
	int			i;

	i = 0;
	z = 0;
	while (i < iter && cabs(z) <= 2)
	{
		z = z * z + c;
		i++;
	}
	return (i);
}

static int	ft_algo(t_data *frac)
{
	int			x;
	int			y;
	int			res;
	t_complex	c;
	double			screeny;
	double			screenx;

	screeny = -(SCREEN_Y / (double)(frac->zoom * 2) + frac->position_y) + frac->ymouse;
	screenx = -(SCREEN_X / (double)(frac->zoom * 2) + frac->position_x) + frac->xmouse;
	y = 0;
	while (y < SCREEN_Y)
	{
		x = 0;
		while (x < SCREEN_X)
		{
			c = (x/(double)frac->zoom + (screenx)) + ((y / (double)frac->zoom + (screeny)) * I);
			if (frac->frac == 1)
				res = (ft_div(c, frac->iter));
			if (frac->frac == 2)
				res = (ft_div2(c, frac->iter, frac->julia));
			if (frac->frac == 3)
				res = (ft_div3(c, frac->iter));
			frac->img_ptr[y * SCREEN_X + x] =
				((1.5 * res * 0xFFFFFF) / frac->iter);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(frac->mlx, frac->win, frac->img, 0, 0);
	return (0);
}

static int	deal_key(int key, t_data *frac)
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
	ft_algo(frac);
	return (0);
}

static int	funct(int x, int y, t_data *frac)
{
	if (frac->lock == 0)
	{
		frac->julia = x / 200.0  - 2.5 + ((y / 200.0 - 2.5) * I);
		ft_algo(frac);
	}
	return (0);
}

static int	mouse_hook(int button, int x, int y, t_data *frac)
{
	if (button == 1)
	{
		frac->xmouse = x/(double)frac->zoom - (SCREEN_X
		/ (double)(frac->zoom * 2) + frac->position_x) + frac->xmouse;
		frac->ymouse = y / (double)frac->zoom - (SCREEN_Y
		/ (double)(frac->zoom * 2) + frac->position_y) + frac->ymouse;
		printf("x = %f y = %f\n", frac->xmouse, frac->ymouse);
		frac->position_y = 0;
		frac->position_x = 0;
		frac->zoom = frac->zoom * 2;
	}
	if (button == 2)
		frac->zoom = frac->zoom * 0.5;
	if (button == 4)
		frac->position_y += 0.03;
	if (button == 5)
		frac->position_y -= 0.03;
	if (button == 6)
		frac->position_x += 0.03;
	if (button == 7)
		frac->position_x -= 0.03;
	ft_algo(frac);
	return (0);
}

static void	ft_init(t_data *frac)
{
	frac->xmouse = 0;
	frac->ymouse = 0;
	frac->zoom = (SCREEN_X + SCREEN_Y) / 8;
	frac->julia = 0;
	frac->position_x = 0;
	frac->position_y = 0;
	frac->hauteur = 1;
	frac->more = 0;
	frac->less = 0;
	frac->iter = 50;
	frac->lock = 1;
}

int			main(int argc, char **argv)
{
	t_data	frac;
	int		i;

	i = 5;
	if (argc == 2)
	{
	frac.frac = atoi(argv[1]);
	ft_init(&frac);
	frac.mlx = mlx_init();
	frac.win = mlx_new_window(frac.mlx, SCREEN_X, SCREEN_Y, "fbecerri frac");
	frac.img = mlx_new_image(frac.mlx, SCREEN_X, SCREEN_Y);
	frac.img_ptr = (int *)mlx_get_data_addr(frac.img, &i, &i, &i);
	ft_algo(&frac);
	mlx_key_hook(frac.win, deal_key, &frac);
	mlx_mouse_hook(frac.win, mouse_hook, &frac);
	mlx_hook(frac.win, 6, (1L<<6), funct, &frac);
	mlx_loop(frac.mlx);
	}
	return (0);
}
