/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 14:38:51 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/20 14:38:53 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"

int					g_color;
int					g_printway;
/*
** label: start - 1, end -2, in the gap - 0
*/
typedef struct		s_room
{
	char			*name;
	int				ind;
	char			label;
	int				coord_x;
	int				coord_y;
	struct s_room	*next;
}					t_room;

typedef struct		s_way
{
	t_room			*room;
	char			is_free;
	struct s_way	*next;
}					t_way;

typedef struct		s_lem
{
	int				ants_amount;
	t_room			*room;
	char			**links;
}					t_lem;

typedef struct		s_hashmap
{
	t_room			*child;
	t_room			*parent;
	struct s_hashmap*next;
}					t_hashmap;

typedef struct		s_lway
{
	t_way			*way;
	struct s_lway	*next;
}					t_lway;

typedef struct		s_ant
{
	int				way_num;
	int				room;
}					t_ant;

typedef struct		s_reader
{
	char			*data;
	struct s_reader	*next;
}					t_reader;
/*
**		COMMENTS
*/
int					is_comment(char *line);
int					is_command(char *line);
char				**new_matrix(int n);
/*
**		READING
*/
int					gnl(char **line, t_reader **u);
int					read_data();
void				add_to_reader(char *line, t_reader **u);
int					error_message(t_reader *r);
void				free_lines_r(t_reader *r);
/*
**		ROOMS
*/
int					num_of_rooms(t_room *room);
int					add_room(t_lem *lem, char *line, char label);
char				*get_name(t_room *room, int ind);
t_room				*get_room(int room_ind, t_room *room);
int					last_room(t_way *way);
/*
**		VALID
*/
int					get_index(t_room *room, char *name);
int					is_room_format(char *line);
int					is_link_format(char *line);
int					is_norm_number(char *line);
int					check_start_end(t_room *room);
int					check_ants_amount(char *line);
int					is_existing_name(t_room *rooms, char *line);
/*
**		OUTPUT
*/
void				output_room(t_lem *lem);
void				output_links_names(t_room *room, char **links, int n);
void				print_way(t_way *way);
void				ant_room_output(int ant_ind, char *room_name);
void				print_data(t_reader *r, t_lem *lem);
/*
**		Algorithm
*/
void				transfer_ants(t_lem *lem);
void				set_start(t_room *room, t_way **queue);
int					all_in_the_end(t_ant *ants, int end, int n);
/*
**		QUEVE
*/
void				add_elem(t_way **q, t_room *elem);
void				pop(t_way **q);
void				way_add(t_way **way, t_room *room);
/*
**		HASHMAP
*/
void				parent_put(t_hashmap **parents,
								t_room *parent, t_room *child);
t_room				*parents_get(t_hashmap *parents, t_room *child);
void				free_hashmap(t_hashmap *head);
/*
**		ANTS
*/
void				ways_transfer(t_lem *lem, t_lway *ways);
void				distibute_ants(t_ant *ants, t_lem *lem, int *dist);
void				go_to_next_room(t_lway *ways, t_lem *lem,
									int i, t_ant **ants);
/*
**		Additional
*/
int					is_visited(int room_ind, int *visited, int n);
void				set_visited(int room_ind, int **visited, int n);
void				bzero_visited(int **visited, int n);
void				fill_visited(int *in_way, int **visited);
int					count_ways(t_lway *ways);
int					no_sol_error();
int					ants_amount_error(t_reader *r);
/*
**		LIST WAYS
*/
int					way_length(t_way *way);
int					add_way_l(t_lway **ways, t_way *way);
void				mark_visited(t_way *way, int **in_way);
void				free_lway(t_lway *ways);
void				free_queue(t_way *q);
#endif
