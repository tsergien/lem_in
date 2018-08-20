/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 14:11:42 by tsergien          #+#    #+#             */
/*   Updated: 2018/08/01 14:11:44 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		parent_put(t_hashmap **parents, t_room *parent, t_room *child)
{
	t_hashmap	*tmp;
	t_hashmap	*new_elem;

	new_elem = (t_hashmap *)malloc(sizeof(t_hashmap));
	new_elem->child = child;
	new_elem->parent = parent;
	new_elem->next = NULL;
	if (!parents || !(*parents))
	{
		(*parents) = new_elem;
		return ;
	}
	tmp = *parents;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_elem;
}

t_room		*parents_get(t_hashmap *parents, t_room *child)
{
	t_hashmap		*tmp;

	tmp = parents;
	while (tmp)
	{
		if (tmp->child == child)
			return (tmp->parent);
		tmp = tmp->next;
	}
	return (NULL);
}

void		free_hashmap(t_hashmap *head)
{
	t_hashmap		*tmp;

	tmp = head;
	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}
