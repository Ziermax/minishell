/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:59:09 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/11 19:28:01 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/libft.h"
#include "../includes/macros.h"

void	*add_dir(void *array, void *dir)
{
	void	**new_array;
	void	**old_array;
	int		len;
	int		i;

	if (!dir)
		return (array);
	old_array = array;
	len = ft_arraylen(old_array);
	new_array = malloc(sizeof(void *) * (len + 2));
	if (!new_array)
		return (free_split(array), NULL);
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

void	*add_array_to_array(void *array, void *to_add, void *position)
{
	void	**new_array;
	int		len[2];
	int		idx[3];

	if (!to_add)
		return (array);
	len[0] = ft_arraylen(array);
	len[1] = ft_arraylen(to_add);
	new_array = malloc(sizeof(void *) * (len[0] + len[1] + 1));
	if (!new_array)
		return (free_split(array), NULL);
	ft_bzero(idx, sizeof(int) * 3);
	while (J[idx] < len[0])
	{
		new_array[I[idx]++] = ((void **)array)[J[idx]];
		if (((void **)array)[J[idx]++] == position)
			break ;
	}
	while (K[idx] < len[1])
		new_array[I[idx]++] = ((void **)to_add)[K[idx]++];
	while (J[idx] < len[0])
		new_array[I[idx]++] = ((void **)array)[J[idx]++];
	new_array[I[idx]] = NULL;
	return (free(array), new_array);
}

int	*add_integer(int *array, int len, int to_add)
{
	int	*new_array;
	int	i;

	if (len <= 0)
		return (free(array), NULL);
	new_array = malloc(sizeof(int) * len);
	if (!new_array)
		return (free(array), NULL);
	i = 0;
	while (i < len - 1)
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[i] = to_add;
	return (free(array), new_array);
}

static int	count_dir_remove(void *array, void *to_remove)
{
	void	**aux;
	int		seen;
	int		len;
	int		i;

	i = -1;
	len = 0;
	seen = 0;
	aux = array;
	while (aux[++i])
	{
		if (aux[i] != to_remove)
			len++;
		else
			seen = 1;
	}
	if (!seen)
		return (NOT_SEEN);
	return (len);
}

void	*remove_dir(void *array, void *to_remove)
{
	void	**new_array;
	void	**aux;
	int		len;
	int		i;

	if (!to_remove || !array)
		return (array);
	len = count_dir_remove(array, to_remove);
	if (len == NOT_SEEN)
		return (array);
	new_array = malloc(sizeof(void *) * (len + 1));
	if (!new_array)
		return (free_split(array), NULL);
	i = -1;
	aux = array;
	while (++i < len)
	{
		while (aux[i] == to_remove)
			aux++;
		new_array[i] = aux[i];
	}
	new_array[i] = NULL;
	return (free(array), free(to_remove), new_array);
}
/*
int	main(void)
{
	char	**array;
	char	**tmp;

	array = ft_split("Hola Mundo Adios MUNDO");
	tmp = ft_split("Cómo estas");
	printf("array:\n");
	print_split(array);
	printf("\ntmp:\n");
	print_split(tmp);
	free_split(array);
	array = add_array_to_array(NULL, tmp, NULL);
	printf("\nadded_array:\n");
	print_split(array);
	//free(array[5]);
	array = remove_dir(array, array[5]);
	printf("\nremoved_array:\n");
	print_split(array);
	free_split(array);
	free(tmp);
}*/
