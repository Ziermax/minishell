/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:47:30 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/19 11:46:10 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built_utils.h"

char	*ft_itoa_brackets(int n)
{
	int		len;
	char	*num;

	len = ft_intlen(n);
	num = ft_calloc(len + 3, sizeof(char));
	if (!num)
		return (NULL);
	num[0] = '[';
	while (len > 0)
	{
		num[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	num[len + 2] = ']';
	return (num);
}

char *make_array(char **content, int size)
{
	char	*var;
	char 	*val;
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

char *get_content(char *var, int *idx)
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

char *get_array(char *input, int size)
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

int	export_array(t_data *data, char *var)
{
	char	*begin;
	char	*array;
	char	*tmp;
	int		size;
	int		delete;

	size = get_length_array(var);
	tmp = get_var(var);
	delete = 0;
	delete = get_index_var(data->exp, tmp);
	begin = ft_strjoin(tmp, "=(");
	free(tmp);
	if (!begin)
		return (1);
	tmp = get_array(var, size);
	if (!tmp)
	{
		free(begin);
		return (1);
	}
	array = ft_threejoin(begin, tmp, ")");
	free(tmp);
	free(begin);
	if (!array)
		return (1);
	if (delete != -1)
	{
		free(data->exp[delete]);
		data->exp[delete] = array;
		return (0);
	}
	data->exp = add_created_data(data->exp, array);
	free(array);
	return (0);
}
