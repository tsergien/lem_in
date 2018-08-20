/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 12:49:49 by tsergien          #+#    #+#             */
/*   Updated: 2018/08/02 12:49:51 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int				num_of_rooms(t_room *room)
{
	int			num;
	t_room		*temp;

	num = 0;
	temp = room;
	while (temp)
	{
		temp = temp->next;
		num++;
	}
	return (num);
}

int				count_ways(t_lway *ways)
{
	int		n;
	t_lway	*tmp;

	n = 0;
	tmp = ways;
	while (tmp)
	{
		n++;
		tmp = tmp->next;
	}
	return (n);
}

static void		transfer(t_ant *ants, t_lem *lem, t_lway *ways)
{
	int		i;
	int		end;
	int		finished_ant;

	finished_ant = 0;
	end = last_room(ways->way);
	while (!all_in_the_end(ants, end, lem->ants_amount))
	{
		i = finished_ant - 1;
		while (++i < lem->ants_amount)
		{
			go_to_next_room(ways, lem, i, &ants);
			if (ants[i].room == end)
				finished_ant = i;
		}
		write(1, "\n", 1);
	}
}

void			ways_transfer(t_lem *lem, t_lway *ways)
{
	t_ant		*ants;
	int			*dist;
	t_lway		*tmp;
	int			i;

	if (!lem)
		return ;
	ants = (t_ant *)malloc(sizeof(t_ant) * lem->ants_amount);
	tmp = ways;
	i = -1;
	dist = (int *)malloc(sizeof(int) * (count_ways(ways) + 1));
	while (tmp)
	{
		dist[++i] = way_length(tmp->way);
		tmp = tmp->next;
	}
	dist[++i] = -1;
	distibute_ants(ants, lem, dist);
	transfer(ants, lem, ways);
	free(ants);
	free(dist);
}
