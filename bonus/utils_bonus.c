/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 04:17:48 by mben-zeh          #+#    #+#             */
/*   Updated: 2023/01/15 23:13:19 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	check_map(t_data *data, char *filename)
{
	data->map.map = load_map(check_and_open(filename));
	if (!data->map.map)
		msg_error(0, 0, strerror(errno), exit);
	count_textur(data);
	check_valid_path(load_map(check_and_open(filename)), data);
}

void	put_image(t_data *data, char *img, int y, int x)
{
	int	width;
	int	height;

	data->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, img, &width, &height);
	if (!data->img_ptr)
		msg_error(img, 0, strerror(errno), exit);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, x, y);
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
}

void	show_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map.map[++i])
	{
		j = -1;
		while (data->map.map[i][++j])
		{
			put_image(data, "textures/dummy.xpm", i * IMG_W, j * IMG_H);
			if (i == 0 || j == 0 || j == data->win.width - 1
				|| i == data->win.height - 1)
				put_image(data, "textures/tree.xpm", i * IMG_W, j * IMG_H);
			else if (data->map.map[i][j] == '1')
				put_image(data, "textures/treewire.xpm", i * IMG_W, j * IMG_H);
			else if (data->map.map[i][j] == 'C')
				put_image(data, "textures/key01.xpm", i * IMG_W, j * IMG_H);
			else if (data->map.map[i][j] == 'P')
				put_image(data, "textures/PB1.xpm", i * IMG_W, j * IMG_H);
			else if (data->map.map[i][j] == 'E')
				put_image(data, "textures/EXIT.xpm", i * IMG_W, j * IMG_H);
			else if (data->map.map[i][j] == 'A')
				put_image(data, "textures/EEEE.xpm", i * IMG_W, j * IMG_H);
		}
	}
}

int	ft_nbrlen(long n)
{
	int	count;

	count = 0;
	if (n <= 0)
	{
		count++;
		n *= (-1);
	}
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	r;
	char	*str;
	int		len;
	int		sign;

	r = n;
	sign = 0;
	len = ft_nbrlen(r);
	str = malloc(len + 1);
	if (!str)
		return (0);
	str[len] = 0;
	if (r < 0)
	{
		str[0] = '-';
		r *= (-1);
		len--;
		sign++;
	}
	while (len > 0)
	{
		str[len-- + sign - 1] = r % 10 + 48;
		r /= 10;
	}
	return (str);
}
