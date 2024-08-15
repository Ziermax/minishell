/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:23:34 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/15 13:11:45 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "../includes/minishell.h"

static void	ft_error(const char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

static void	check_user(int *tube)
{
	char	*args[2];

	args[0] = ft_strdup("/usr/bin/whoami");
	args[1] = NULL;
	close(tube[0]);
	dup2(tube[1], STDOUT_FILENO);
	execve(args[0], args, NULL);
	ft_error("execve");
}

static char	*get_user(int *tube)
{
	char	buffer[256];
	ssize_t	count;

	close(tube[1]);
	count = read(tube[0], buffer, sizeof(buffer) - 1);
	if (count == -1)
		ft_error("read");
	buffer[count--] = '\0';
	if (buffer[count] == '\n')
		buffer[count] = '\0';
	wait(NULL);
	close(tube[0]);
	return (ft_strdup(buffer));
}

char	*search_for_my_home(void)
{
	int		tube[2];
	pid_t	pid;
	char	*user;
	char	*home;

	if (pipe(tube) == -1)
		ft_error("pipe");
	pid = fork();
	if (pid == -1)
		ft_error("fork");
	if (pid == 0)
		check_user(tube);
	user = get_user(tube);
	if (!user)
		return (NULL);
	home = ft_strjoin("/home/", user);
	free(user);
	return (home);
}
