/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:46:51 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/10 16:10:42 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../Libft/includes/libft.h"
#include "../includes/expand.h"

int	ft_isvarchar(int c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*remove_quotes_string(char *string)
{
	int	len;
	int	quote;

	if (!string)
		return (NULL);
	quote = *string;
	if (quote != '\'' && quote != '\"')
		return (ft_strdup(string));
	len = ft_strlen(string);
	if (len < 2)
		return (ft_calloc(sizeof(char), 1));
	if (string[len - 1] == '\'' || string[len - 1] == '\"')
		len -= 2;
	else
		len -= 1;
	printf("len: %d\n", len);
	string = ft_substr(string, 1, len);
	if (!string)
		return (NULL);
//	if (quote == '\'')
//		string = add_slash(string, "$ *\"'");
//	if (quote == '\"')
//		string = add_slash(string, " *\"'");
	return (string);
}

char	*remove_quotes(char *string)
{
	char	**split_string;
	int		i;

	split_string = ultra_split(string, no_skip, xp_next_string);
	if (!split_string)
		return (NULL);
	i = -1;
	while (split_string[++i])
	{
		printf("remove[%d]: %s\n", i, split_string[i]);
		if (split_string[i][0] != '\'' && split_string[i][0] != '\"')
			continue ;
		string = remove_quotes_string(split_string[i]);
		if (!string)
			return (free_split(split_string), NULL);
		free(split_string[i]);
		split_string[i] = string;
	}
	string = ft_splitjoin(split_string);
	free_split(split_string);
	return (string);
}

char	**expand_full(char **split_string)
{
	int		i;
	char	**expand;

	return (split_string);
}
