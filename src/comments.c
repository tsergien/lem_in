/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 16:23:51 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/21 16:23:55 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void		exec_command(char *line)
{
	if (ft_strcmp("##color", line) == 0)
		g_color = 1;
	else if (ft_strcmp("##printway", line) == 0)
		g_printway = 1;
	return ;
}

int				gnl(char **line, t_reader **u)
{
	while (get_next_line(0, line) > 0)
	{
		if (ft_strcmp(*line, "") == 0)
		{
			free(*line);
			return (0);
		}
		add_to_reader(*line, u);
		if (ft_strcmp("##start", *line) != 0 && ft_strcmp("##end", *line)
			!= 0 && is_command(*line))
			exec_command(*line);
		else if (!is_comment(*line))
			return (1);
		free(*line);
	}
	return (0);
}

int				is_command(char *line)
{
	if (ft_strcmp("##start", line) == 0)
		return (1);
	else if (ft_strcmp("##end", line) == 0)
		return (1);
	else if (ft_strcmp("##color", line) == 0)
		return (1);
	else if (ft_strcmp("##printway", line) == 0)
		return (1);
	return (0);
}

int				is_comment(char *line)
{
	if (*line == '#' && !is_command(line))
		return (1);
	return (0);
}

char			**new_matrix(int n)
{
	char	**m;
	int		i;

	i = -1;
	m = (char **)malloc(sizeof(char *) * n);
	while (++i < n)
	{
		m[i] = (char *)malloc(sizeof(char) * n);
		ft_bzero(m[i], n);
	}
	return (m);
}
