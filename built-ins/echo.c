/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:18:22 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/24 15:03:31 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built.h"

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
	if ((*s)[0] == '-' && (*s)[1] == 'n')
	{
		i = 1;
		while ((*s)[i] == 'n')
			i++;
		newline = 0;
		s++;
	}
	return (print_echo2(s, newline));
}
