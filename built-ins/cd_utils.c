/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:29:18 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/21 13:25:23 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built.h"
#include "../includes/built_utils.h"

int	getcdtype(char *str)
{
	if (!str)
		return (1);
	if (str[0] == '-' && !str[1])
		return (0);
	else if (str[0] == '-' && str[1])
	{
		fd_printf(2, "minishell: cd: -%c: invalid option\n", str[1]);
		fd_printf(2, "cd: options are not avaliable\n");
		return (-1);
	}
	else if (str[0] == '~')
		return (1);
	else if (str[0] == '.' && !str[1])
		return (2);
	return (3);
}

void	delete_last_slash(char *str)
{
	int	i;

	if (!str)
		return ;
	i = ft_strlen(str) - 1;
	if (!i)
		return ;
	if (str[i] == '/')
		str[i] = '\0';
}

int	put_pwd_env(t_data *data, char *var)
{
	int		idx;
	char	**new;
	char	**save;
	char	*equalvar;

	idx = get_index_var(data->envp, var);
	if (idx == -1 && get_index_var(data->exp, var) != -1)
	{
		equalvar = ft_strjoin(var, "=");
		if (!equalvar)
			return (1);
		save = ft_splitdup(data->envp);
		if (!save)
			return (1);
		new = add_created_data(data->envp, equalvar);
		free(equalvar);
		if (!new)
		{
			data->envp = save;
			return (1);
		}
		data->envp = new;
		free_split(save);
	}
	return (0);
}
