/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visited.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 16:57:29 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/27 16:57:31 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			is_visited(int room_ind, int *visited, int n)
{
	int		i;

	i = -1;
	while (++i < n)
	{
		if (visited[i] == room_ind)
			return (1);
	}
	return (0);
}

void		set_visited(int room_ind, int **visited, int n)
{
	int		i;

	i = 0;
	while (i < n && (*visited)[i] != -1)
	{
		if ((*visited)[i] == room_ind)
			return ;
		i++;
	}
	if (i < n)
		(*visited)[i] = room_ind;
}

void		bzero_visited(int **visited, int n)
{
	int		i;

	i = -1;
	while (++i < n)
		(*visited)[i] = -1;
}

void		mark_visited(t_way *way, int **in_way)
{
	int		i;

	i = 0;
	while ((*in_way)[i] != -1)
		i++;
	while (way)
	{
		if (way->room->label == 0)
		{
			(*in_way)[i] = way->room->ind;
			i++;
		}
		way = way->next;
	}
}

void		fill_visited(int *in_way, int **visited)
{
	int		i;

	i = 0;
	while (in_way[i] != -1)
	{
		(*visited)[i] = in_way[i];
		i++;
	}
}
