/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:43:07 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/08 18:49:27 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built.h"

static int	ft_get_new(char **old, char ***new, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old[i])
	{
		if (i != index)
		{
			(*new)[j] = ft_strdup(old[i]);
			if (!(*new)[j])
				return (-1);
			j++;
		}
		i++;
	}
	(*new)[j] = NULL;
	return (0);
}

int	ft_delete_var(char ***str, char *var)
{
	int		idx_del;
	char	**new;

	idx_del = check_var(*str, var);
	if (idx_del == -1)
	{
		free(var);
		return (0);
	}
	new = ft_calloc(ft_splitlen(*str), sizeof(char *));
	if (!new)
	{
		free(var);
		return (1);
	}
	if (ft_get_new(*str, &new, idx_del) == -1)
	{
		free(var);
		return (ft_free(&new));
	}
	free(*str);
	*str = new;
	free(var);
	return (0);
}

int	ft_unset(char **argv, t_data *data)
{
	int	flag;

	argv++;
	if (!argv)
		return (0);
	flag = 0;
	while (*argv)
	{
		flag += ft_delete_var(&(data->env), get_var(*argv));
		flag += ft_delete_var(&(data->exp), get_var(*argv));
		argv++;
	}
	return (flag > 0);
}
