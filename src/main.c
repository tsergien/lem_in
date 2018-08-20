/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 14:38:03 by tsergien          #+#    #+#             */
/*   Updated: 2018/08/13 16:45:34 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			error_message(t_reader *r)
{
	free_lines_r(r);
	write(2, "Room input error.\n", 19);
	return (0);
}

static void	free_job(t_lem *lem)
{
	t_room		*t;
	int			i;
	int			num_rooms;

	num_rooms = num_of_rooms(lem->room);
	i = -1;
	while (lem->room)
	{
		t = lem->room->next;
		free(lem->room->name);
		free(lem->room);
		while (++i < num_rooms)
			free(lem->links[i]);
		lem->room = t;
	}
}

int			main(void)
{
	t_lem	lem;

	g_color = 0;
	g_printway = 0;
	if (!read_data(&lem))
		return (0);
	transfer_ants(&lem);
	free_job(&lem);
	return (0);
}
