/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:18:22 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/01 14:19:25 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static int	print_echo2(char **s, int newline)
{
	while (*s)
	{
		if (printf("%s", *s) == -1)
			return (1);
		s++;
		if (*s)
			if (printf(" ") == -1)
				return (1);
	}
	if (newline)
		if (printf("\n") == -1)
			return (1);
	return (0);
}

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
	return (print_echo2(s, newline));
}
