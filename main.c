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

static int	ft_div(t_data *fdf, int j)
{
	float	c[2];
	float	z[2];
	float	tmp;
	float	res;

	z[0] = 0;
	z[1] = 0;
	res = 0;
	fdf->i = 0;
	c[0] = (j % SCREEN_X) / (float)200 - 2.5;
	c[1] = (j / SCREEN_X) / (float)200 - 2.5;
	while (fdf->i < 100 && res < 10000)
	{
		tmp = z[0];
		z[0] = z[0] * z[0] - z[1] * z[1] + c[0];
		z[1] = 2 * tmp * z[1] + c[1];
		res = sqrt(z[0] * z[0] + z[1] * z[1]);
		fdf->i++;
	}
	return (res);
}

void	ft_color(t_data *fdf, int j)
{
	int color;
	float percent;

	color = 0xFF7F24;
	percent = fdf->i / (float)100;
	color = color * percent + 0x0000FF;
	fdf->img_ptr[j] = color;
}

static int	ft_algo(t_data *fdf)
{
	int		j;
	float	res;

	j = 0;
	while (j < SCREEN_Y * SCREEN_X)
	{
		res = ft_div(fdf, j);
		if (res <= 1000)
			fdf->img_ptr[j] = 0x0;
		else
			ft_color(fdf, j);
		j++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	return (0);
}

static int	deal_key(int key, t_data *fdf)
{
	if (key == KEY_LESS)
		fdf->zoom -= 5;
	if (key == KEY_PLUS)
		fdf->zoom += 5;
	if (key == KEY_UP)
		fdf->position_y += 15;
	if (key == KEY_DOWN)
		fdf->position_y -= 15;
	if (key == KEY_RIGHT)
		fdf->position_x += 15;
	if (key == KEY_LEFT)
		fdf->position_x -= 15;
	if (key == KEY_SPACE)
		exit (0);
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, SCREEN_X, SCREEN_Y);
	fdf->img_ptr = (int *)mlx_get_data_addr(fdf->img, &key, &key, &key);
	ft_algo(fdf);
	return (0);
}

static void	ft_init(t_data *fdf)
{
	fdf->zoom = 53;
	fdf->position_x = SCREEN_X / 4;
	fdf->position_y = SCREEN_Y / 4;
	fdf->hauteur = 1;
	fdf->more = 0;
	fdf->less = 0;
}

int			main(int argc, char **argv)
{
	t_data	fdf;
	int		i;

	i = 5;
	(void)argc;
	(void)argv;
	ft_init(&fdf);
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, SCREEN_X, SCREEN_Y, "prastoin's fdf");
	fdf.img = mlx_new_image(fdf.mlx, SCREEN_X, SCREEN_Y);
	fdf.img_ptr = (int *)mlx_get_data_addr(fdf.img, &i, &i, &i);
	ft_algo(&fdf);
	mlx_key_hook(fdf.win, deal_key, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
