/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:57:51 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/21 17:22:36 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	look_for(char *line, int *i, char c)
{
	int	p;

	p = -1;
	(*i)++;
	if (c == '(')
	{
		c = ')';
		p = 0;
	}
	while (line[*i])
	{
		if (p == -1 && line[*i] == '(')
			p++;
		if (c == ')' && (line[*i] == '\'' || line[*i] == '\"'))
			if (look_for(line, i, line[*i]))
				return (1);
		if (line[*i] == c)
		{
			if (p > 0)
				p--;
			else
				return (0);
		}
		(*i)++;
	}
	return (1);
}

int	check_line(char *line)
{
	int	i;
	int	flag;

	if (!line)
		return (0);
	i = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] == '(' || line[i] == '\'' || line[i] == '\"')
			flag += look_for(line, &i, line[i]);
		i++;
	}
	return (flag);
}
