/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:02:47 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/15 20:06:51 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/structs.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../includes/signals.h"
#include <signal.h>

t_cmd	*add_command(t_cmd **cmd_lst)
{
	t_cmd	*command;

	command = ft_calloc(sizeof(t_cmd), 1);
	if (!command)
		return (NULL);
	lst_add_back(cmd_lst, command);
	command->fd_write = -1;
	command->fd_read = -1;
	command->fd_aux = -1;
	return (command);
}

static void	write_heredoc(char *lim, int fd)
{
	char	*limiter;
	char	*line;
	int		len;

	limiter = ft_strjoin(lim, "\n");
	if (!limiter)
		return ;
	signal(SIGINT, SIG_DFL);
	len = ft_strlen(limiter);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			fd_printf(2, "\n"PRMTERR"warning: here-document at last line"
				" by end-of-file (wanted '%s')\n", lim);
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, len + 1))
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(limiter);
	free(line);
}

static char	*read_heredoc(int fd)
{
	char	*line;
	char	*text;
	char	*tmp;

	text = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_strjoin(text, line);
		free(text);
		free(line);
		if (!tmp)
			return (NULL);
		text = tmp;
	}
	if (!text)
		return (ft_calloc(sizeof(char), 1));
	return (text);
}

char	*heredoc(char *word)
{
	char	*heretext;
	int		fd_pipe[2];
	int		pid;

	pipe(fd_pipe);
	signal(SIGINT, doc_sig);
	pid = fork();
	if (pid == 0)
	{
		write_heredoc(word, fd_pipe[WR]);
		close(fd_pipe[WR]);
		close(fd_pipe[RD]);
		exit(0);
	}
	close(fd_pipe[WR]);
	wait(NULL);
	heretext = read_heredoc(fd_pipe[RD]);
	close(fd_pipe[RD]);
	return (heretext);
}

void	*heredoc_string(char *before, char *now, char *limiter)
{
	char	*new_heredoc;

	before = ft_strjoin(before, now);
	if (!before)
		return (NULL);
	limiter = ft_strjoin(limiter, "\n");
	if (!limiter)
		return (free(before), NULL);
	new_heredoc = ft_strjoin(before, limiter);
	free(limiter);
	free(before);
	return (new_heredoc);
}
