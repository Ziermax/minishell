/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:24:16 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/11 22:14:25 by mvelazqu         ###   ########.fr       */
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
//	if (split_string[i][0] != '$' || (split_string[i][0] &&
//			!ft_isvarchar(split_string[i][1]) && split_string[i][1] != '?'))
//		continue ;

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
/*
int	main(int argc, char **argv, char **envp)
{
	char	**expansion;
	char	*str;
	char	*tmp;
	t_data	data;
	int		i;

	if (argc > 2)
		return (1);
	if (argc == 1)
		str = "'$USER'\\\"$USER.HOla Mundo\"\\$USER\\\"";
	else
		str = argv[1];
	data.exit_status = 123;
	data.envp = envp;
	printf("Expanding this:\n%s\n", str);
	expansion = expand_envvar(str, &data);
	if (!expansion)
		return (2);
	printf("Preresult:\n");
	print_split(expansion);
	i = -1;
	while (expansion[++i])
	{
		str = remove_quotes_string(expansion[i]);
		if (!str)
			return (free_split(expansion), 3);
		//tmp = remove_slash(str, "");
		//free(str);
		//if (!tmp)
		//	return (4);
		free(expansion[i]);
		expansion[i] = str;//Change str to tmp
	}
	printf("Result:\n");
	print_split(expansion);
	free_split(expansion);
}*/
/*
static char	*expand_v(char *string, t_data *data)
{
	char	*expanded;
	char	*slashed;

	expanded = search_envvar(string, data);
	if (!expanded)
		return (NULL);
	slashed = add_slash(expanded, "*\\\"\'");
	free(expanded);
	return (slashed);
}

static char	*expand_env(char *string, t_data *data)
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
}*/
	/*int		i;

	split_string = ultra_split(string, no_skip, xp_next_string);
	if (!split_string)
		return (NULL);
	i = -1;
	while (split_string[++i])
	{
		if (split_string[i][0] == '\'')
			continue ;
		string = expand_env(split_string[i], data);
		if (!string)
			return (free_split(split_string), NULL);
		free(split_string[i]);
		split_string[i] = string;
	}
	string = ft_splitjoin(split_string);
	free_split(split_string);
	if (!string)
		return (NULL);
	split_string = ultra_split(string, skip_spaces, xp_next_word);
	free(string);
	return (split_string);*/
