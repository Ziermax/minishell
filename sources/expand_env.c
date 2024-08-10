/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:17:45 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/03 13:11:49 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/expand.h"

char	*expand_env_var(char *string, t_data *data)
{
	char	**split_string;
	char	*tmp;

	string = ;
}


char	*expand_env_string(char *string, t_data *data)
{
	char	**split_string;
	char	*tmp;

	split_string = ultra_split(string, no_skip, xp_next_string);
	if (!split_string)
		return (NULL);
	i = -1;
	while (split_string[++i])
	{
		if (split_string[i][0] == '\'')
			continue ;
		tmp = expand_var(split_string[i], data);
		if (!tmp)
			return (free_split(split_string), NULL);
		free(split_string[i]);
		split_string[i] = tmp;
	}
	split_string = remove_quotes(split_string);
	if (!split_string)
		return (NULL);
	string = ft_splitjoin(split_string);
	free_split(split_string);
	return (string);
}

char	*expand_envvar(char *string, t_data *data)
{
	char	**split_string;
	char	*tmp;

	string = 
	tmp = expand_env_string(string, data);
}
