/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:51:28 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/15 11:41:27 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built_utils.h"

int	print_export(char **exp)
{
	int		i;
	char	*quot;

	sort(exp);
	i = 0;
	while (exp[i])
	{
		quot = put_quots(exp[i]);
		if (!quot)
			return (1);
		fd_printf(1, "declare -x %s\n", quot);
		free(quot);
		i++;
	}
	return (0);
}
