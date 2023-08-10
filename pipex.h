/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:34:29 by jrosmari          #+#    #+#             */
/*   Updated: 2023/08/03 16:35:16 by jrosmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 21:48:41 by jrosmari          #+#    #+#             */
/*   Updated: 2023/02/25 21:30:52 by jrosmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

typedef struct s_Pip_str{
	char	*infile;
	char	*outfile;
	char	*left_path;
	char	*right_path;
	char	**left_args;
	char	**right_args;
}t_Pip_str;
char		*getpath_help(char *envp[]);
void		clean_arr(char **arr);
char		*getpath(char *func, char *envp[]);
void		clean(t_Pip_str pip);
t_Pip_str	init(char *argv[], char *envp[]);
#endif
