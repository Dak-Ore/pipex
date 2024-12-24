/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:38:14 by rsebasti          #+#    #+#             */
/*   Updated: 2024/12/19 12:38:20 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

char	**killsplit(char **tab);
char	**ft_split(char const *s, char c);
char	*ft_strdoublejoin(char const *s1, char const *s2, char const *s3);
char	*search_path(char **env, char *cmd, char *ogcmd);
char	*ft_strchr(const char *s, int c);

#endif