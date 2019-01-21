/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 10:19:44 by prastoin          #+#    #+#             */
/*   Updated: 2019/01/14 16:54:14 by fbecerri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"
#include <stdio.h>

static void	*ft_algo(t_worker_arg *arg)
{
	const	t_data *frac = arg->frac;
	int			x;
	int			y;
	int			res;
	t_complex	c;

	y = arg->start_y - 1;
	while (++y < arg->end_y)
	{
		x = -1;
		while (++x < SCREEN_X)
		{
			c = (x/(double)frac->zoom + (frac->screenx))
			+ ((y / (double)frac->zoom + (frac->screeny)) * I);
			if (frac->frac == 1)
				res = (ft_div(c, frac->iter));
			if (frac->frac == 2)
				res = (ft_div2(c, frac->iter, frac->julia));
			if (frac->frac == 3)
				res = (ft_div3(c, frac->iter));
			if (frac->frac == 4)
				res = (ft_div4(c, frac->iter));
			if (frac->frac == 5)
				res = (ft_div5(c, frac->iter));
			if (frac->frac == 6)
				res = (ft_div6(c, frac->iter, frac->julia));
			frac->img_ptr[y * SCREEN_X + x] =
				((1.5 * res * 0xFFFFFF) / frac->iter);
		}
	}
	return (NULL);
}


int			render(t_data *frac)
{
	pthread_t		threads[NBR_THREADS];
	t_worker_arg	args[NBR_THREADS];
	int				i;

	i = 0;
	frac->screeny = -(SCREEN_Y / (double)(frac->zoom * 2) + frac->position_y)
	+ frac->ymouse / 2;
	frac->screenx = -(SCREEN_X / (double)(frac->zoom * 2) + frac->position_x)
	+ frac->xmouse / 2;
	while (i < NBR_THREADS)
	{
		args[i] = (t_worker_arg) {
			.frac = frac,
			.start_y = i * (float)(SCREEN_Y / NBR_THREADS),
			.end_y = (i + 1) * (float)(SCREEN_Y / NBR_THREADS)
		};
	pthread_create(threads + i, NULL, (void*)ft_algo, args + i);
	i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(frac->mlx, frac->win, frac->img, 0, 0);
	return (0);
}

void		ft_init(t_data *frac)
{
	frac->xmouse = 0;
	frac->ymouse = 0;
	frac->zoom = (SCREEN_X + SCREEN_Y) / 8;
	frac->position_x = 0;
	frac->position_y = 0;
	frac->iter = 50;
	frac->lock = 1;
}

int			main(int argc, char **argv)
{
	t_data	frac;
	int		i;

	frac.julia = -0.25 + 0.66 * I;
	i = 5;
	if (argc == 2)
	{
	frac.frac = atoi(argv[1]);
	ft_init(&frac);
	frac.mlx = mlx_init();
	frac.win = mlx_new_window(frac.mlx, SCREEN_X + 250, SCREEN_Y, "fbecerri frac");
	frac.img = mlx_new_image(frac.mlx, SCREEN_X, SCREEN_Y);
	frac.img_ptr = (int *)mlx_get_data_addr(frac.img, &i, &i, &i);
	main_init(&frac);
	render(&frac);
	mlx_key_hook(frac.win, deal_key, &frac);
	mlx_mouse_hook(frac.win, mouse_hook, &frac);
	mlx_hook(frac.win, 6, (1L<<6), funct, &frac);
	mlx_loop(frac.mlx);
	}
	return (0);
}
