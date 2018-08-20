/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 12:45:44 by tsergien          #+#    #+#             */
/*   Updated: 2018/08/06 12:45:46 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			add_way_l(t_lway **ways, t_way *way)
{
	t_lway		*tmp;
	t_lway		*new_elem;

	if (!way)
		return (0);
	new_elem = (t_lway *)malloc(sizeof(t_lway));
	new_elem->way = way;
	new_elem->next = NULL;
	tmp = *ways;
	if (!(*ways))
	{
		*ways = new_elem;
		return (1);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_elem;
	return (1);
}

int			way_length(t_way *way)
{
	int		len;

	len = 0;
	while (way)
	{
		len++;
		way = way->next;
	}
	return (len);
}

void		free_lway(t_lway *ways)
{
	t_lway		*tmp;

	while (ways)
	{
		tmp = ways->next;
		free_queue(ways->way);
		free(ways);
		ways = tmp;
	}
}

void		free_queue(t_way *q)
{
	t_way		*tmp;

	while (q)
	{
		tmp = q->next;
		free(q);
		q = tmp;
	}
}
