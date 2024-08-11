/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:27:03 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/11 15:37:16 by mvelazqu         ###   ########.fr       */
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

char	**split_for_each(char **split, char *(*func)(char *))
{
	char	**new_split;
	int		len;
	int		i;

	len = ft_arraylen(split);
	new_split = malloc(sizeof(char *) * (len + 1));
	if (!new_split)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_split[i] = func(split[i]);
		if (!new_split[i])
			return (free_split(new_split), NULL);
		i++;
	}
	new_split[i] = NULL;
	return (new_split);
}
