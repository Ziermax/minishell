/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:06:33 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/12 16:30:21 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/built.h"
#include "../includes/signals.h"

int	g_exit_status = 0;

static void	manage_heredoc(t_data *data, char *line)
{
	char	*newline;

	if (g_exit_status == 130)
	{
		add_history(line);
		free(data->heredoc);
		data->heredoc = NULL;
		return ;
	}
	newline = ft_threejoin(line, "\n", data->heredoc);
	free(data->heredoc);
	if (!newline)
	{
		data->end = 1;
		return ;
	}
	add_history(newline);
	free(newline);
	data->heredoc = NULL;
}

static void	read_shell(t_data *data)
{
	char	*line;

	while (!data->end)
	{
		line = readline("minishell> ");
		if (g_exit_status == 130)
		{
			data->exit_status = g_exit_status;
			g_exit_status = 0;
		}
		if (line)
		{
			if (!check_line(line))
			{
				minishell(line, data);
				if (data->heredoc)
					manage_heredoc(data, line);
				else if (line && line[0])
					add_history(line);
			}
			free(line);
		}
		else
			ft_exit(NULL, data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	argc = argc;
	argv = argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, normal_sig);
	if (init_data(&data, envp) == -1)
		return (1);
	read_shell(&data);
	free_split(data.envp);
	free_split(data.exp);
	free(data.pwd);
	free(data.home);
	free(data.heredoc);
	return (data.exit_status);
}
