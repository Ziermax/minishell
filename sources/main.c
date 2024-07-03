/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:06:33 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/03 15:32:15 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	read_shell(t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (line)
		{
			if (check_line(line))
				fd_printf(2, "Error\n");
			if (line)
				add_history(line);
			minishell(line, data);
		}
		else
			return (0);
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
	ft_free(&data.env);
	ft_free(&data.exp);
	return (0);
}
