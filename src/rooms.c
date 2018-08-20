/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 15:52:39 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/23 15:52:42 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_room			*get_room(int room_ind, t_room *room)
{
	t_room		*ptr;

	ptr = room;
	while (ptr)
	{
		if (room_ind == ptr->ind)
			return (ptr);
		ptr = ptr->next;
	}
	return (0);
}

int				get_index(t_room *room, char *name)
{
	t_room	*ptr;

	ptr = room;
	while (ptr)
	{
		if (ft_strequ(name, ptr->name))
			return (ptr->ind);
		ptr = ptr->next;
	}
	return (-1);
}

char			*get_name(t_room *room, int ind)
{
	int		i;
	t_room	*ptr;

	i = 0;
	ptr = room;
	while (ptr)
	{
		if (ptr->ind == ind)
			return (ft_strdup(ptr->name));
		ptr = ptr->next;
	}
	return (0);
}

t_room			*set_data_room(char *line, char label)
{
	t_room		*new_r;

	new_r = (t_room *)malloc(sizeof(t_room));
	new_r->name = ft_strsub(line, 0, ft_strchr(line, ' ') - line);
	new_r->coord_x = ft_atoi(ft_strchr(line, ' '));
	new_r->coord_y = ft_atoi(ft_strrchr(line, ' '));
	new_r->label = label;
	new_r->next = NULL;
	return (new_r);
}

int				add_room(t_lem *lem, char *line, char label)
{
	t_room		*tmp;
	t_room		*new_r;

	new_r = set_data_room(line, label);
	if (lem->room == NULL)
	{
		lem->room = new_r;
		return (1);
	}
	tmp = lem->room;
	while (lem->room)
	{
		if (ft_strcmp(lem->room->name, new_r->name) == 0 || (new_r->coord_x ==
		lem->room->coord_x && new_r->coord_y == lem->room->coord_y))
			return (0);
		if (!(lem->room->next))
			break ;
		lem->room = lem->room->next;
	}
	lem->room->next = new_r;
	lem->room = tmp;
	return (1);
}
