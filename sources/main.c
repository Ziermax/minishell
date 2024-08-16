/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:06:33 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/16 12:07:52 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/built.h"
#include "../includes/signals.h"
#include "../Libft/includes/libft.h"

int	g_exit_status = 0;

static char	*get_prompt(t_data *data)
{
	char	*prompt;

	prompt = ft_strrchr(data->pwd, '/');
	if (!prompt)
		return (ft_strdup(PROMTP));
	if (!data->exit_status)
		data->arrow_color = BIGREEN;
	else
		data->arrow_color = BIRED;
	if (data->pwd == prompt)
		prompt = ft_multiplejoin(4, data->arrow_color, "➜  \033[1;36m",
				data->pwd, "\033[1;33m > \033[0;39m");
	else
		prompt = ft_multiplejoin(4, data->arrow_color, "➜  \033[1;36m",
				prompt + 1, "\033[1;33m > \033[0;39m");
	return (prompt);
}

static void	read_shell(t_data *data)
{
	char	*line;

	while (!data->end)
	{
		data->prompt = get_prompt(data);
		if (!data->prompt)
			break ;
		line = readline(data->prompt);
		free(data->prompt);
		if (g_exit_status == 130)
		{
			data->exit_status = g_exit_status;
			g_exit_status = 0;
		}
		if (!line)
			ft_exit(NULL, data);
		else if (!check_line(line))
			minishell(line, data);
		if (line && line[0])
			add_history(line);
		free(line);
	}
}

static void	free_data(t_data *data)
{
	if (data->envp)
		free_split(data->envp);
	if (data->exp)
		free_split(data->exp);
	if (data->pwd)
		free(data->pwd);
	if (data->home)
		free(data->home);
	if (data->heredoc)
		free(data->heredoc);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	argc = argc;
	argv = argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, normal_sig);
	if (init_data(&data, envp))
		return (1);
	data.exit_status = 0;
	read_shell(&data);
	free_data(&data);
	return (data.exit_status);
}
