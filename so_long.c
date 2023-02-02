/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 04:17:31 by mben-zeh          #+#    #+#             */
/*   Updated: 2023/01/15 23:10:17 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	ft_move_to(t_data *data, int x_new, int y_new, char *img)
{
	if (data->map.map[y_new][x_new] == 'E')
	{
		ft_putmsg(1);
		exit(0);
	}
	if (data->map.map[y_new][x_new] == 'C')
	{
		data->textur.c--;
		if (data->textur.c == 0)
		{
			put_image(data, "textures/dummy.xpm", data->map.pexit.y,
				data->map.pexit.y);
			put_image(data, "textures/EXIT1.xpm", data->map.pexit.y,
				data->map.pexit.x);
		}
	}
	data->map.map[data->map.player.y][data->map.player.x] = '0';
	data->map.map[y_new][x_new] = 'P';
	put_image(data, "textures/dummy.xpm", data->map.player.y,
		data->map.player.x);
	put_image(data, "textures/dummy.xpm", y_new, x_new);
	put_image(data, img, y_new, x_new);
	free(img);
}

char	*ft_swap_to(t_data *data)
{
	char		*str;
	char		*move;
	static int	m;

	str = NULL;
	if (data->keycode == 0 && m % 2 == 0)
		str = ft_strdup("textures/PL1.xpm");
	else if (data->keycode == 1 && m % 2 == 0)
		str = ft_strdup("textures/PB1.xpm");
	else if (data->keycode == 2 && m % 2 == 0)
		str = ft_strdup("textures/PR1.xpm");
	else if (data->keycode == 13 && m % 2 == 0)
		str = ft_strdup("textures/PT1.xpm");
	else if (data->keycode == 0 && m % 2 != 0)
		str = ft_strdup("textures/PL2.xpm");
	else if (data->keycode == 1 && m % 2 != 0)
		str = ft_strdup("textures/PB2.xpm");
	else if (data->keycode == 2 && m % 2 != 0)
		str = ft_strdup("textures/PR2.xpm");
	else if (data->keycode == 13 && m % 2 != 0)
		str = ft_strdup("textures/PT2.xpm");
	m++;
	ft_putstr("The number of movemet is : ");
	move = ft_itoa(m);
	return (ft_putstr(move), ft_putstr("\n"), free(move), str);
}

int	ft_keycode(int keycode, t_data *data)
{
	int		*x;
	int		*y;
	char	**map;
	int		c;

	x = &data->map.player.x;
	y = &data->map.player.y;
	map = data->map.map;
	data->keycode = keycode;
	c = data->textur.c;
	if (keycode == 0)
		if (map[*y][*x - 1] != '1' && (map[*y][*x - 1] != 'E' || !c))
			return (ft_move_to(data, *x - 1, *y, ft_swap_to(data)), (*x)--, 0);
	if (keycode == 1)
		if (map[*y + 1][*x] != '1' && (map[*y + 1][*x] != 'E' || !c))
			return (ft_move_to(data, *x, *y + 1, ft_swap_to(data)), (*y)++, 0);
	if (keycode == 2)
		if (map[*y][*x + 1] != '1' && (map[*y][*x + 1] != 'E' || !c))
			return (ft_move_to(data, *x + 1, *y, ft_swap_to(data)), (*x)++, 0);
	if (keycode == 13)
		if (map[*y - 1][*x] != '1' && (map[*y - 1][*x] != 'E' || !c))
			return (ft_move_to(data, *x, *y - 1, ft_swap_to(data)), (*y)--, 0);
	if (keycode == 53)
		exit(0);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 2)
	{
		check_map(&data, av[1]);
		data.mlx_ptr = mlx_init();
		data.win_ptr = mlx_new_window(data.mlx_ptr, data.win.width * IMG_W,
				data.win.height * IMG_H, "so_long");
		show_map(&data);
		mlx_hook(data.win_ptr, 17, 0, ft_close, &data);
		mlx_hook(data.win_ptr, 2, 0, ft_keycode, &data);
		mlx_loop(data.mlx_ptr);
	}
	else
		msg_error(0, 0, "usage :./so_long *.ber", exit);
	return (0);
}

//w=13,s=1,a=0,d=2
