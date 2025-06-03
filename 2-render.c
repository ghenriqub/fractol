/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:47:37 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/05/18 10:56:11 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_mandel_vs_julia(t_complex *z, t_complex *c, t_fractol *fractol)
{
	if (!(ft_strncmp(fractol->name, "julia", 5)))
	{
		c->x = fractol->julia_x;
		c->y = fractol->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}

static void	ft_put_pixel(int x, int y, t_img *img, int colour)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = colour;
}

static void	ft_handle_pixel(int x, int y, t_fractol *fractol)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			colour;

	i = 0;
	z.x = (ft_map(x, -2, +2, WIDTH) * fractol->zoom) + fractol->shift_x;
	z.y = (ft_map(y, +2, -2, HEIGHT) * fractol->zoom) + fractol->shift_y;
	ft_mandel_vs_julia(&z, &c, fractol);
	while (i < fractol->iterations)
	{
		z = ft_sum_complex(ft_square_complex(z), c);
		if (((z.x * z.x) + (z.y * z.y)) > fractol->escape_value)
		{
			colour = ft_map(i, BLACK, BLUE, fractol->iterations);
			ft_put_pixel(x, y, &fractol->img, colour);
			return ;
		}
		++i;
	}
	ft_put_pixel(x, y, &fractol->img, WHITE);
}

void	ft_fractol_render(t_fractol *fractol)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			ft_handle_pixel(x, y, fractol);
	}
	mlx_put_image_to_window (fractol->mlx_connection, fractol->mlx_window, \
							fractol->img.img_ptr, 0, 0);
}
