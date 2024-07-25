/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:11:59 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/25 18:28:21 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/structs.h"

int	ft_isvarchar(int c)
{
	return (ft_isalnum(c) || c == '_');
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

char	**expand_and_replace(char **expansion, int *index,
	char **(*create_array)(char *, int *))
{
	char	**new;
	int		i;

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

char	*remove_quotes(char *string)
{
	char	**splt_str;
	char	*tmp;
	int		len;
	int		i;

	splt_str = ultra_split(string, no_skip, next_string);
	if (!splt_str)
		return (NULL);
	i = -1;
	while (splt_str[++i])
	{
		if (splt_str[i][0] != '\'' && splt_str[i][0] != '\"')
			continue ;
		len = ft_strlen(splt_str[i]);
		if (splt_str[i][len - 1] == '\'' || splt_str[i][len - 1] == '\"')
			splt_str[i][len - 1] = '\0';
		tmp = ft_substr(splt_str[i], 1, len);
		if (!tmp)
			return (free_split(splt_str), NULL);
		free(splt_str[i]);
		splt_str[i] = tmp;
	}
	tmp = ft_splitjoin(splt_str);
	free_split(splt_str);
	return (tmp);
}
