/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:06:33 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/09 18:34:39 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	manage_heredoc(t_data *data, char *line)
{
	char	*newline;

	newline = ft_threejoin(line, "\n", data->heredoc);
	free(data->heredoc);
	if (!newline)
	{
		data->end = 1;
		return ;
	}
	add_history(newline);
	free(newline);
}

static void	read_shell(t_data *data)
{
	char	*line;

	while (!data->end)
	{
		line = readline("minishell> ");
		if (line)
		{
			if (check_line(line))
				fd_printf(2, "Error: input not close\n");
			minishell(line, data);
			if (data->heredoc)
				manage_heredoc(data, line);
			else if (line)
				add_history(line);
		}
		else
			return ;
		free(line);
	}
}

static void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		fd_printf(1, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	argc = argc;
	argv = argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	if (init_data(&data, envp) == -1)
		return (1);
	read_shell(&data);
	free_split(data.envp);
	free_split(data.exp);
	return (0);
}
