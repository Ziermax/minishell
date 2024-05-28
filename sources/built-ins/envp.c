/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:56:10 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/28 14:17:24 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	print_env(char **envp)
{
	int	error;

	while (*envp)
	{
		error = printf("%s\n", *envp);
		if (error == -1)
			return (1);
		envp++;
	}
	return (0);
}
