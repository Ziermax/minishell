/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:27:03 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/11 20:00:02 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	print_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		fd_printf(1, "%s\n", split[i]);
		i++;
	}
}

char	**split_for_each(char **split, char *(*fun)(char *))
{
	char	**new_split;
	int		len;
	int		i;

	if (!split || !fun)
		return (NULL);
	len = ft_arraylen(split);
	new_split = malloc(sizeof(char *) * (len + 1));
	if (!new_split)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_split[i] = fun(split[i]);
		if (!new_split[i])
			return (free_split(new_split), NULL);
		i++;
	}
	new_split[i] = NULL;
	return (new_split);
}

char	**split_for_each_aux(char **split, void *aux,
		char *(*fun)(char *, void *))
{
	char	**new_split;
	int		len;
	int		i;

	if (!split || !fun)
		return (NULL);
	len = ft_arraylen(split);
	new_split = malloc(sizeof(char *) * (len + 1));
	if (!new_split)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_split[i] = fun(split[i], aux);
		if (!new_split[i])
			return (free_split(new_split), NULL);
		i++;
	}
	new_split[i] = NULL;
	return (new_split);
}

char	**ultra_split_for_each_aux(char **split, void *aux,
		char **(*fun)(char *, void *))
{
	char	**new_split;
	char	**tmp;
	int		i;

	new_split = NULL;
	i = -1;
	while (split[++i])
	{
		tmp = fun(split[i], aux);
		if (!tmp)
			return (free_split(new_split), NULL);
		new_split = add_array_to_array(new_split, tmp, NULL);
		if (!new_split)
			return (free_split(tmp), NULL);
		free(tmp);
	}
	if (!new_split)
		return (ft_calloc(sizeof(char *), 1));
	return (new_split);
}
