/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:06:33 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/21 17:40:54 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	read_shell(t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (line)
		{
			if (check_line(line))
				printf("Error\n");
			if (line)
				add_history(line);
			parse(line);
		}
		else
			return ;
		if (line)
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
	read_shell(&data);
	ft_free(&data.env);
	ft_free(&data.exp);
	return (0);
}
