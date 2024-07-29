/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:09:14 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/29 12:33:57 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/executor.h"

void	error_command(char *command)
{
	DIR	*aux;

	aux = opendir(command);
	if (!command)
		fd_printf(2, "minichell: : permission denied\n");
	else if (aux)
	{
		closedir(aux);
		fd_printf(2, "minichell: %s: Is a directory\n", command);
	}
	else if (!ft_strchr(command, '/'))
		fd_printf(2, "minichell: %s: command not found\n", command);
	else if (access(command, F_OK) == 0)
		fd_printf(2, "minichell: %s: Permission denied\n", command);
	else
		fd_printf(2, "minichell: %s: No such file or directory\n", command);
}

void	get_exit_status(t_executor *executor_data)
{
	int	i;

	i = 0;
	while (i < executor_data->num_of_cmd)
	{
		executor_data->exit_status = 0;
		waitpid(executor_data->pids[i], &executor_data->exit_status, 0);
		executor_data->exit_status = executor_data->exit_status >> 8;
		i++;
	}
	free(executor_data->pids);
	executor_data->pids = NULL;
	executor_data->num_of_cmd = 0;
}
