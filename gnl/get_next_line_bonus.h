/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 19:07:17 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/17 14:40:01 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

int		get_next_line(int fd, char **line);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		get_next_line(int fd, char **line);
int		ft_aux(ssize_t nbytes, char **x, char **line);
int		ft_nbytesnegativo(ssize_t *nbytes, char **x);
int		ft_negative(char **x, char **line);
char	*ft_strchr(const char *s, int c);

#endif
