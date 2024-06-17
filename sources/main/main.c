/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:06:33 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/17 15:19:04 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	find_comma(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			i++;
			while (line[i] && line[i] != '\"')
				i++;
			if (line[i] != '\"')
				return ('\"');
		}
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (line[i] != '\'')
				return ('\'');
		}
		i++;
	}
	return ('\0');
}

static char	*get_newline(char *newline)
{
	char	*line;
	char	*new;

	line = readline("> ");
	if (!line)
		return (newline);
	new = ft_strjoin(newline, line);
	free(line);
	if (!new)
		return (newline);
	free(newline);
	return (new);
}

static char	*check_line(char *line)
{
	char	*newline;
	char	comma;

	comma = find_comma(line);
	if (!comma)
		return (line);
	newline = ft_strdup(line);
	free(line);
	while (comma)
	{
		newline = get_newline(newline);
		comma = find_comma(newline);
	}
	return (newline);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;

	argc = 0;
	argv = 0;
	if (init_data(&data, envp) == -1)
		return (1);
	while (1)
	{
		 line = readline("minishell> ");
		if (line)
		{
			line = check_line(line);
			if (ft_strcmp("exit", line) == 0)
			{
				free(line);
				break ;
			}
			// add_history(line);
		}
		free(line);
	}
	ft_free(&data.env);
	ft_free(&data.exp);
	return (0);
}
