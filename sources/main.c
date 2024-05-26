/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:06:33 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/05/26 17:52:18 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	argc = 0;
	argv = 0;
	envp = 0;

	while (1)
	{
		fd_printf(1, "-> minishell ");
		line = get_next_line(0);
		if (!line)
		{
			write(1, "\n", 1);
			continue ;
		}
		minisheller(line);
		free(line);
	}
	return (0);
}
