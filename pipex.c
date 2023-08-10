/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:00:59 by jrosmari          #+#    #+#             */
/*   Updated: 2023/07/30 18:37:37 by jrosmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(t_Pip_str pip)
{
	int	fd;

	fd = open(pip.infile, O_RDWR, S_IRUSR | S_IWUSR);
	return (fd);
}

int	open_outfile(t_Pip_str pip)
{
	int	fd;

	fd = open(pip.outfile, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	return (fd);
}

void	pipex(int fd[], t_Pip_str pip, char *envp[])
{
	int		fd_pipe[2];
	int		pid;

	if (pipe(fd_pipe) == -1)
		perror("pipe error");
	pid = fork();
	if (pid < 0)
		perror("fork error");
	if (pid == 0)
	{
		dup2(fd[1], STDIN_FILENO);
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[0]);
		close(fd[1]);
		execve(pip.left_path, pip.left_args, envp);
	}
	else
	{
		waitpid(pid, NULL, 0);
		dup2(fd[2], STDOUT_FILENO);
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[1]);
		close(fd[2]);
		execve(pip.right_path, pip.right_args, envp);
	}
}

int	maintoolong(t_Pip_str pip, int fd)
{
	if (pip.left_path[0] == 'z' && pip.left_path[1] == 's')
	{
		ft_printf("%s\n", pip.left_path);
		if (pip.right_path[0] == 'z' && pip.right_path[1] == 's')
			ft_printf("%s\n", pip.right_path);
		clean(pip);
		return (-1);
	}
	if (pip.right_path[0] == 'z' && pip.right_path[1] == 's')
	{
		ft_printf("%s\n", pip.right_path);
		clean(pip);
		return (-1);
	}
	if (fd == -1)
	{
		ft_printf("Error opening outfile: %s\n", pip.outfile);
		clean(pip);
		return (-1);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_Pip_str	pip;
	int			fd[3];

	if (argc != 5)
	{
		ft_printf("Wrong amount of arguments\n");
		return (-1);
	}
	pip = init(argv, envp);
	fd[1] = open_infile(pip);
	if (fd[1] == -1)
	{
		ft_printf("zsh: No such file or directory: %s\n", pip.infile);
		if (pip.right_path[0] == 'z' && pip.right_path[1] == 's')
			ft_printf("%s\n", pip.right_path);
		clean(pip);
		return (-1);
	}
	fd[2] = open_outfile(pip);
	if (maintoolong(pip, fd[2]) == -1)
		return (-1);
	pipex(fd, pip, envp);
	clean(pip);
	return (0);
}
