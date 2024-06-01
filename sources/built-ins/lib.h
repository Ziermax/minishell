/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vilbasura.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:48:29 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/01 15:08:21 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <sys/errno.h>
# include "../../Libft/includes/libft.h"

# define MAX_PATH 1024

# define RESET		"\x1b[0m"
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define WHITE		"\033[0;97m"
# define GRAY		"\033[0;90m"

typedef struct	s_data
{
	char	**envp;
	char	**exp;
}				t_data;

int		print_pwd(void);
int		print_char(char **s);
int		print_echo(char **s);
int		ft_cd(char *path);
int		ft_export(char **s, char **envp);
int		ft_unset(char **s, char **envp);
int		ft_exit(void);

char	*get_pwd(void);

char	**split(char *str, char c);

int		ft_export2(char **s, t_data *data);

void	put_quotts(char *s);
void	sort(char **s);
char	**get_dup(char **envp);
void	ft_freeze(char **s);

#endif
