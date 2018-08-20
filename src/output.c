/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 14:36:38 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/24 14:36:42 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		print_data(t_reader *r, t_lem *lem)
{
	t_reader	*tmp;

	tmp = r;
	while (tmp)
	{
		if (!tmp->next)
		{
			if ((is_link_format(tmp->data) &&
			is_existing_name(lem->room, tmp->data))
			|| is_room_format(tmp->data) || is_comment(tmp->data)
			|| is_command(tmp->data))
				ft_putstr_endl(tmp->data);
		}
		else
			ft_putstr_endl(tmp->data);
		tmp = tmp->next;
	}
}

void		add_to_reader(char *line, t_reader **u)
{
	t_reader	*tmp;
	t_reader	*new_elem;

	new_elem = (t_reader *)malloc(sizeof(t_reader));
	new_elem->data = ft_strdup(line);
	new_elem->next = NULL;
	if (!u || !(*u))
	{
		*u = new_elem;
		return ;
	}
	tmp = *u;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new_elem;
}

static void	set_color(int color)
{
	char	*str;
	char	*template;

	color = (18 + color) % 219 + 1;
	template = ft_strnew(10);
	ft_strcpy(template, "\x1b[38;5;");
	str = ft_itoa(color);
	write(1, template, 7);
	write(1, str, ft_strlen(str));
	write(1, "m", 1);
	free(template);
	free(str);
}

void		ant_room_output(int ant_ind, char *room_name)
{
	if (g_color)
		set_color(ant_ind);
	write(1, "L", 1);
	ft_putnbr(ant_ind);
	write(1, "-", 1);
	ft_putstr(room_name);
	write(1, "\e[0m ", 5);
	free(room_name);
}

void		print_way(t_way *way)
{
	t_way	*tmp;

	tmp = way;
	write(1, "way: ", 5);
	write(1, "start = ", 8);
	while (way)
	{
		write(1, way->room->name, ft_strlen(way->room->name));
		way = way->next;
		if (way)
			write(1, " -> ", 4);
	}
	write(1, " = end\n", 7);
}
