/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:47:30 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/19 14:00:00 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built_utils.h"

static char	*make_array(char **content, int size)
{
	char	*var;
	char	*val;
	char	*value;
	char	*index;
	int		i;

	i = 0;
	var = ft_strdup("");
	while (i < size)
	{
		index = ft_itoa_brackets(i);
		value = ft_threejoin("\"", content[i], "\"");
		val = ft_threejoin(index, "=", value);
		free(index);
		free(value);
		if (i)
			var = ft_threejoin(var, " ", val);
		else
			var = ft_threejoin(var, "", val);
		free(val);
		if (!var)
			return (NULL);
		i++;
	}
	return (var);
}

static char	*get_content(char *var, int *idx)
{
	int		i;
	int		size;
	char	*value;

	i = *idx;
	size = 0;
	while (var[i] != ' ' && var[i] != ')')
	{
		i++;
		size++;
	}
	value = ft_calloc(size + 1, sizeof(char));
	if (!value)
		return (NULL);
	i = 0;
	while (var[*idx] != ' ' && var[*idx] != ')')
	{
		value[i++] = var[*idx];
		(*idx)++;
	}
	return (value);
}

static char	*get_array(char *input, int size)
{
	char	**array;
	char	*arr;
	int		i;
	int		idx_arr;

	array = ft_calloc(size + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (input[i] != '(')
		i++;
	i++;
	idx_arr = 0;
	while (input[i] && input[i] != ')')
	{
		if (input[i] != ' ' && input[i] != '\t')
			array[idx_arr++] = get_content(input, &i);
		i++;
	}
	arr = make_array(array, size);
	free_split(array);
	return (arr);
}

static char	*export_array2(char *var)
{
	char	*begin;
	char	*tmp;
	char	*arr;
	int		size;

	size = get_length_array(var);
	tmp = get_var(var);
	begin = ft_strjoin(tmp, "=(");
	free(tmp);
	if (!begin)
		return (NULL);
	tmp = get_array(var, size);
	if (!tmp)
	{
		free(begin);
		return (NULL);
	}
	arr = ft_threejoin(begin, tmp, ")");
	free(begin);
	free(tmp);
	return (arr);
}

int	export_array(t_data *data, char *var)
{
	char	*array;
	char	*tmp;
	char	**new;
	int		idx;

	array = export_array2(var);
	if (!array)
		return (1);
	tmp = get_var(var);
	idx = get_index_var(data->exp, tmp);
	free(tmp);
	if (idx != -1)
	{
		free(data->exp[idx]);
		data->exp[idx] = array;
	}
	else
	{
		new = add_created_data(data->exp, array);
		free(array);
		if (!new)
			return (1);
		data->exp = new;
	}
	return (0);
}
