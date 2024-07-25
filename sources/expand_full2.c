/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_full2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:16:29 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/25 18:18:56 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/expand.h"
#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	char	**expansion;
	t_data	data;

	if (argc != 2)
		return (0);
	data.exit = 2147483647;
	data.envp = envp;
	expansion = expand_full(argv[1], &data);
	if (!expansion)
		return (write(2, "Error\n", 6));
	print_split(expansion);
	free_split(expansion);
}
