/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:59:09 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/10 19:54:54 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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

static void	fill_array(void **new_array, void **array1,
	void **array2, void *position)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (array1[j])
	{
		new_array[i++] = array1[j];
		if (array1[j] == position)
		{
			while (array2[k])
			{
				new_array[i++] = array2[k];
				k++;
			}
		}
		j++;
	}
	new_array[i] = NULL;
}

void	*add_array_to_array(void *array, void *to_add, void *position)
{
	void	**new_array;
	int		len[2];

	if (!to_add)
		return (array);
	len[0] = ft_arraylen(array);
	len[1] = ft_arraylen(to_add);
	new_array = malloc(sizeof(void *) * (len[0] + len[1] + 1));
	if (!new_array)
		return (free_split(array), NULL);
	fill_array(new_array, array, to_add, position);
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
	free(array);
	new_array[i] = to_add;
	return (free(array), new_array);
}

void	*remove_dir(void *array, void *to_remove)
{
	void	**aux;
	int		seen;
	int		len;
	int		i;

	if (!to_remove || !array)
		return (array);
	aux = array;
	seen = 0;
	len = -1;
	while (aux[++len])
		if (!seen && aux[len] == to_remove)
			len = seen -= 1;
	if (!seen)
		return (array);
	aux = malloc(sizeof(void *) * (len + 1));
	if (!aux)
		return (free_split(array), NULL);
	i = -1;
	while (++i < len)
	{
		if (((void **)array)[i] == to_remove)
			array += sizeof(array);
		aux[i] = ((void **)array)[i];
	}
	return (free(array - sizeof(void *)), aux);
}
/*
#include <stdio.h>
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
	array = add_array_to_array(array, tmp, array[1]);
	printf("\nadded_array:\n");
	print_split(array);
	free(array[5]);
	array = remove_dir(array, array[5]);
	printf("\nremoved_array:\n");
	print_split(array);
	free_split(array);
	free(tmp);
}*/
