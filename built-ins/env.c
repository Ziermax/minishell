/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:28:25 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/13 16:45:24 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built.h"
#include "../Libft/includes/libft.h"

int	ft_env(char **argv, t_data *data)
{
	argv++;
	if (*argv)
	{
		if (*argv[0] == '-')
		{
			if (argv[0][1] == '-')
				fd_printf(2, "env: unrecognized option '%s'\n", *argv);
			else
				fd_printf(2, "env: invalid option -- '%c'\n", argv[0][1]);
			fd_printf(2, "minishell: env is not accepting options today\n");
			return (125);
		}
		fd_printf(2, "env: ‘%s’: No such file or directory\n", *argv);
		return (127);
	}
	print_split(data->envp);
	return (0);
}
