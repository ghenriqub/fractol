/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:15:42 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/06/03 14:28:59 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_putstr_fd(const char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i])
		i++;
	write (fd, s, i);
}

static double	ft_atodbl(char *s)
{
	long	integer_part;
	double	fractional_part;
	double	pow;
	int		sign;

	integer_part = 0;
	fractional_part = 0;
	sign = 1;
	pow = 1;
	while (*s < 33)
		++s;
	while ('+' == *s || '-' == *s)
		if ('-' == *s++)
			sign = -sign;
	while (*s != '.' && *s)
		integer_part = (integer_part * 10) + (*s++ - 48);
	if ('.' == *s)
		++s;
	while (*s)
	{
		pow /= 10;
		fractional_part += (*s++ - 48) * pow;
	}
	return ((integer_part + fractional_part) * sign);
}

static void	ft_print_usage(void)
{
	const char	*error_message;

	error_message = "Please enter one of the above:\n" \
					"\t\"./fractol mandelbrot\"\n" \
					"\t\"./fractol julia <value_1> <value_2>\"\n";
	ft_putstr_fd(error_message, STDERR_FILENO);
}

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	if (!s1 || !s2 || n <= 0)
		return (0);
	while ((*s1 == *s2) && (n > 0) && *s1)
	{
		++s1;
		++s2;
		--n;
	}
	return (*s1 - *s2);
}

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc == 2 && !(ft_strncmp(argv[1], "mandelbrot", 10)))
	{
		fractol.name = argv[1];
		fractol.julia_x = 0;
		fractol.julia_y = 0;
		ft_fractol_init(&fractol);
		ft_fractol_render(&fractol);
		mlx_loop(fractol.mlx_connection);
	}
	else if (argc == 4 && !(ft_strncmp(argv[1], "julia", 5)))
	{
		fractol.name = argv[1];
		fractol.julia_x = ft_atodbl(argv[2]);
		fractol.julia_y = ft_atodbl(argv[3]);
		ft_fractol_init(&fractol);
		ft_fractol_render(&fractol);
		mlx_loop(fractol.mlx_connection);
	}
	else
	{
		ft_print_usage();
		exit(EXIT_FAILURE);
	}
}
