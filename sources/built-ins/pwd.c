/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:21:28 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/28 14:44:20 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*get_pwd(void)
{
	return (getcwd(NULL, 0));
}

int	print_pwd()
{
	char	*pwd;

	pwd = get_pwd();
	if (!pwd)
	{
		perror("Error");
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
