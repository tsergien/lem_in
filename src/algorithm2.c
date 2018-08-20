/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 14:00:21 by tsergien          #+#    #+#             */
/*   Updated: 2018/08/06 14:00:24 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int		get_next_room_ind(t_way *way, int ind)
{
	t_way	*tmp;

	tmp = way;
	if (!way)
		return (-1);
	while (tmp->next)
	{
		if (tmp->room->ind == ind)
			return (tmp->next->room->ind);
		tmp = tmp->next;
	}
	return (-1);
}

static t_way	*get_room_way(t_way *way, int ind)
{
	t_way	*tmp;

	tmp = way;
	while (tmp)
	{
		if (tmp->room->ind == ind)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static t_way	*way_ind(t_lway *ways, int ind)
{
	t_lway	*tmp;
	int		i;

	i = 0;
	tmp = ways;
	while (tmp->next && i != ind)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp->way);
}

int				all_in_the_end(t_ant *ants, int end, int n)
{
	int		i;

	i = -1;
	while (++i < n)
	{
		if (ants[i].room != end)
			return (0);
	}
	return (1);
}

void			go_to_next_room(t_lway *ways, t_lem *lem, int i, t_ant **ants)
{
	t_way	*next_room;
	int		end;
	t_way	*way;
	t_way	*cur;

	way = way_ind(ways, (*ants)[i].way_num);
	end = last_room(way);
	if ((*ants)[i].room != end)
	{
		next_room = get_room_way(way, get_next_room_ind(way, (*ants)[i].room));
		if (!next_room)
		{
			(*ants)[i].room = end;
			return ;
		}
		if (next_room->is_free)
		{
			cur = get_room_way(way, (*ants)[i].room);
			(*ants)[i].room = next_room->room->ind;
			next_room->is_free = next_room->room->label == 2 ? 1 : 0;
			cur->is_free = 1;
			ant_room_output(i + 1, get_name(lem->room, (*ants)[i].room));
		}
	}
}
