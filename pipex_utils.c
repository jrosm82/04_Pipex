/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:58:13 by jrosmari          #+#    #+#             */
/*   Updated: 2023/08/10 19:58:27 by jrosmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*getpath_help(char *envp[])
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup("");
	while (envp[i] != NULL)
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && \
		envp[i][3] == 'H')
		{
			free(str);
			str = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 4);
		}
		i++;
	}
	return (str);
}

void	clean_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	clean(t_Pip_str pip)
{
	free(pip.infile);
	unlink(pip.outfile);
	free(pip.outfile);
	clean_arr(pip.left_args);
	clean_arr(pip.right_args);
	free(pip.left_path);
	free(pip.right_path);
}

char	*getpath(char *func, char *envp[])
{
	int		i;
	char	*str;
	char	*str2;
	char	**paths;

	i = 0;
	str = getpath_help(envp);
	paths = ft_split(str, ':');
	free(str);
	i = 0;
	while (paths[i] != NULL)
	{
		str2 = ft_strjoin(paths[i], "/");
		str = ft_strjoin(str2, func);
		free(str2);
		if (access(str, F_OK) == 0)
		{
			clean_arr(paths);
			return (str);
		}
		free(str);
		i++;
	}
	clean_arr(paths);
	return (ft_strjoin("zsh: command not found: ", func));
}

t_Pip_str	init(char *argv[], char *envp[])
{
	t_Pip_str	pips;

	pips.infile = ft_strdup(argv[1]);
	pips.outfile = ft_strdup(argv[4]);
	pips.left_args = ft_split(argv[2], ' ');
	pips.right_args = ft_split(argv[3], ' ');
	pips.left_path = getpath(pips.left_args[0], envp);
	pips.right_path = getpath(pips.right_args[0], envp);
	return (pips);
}
