/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:20:38 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/01 13:26:35 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static char	*ft_join(char *str1, char *str2)
{
	char	*join;
	int		len1;
	int		len2;
	int		i;

	if (!str1 && !str2)
		return (NULL);
	len1 = strlen(str1);
	len2 = strlen(str2);
	if (!len1 && !len2)
		return (calloc(sizeof(char), 1));
	join = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!join)
		return (NULL);
	i = -1;
	while (++i < len1)
		join[i] = str1[i];
	while (i < len1 + len2)
	{
		join[i] = str2[i - len1];
		i++;
	}
	join[i] = '\0';
	return (join);
}

int	ft_cd(char *path)
{
	char	*newpath;
	char	*slash;
	char	*pwd;

	if (path[0] == '/')
		chdir(path);
	else
	{
		pwd = get_pwd();
		slash = ft_join(pwd, "/");
		free(pwd);
		newpath = ft_join(slash, path);
		free(slash);
		chdir(newpath);
		free(newpath);
	}
	return (0);
}
