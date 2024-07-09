/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:28:25 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/09 16:47:23 by adrmarqu         ###   ########.fr       */
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
			fd_printf(2, "env: options are not avaliable");
		else
			fd_printf(2, "env: arguments are not avaliable");
		data->end = 0;
		return (1);
	}
	print_split(data->envp);
	return (0);
}
