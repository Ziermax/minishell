/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:51:28 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/02 13:33:09 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built_utils.h"

int	print_export(char **exp)
{
	int		i;
	char	*arr;
	char	*quot;

	sort(exp);
	i = 0;
	while (exp[i])
	{
		arr = get_value(exp[i]);
		if (arr && arr[0] == '(')
			fd_printf(1, "declare -ax %s\n", exp[i]);
		else
		{
			quot = put_quots(exp[i]);
			if (!quot)
				return (1);
			fd_printf(1, "declare -x %s\n", quot);
			free(quot);
		}
		free(arr);
		i++;
	}
	return (0);
}
