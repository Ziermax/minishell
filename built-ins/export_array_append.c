/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_array_append.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:14:10 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/19 14:00:22 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built_utils.h"

static char	*fuse_arrays(char *arr, char *var)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i] != ')')
		i++;
	j = 0;
	while (var[j] != '(')
		j++;
	j++;
	arr[i++] = ' ';
	while (var[j])
	{
		arr[i++] = var[j++];
	}
	return (arr);
}

static int	update_var(t_data *data, char *var, int idx)
{
	char	*new_array;
	int		i;
	int		j;

	i = ft_strlen(var) + ft_strlen(data->exp[idx]);
	new_array = ft_calloc(i + 1, sizeof(char));
	if (!new_array)
		return (1);
	i = 0;
	j = 0;
	while (data->exp[idx][i])
	{
		if (data->exp[idx][i] == '[')
		{
			while (data->exp[idx][i] != '\"')
				i++;
		}
		if (data->exp[idx][i] == '\"')
			i++;
		new_array[j++] = data->exp[idx][i++];
	}
	new_array = fuse_arrays(new_array, var);
	return (export_array(data, new_array));
}

static char	*add_newvar(char *new, int *j, char *var)
{
	char	*x;
	int		i;

	x = get_value(var);
	i = 0;
	while (x[i])
	{
		new[*j] = x[i++];
		(*j)++;
	}
	return (new);
}

int	update_value(t_data *data, char *var, int idx)
{
	int		i;
	int		j;
	char	*new;

	i = ft_strlen(var) + ft_strlen(data->exp[idx]);
	new = ft_calloc(i + 1, sizeof(char));
	if (!new)
		return (1);
	i = 0;
	j = 0;
	while (data->exp[idx][i])
	{
		if (data->exp[idx][i] == '\"')
		{
			new[j++] = data->exp[idx][i++];
			while (data->exp[idx][i] != '\"')
				new[j++] = data->exp[idx][i++];
			new = add_newvar(new, &j, var);
		}
		new[j++] = data->exp[idx][i++];
	}
	free(data->exp[idx]);
	data->exp[idx] = new;
	return (0);
}

int	export_array_append(t_data *data, char *append)
{
	char	*name;
	int		idx;

	name = get_var(append);
	if (!name)
		return (1);
	idx = get_index_var(data->exp, name);
	if (idx == -1)
	{
		free(name);
		return (export_array(data, append));
	}
	return (update_var(data, append, idx));
}
