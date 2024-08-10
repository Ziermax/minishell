/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:19:13 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/10 22:07:25 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../Libft/includes/libft.h"
#include "../includes/expand.h"

char	**expand_string(char *string, t_data *data)
{
	char	**expansion;
	char	**tmp;
	int		i;

	string = remove_slash(string, "\\\"'$* ");
	if (!string)
		return (NULL);
	expansion = expand_envvar(string, data);
	free(string);
	if (!expansion)
		return (NULL);
	i = -1;
	while (expansion[++i])
	{
		if (!ft_isasterisk(expansion[i]))
			continue ;
	}
}

char	**expand_split(char **split_string, t_data *data)
{
	int		i;
	void	*tmp;

	i = -1;
	while (split_string[++i])
	{
	}
}
