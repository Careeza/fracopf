/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 13:58:31 by prastoin          #+#    #+#             */
/*   Updated: 2019/01/14 15:50:27 by fbecerri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAC_H
# define FRAC_H

# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include "include/mlx.h"
# include <stddef.h>
# include <complex.h>

# define KEY_LESS 78
# define KEY_PLUS 69
# define KEY_UP 125
# define KEY_DOWN 126
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_SPACE 53
# define KEY_NUM6 88
# define KEY_NUM3 85
# define SCREEN_X 500
# define SCREEN_Y 500

typedef _Complex double	t_complex;

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	void	*ximg;
	void	*img;
	int		*img_ptr;

	int		dim;
	char	**tab;
	int		fd;
	int		ord;
	int		ab;
	int		**z;
	int		more;
	int		less;

	double	zoom;
	double	position_y;
	double	position_x;
	int		hauteur;
	int		isoparr;
	int		frac;
	t_complex julia;
	int			lock;

	double	xmouse;
	double	ymouse;
	int i;
	int x;
	int y;
	int xstart;
	int ystart;
	int zstart;
	double grad;
	int		iter;
}				t_data;

int				get_z_max(t_data *fdf);
int				parser(t_data *fdf);
int				data(t_data *fdf);
int				algo(t_data *fdf, int x, int y);

#endif


