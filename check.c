/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:55:31 by mben-zeh          #+#    #+#             */
/*   Updated: 2023/01/12 16:55:33 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

char	**load_map(int fd)
{
	char	**map;
	char	*str;
	char	*temp;

	temp = NULL;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		temp = ft_strjoin(temp, str);
		if (str[0] == '\n')
			return (free(temp), msg_error(0, 0, "\x1B[33m empty line!", exit),
				NULL);
		free(str);
	}
	if (!temp)
		return (free(temp), msg_error(0, 0, "\x1B[33m empty File!", exit),
			NULL);
	else if (temp[ft_strlen(temp) - 1] == '\n')
		return (free(temp), msg_error(0, 0, "\x1B[33m empty line!", exit),
			NULL);
	return (map = ft_split(temp, '\n'), close(fd), free(temp), map);
}

void	check_all(t_data *data, int i, int j)
{
	if ((i == 0 || j == 0 || !data->map.map[i + 1] || !data->map.map[i][j + 1])
		&& data->map.map[i][j] != '1')
		msg_error(0, 0, "\x1B[33m 🅸 🅽 🆅 🅰 🅻 🅸 🅳  🅼 🅰 🅿\n", exit);
	if (data->map.map[i][j] == 'P' && data->textur.p < 1)
	{
		data->textur.p++;
		data->map.player.y = i;
		data->map.player.x = j;
	}
	else if (data->map.map[i][j] == 'C')
	{
		data->textur.c++;
		ft_lstadd_back(&data->map.collect, ft_lstnew(j, i));
	}
	else if (data->map.map[i][j] == 'E' && data->textur.e < 1)
	{
		data->textur.e++;
		data->map.pexit.y = i;
		data->map.pexit.x = j;
	}
	else if (data->map.map[i][j] != '0' && data->map.map[i][j] != '1')
		msg_error(0, 0, "\x1B[33m 🅸 🅽 🆅 🅰 🅻 🅸 🅳  🅼 🅰 🅿\n", exit);
}

void	count_textur(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->textur.p = 0;
	data->textur.c = 0;
	data->textur.e = 0;
	data->win.width = ft_strlen(data->map.map[0]);
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
			check_all(data, i, j++);
		if (data->win.width != j)
			msg_error(0, 0, "\x1B[33m🅸 🅽 🆅 🅰 🅻 🅸 🅳  🅼 🅰 🅿\n", exit);
		i++;
	}
	if (!data->textur.c || !data->textur.e || !data->textur.p)
		msg_error(0, 0, "\x1B[33m🅸 🅽 🆅 🅰 🅻 🅸 🅳  🅼 🅰 🅿\n", exit);
	data->win.height = i;
}

void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == 'E')
		map[y][x] = 'R';
	if (map[y][x] != '0' && map[y][x] != 'P' && map[y][x] != 'C')
		return ;
	map[y][x] = 'X';
	flood_fill(map, x + 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y - 1);
}

void	check_valid_path(char **map, t_data *data)
{
	t_list	*temp;

	flood_fill(map, data->map.player.x, data->map.player.y);
	if (map[data->map.pexit.y][data->map.pexit.x] != 'R')
		msg_error(0, 0, "\x1B[33m 🅸 🅽 🆅 🅰 🅻 🅸 🅳  🅿 🅰 🆃 🅷", exit);
	temp = data->map.collect;
	while (temp)
	{
		if (map[temp->y][temp->x] != 'X')
		{
			ft_free(map);
			ft_freelist(data->map.collect);
			data->map.collect = NULL;
			msg_error(0, 0, "\x1B[33m🅸 🅽 🆅 🅰 🅻 🅸 🅳  🅿 🅰 🆃 🅷\n", exit);
		}
		temp = temp->next;
	}
	ft_free(map);
}
