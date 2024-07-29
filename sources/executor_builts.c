/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:18:51 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/29 00:54:46 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built.h"
#include "../includes/executor.h"

int	ft_isbuilting(char *str)
{
	if (!ft_strncmp(str, "echo", 5))
		return (ECHO);
	if (!ft_strncmp(str, "unset", 6))
		return (UNSET);
	if (!ft_strncmp(str, "export", 7))
		return (EXPORT);
	if (!ft_strncmp(str, "env", 4))
		return (ENV);
	if (!ft_strncmp(str, "cd", 3))
		return (CD);
	if (!ft_strncmp(str, "pwd", 4))
		return (PWD);
	if (!ft_strncmp(str, "exit", 6))
		return (EXIT);
	return (0);
}

void	execbuilt(char	**cmd_argv, t_data *data)
{
	int	cmd_flag;

	cmd_flag = ft_isbuilting(cmd_argv[0]);
	printf("is Builting\n");
//	if (cmd_flag == ECHO)
//		ft_echo(cmd_argv, data);
//	else if (cmd_flag == UNSET)
//		ft_unset(cmd_argv, data);
//	else if (cmd_flag == EXPORT)
//		ft_export(cmd_argv, data);
//	//else if (cmd_flag == ENV)
//		//ft_env(cmd_argv, data);
//	else if (cmd_flag == CD)
//		ft_cd(cmd_argv, data);
//	else if (cmd_flag == PWD)
//		ft_pwd(cmd_argv, data);
//	//else if (cmd_flag == EXIT)
//		//ft_export(cmd_argv, data);
	exit(0);
	cmd_flag = cmd_flag + 1;
	data = data + 1;
	return ;
}
