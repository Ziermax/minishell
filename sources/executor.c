/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:10:51 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/09 10:43:19 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/executor.h"
#include "../includes/token.h"
#include "../includes/built.h"
#include <sys/types.h>
#include <sys/wait.h>

int	executor(t_cmd *command, t_data *data);

int	ft_pwd(void)
{
	return (print_pwd());
}

int	ft_echo(char **argv)
{
	return (print_echo(argv));
}

int	heredoc_case(char *content)
{
	int		pipe_doc[2];

	if (pipe(pipe_doc) == -1)
		return (-1);
	write(pipe_doc[1], content, ft_strlen(content));
	close(pipe_doc[1]);
	return (pipe_doc[0]);
}
/*	char	*line;
	char	*limitator;

	if (pipe(pipe_doc) == -1)
		return (-1);
	limitator = ft_strjoin(content, "\n");
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
	return (pipe_doc[0]);*/

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
	fd_printf(2, "opening: \"%s\" in %d ass: %s\n",
		file, fd, get_type_str(open_mode));
	if (fd == -1)
		return (-1);
	return (fd);
}

		//printf("Mode: %s read: %d write: %d\n", get_type_str(file->open_mode),
			//command->fd_read, command->fd_write);
void	manage_files(t_cmd *command)
{
	t_file	*file;

	file = command->files;
	//lst_for_each(file, print_file);
	while (file)
	{
		if (file->open_mode == R_OUT || file->open_mode == APP)
			command->fd_write = open_file(file->string, file->open_mode,
					command->fd_write);
		else if (file->open_mode == R_IN || file->open_mode == HDOC)
			command->fd_read = open_file(file->string, file->open_mode,
					command->fd_read);
		if (((file->open_mode == R_IN || file->open_mode == HDOC)
				&& command->fd_read == -1) || ((file->open_mode == R_OUT
					|| file->open_mode == APP) && command->fd_write == -1))
		{
			fd_printf(2, "minichell: %s: %s\n", file->string, strerror(errno));
			break ;
		}
		file = file->next;
	}
	if (file)
		file = file->next;
	while (file)
	{
		if (file->open_mode == HDOC)
			close(heredoc_case(file->string));
		file = file->next;
	}
}

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

	//printf("cmd: %s, read: %d, write: %d\n",
	//	command->path, command->fd_read, command->fd_write);
	//fd_printf(2, "Problem: %s, split: %p, envp: %p\n", command->path,
		//command->cmd_split, command->envp);
	//perror(command->path);

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
	if (cmd_flag == ECHO)
		ft_echo(&cmd_argv[1]);
	if (cmd_flag == UNSET)
		ft_unset(data, cmd_argv);
	if (cmd_flag == EXPORT)
		ft_export(data, cmd_argv);
	//if (cmd_flag == ENV)
		//ft_env(data, cmd_argv);
	if (cmd_flag == CD)
		ft_cd(data, cmd_argv);
	if (cmd_flag == PWD)
		ft_pwd();
	//if (cmd_flag == EXIT)
		//ft_export(data, cmd_argv);
	exit(0);
	return ;
}

void	execute_command(t_cmd *command, t_data *data)
{
	data = data;
	if (command->fd_write != -1)
		dup2(command->fd_write, STDOUT_FILENO);
	if (command->fd_read != -1)
		dup2(command->fd_read, STDIN_FILENO);
	close(command->fd_read);
	close(command->fd_write);
	close(command->fd_aux);
	if (command->subcommand)
		exit(executor(command->subcommand, data));
	if (!command->cmd_split)
		exit(0);
	if (ft_isbuilting(command->cmd_split[0]))
		execbuilt(command->cmd_split, data);
	execve(command->path, command->cmd_split, command->envp);
	error_command(command->cmd_split[0]);
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

		//printf("executring: %s\n", command->path);
			//printf("pipe: [%d, %d]\n", pipe_end[RD], pipe_end[WR]);
		//printf("closeing: %d\n", command->fd_read);
		//printf("closeing: %d\n\n", command->fd_write);
int	executor(t_cmd *command, t_data *data)
{
	t_executor	exdt;
	int			pipe_end[2];

	ft_bzero(&exdt, sizeof(t_executor));
	while (command)
	{
		exdt.num_of_cmd += 1;
		if (command->connection_type == PIPE)
		{
			pipe(pipe_end);
			command->fd_write = pipe_end[WR];
			command->fd_aux = pipe_end[RD];
			command->next->fd_read = pipe_end[RD];
		}
		manage_files(command);
		exdt.pid = fork();
		if (exdt.pid == -1)
			return (-1);
		if (!exdt.pid)
			execute_command(command, data);
		exdt.pids = add_integer(exdt.pids, exdt.num_of_cmd, exdt.pid);
		if (!exdt.pids)
			return (-1);
		close(command->fd_read);
		close(command->fd_write);
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
