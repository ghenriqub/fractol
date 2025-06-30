/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:25:16 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/06/04 17:18:56 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h> // perror
# include <stdlib.h> // malloc, free
# include <unistd.h> // write, strerror
# include "minilibx-linux/mlx.h" // minilibx
# include "X11/X.h" // mouse handle
# include "X11/keysym.h" // key handle

# define BLACK 0X000000
# define WHITE 0XFFFFFF
# define RED 0XFF0000
# define GREEN 0X00FF00
# define BLUE 0X0000FF
# define BRITISH 0XFCBE11
# define MAGENTA 0XFF00FF
# define LIME 0XCCFF00
# define ORANGE 0XFF6600
# define PURPLE 0X660066
# define AQUA 0X33CCCC
# define PINK 0XFF66B2
# define ELECTRIC 0X0066FF
# define LAVA 0XFF3300
# define NEON 0XCFFF04

# define WIDTH 800
# define HEIGHT 800
# define ITERATIONS 42
# define BACKGROUND BLACK
# define MARGIN GREEN
# define POINT WHITE

typedef struct s_complex
{
	double	x;
	double	y;
}	t_complex;

typedef struct s_image
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_fractol
{
	char	*name;
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;
	double	escape_value;
	int		iterations;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
}	t_fractol;

void		ft_fractol_render(t_fractol *fractol);
int			ft_strncmp(const char *s1, const char *s2, unsigned int n);

t_complex	ft_sum_complex(t_complex z1, t_complex z2);
t_complex	ft_square_complex(t_complex z);

void		ft_fractol_init(t_fractol *fractol);
void		ft_data_init(t_fractol *fractol);
void		ft_events_init(t_fractol *fractol);
int			ft_julia_track(int x, int y, t_fractol *fractol);

int			ft_key_handle(int keysym, t_fractol *fractol);
int			ft_close_handle(t_fractol *fractol);
int			ft_mouse_handle(int button, int x, int y, t_fractol *fractol);

#endif
