/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:06:33 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/09/28 13:59:40 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/built.h"
#include "../includes/signals.h"
#include "../Libft/includes/libft.h"
#include <sys/types.h>
#include <sys/wait.h>

int	g_exit_status = 0;

static char	*get_prompt(t_data *data)
{
	char	*prompt;

	if (!data->exit_status)
		data->arrow_color = BIGREEN;
	else
		data->arrow_color = BIRED;
	prompt = ft_strrchr(data->pwd, '/');
	if (!prompt)
		return (ft_strjoin(data->arrow_color,
				"➜  \033[1;36m???\033[1;33m > \033[0;39m"));
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
		signal(SIGINT, normal_sig);
		signal(SIGQUIT, SIG_IGN);
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
		else if (!check_line(line, data))
			minishell(line, data);
		if (line && line[0])
			add_history(line);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	if (argc != 1)
		return (fd_printf(2, PRMTERR"No arguments required\n"), 0);
	argv = argv;
	if (init_data(&data, envp))
		return (1);
	data.exit_status = 0;
	read_shell(&data);
	del_data(&data);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	return (data.exit_status);
}
