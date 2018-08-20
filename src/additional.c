/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 18:17:49 by tsergien          #+#    #+#             */
/*   Updated: 2018/08/10 18:17:52 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			is_existing_name(t_room *rooms, char *line)
{
	int		flag1;
	int		flag2;
	int		len;

	flag1 = 0;
	flag2 = 0;
	len = 1;
	while (rooms)
	{
		if (ft_strstr(line, rooms->name) == line)
		{
			len += ft_strlen(rooms->name);
			flag1 = 1;
		}
		else if (ft_strstr(line, rooms->name) != line &&
		ft_strstr(line, rooms->name) != 0)
		{
			len += ft_strlen(rooms->name);
			flag2 = 1;
		}
		rooms = rooms->next;
	}
	if ((size_t)len != ft_strlen(line))
		return (0);
	return (((flag1 == 1 && flag2 == 1) ? 1 : 0));
}

int			no_sol_error(void)
{
	write(2, "No solutions! Not enough links.\n", 32);
	return (0);
}

int			ants_amount_error(t_reader *r)
{
	free_lines_r(r);
	write(2, "Ants input error.\n", 18);
	return (0);
}
