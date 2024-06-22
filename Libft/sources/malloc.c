/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:43:14 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/21 23:46:16 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/libft.h"

void	*ft_calloc(int count, int size)
{
	char	*rtrn;
	int		i;

	rtrn = malloc(sizeof(char) * count * size);
	if (!rtrn)
		return (NULL);
	i = 0;
	count = count * size;
	while (i < count)
		rtrn[i++] = 0;
	return (rtrn);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	*add_dir(void *array, void *dir)
{
	void	**new_array;
	void	**old_array;
	int		len;
	int		i;
	
	old_array = array;
	len = ft_arraylen(old_array);
	new_array = malloc(sizeof(void *) * (len + 2));
	if (!new_array)
		return (free(old_array), NULL);
	i = 0;
	while (i < len)
	{
		new_array[i] = old_array[i];
		i++;
	}
	new_array[i] = dir;
	new_array[i + 1] = NULL;
	free(old_array);
	return (new_array);
}
