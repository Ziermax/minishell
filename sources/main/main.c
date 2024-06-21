/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:06:33 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/21 13:28:44 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;

	argc = 0;
	argv = 0;
	if (init_data(&data, envp) == -1)
		return (1);
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
		free(line);
	}
	ft_free(&data.env);
	ft_free(&data.exp);
	return (0);
}
