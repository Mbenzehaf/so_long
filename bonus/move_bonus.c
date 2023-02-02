/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 07:22:07 by mben-zeh          #+#    #+#             */
/*   Updated: 2023/01/19 07:22:09 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	ft_move_p(t_data *data, int x_new, int y_new, char *img)
{
	if (data->map.map[y_new][x_new] == 'E')
		return (ft_putmsg(1), exit(0), 0);
	if (data->map.map[y_new][x_new] == 'A')
		return (ft_putmsg(2), exit(0), 0);
	if (data->map.map[y_new][x_new] == 'C')
	{
		data->textur.c--;
		if (data->textur.c == 0)
		{
			put_image(data, "textures/dummy.xpm", data->map.pexit.y * IMG_H,
				data->map.pexit.y * IMG_W);
			put_image(data, "textures/EXIT1.xpm", data->map.pexit.y * IMG_H,
				data->map.pexit.x * IMG_W);
		}
	}
	data->map.map[data->map.player.y][data->map.player.x] = '0';
	data->map.map[y_new][x_new] = 'P';
	put_image(data, "textures/dummy.xpm", data->map.player.y * IMG_H,
		data->map.player.x * IMG_W);
	put_image(data, "textures/dummy.xpm", y_new * IMG_H, x_new * IMG_W);
	put_image(data, img, y_new * IMG_H, x_new * IMG_W);
	return (free(img), 0);
}

void	ft_move_e(t_data *data, int *pos_old, int *pos_new, int dir)
{
	if (data->map.map[pos_new[0]][pos_new[1]] == 'P')
		(ft_putmsg(2), exit(0));
	data->map.map[pos_old[0]][pos_old[1]] = '0';
	data->map.map[pos_new[0]][pos_new[1]] = 'A';
	put_image(data, "textures/dummy.xpm", pos_old[0] * IMG_H, pos_old[1]
		* IMG_W);
	put_image(data, "textures/dummy.xpm", pos_old[0] * IMG_H, pos_old[1]
		* IMG_W);
	if (!dir)
		put_image(data, "textures/EEEE.xpm", pos_new[0] * IMG_H, pos_new[1]
			* IMG_W);
	else
		put_image(data, "textures/ENEMY2.xpm", pos_new[0] * IMG_H, pos_new[1]
			* IMG_W);
}

void	ft_m_e(t_data *data, t_list *temp)
{
	int		pos[4];
	char	**map;

	map = data->map.map;
	while (temp)
	{
		pos[0] = temp->y;
		pos[1] = temp->x;
		pos[2] = temp->y;
		if ((map[temp->y][temp->x - 1] == '0' || map[temp->y][temp->x
			- 1] == 'P') && !temp->dir)
		{
			pos[3] = --temp->x;
			ft_move_e(data, pos, &pos[2], temp->dir);
		}
		else if ((map[temp->y][temp->x + 1] == '0' || map[temp->y][temp->x
			+ 1] == 'P') && temp->dir)
		{
			pos[3] = ++temp->x;
			ft_move_e(data, pos, &pos[2], temp->dir);
		}
		else
			temp->dir = !temp->dir;
		temp = temp->next;
	}
}
