/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:08:07 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/05/28 20:53:23 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_istoken(int c)
{
	return (c == '<' || c == '>' || c == '&' || c == '|');
}

static char	*next_special_token(char *str)
{
	int	special;

	special = *str;
	while (*str == special)
		str++;
	return (str);
}

char	*next_token(char *str)
{
	if (!str || *str == '\'' || *str == '\"')
		return (next_string(str));
	if (ft_istoken(*str))
		return (next_special_token(str));
	while (*str && *str != '\'' && *str != '\"'
		&& !ft_istoken(*str) && !ft_isspace(*str))
		str++;
	return (str);
}

t_token	*tokener(char *line)
{
	t_token	*tokens;
	char	**splitted_line;
	int		i;

	tokens = NULL;
	splitted_line = ultra_split(line, skip_spaces, next_token);
	i = 0;
	while (splitted_line[i])
	{
		printf("splitted_line[%d]: \"%s\"\n", i, splitted_line[i]);
		i++;
	}
	free_split(splitted_line);
	return (tokens);
}

int	main(void)
{
	char	**splitted_line;
	int		i;

	splitted_line = ultra_split(
			">hola\"hola\">out|cat>>infile||hola<infile&&and>out<<<||",
			skip_spaces, next_token);
	i = 0;
	while (splitted_line[i])
	{
		printf("splitted_line[%d]: \"%s\"\n", i, splitted_line[i]);
		i++;
	}
	free_split(splitted_line);
}
