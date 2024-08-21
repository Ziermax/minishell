/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:04:09 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/21 13:15:48 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built.h"
#include "../includes/built_utils.h"

static int	ft_update_pwd(char **data, char *path, char *index)
{
	int		idx;
	char	*new;
	char	*equal;

	idx = get_index_var(data, index);
	if (idx == -1)
		return (1);
	equal = ft_strjoin(index, "=");
	if (!equal)
		return (1);
	new = ft_strjoin(equal, path);
	free(equal);
	if (!new)
		return (1);
	free(data[idx]);
	data[idx] = new;
	return (0);
}

int	update_environment(t_data *data, char *path)
{
	int		idx_pwd;
	int		idx_old;
	int		ret;

	if (!path)
		return (1);
	ret = 0;
	idx_pwd = get_index_var(data->envp, "PWD");
	idx_old = get_index_var(data->envp, "OLDPWD");
	if (idx_pwd == -1 && idx_old == -1)
		return (0);
	else if (idx_pwd != -1)
	{
		if (idx_old != -1)
		{
			ret += ft_update_pwd(data->envp, data->pwd, "OLDPWD");
			ret += ft_update_pwd(data->exp, data->pwd, "OLDPWD");
		}
		ret += ft_update_pwd(data->envp, path, "PWD");
		ret += ft_update_pwd(data->exp, path, "PWD");
		return (ret);
	}
	ret += ft_update_pwd(data->envp, data->pwd, "OLDPWD");
	ret += ft_update_pwd(data->exp, data->pwd, "OLDPWD");
	return (ret);
}
