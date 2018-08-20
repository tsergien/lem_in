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
	int		flag;
	t_room	*tmp;
	int		len;

	flag = 0;
	len = 1;
	tmp = rooms;
	while (tmp)
	{
		if (ft_strstr(line, tmp->name) == line)
		{
			len += ft_strlen(tmp->name);
			flag += 1;
		}
		else if (ft_strstr(line, tmp->name) != line &&
		ft_strstr(line, tmp->name) != 0)
		{
			len += ft_strlen(tmp->name);
			flag += 2;
		}
		tmp = tmp->next;
	}
	if ((size_t)len != ft_strlen(line))
		return (0);
	return ((flag == 3 ? 1 : 0));
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
