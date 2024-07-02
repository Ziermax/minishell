/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:21:35 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/24 14:41:26 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built.h"

int	print_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		fd_printf(1, "pwd: %s", strerror(errno));
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}