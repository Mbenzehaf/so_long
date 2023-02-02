/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 06:33:03 by mben-zeh          #+#    #+#             */
/*   Updated: 2023/01/09 06:33:05 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	ft_putmsg(int i)
{
	if (i == 1)
	{
		ft_putstr("\x1B[32m██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗██╗███╗   ██╗\n\
╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║    ██║██║████╗  ██║\n\
 ╚████╔╝ ██║   ██║██║   ██║    ██║ █╗ ██║██║██╔██╗ ██║\n\
  ╚██╔╝  ██║   ██║██║   ██║    ██║███╗██║██║██║╚██╗██║\n\
   ██║   ╚██████╔╝╚██████╔╝    ╚███╔███╔╝██║██║ ╚████║\n\
   ╚═╝    ╚═════╝  ╚═════╝      ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝\n\x1B[0m");
	}
	else if (i == 2)
	{
		ft_putstr("\x1B[33m ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗\n\
██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗\n\
██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝\n\
██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗\n\
╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║\n\
 ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝\n");
	}
	else
	{
		ft_putstr("\x1B[31m███████╗██████╗ ██████╗  ██████╗ ██████╗ \n\
██╔════╝██╔══██╗██╔══██╗██╔═══██╗██╔══██╗\n\
█████╗  ██████╔╝██████╔╝██║   ██║██████╔╝\n\
██╔══╝  ██╔══██╗██╔══██╗██║   ██║██╔══██╗\n\
███████╗██║  ██║██║  ██║╚██████╔╝██║  ██║\n\
╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝\n\x1B[33m");
	}
}

void	msg_error(char *prmsg, int i, char *msg, void fun())
{
	ft_putmsg(i);
	ft_putstr("\t\t Error :\n");
	ft_putstr(prmsg);
	ft_putstr(" ");
	ft_putstr(msg);
	ft_putstr("\n");
	fun(1);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	check_and_open(char *filename)
{
	int	fd;

	if (ft_strncmp(&filename[ft_strlen(filename) - 4], ".ber", 5))
		msg_error(filename, 0, " : Extension File is invalid!", exit);
	fd = open(filename, O_RDONLY | O_DIRECTORY);
	if (fd != -1)
		msg_error(filename, 0, ": Is a directory", exit);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		msg_error(filename, 0, strerror(errno), exit);
	return (fd);
}

int	ft_close(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
	return (0);
}
