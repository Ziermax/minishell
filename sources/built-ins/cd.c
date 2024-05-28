/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:20:38 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/28 15:14:56 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	ft_cd(char *path)
{
	char	*newpath;
	char	*slash;
	char	*pwd;

	//if (!path)
	//	chdir(get_home());
	if (path[0] == '/')
		chdir(path);
	else
	{
		pwd = get_pwd();
		slash = ft_strjoin(pwd, "/");
		free(pwd);
		newpath = ft_strjoin(slash, path);
		free(slash);
		chdir(newpath);
		free(newpath);
	}
	return (0);
}
