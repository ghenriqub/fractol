/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:21:51 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/06/03 15:06:15 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_malloc_error(void)
{
	perror ("Problems with memory allocation!");
	exit (EXIT_FAILURE);
}

void	ft_data_init(t_fractol *fractol)
{
	fractol->escape_value = 4;
	fractol->iterations = ITERATIONS;
	fractol->shift_x = 0.0;
	fractol->shift_y = 0.0;
	fractol->zoom = 1.0;
}

void	ft_events_init(t_fractol *fractol)
{
	mlx_hook(fractol->mlx_window, KeyPress, KeyPressMask, \
				ft_key_handle, fractol);
	mlx_hook(fractol->mlx_window, ButtonPress, ButtonPressMask, \
				ft_mouse_handle, fractol);
	mlx_hook(fractol->mlx_window, DestroyNotify, StructureNotifyMask, \
				ft_close_handle, fractol);
}

void	ft_fractol_init(t_fractol *fractol)
{
	fractol->mlx_connection = mlx_init();
	if (!fractol->mlx_connection)
		ft_malloc_error();
	fractol->mlx_window = mlx_new_window(fractol->mlx_connection, WIDTH, \
											HEIGHT, fractol->name);
	if (!fractol->mlx_window)
	{
		mlx_destroy_display(fractol->mlx_connection);
		free(fractol->mlx_connection);
		ft_malloc_error();
	}
	fractol->img.img_ptr = mlx_new_image(fractol->mlx_connection, \
											WIDTH, HEIGHT);
	if (!fractol->img.img_ptr)
	{
		mlx_destroy_window(fractol->mlx_connection, fractol->mlx_window);
		mlx_destroy_display(fractol->mlx_connection);
		free(fractol->mlx_connection);
		ft_malloc_error();
	}
	fractol->img.pixels_ptr = mlx_get_data_addr(fractol->img.img_ptr, \
			&fractol->img.bpp, &fractol->img.line_len, &fractol->img.endian);
	ft_events_init(fractol);
	ft_data_init(fractol);
}
