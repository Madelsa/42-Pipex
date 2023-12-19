/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:19:38 by mabdelsa          #+#    #+#             */
/*   Updated: 2023/12/17 07:34:33 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	create_final_child_process(char *av, char **envp)
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

	pipe_and_fork(&pid, fd);
	if (pid == 0)
		locate_and_execute_command_c(av, envp, fd);
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (ft_putstr_fd("Error: Bad file descriptor\n", 2),
				close(fd[0]), exit(1));
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	here_doc(int ac, char **av, int *flag, int *i)
{
	pid_t	pid;
	int		fd[2];
	int		file_out;

	if (ac != 6)
		return (ft_putstr_fd("Error: Invalid input format\n", 2));
	*flag = 1;
	*i = 3;
	file_out = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (file_out == -1)
		return (ft_putstr_fd("Error: No such file or directory\n", 2),
			exit(1));
	if (dup2(file_out, STDOUT_FILENO) == -1)
		return (ft_putstr_fd("Error: Bad file descriptor\n", 2)
			, close(file_out), exit(1));
	close(file_out);
	pipe_and_fork(&pid, fd);
	if (pid == 0)
		here_doc_bash_read(fd, av[2]);
	else
		here_doc_close_wait(&pid, fd);
}

void	multi_pipe(char **av, int *flag, int *i)
{
	int	file_in;

	*flag = 0;
	*i = 2;
	file_in = open(av[1], O_RDONLY, 0777);
	if (file_in == -1)
		return (ft_putstr_fd("Error: No such file or directory\n", 2), exit(1));
	if (dup2(file_in, STDIN_FILENO) == -1)
		return (ft_putstr_fd("Error: Bad file descriptor\n", 2)
			, close(file_in), exit(1));
	close(file_in);
}

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	flag;
	int	file_out;

	if (ac < 5)
		return (ft_putstr_fd("Error: Invalid input format\n", 2), 1);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		here_doc(ac, av, &flag, &i);
	else
		multi_pipe(av, &flag, &i);
	while (i < ac - 2)
		create_child_processes(av[i++], envp);
	if (flag == 0)
	{
		file_out = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (file_out == -1)
			return (ft_putstr_fd("Error: No such file or directory\n", 2), 1);
		if (dup2(file_out, STDOUT_FILENO) == -1)
			return (ft_putstr_fd("Error: Bad file descriptor\n", 2)
				, close(file_out), 1);
		close(file_out);
	}
	create_final_child_process(av[ac - 2], envp);
	return (0);
}
