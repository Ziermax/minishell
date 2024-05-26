/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:08:07 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/05/26 19:43:37 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_tokens(char *line)
{
	int	count;
	int	i;

	i = 0;
	while (line[i])
	{
		while (
		i++;
	}
	return (count);
}

static char	**split_line_to_tokens(char *line)
{
	char	**splitted;
	int		tokens;

	tokens = count_tokens(line);
	splitted = (char **)malloc(sizeof(char *) * (tokens + 1));
	if (!splitted)
		return (NULL);
}

t_token	*tokener(char *line)
{
	t_token	*tokens;
	char	**splitted_line;
	int		i;

	splitted_line = split_line_to_tokens(line);
	while (splitted_line[i])
	{
		i++;
	}
	return (tokens);
}
