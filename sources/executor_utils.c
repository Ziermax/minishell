/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:09:14 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/20 16:53:42 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/executor.h"

int	error_command(char *command)
{
	DIR	*aux;

	if (!command)
	{
		fd_printf(2, PRMTERR": permission denied\n");
		return (126);
	}
	aux = opendir(command);
	if (aux)
	{
		closedir(aux);
		fd_printf(2, PRMTERR"%s: Is a directory\n", command);
		return (126);
	}
	else if (!ft_strchr(command, '/'))
		return (fd_printf(2, PRMTERR"%s: command not found\n", command),
			127);
	else if (access(command, F_OK) == 0)
		return (fd_printf(2, PRMTERR"%s: Permission denied\n", command),
			126);
	fd_printf(2, PRMTERR"%s: No such file or directory\n", command);
	return (127);
}

void	get_exit_status(t_executor *executor_data, t_cmd **cmd)
{
	t_cmd	*command;
	int		i;

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
	command = *cmd;
	i = executor_data->exit_status;
	while (command && ((command->connection_type == PIPE)
			|| (command->connection_type == OR && i == 0)
			|| (command->connection_type == AND && i != 0)))
		command = command->next;
	*cmd = command;
}

void	pipetion(t_cmd *command)
{
	int	pipe_end[2];

	if (pipe(pipe_end) == -1)
		return ;
	command->fd_write = pipe_end[WR];
	command->fd_aux = pipe_end[RD];
	command->next->fd_read = pipe_end[RD];
}

void	execut_piped_command(t_cmd *command, t_data *data, t_executor *exdt)
{
	exdt->pid = fork();
	if (exdt->pid == -1)
	{
		data->end = 1;
		return ;
	}
	if (!exdt->pid)
		execute_command(command, data);
	exdt->pids = add_integer(exdt->pids, exdt->num_of_cmd, exdt->pid);
	if (!exdt->pids)
		data->end = 1;
}
