/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 10:19:44 by prastoin          #+#    #+#             */
/*   Updated: 2019/01/10 16:34:52 by fbecerri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

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

static int	ft_algo(t_data *fdf)
{
	int		x;
	int		y;
	int		res;

	y = 0;
	while (y < SCREEN_Y)
	{
		x = 0;
		while (x < SCREEN_X)
		{
			if (fdf->frac == 1)
				res = (ft_div((x/(double)fdf->zoom - (SCREEN_X / (double)(fdf->zoom * 2)) + fdf->position_x) + ((y / (double)fdf->zoom - (SCREEN_Y / (double)(fdf->zoom * 2)) + fdf->position_y) * I), fdf->iter));
			if (fdf->frac == 2)
				res = (ft_div2((x/(double)fdf->zoom - (SCREEN_X / (double)(fdf->zoom * 2)) + fdf->position_x) + ((y / (double)fdf->zoom - (SCREEN_Y / (double)(fdf->zoom * 2)) + fdf->position_y) * I), fdf->iter, fdf->julia));
			if (fdf->frac == 3)
				res = (ft_div3((x/(double)fdf->zoom - (SCREEN_X / (double)(fdf->zoom * 2)) + fdf->position_x) + ((y / (double)fdf->zoom - (SCREEN_Y / (double)(fdf->zoom * 2)) + fdf->position_y) * I), fdf->iter));
			fdf->img_ptr[y * SCREEN_X + x] = ((1.5 * res * 0xFFFFFF) / fdf->iter);
			x++;
		}
		y++;
	}
	fdf->img_ptr[1000*500+500] = 0xFF;
	fdf->img_ptr[1000*500+501] = 0xFF;
	fdf->img_ptr[1000*500+499] = 0xFF;
	fdf->img_ptr[1000*499+500] = 0xFF;
	fdf->img_ptr[1000*499+501] = 0xFF;
	fdf->img_ptr[1000*499+499] = 0xFF;
	fdf->img_ptr[1000*501+500] = 0xFF;
	fdf->img_ptr[1000*501+501] = 0xFF;
	fdf->img_ptr[1000*501+499] = 0xFF;
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	return (0);
}

/*
static int	ft_div(t_data *fdf, int j)
{
	int			i;
	t_complex	z;
	t_complex	c;

	z = 0;
	i = 0;
	c = (j % SCREEN_X) / (double)fdf->zoom - 2.5 + (fdf->position_x);
	c += ((j / SCREEN_X) / (double)fdf->zoom - 2.5 + fdf->position_y) * I;
	while (i < 50 && cabs(z) <= 2)
	{
		z = z * z + c;
		i++;
	}
	return (i);
}

void	ft_color(t_data *fdf, int j, int i)
{
	int color;
	double percent;

	color = 0xFFFFFF;
	percent = i / (double)100;
	color = color * percent;
	fdf->img_ptr[j] = color;
}

static int	ft_algo(t_data *fdf)
{
	int		j;
	double	res;

	j = 0;
	while (j < 1000000)
	{
		res = ft_div(fdf, j);
		if (res >= 99)
		{
			fdf->img_ptr[j] = 0x0;
		}
		else
		{
			ft_color(fdf, j, res);
		}
		j++;
	}
	return (0);
}
*/
static int	deal_key(int key, t_data *fdf)
{
	printf("%d--key\n", key);
	if (key == KEY_LESS)
		fdf->zoom -= 25;
	if (key == KEY_PLUS)
		fdf->iter++;
	if (key == 49)
		fdf->lock = fdf->lock == 0 ? 1 : 0;
	if (key == KEY_UP)
		fdf->position_y += (20 / fdf->zoom);
	if (key == KEY_DOWN)
		fdf->position_y -= (20 / fdf->zoom);
	if (key == KEY_RIGHT)
		fdf->position_x += (20 / fdf->zoom);
	if (key == KEY_LEFT)
		fdf->position_x -= (20 / fdf->zoom);
	if (key == KEY_SPACE)
		exit (0);
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, SCREEN_X, SCREEN_Y);
	fdf->img_ptr = (int *)mlx_get_data_addr(fdf->img, &key, &key, &key);
	ft_algo(fdf);
	return (0);
}

static int	funct(int x, int y, t_data *fdf)
{
	if (fdf->lock == 0)
	{
		printf("x = %d--y = %d\n", x, y);
		fdf->julia = x / 200.0  - 2.5 + ((y / 200.0 - 2.5) * I);
		ft_algo(fdf);
	}
	return (0);
}

static int	mouse_hook(int button, int x, int y, t_data *fdf)
{
	printf("button = %d, x = %d, y = %d\n", button, x, y);
	printf("z = %f+i%f\n",creal(fdf->julia),cimag(fdf->julia));
	if (button == 1)
		fdf->zoom = fdf->zoom * 2;
	if (button == 2)
		fdf->zoom = fdf->zoom * 0.5;
	if (button == 4)
		fdf->position_y += 0.03;
	if (button == 5)
		fdf->position_y -= 0.03;
	if (button == 6)
		fdf->position_x += 0.03;
	if (button == 7)
		fdf->position_x -= 0.03;
	deal_key(0, fdf);
	return (0);
}

static void	ft_init(t_data *fdf)
{
	fdf->zoom = 200;
	fdf->julia = 0;
	fdf->position_x = 0;
	fdf->position_y = 0;
	fdf->hauteur = 1;
	fdf->more = 0;
	fdf->less = 0;
	fdf->iter = 50;
	fdf->lock = 0;
}

int			main(int argc, char **argv)
{
	t_data	fdf;
	int		i;

	i = 5;
	(void)argc;
	fdf.frac = atoi(argv[1]);
	ft_init(&fdf);
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, SCREEN_X, SCREEN_Y, "prastoin's fdf");
	fdf.img = mlx_new_image(fdf.mlx, SCREEN_X, SCREEN_Y);
	fdf.img_ptr = (int *)mlx_get_data_addr(fdf.img, &i, &i, &i);
	ft_algo(&fdf);
	mlx_key_hook(fdf.win, deal_key, &fdf);
	mlx_mouse_hook(fdf.win, mouse_hook, &fdf);
	mlx_hook(fdf.win, 6, (1L<<6), funct, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
