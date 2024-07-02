/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:10:51 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/02 16:39:14 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/executor.h"
#include "../includes/token.h"
#include <sys/types.h>
#include <sys/wait.h>

t_pipe	*circular_pipes(void)
{
	t_pipe	*pip1;
	t_pipe	*pip2;

	pip1 = ft_calloc(sizeof(t_pipe), 1);
	if (!pip1)
		return (NULL);
	pip2 = ft_calloc(sizeof(t_pipe), 1);
	if (pip2)
		return (free(pip1), NULL);
	pip1->next = pip2;
	pip2->next = pip1;
	return (pip1);
}

int	heredoc_case(char *word)
{
	int		pipe_doc[2];
	char	*line;
	char	*limitator;

	printf("heredoc\n");
	if (pipe(pipe_doc) == -1)
		return (-1);
	limitator = ft_strjoin(word, "\n");
	if (!limitator)
		return (-1);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, limitator, ft_strlen(limitator) + 1))
			break ;
		write(pipe_doc[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	free(limitator);
	close(pipe_doc[1]);
	return (pipe_doc[0]);
}

int	open_file(char *file, t_type open_mode, int last_fd)
{
	int	o_flag;
	int	fd;

	close(last_fd);
	if (open_mode == R_OUT)
		o_flag = O_WRONLY | O_TRUNC | O_CREAT;
	else if (open_mode == APP)
		o_flag = O_WRONLY | O_APPEND | O_CREAT;
	else if (open_mode == R_IN)
		o_flag = O_RDONLY;
	if (open_mode != HDOC)
		fd = open(file, o_flag, 420);
	else
		fd = heredoc_case(file);
	if (fd == -1)
		return (-1);
	printf("opening: \"%s\" in %d ass: %s\n",
		file, fd, get_type_str(open_mode));
	return (fd);
}

void	manage_files(t_cmd *command)
{
	t_file	*file;

	file = command->files;
	while (file)
	{
		if (file->open_mode == R_OUT || file->open_mode == APP)
			command->fd_write = open_file(file->string, file->open_mode,
					command->fd_write);
		else if (file->open_mode == R_IN || file->open_mode == HDOC)
			command->fd_read = open_file(file->string, file->open_mode,
					command->fd_read);
		printf("Mode: %s read: %d write: %d\n",
			get_type_str(file->open_mode), command->fd_read, command->fd_write);
		if (((file->open_mode == R_IN || file->open_mode == HDOC)
				&& command->fd_read == -1) || ((file->open_mode == R_OUT
					|| file->open_mode == APP) && command->fd_write == -1))
			break ;
		file = file->next;
	}
	printf("Exiting\n");
	if (file)
		file = file->next;
	while (file)
	{
		if (file->open_mode == HDOC)
			close(heredoc_case(file->string));
		file = file->next;
	}
}

void	execute_command(t_cmd *command)
{
	//sleep(5);
	//printf("cmd: %s, read: %d, write: %d\n",
	//	command->path, command->fd_read, command->fd_write);
	if (command->fd_write != -1)
		dup2(command->fd_write, STDOUT_FILENO);
	if (command->fd_read != -1)
		dup2(command->fd_read, STDIN_FILENO);
	close(command->fd_read);
	close(command->fd_write);
	close(command->fd_aux);
	execve(command->path, command->cmd_split, command->envp);
	//fd_printf(2, "Problem: %s, split: %p, envp: %p\n", command->path,
		//command->cmd_split, command->envp);
	//perror(command->path);
	exit(0);
}

void	get_exit_status(t_executor *executor_data)
{
	int	i;

	i = 0;
	while (i < executor_data->num_of_cmd)
	{
		waitpid(executor_data->pids[i], &executor_data->exit_status, WUNTRACED);
		i++;
	}
	free(executor_data->pids);
	executor_data->pids = NULL;
	executor_data->num_of_cmd = 0;
}

int	executor(t_cmd *command)
{
	t_executor	exdt;
	int			pipe_end[2];

	ft_bzero(&exdt, sizeof(t_executor));
	while (command)
	{
		//printf("executring: %s\n", command->path);
		exdt.num_of_cmd += 1;
		if (command->connection_type == PIPE)
		{
			pipe(pipe_end);
			printf("pipe: [%d, %d]\n", pipe_end[RD], pipe_end[WR]);
			command->fd_write = pipe_end[WR];
			command->fd_aux = pipe_end[RD];
			command->next->fd_read = pipe_end[RD];
		}
		manage_files(command);
		exdt.pid = fork();
		if (!exdt.pid)
			execute_command(command);
		exdt.pids = add_integer(exdt.pids, exdt.num_of_cmd, exdt.pid);
		if (!exdt.pids)
			return (-1);
		close(command->fd_read);
		printf("closeing: %d\n", command->fd_read);
		close(command->fd_write);
		printf("closeing: %d\n\n", command->fd_write);
		if (command->connection_type == AND || command->connection_type == OR
			|| command->connection_type == NO_TYPE)
		{
			get_exit_status(&exdt);
			if (command->connection_type == AND && exdt.exit_status != 0)
				break;
			if (command->connection_type == OR && exdt.exit_status == 0)
				break;
		}
		command = command->next;
	}
	return (exdt.exit_status);
}
