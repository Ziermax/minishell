/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:02:49 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/23 20:39:06 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/structs.h"

int	ft_isexpansible(char *str)
{
	int	asterisk;

	if (!str)
		return (0);
	asterisk = 0;
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
		{
			str = next_string(str);
			continue ;
		}
		if (*str == '*')
			asterisk = 1;
		else if (*str == '/')
			return (0);
		str++;
	}
	return (asterisk);
}

int	ft_isseparable(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
			str = next_string(str);
		else if (*str == ' ')
			return (1);
		else
			str++;
	}
	return (0);
}

int	ft_isvarchar(int c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*search_envvar(char *key, t_data *data)
{
	char	*value;
	int		len;

	if (!key)
		return (NULL);
	if (*key == '?')
		return (ft_itoa(data->exit));
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

char	**expand_and_replace(char **expansion, int *index,
	char **(*create_array)(char *, int *))
{
	char	**new;
	int		i;
	static int	id;

	i = *index;
	new = create_array(expansion[i], index);
	if (!new)
		return (free_split(expansion), NULL);
	if (!*new)
		return (free_split(new), expansion);
	expansion = add_array_to_array(expansion, new, expansion[i]);
	if (!expansion)
		return (free_split(new), NULL);
	expansion = remove_dir(expansion, expansion[i]);
	free(new);
	return (expansion);
}
