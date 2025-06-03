/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:10:53 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/06/03 15:21:48 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_close_handle(t_fractol *fractol)
{
	mlx_destroy_image(fractol->mlx_connection, fractol->img.img_ptr);
	mlx_destroy_window(fractol->mlx_connection, fractol->mlx_window);
	mlx_destroy_display(fractol->mlx_connection);
	free(fractol->mlx_connection);
	exit(EXIT_SUCCESS);
}

int	ft_key_handle(int keysym, t_fractol *fractol)
{
	if (keysym == XK_Escape)
		ft_close_handle(fractol);
	else if (keysym == XK_Left)
		fractol->shift_x -= (0.5 * fractol->zoom);
	else if (keysym == XK_Right)
		fractol->shift_x += (0.5 * fractol->zoom);
	else if (keysym == XK_Up)
		fractol->shift_y += (0.5 * fractol->zoom);
	else if (keysym == XK_Down)
		fractol->shift_y -= (0.5 * fractol->zoom);
	else if (keysym == XK_Page_Up)
		fractol->iterations += 10;
	else if (keysym == XK_Page_Down)
		fractol->iterations -= 10;
	ft_fractol_render(fractol);
	return (0);
}

int	ft_mouse_handle(int button, int x, int y, t_fractol *fractol)
{
	(void)x, (void)y;
	if (button == Button5)
		fractol->zoom *= 1.15;
	else if (button == Button4)
		fractol->zoom *= 0.85;
	ft_fractol_render(fractol);
	return (0);
}

int	ft_julia_track(int x, int y, t_fractol *fractol)
{
	if (!ft_strncmp(fractol->name, "julia", 5))
	{
		(void)x;
		(void)y;
		mlx_hook(fractol->mlx_window, MotionNotify, PointerMotionMask, \
													ft_julia_track, fractol);
	}
	return (0);
}
