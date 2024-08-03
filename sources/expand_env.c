/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:17:45 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/03 17:49:04 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/expand.h"

int	ft_isvarchar(int c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*search_envvar(char *key, t_data *data)
{
	char	*value;
	int		len;

	if (!key)
		return (NULL);
	if (*key == '?')
		return (ft_itoa(data->exit_status));
	if (!data->envp)
		return (ft_strdup(""));
	key = ft_strjoin(key, "=");
	if (!key)
		return (NULL);
	len = ft_strlen(key);
	value = search_word_in_split(key, data->envp, len);
	if (!value)
		return (free(key), ft_strdup(""));
	return (free(key), ft_strdup(&value[len]));
}

static char	*expand_v(char *string, t_data *data)
{
	char	*expanded;
//	char	*slashed;

	expanded = search_envvar(string, data);
	if (!expanded)
		return (NULL);
	return (expanded);
//	slashed = add_slash(expanded, "*\\\"\'");
//	free(expanded);
//	return (slashed);
}

static char	*expand_var(char *string, t_data *data)
{
	char	**split_string;
	int		i;

	split_string = ultra_split(string, no_skip, next_var);
	if (!split_string)
		return (NULL);
	i = -1;
	while (split_string[++i])
	{
		if (split_string[i][0] != '$' || (split_string[i][0] &&
				!ft_isvarchar(split_string[i][1]) && split_string[i][1] != '?'))
			continue ;
		string = expand_v(&split_string[i][1], data);
		if (!string)
			return (free_split(split_string), NULL);
		free(split_string[i]);
		split_string[i] = string;
	}
	string = ft_splitjoin(split_string);
	free_split(split_string);
	return (string);
}

char	**expand_envvar(char *string, t_data *data)
{
	char	**split_string;
	char	*aux;

//	string = remove_slash(string, "\\\"'$* ");
//	if (!string)
//		return (NULL);
	aux = remove_quotes(string);
//	free(string);
	if (!aux)
		return (NULL);
	string = expand_var(aux, data);
	if (!string)
		return (NULL);
	split_string = ultra_split(string, skip_spaces, xp_next_string);
	free(string);
	return (split_string);
}
