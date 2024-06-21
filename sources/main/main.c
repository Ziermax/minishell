/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:06:33 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/21 14:52:44 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	read_shell(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (line)
		{
			line = check_line(line);
			if (!line)
				break ;
			if (ft_strcmp("exit", line) == 0)
			{
				free(line);
				break ;
			}
			add_history(line);
		}
		else
			return ;
		free(line);
	}
}

static void handle_sigint(int sig)
{
    if (sig == SIGINT)
    {
        printf("\n");
        rl_replace_line("", 0);
		rl_on_new_line();
        rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	argc = 0;
	argv = 0;
	if (init_data(&data, envp) == -1)
		return (1);
	read_shell();
	ft_free(&data.env);
	ft_free(&data.exp);
	return (0);
}
