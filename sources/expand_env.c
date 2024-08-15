/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:24:16 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/15 20:06:15 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/expand.h"

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

static char	*expand_var(char *string, void *data)
{
	char	*expanded;
	char	*slashed;

	if (!string || !data)
		return (NULL);
	if (*string != '$' || (!xp_ft_isvarchar(string[1]) && string[1] != '?'))
		return (ft_strdup(string));
	expanded = search_envvar(&string[1], data);
	if (!expanded)
		return (NULL);
	slashed = add_slash(expanded, "*\\\"\'");
	free(expanded);
	return (slashed);
}

static char	*expand_env_string(char *string, void *data)
{
	char	**split_string;
	char	**tmp;

	if (!string || !data)
		return (NULL);
	if (*string == '\'')
		return (ft_strdup(string));
	split_string = ultra_split(string, no_skip, xp_next_var);
	if (!split_string)
		return (NULL);
	tmp = split_for_each_aux(split_string, data, expand_var);
	free_split(split_string);
	if (!tmp)
		return (NULL);
	split_string = tmp;
	string = ft_splitjoin(split_string);
	free_split(split_string);
	return (string);
}

char	**expand_envvar(char *string, t_data *data)
{
	char	**split_string;
	char	**tmp;

	split_string = ultra_split(string, no_skip, xp_next_string);
	if (!split_string)
		return (NULL);
	tmp = split_for_each_aux(split_string, data, expand_env_string);
	free_split(split_string);
	if (!tmp)
		return (NULL);
	split_string = tmp;
	string = ft_splitjoin(split_string);
	free_split(split_string);
	if (!string)
		return (NULL);
	split_string = ultra_split(string, skip_spaces, xp_next_word);
	free(string);
	return (split_string);
}
