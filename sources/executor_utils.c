/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:09:14 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/31 17:56:07 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/executor.h"

int	error_command(char *command)
{
	DIR	*aux;

	if (!command)
	{
		fd_printf(2, "minichell: : permission denied\n");
		return (126);
	}
	aux = opendir(command);
	if (aux)
	{
		closedir(aux);
		fd_printf(2, "minichell: %s: Is a directory\n", command);
		return (126);
	}
	else if (!ft_strchr(command, '/'))
		return (fd_printf(2, "minichell: %s: command not found\n", command),
			127);
	else if (access(command, F_OK) == 0)
		return (fd_printf(2, "minichell: %s: Permission denied\n", command),
			126);
	fd_printf(2, "minichell: %s: No such file or directory\n", command);
	return (127);
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
