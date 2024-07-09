/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:50:23 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/09 11:36:57 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built.h"

int	ft_env(char **argv, t_data *data)
{
	argv++;
	if (argv)
	{
		fd_printf(2, "minishell: env: We are not accepting arguments today\n");
		return (1);
	}
	print_split(data->env);
	return (0);
}
