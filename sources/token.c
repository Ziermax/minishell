/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:08:07 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/05/29 20:54:27 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_istoken(int c)
{
	return (c == '<' || c == '>' || c == '&' || c == '|');
}

char	*next_token(char *str)
{
	int	special;

	if (ft_istoken(*str))
	{
		special = *str;
		while (*str == special)
			str++;
		return (str);
	}
	while (*str && !ft_istoken(*str) && !ft_isspace(*str))
	{
		if (*str == '\'' || *str == '\"')
			str = next_string(str);
		if (*str)
			str++;
	}
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
	char	*str;

	str = "l$USER>i$USERnfile<outf\"ile cat \"e|g\"rep $USER\"hola|>outfile \"Holla mundo\"";
	splitted_line = ultra_split(str, skip_spaces, next_token);
	i = 0;
	while (splitted_line[i])
	{
		printf("splitted_line[%d]: %s\n", i, splitted_line[i]);
		i++;
	}
	free_split(splitted_line);
}
