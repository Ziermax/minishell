/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:38:15 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/21 13:25:37 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built.h"
#include "../includes/built_utils.h"

int	cd_point(t_data *data)
{
	char	*cwd;
	char	*cd;
	int		flag;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		fd_printf(2, "cd: error retrieving current directory: getcwd: cannot"
			"access parent derectories: No such file or directory\n");
		if (data->pwd)
			cd = ft_strjoin(data->pwd, "/.");
		else
			cd = ft_strdup(".");
		if (!cd)
			return (1);
		flag = update_environment(data, cd);
		free(data->pwd);
		data->pwd = cd;
		return (flag > 0);
	}
	free(cwd);
	return (ft_chdir(data, data->pwd));
}

int	cd_old(t_data *data)
{
	int		idx;
	char	*path;

	idx = get_index_var(data->envp, "OLDPWD");
	if (idx == -1)
		return (fd_printf(2, "minishell: cd: OLDPWD not set\n"), 1);
	path = get_value(data->envp[idx]);
	if (!path)
		return (1);
	idx = ft_chdir(data, path);
	if (!idx)
		fd_printf(1, "%s\n", data->pwd);
	free(path);
	return (idx);
}

int	cd_home_append(t_data *data, char *path)
{
	char	*cd;
	char	*home;
	int		ret;

	home = getenv("HOME");
	if (!home && !path)
		return (fd_printf(2, "minishell: cd: HOME not set\n"), 1);
	if (!path || (path[0] == '~' && !path[1]))
		return (ft_chdir(data, data->home));
	else
	{
		cd = ft_strjoin(data->home, path + 1);
		if (!cd)
			return (1);
		ret = ft_chdir(data, cd);
		free(cd);
	}
	return (ret);
}
