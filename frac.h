/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 13:58:31 by prastoin          #+#    #+#             */
/*   Updated: 2019/01/14 16:48:12 by fbecerri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAC_H
# define FRAC_H

# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "include/mlx.h"
# include <stddef.h>
# include <complex.h>
# include <pthread.h>
# include "libft.h"

# define NBR_THREADS 75
# define KEY_LESS 69
# define KEY_PLUS 44
# define KEY_UP 125
# define KEY_DOWN 126
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_SPACE 53
# define KEY_NUM6 88
# define KEY_NUM3 85
# define SCREEN_X 750
# define SCREEN_Y 750

typedef _Complex double	t_complex;

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*img_ptr;

	void	*img2;
	int		*img_new_ptr;

	double	zoom;
	double	position_y;
	double	position_x;
	int		frac;
	t_complex julia;
	int			lock;

	double	xmouse;
	double	ymouse;
	double	screenx;
	double	screeny;
	int		iter;
}				t_data;

typedef struct			s_worker_arg
{
	t_data		*frac;
	int			start_y;
	int			end_y;
}						t_worker_arg;

void	ft_init(t_data *frac);
int		main_init(t_data *frac);

int		render(t_data *frac);

int		ft_div6(t_complex z, int iter, t_complex c);
int		ft_div5(t_complex c, int iter);
int		ft_div4(t_complex c, int iter);
int		ft_div3(t_complex c, int iter);
int		ft_div2(t_complex z, int iter, t_complex c);
int		ft_div(t_complex c, int iter);

int		deal_key(int key, t_data *frac);
int		funct(int x, int y, t_data *frac);
int		mouse_hook(int button, int x, int y, t_data *frac);

#endif


