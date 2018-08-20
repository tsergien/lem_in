/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 15:52:41 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/27 15:52:44 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void		add_neighbours(t_way **queue, t_lem *lem,
								int **visited, t_hashmap **parents)
{
	int		j;
	int		rooms;
	t_room	*j_room;

	j = -1;
	rooms = num_of_rooms(lem->room);
	while (++j < rooms)
	{
		j_room = get_room(j, lem->room);
		if ((*queue)->room->ind != j && lem->links[(*queue)->room->ind][j] == 1
		&& !is_visited(j, *visited, rooms))
		{
			add_elem(queue, j_room);
			parent_put(parents, (*queue)->room, j_room);
		}
	}
	set_visited((*queue)->room->ind, visited, rooms);
}

static t_way	*build_way(t_hashmap **parents, t_way *queue)
{
	t_way	*way;
	t_room	*tmp;

	tmp = queue->room;
	way = NULL;
	while (tmp != NULL)
	{
		way_add(&way, tmp);
		tmp = parents_get(*parents, tmp);
	}
	if (g_printway)
		print_way(way);
	free_hashmap(*parents);
	free_queue(queue);
	return (way);
}

static t_way	*bfs(t_lem *lem, int **in_way)
{
	t_hashmap	*parents;
	t_way		*queue;
	int			*visited;

	queue = NULL;
	parents = NULL;
	visited = (int *)malloc(sizeof(int) * (num_of_rooms(lem->room) + 1));
	bzero_visited(&visited, num_of_rooms(lem->room) + 1);
	fill_visited(*in_way, &visited);
	set_start(lem->room, &queue);
	parent_put(&parents, queue->room, NULL);
	while (queue)
	{
		add_neighbours(&queue, lem, &visited, &parents);
		if (queue->room->label == 2)
			break ;
		pop(&queue);
	}
	free(visited);
	if (!queue)
	{
		free_hashmap(parents);
		return (NULL);
	}
	return (build_way(&parents, queue));
}

static t_lway	*mult_ways(t_lem *lem)
{
	int		*in_way;
	t_lway	*ways;
	t_way	*tmp_way;

	ways = NULL;
	in_way = (int *)malloc(sizeof(int) * (num_of_rooms(lem->room) + 1));
	bzero_visited(&in_way, num_of_rooms(lem->room) + 1);
	while (1)
	{
		tmp_way = bfs(lem, &in_way);
		if (!tmp_way || !add_way_l(&ways, tmp_way))
			break ;
		mark_visited(tmp_way, &in_way);
		if (way_length(tmp_way) == 2)
			break ;
	}
	free(in_way);
	return (ways);
}

void			transfer_ants(t_lem *lem)
{
	t_lway	*ways;
	int		i;

	i = 0;
	if (lem->ants_amount == 0)
		return ;
	ways = mult_ways(lem);
	if (!ways)
	{
		write(2, "No solutions!\n", 14);
		return ;
	}
	ways_transfer(lem, ways);
	free_lway(ways);
}
