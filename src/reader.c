/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 14:38:23 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/20 14:38:26 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void		set_room_indexes(t_room *room)
{
	int		ind;
	t_room	*ptr;

	ptr = room;
	ind = 0;
	while (room)
	{
		room->ind = ind;
		ind++;
		room = room->next;
	}
	room = ptr;
}

void			free_lines_r(t_reader *r)
{
	t_reader	*tmp;

	while (r)
	{
		tmp = r->next;
		free(r->data);
		free(r);
		r = tmp;
	}
}

static void		read_links(t_lem *lem, char **line, t_reader **u)
{
	int		l1;
	int		l2;
	char	*name;

	l1 = -2;
	while (is_link_format(*line) && is_existing_name(lem->room, *line))
	{
		name = ft_strsub(*line, 0, ft_strchr(*line, '-') - *line);
		l2 = ft_strlen(name);
		l1 = get_index(lem->room, name);
		free(name);
		name = ft_strsub(*line, l2 + 1, ft_strlen(*line) - 1 - l2);
		l2 = get_index(lem->room, name);
		free(name);
		if (l1 == -1 || l2 == -1)
			break ;
		lem->links[l2][l1] = 1;
		lem->links[l1][l2] = 1;
		free(*line);
		if (!gnl(line, u))
			return ;
	}
	if (l1 != -2)
		free(*line);
}

static int		read_rooms(t_lem *lem, char **line, t_reader **u)
{
	char	label;

	lem->room = NULL;
	while (gnl(line, u) > 0)
	{
		if (!is_command(*line) && !is_room_format(*line))
			break ;
		if (ft_strcmp("##start", *line) == 0 || ft_strcmp("##end", *line) == 0)
		{
			label = ft_strcmp("##start", *line) == 0 ? 1 : 2;
			free(*line);
			if (!gnl(line, u) || !is_room_format(*line))
				return (0);
		}
		else
			label = 0;
		if (!add_room(lem, *line, label))
			return (0);
		free(*line);
	}
	set_room_indexes(lem->room);
	return (1);
}

int				read_data(t_lem *lem)
{
	char	*line;
	t_reader*r;

	r = NULL;
	if (!gnl(&line, &r) || !check_ants_amount(line))
	{
		if (line && *line)
			free(line);
		return (ants_amount_error(r));
	}
	lem->ants_amount = ft_atoi(line);
	free(line);
	if (!read_rooms(lem, &line, &r) || !check_start_end(lem->room))
		return (error_message(r));
	lem->links = new_matrix(num_of_rooms(lem->room));
	read_links(lem, &line, &r);
	print_data(r, lem);
	free_lines_r(r);
	return (1);
}
