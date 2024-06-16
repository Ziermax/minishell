/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:06:33 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/16 12:09:30 by adrmarqu         ###   ########.fr       */
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
		write(1, "-> minishell ", 13);
		line = get_next_line(0);
		if (!line)
		{
			write(1, "\n", 1);
			continue ;
		}
		printf("line: \"%s\"\n", line);
		if (search_word_relative("exit", line, STR_START))
		{
			free(line);
			break ;
		}
		free(line);
	}
	return (0);
}
