/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:01:12 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/05/26 20:02:41 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define STR_START 1
# define STR_ANY 2
# define STR_END 4

int		ft_strlen(char *str);
int		ft_strcmp(char *str1, char *str2);
char	*search_word_relative(char *word, char *str, int flag);
char	*search_word_in_str(char *word, char *str);
char	*search_word_in_split(char *word, char **split);
void	*ft_calloc(int count, int size);
char	*ft_strdup(char *str);
void	free_split(char **split);
void	free_split_save(char **split, char *save);
char	*ft_strjoin(char *str1, char *str2);
char	*ft_threejoin(char *str1, char *str2, char *str3);
char	**ft_split_char(char *str, char c);
char	**ft_split(char *str);
int		fd_printf(int fd, char *str, ...);
void	error_printf(int error, char *str, ...);
char	*get_next_line(int fd);
/*	is_identifiers	*/
int		ft_isdigit(int c);
int		ft_isupper(int c);
int		ft_islower(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isspace(int c);
int		ft_isprint(int c);
int		ft_isacsii(int c);

#endif
