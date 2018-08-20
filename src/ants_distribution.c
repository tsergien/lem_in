/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_distribution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 16:25:27 by tsergien          #+#    #+#             */
/*   Updated: 2018/08/06 16:25:29 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int	min_ind(int *a)
{
	int		i;
	int		min;
	int		ind;

	i = 0;
	min = a[0];
	ind = 0;
	while (a[++i] != -1)
	{
		if (min > a[i])
		{
			min = a[i];
			ind = i;
		}
	}
	return (ind);
}

static int	start_room_ind(t_lem *lem)
{
	t_room	*tmp;

	tmp = lem->room;
	while (tmp)
	{
		if (tmp->label == 1)
			return (tmp->ind);
		tmp = tmp->next;
	}
	return (-1);
}

void		distibute_ants(t_ant *ants, t_lem *lem, int *dist)
{
	int		i;
	int		ind;
	int		start_room;

	i = -1;
	start_room = start_room_ind(lem);
	while (++i < lem->ants_amount)
	{
		ind = min_ind(dist);
		(ants[i]).way_num = ind;
		(ants[i]).room = start_room;
		dist[ind] = dist[ind] + 1;
	}
}
