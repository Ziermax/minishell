/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:41:21 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/02 15:24:06 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# define NUMBR "0123456789abcdef"

# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_flag
{
	int 	length;
	int		error;
	int		space;
	int		minus;
	int		alter;
	int		zero;
	int		width;
	int		aim;
	char	sign;
	char	type;
}	t_flag;

int	ft_printf(char const *s, ...);
int	ft_di(int n);
int	ft_u(unsigned int n);
int	ft_dir(unsigned long p);
int	ft_xx(unsigned int n, char x);

int	ft_putnbr(unsigned long n, unsigned long base, char x);
int	ft_putchar(char c);
int	ft_putstr(char *s);

t_flag	init_struct(void);
void	get_flags(char **s, t_flag *flag);

#endif