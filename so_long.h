/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 04:18:03 by mben-zeh          #+#    #+#             */
/*   Updated: 2023/01/09 04:18:06 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define IMG_H 50
# define IMG_W 50

typedef struct s_player
{
	int					x;
	int					y;
}						t_player;
typedef struct s_exit
{
	int					x;
	int					y;
}						t_exit;

typedef struct s_list
{
	int					x;
	int					y;
	struct s_list		*next;
}						t_list;

typedef struct s_collect
{
	int					x;
	int					y;
	struct s_collect	*next;
}						t_collect;
typedef struct s_textur
{
	int					c;
	int					e;
	int					p;
}						t_textur;

typedef struct s_map
{
	char				**map;
	t_player			player;
	t_exit				pexit;
	t_list				*collect;
}						t_map;

typedef struct s_win
{
	int					width;
	int					height;
}						t_win;

typedef struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	t_win				win;
	t_map				map;
	t_textur			textur;
	int					keycode;

}						t_data;

void					check_map(t_data *data, char *filename);
char					**ft_split(char const *s, char c);
void					ft_putstr(char *s);
void					msg_error(char *prmsg, int i, char *msg, void fun());
char					**load_map(int fd);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						check_and_open(char *filename);
void					chech_is_n_contain(char *str);
void					count_textur(t_data *data);
t_list					*ft_lstnew(int x, int y);
void					ft_lstadd_back(t_list **lst, t_list *new);
void					ft_free(char **str);
void					ft_freelist(t_list *lst);
void					ft_putmsg(int i);
void					check_all(t_data *data, int i, int j);
void					check_valid_path(char **map, t_data *data);
void					flood_fill(char **map, int x, int y);
int						ft_close(t_data *data);
void					put_image(t_data *data, char *img, int y, int x);
void					show_map(t_data *data);
char					*ft_itoa(int n);
#endif