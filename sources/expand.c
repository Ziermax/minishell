/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:19:13 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/15 20:09:05 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../Libft/includes/libft.h"
#include "../includes/expand.h"

static char	**expand_asterisk_aux(char *string, void *null)
{
	char	**expansion;

	(void)null;
	expansion = expand_asterisk(string);
	if (!expansion)
		return (NULL);
	if (ft_isasterisk(string) && *expansion)
		return (expansion);
	free_split(expansion);
	string = remove_slash(string, "");
	if (!string)
		return (NULL);
	expansion = add_dir(NULL, string);
	if (!expansion)
		return (NULL);
	return (expansion);
}

char	**expand_string(char *string, void *data)
{
	char	**expansion;
	char	**aux;

	string = remove_slash(string, "\\\"'* ");
	if (!string)
		return (NULL);
	aux = expand_envvar(string, data);
	free(string);
	if (!aux)
		return (NULL);
	expansion = split_for_each(aux, remove_quotes_string);
	free_split(aux);
	if (!expansion)
		return (NULL);
	aux = ultra_split_for_each_aux(expansion, NULL, expand_asterisk_aux);
	free_split(expansion);
	if (!aux)
		return (NULL);
	expansion = split_for_each_aux(aux, "", remove_slash);
	free_split(aux);
	return (expansion);
}

char	**expand_split(char **split_string, t_data *data)
{
	char	**expansion;

	expansion = ultra_split_for_each_aux(split_string, data, expand_string);
	free_split(split_string);
	if (!expansion)
		return (NULL);
	return (expansion);
}
