/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 17:31:53 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/27 17:31:56 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		add_elem(t_way **q, t_room *elem)
{
	t_way	*tmp;

	tmp = *q;
	if (!(*q))
	{
		(*q) = (t_way *)malloc(sizeof(t_way));
		(*q)->room = elem;
		(*q)->next = NULL;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_way *)malloc(sizeof(t_way));
	tmp->next->room = elem;
	tmp->next->next = NULL;
}

void		set_start(t_room *room, t_way **queue)
{
	t_room	*ptr;

	ptr = room;
	while (ptr)
	{
		if (ptr->label == 1)
		{
			add_elem(queue, ptr);
			break ;
		}
		ptr = ptr->next;
	}
}

void		pop(t_way **q)
{
	t_way	*tmp;

	if (!(*q))
		return ;
	tmp = (*q)->next;
	free(*q);
	*q = tmp;
}

void		way_add(t_way **way, t_room *room)
{
	t_way	*new_elem;

	new_elem = (t_way *)malloc(sizeof(t_way));
	new_elem->room = room;
	new_elem->is_free = 1;
	new_elem->next = NULL;
	if (!way)
	{
		*way = new_elem;
		return ;
	}
	new_elem->next = *way;
	*way = new_elem;
}

int			last_room(t_way *way)
{
	t_way	*tmp;
	int		res;

	tmp = way;
	if (!tmp)
		return (-1);
	while (tmp->next)
		tmp = tmp->next;
	res = tmp->room->ind;
	return (res);
}
