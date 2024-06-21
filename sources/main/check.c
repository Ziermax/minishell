/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:57:51 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/21 14:10:25 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	look_for(char *line, int *i, char c)
{
	int	p;

	p = 0;
	(*i)++;
	if (c == '(')
		c = ')';
	while (line[*i])
	{
		if (line[*i] == '(')
			p++;
		if (c == ')' && (line[*i] == '\'' || line[*i] == '\"'))
			if (look_for(line, i, line[*i]))
				return (1);
		if (line[*i] == c)
		{
			if (p)
				p--;
			else
				return (0);
		}
		(*i)++;
	}
	return (1);
}

static int	check_ending(char *line)
{
	int	i;
	int	flag;

	if (!line)
		return (-1);
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

static char	*get_newline(char *line)
{
	char	*newline;
	char	*new;

	if (!line)
		return (NULL);
	new = readline("> ");
	if (!new)
	{
		free(line);
		return (NULL);
	}
	newline = ft_threejoin(line, "\n", new);
	free(new);
	free(line);
	return (newline);
}

static int	check_parenthesis(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (line[j])
	{
		if (line[j] == '(')
		{
			if (search_char(line[i], " \t\r=$()\'\""))
				return (1);
		}
		i++;
		j++;
	}
	return (0);
}

char	*check_line(char *line)
{
	char	*newline;

	if (check_parenthesis(line))
	{
		free(line);
		return (NULL);
	}
	if (!check_ending(line))
		return (line);
	newline = get_newline(ft_strdup(line));
	free(line);
	while (check_ending(newline))
		newline = get_newline(newline);
	if (!newline)
		return (NULL);
	return (newline);
}
