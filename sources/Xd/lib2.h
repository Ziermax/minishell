/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:15:32 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/11 17:28:48 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB2_H
# define LIB2_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	char		**env;
	char		**exp;
	int			flag;
}				t_data;

#endif
