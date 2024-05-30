/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vilbasura.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:48:29 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/30 16:57:40 by adrmarqu         ###   ########.fr       */
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

int		print_pwd(void);
int		print_env(char **envp);
int		print_echo(char **s);
int		ft_cd(char *path);
int		ft_export(char **s, char **envp);
int		ft_unset(char **s, char **envp);
int		ft_exit(void);

char	*get_pwd(void);

#endif
