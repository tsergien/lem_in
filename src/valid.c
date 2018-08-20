/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 13:55:32 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/27 13:55:57 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int				is_norm_number(char *line)
{
	int		digits;
	char	*ptr;

	ptr = line;
	digits = 0;
	if (ptr == NULL)
		return (0);
	if (*ptr == '-' || *ptr == '+')
		ptr++;
	while (ft_isdigit(*ptr))
	{
		ptr++;
		digits++;
	}
	if (digits == 0 || digits > 10)
		return (0);
	if (digits == 10 && ft_strcmp(line, "2147483647") > 0)
		return (0);
	if (!((*ptr >= 9 && *ptr <= 13) || *ptr == 32
	|| *ptr == '\0'))
		return (0);
	return (1);
}

int				check_ants_amount(char *line)
{
	char		*ptr;

	if (!is_norm_number(line) || *line == '-')
		return (0);
	ptr = line;
	if (*ptr == '-' || *ptr == '+')
		ptr++;
	while (ft_isdigit(*ptr))
		ptr++;
	if (*ptr != '\0')
		return (0);
	if (ft_atoi(line) < 0)
		return (0);
	return (1);
}

int				is_room_format(char *line)
{
	if (!line)
		return (0);
	if (*line == 'L' || *line == '#')
		return (0);
	line = ft_strchr(line, ' ');
	if (!line)
		return (0);
	line++;
	if (!line || !is_norm_number(line))
		return (0);
	while (*line && (ft_isdigit(*line) || *line == '+'
	|| *line == '-'))
		line++;
	line++;
	if (!is_norm_number(line))
		return (0);
	while (*line && (ft_isdigit(*line) || *line == '+'
	|| *line == '-'))
		line++;
	if (*line != '\0')
		return (0);
	return (1);
}

int				is_link_format(char *line)
{
	char	*p1;
	char	*p2;
	char	*ptr;

	ptr = line;
	if (*line == 'L')
		return (0);
	p1 = ft_strchr(line, '-');
	p2 = ft_strrchr(line, '-');
	if (!p1 || p1 != p2)
		return (0);
	while (*ptr)
	{
		if (*ptr != '-' && !ft_isalnum(*ptr))
			return (0);
		ptr++;
	}
	return (1);
}

int				check_start_end(t_room *room)
{
	int		start;
	int		end;
	t_room	*tmp;

	tmp = room;
	start = 0;
	end = 0;
	while (tmp)
	{
		if (tmp->label == 1)
			start++;
		if (tmp->label == 2)
			end++;
		tmp = tmp->next;
	}
	if (start == 1 && end == 1)
		return (1);
	return (0);
}
