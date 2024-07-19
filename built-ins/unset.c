/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:31:29 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/19 13:34:57 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built.h"
#include "../includes/built_utils.h"
#include "../Libft/includes/libft.h"

char	**update_data(char **data, int idx)
{
	int	i;

	i = idx;
	while (data[i])
	{
		if (i == idx)
			free(data[i]);
		if (data[i + 1])
			data[i] = data[i + 1];
		else
			data[i] = NULL;
		i++;
	}
	return (data);
}

static int	make_unset(t_data *data, char *var)
{
	int		idx;
	int		error;
	char	**tmp;

	error = 0;
	idx = get_index_var(data->envp, var);
	if (idx != -1)
	{
		tmp = update_data(data->envp, idx);
		if (tmp)
			data->envp = tmp;
		else
			error = 1;
	}
	idx = get_index_var(data->envp, var);
	if (idx != -1)
	{
		tmp = update_data(data->exp, idx);
		if (tmp)
			data->exp = tmp;
		else
			error = 1;
	}
	return (error);
}

static int	check_options(char *str)
{
	if (str[0] == '-')
	{
		fd_printf(2, "minishell: unset: %s: invalid option\n", str);
		fd_printf(2, "unset: options are not avaliable\n");
		return (1);
	}
	return (0);
}

int	ft_unset(char **argv, t_data *data)
{
	int	flag;

	argv++;
	if (!argv || !*argv)
		return (0);
	if (check_options(*argv))
		return (2);
	flag = 0;
	while (*argv)
	{
		flag += make_unset(data, *argv);
		argv++;
	}
	print_split(data->envp);
	return (flag > 0);
}
