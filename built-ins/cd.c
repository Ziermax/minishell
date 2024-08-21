/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:25:32 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/21 13:25:12 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built.h"
#include "../includes/built_utils.h"

int	ft_chdir(t_data *data, char *path)
{
	char	*pwd;
	int		ret;

	ret = 0;
	if (chdir(path) == -1)
	{
		fd_printf(2, "minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (fd_printf(2, "minishell: Failed to update pwd\n"), 1);
	delete_last_slash(pwd);
	if (update_environment(data, pwd) > 0)
		ret = 1;
	free(data->pwd);
	data->pwd = pwd;
	return (ret);
}

int	ft_cd(char **argv, t_data *data)
{
	int	cd_type;

	argv++;
	if (ft_arraylen(argv) > 1)
		return (fd_printf(2, "minishell: cd: too many arguments\n"), 1);
	if (put_pwd_env(data, "OLDPWD") || put_pwd_env(data, "PWD"))
		return (1);
	cd_type = getcdtype(*argv);
	if (cd_type == -1)
		return (2);
	else if (cd_type == 0)
		return (cd_old(data));
	else if (cd_type == 1)
		return (cd_home_append(data, *argv));
	else if (cd_type == 2)
		return (cd_point(data));
	else if (cd_type == 3)
		return (ft_chdir(data, *argv));
	return (1);
}
