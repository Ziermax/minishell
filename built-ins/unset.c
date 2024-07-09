/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:31:29 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/09 18:33:33 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built.h"
#include "../includes/built_utils.h"
#include "../Libft/includes/libft.h"

static void	ft_get_new(char **old, char **new, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old[i])
	{
		if (i != index)
		{
			new[j] = old[i];
			j++;
		}
		i++;
	}
	free(old[index]);
}

int	ft_delete_var(char **data, char *var)
{
	int		idx_del;
	char	**new;

	idx_del = check_var(data, var);
	if (idx_del == -1)
	{
		free(var);
		return (0);
	}
	new = ft_calloc(ft_arraylen(data), sizeof(char *));
	if (!new)
	{
		free(var);
		return (free_split(new), 1);
	}
	ft_get_new(data, new, idx_del);
	free(data);
	data = new;
	free(var);
	return (0);
}

static int	check_options(char *str)
{
	if (str[0] == '-')
	{
		fd_printf(2, "minishell: unset: options are not avaliable\n");
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
	flag = 0;
	while (*argv)
	{
		flag += check_options(*argv);
		flag += ft_delete_var(data->envp, get_var(*argv));
		flag += ft_delete_var(data->exp, get_var(*argv));
		argv++;
	}
	return (flag > 0);
}
