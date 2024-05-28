/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:18:22 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/28 14:19:25 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	print_echo(char **s)
{
	int	newline;
	int	i;

	newline = 1;
	while ((*s)[0] == '-')
	{
		i = 1;
		while ((*s)[i] == 'n')
			i++;
		if ((*s)[i])
			break ;
		newline = 0;
		s++;
	}
	while (*s)
	{
		printf("%s", *s);
		s++;
		if (*s)
			printf(" ");
	}
	if (newline)
		printf("\n");
	return (0);
}
