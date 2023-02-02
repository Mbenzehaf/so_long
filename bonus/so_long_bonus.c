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
	return (move = ft_itoa(++m), put_image(data, "textures/tree.xpm", 0, 0),
		put_image(data, "textures/tree.xpm", 0, IMG_W),
		mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 10, 0xFFC300, move),
		free(move), str);
}

int	ft_keycode(int keycode, t_data *data)
{
	int		*x;
	int		*y;
	char	**map;

	x = &data->map.player.x;
	y = &data->map.player.y;
	map = data->map.map;
	data->keycode = keycode;
	if (keycode == 0 && (map[*y][*x - 1] != '1' && (map[*y][*x - 1] != 'E'
		|| !data->textur.c || map[*y][*x - 1] == 'A')))
		(ft_move_p(data, *x - 1, *y, ft_swap_to(data)), (*x)--, 0);
	if (keycode == 1 && (map[*y + 1][*x] != '1' && (map[*y + 1][*x] != 'E'
		|| !data->textur.c || map[*y + 1][*x] == 'A')))
		(ft_move_p(data, *x, *y + 1, ft_swap_to(data)), (*y)++, 0);
	if (keycode == 2 && (map[*y][*x + 1] != '1' && (map[*y][*x + 1] != 'E'
		|| !data->textur.c || map[*y][*x + 1] == 'A')))
		(ft_move_p(data, *x + 1, *y, ft_swap_to(data)), (*x)++, 0);
	if (keycode == 13 && (map[*y - 1][*x] != '1' && (map[*y - 1][*x] != 'E'
		|| !data->textur.c || map[*y - 1][*x] == 'A')))
		(ft_move_p(data, *x, *y - 1, ft_swap_to(data)), (*y)--);
	if (keycode == 53)
		exit(0);
	return (0);
}

int	ft_m_c(t_data *data, t_list *temp)
{
	if (temp->v == 0)
		return (put_image(data, "textures/key01.xpm", temp->y * IMG_H, temp->x
				* IMG_W), temp->v++, 0);
	else if (temp->v == 1)
		return (put_image(data, "textures/key04.xpm", temp->y * IMG_H, temp->x
				* IMG_W), temp->v++, 0);
	else if (temp->v == 2)
		return (put_image(data, "textures/key03.xpm", temp->y * IMG_H, temp->x
				* IMG_W), temp->v++, 0);
	else if (temp->v == 3)
		return (put_image(data, "textures/key04.xpm", temp->y * IMG_H, temp->x
				* IMG_W), temp->v++, 0);
	else if (temp->v == 4)
		return (put_image(data, "textures/key05.xpm", temp->y * IMG_H, temp->x
				* IMG_W), temp->v++);
	else if (temp->v == 5)
		return (put_image(data, "textures/key06.xpm", temp->y * IMG_H, temp->x
				* IMG_W), temp->v++);
	else if (temp->v == 6)
		return (put_image(data, "textures/key07.xpm", temp->y * IMG_H, temp->x
				* IMG_W), temp->v++);
	else
		return (put_image(data, "textures/key08.xpm", temp->y * IMG_H, temp->x
				* IMG_W), temp->v = 0);
	return (0);
}

int	move_e(t_data *data)
{
	t_list		*temp;
	static int	c;

	if (c % 2000 != 0 || !c)
		return (c++, 0);
	temp = data->map.enemy;
	ft_m_e(data, temp);
	temp = data->map.collect;
	while (temp)
	{
		if (data->map.map[temp->y][temp->x] == 'C')
		{
			put_image(data, "textures/dummy.xpm", temp->y * IMG_H, temp->x
				* IMG_W);
			ft_m_c(data, temp);
		}
		temp = temp->next;
	}
	c++;
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
		mlx_loop_hook(data.mlx_ptr, move_e, &data);
		mlx_loop(data.mlx_ptr);
	}
	else
		msg_error(0, 0, "usage :./so_long *.ber", exit);
	return (0);
}
//w=13,s=1,a=0,d=2