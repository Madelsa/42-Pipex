/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:19:38 by mabdelsa          #+#    #+#             */
/*   Updated: 2023/12/15 17:24:32 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void create_final_child_process(char *av, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Error: resource temporarily unavailable\n", 2));
	else if (pid == 0)
        locate_and_execute_command_p(av, envp);
	else
		waitpid(pid, NULL, 0);
}

void	create_child_processes(char *av, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (ft_putstr_fd("Error: Broken Pipe\n", 2));
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Error: resource temporarily unavailable\n", 2));
	else if (pid == 0)
        locate_and_execute_command_c(av, envp, fd);
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (ft_putstr_fd("Error: Bad file descriptor\n", 2), exit(1));
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void here_doc(int ac, char **av)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	if (ac != 6)
		return (ft_putstr_fd("Error: Invalid input format\n", 2));
	if (pipe(fd) == -1)
		return (ft_putstr_fd("Error: Broken Pipe\n", 2));
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Error: resource temporarily unavailable\n", 2));
	if (pid == 0)
	{
		close(fd[0]);
		while ((line = get_next_line(0)) != NULL)
		{
			if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
				return(free(line), close(fd[1]), exit(0));
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);

	}
}

int	main(int ac, char **av, char **envp)
{
	int	i;
	int flag;
	int	file_in;
	int file_out;

	if (ac < 5)
		return (ft_putstr_fd("Error: Invalid input format\n", 2), 1);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		flag = 1;
		i = 3;
		file_out = open(av[ac - 1],  O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (file_out == -1)
			return (ft_putstr_fd("Error: No such file or directory\n", 2), 1);
		dup2(file_out, STDOUT_FILENO);
		close(file_out);
		here_doc(ac, av);
	}
	else
	{
		flag = 0;
		i = 2;
		file_in = open(av[1], O_RDONLY, 0777);
		if (file_in == -1)
			return (ft_putstr_fd("Error: No such file or directory\n", 2), 1);
		if (dup2(file_in, STDIN_FILENO) == -1)
			return (ft_putstr_fd("Error: Bad file descriptor\n", 2), 1);
		close(file_in);
	}
	while (i < ac - 2)
		create_child_processes(av[i++], envp);
	if (flag == 0)
	{
		file_out = open(av[ac - 1],  O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (file_out == -1)
			return (ft_putstr_fd("Error: No such file or directory\n", 2), 1);
		dup2(file_out, STDOUT_FILENO);
		close(file_out);
	}
	create_final_child_process(av[ac - 2], envp);
	return (0);
}
