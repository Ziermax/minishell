/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:01:12 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/10 19:55:01 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>

# define STR_START 1
# define STR_ANY 2
# define STR_END 4

/*	string functions	*/
int		ft_strncmp(char *str1, char *str2, int bytes);
int		ft_strlcat(char *dst, char *src, int dstsize);
int		ft_strfcat(char *dst, char *src, int dstsize, int from);
void	print_split(char **split);
void	ft_memset(void *dir, int c, size_t bytes);
void	ft_bzero(void *dir, size_t bytes);
void	swap_strings(char **str_p, char *str);
/*	length	functions	*/
int		ft_intlen(int nbr);
int		ft_splitlen(char **split);
int		ft_strlen(char *str);
int		ft_arraylen(void *array);
/*	mallocers functions	*/
void	*ft_calloc(int count, int size);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *str1, char *str2);
char	*ft_threejoin(char *str1, char *str2, char *str3);
char	*ft_splitjoin(char **split);
/*	array functions		*/
void	*add_dir(void *array, void *dir);
int		*add_integer(int *array, int len, int to_add);
void	*add_array_to_array(void *array, void *to_add, void *position);
void	*remove_dir(void *array, void *to_remove);
/*	search functions	*/
char	*ft_strchr(char *str, int c);
char	*search_word_relative(char *word, char *str, int flag, int bytes);
char	*search_word_in_str(char *word, char *str);
char	*search_word_in_split(char *word, char **split, int bytes);
/*	is_identifiers functions	*/
int		ft_isdigit(int c);
int		ft_isupper(int c);
int		ft_islower(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isspace(int c);
int		ft_isprint(int c);
int		ft_isacsii(int c);
/*	split functions	*/
void	free_split(char **split);
void	free_split_save(char **split, char *save);
char	*no_skip(char *str);
char	*skip_spaces(char *str);
char	*next_string(char *str);
char	*next_word(char *str);
char	**ultra_split(char *str, char *(*skip)(char *), char *(*next)(char *));
char	**ft_split(char *str);
char	**ft_split_char(char *str, char *separator);
/*	list functions	*/
void	lst_add_back(void *list, void *node);
void	lst_add_front(void *list, void *node);
void	lst_clear(void *list, void (*del)(void *));
void	lst_for_each(void *list, void (*func)(void *));
/*	extra functions	*/
int		fd_printf(int fd, const char *str, ...);
void	error_printf(int error, char *str, ...);
char	*get_next_line(int fd);
void	dont(char null, ...);

#endif
