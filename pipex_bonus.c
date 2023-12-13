/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:19:38 by mabdelsa          #+#    #+#             */
/*   Updated: 2023/12/13 17:14:11 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	locate_and_execute_command_c(char *av, char **envp, int *fd)
{
	char	**command;
	char	*full_command_path;

	close(fd[0]);
	command = extract_command(av);
	full_command_path = locate_command_path(command[0], envp);
	if (full_command_path == NULL)
		return (ft_putstr_fd("Error: Command not found\n", 2),
			free_arr(command), exit(1));
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (ft_putstr_fd("Error: Bad file descriptor\n", 2), exit(1));
	close(fd[1]);
	if (execve(full_command_path, command, envp) == -1)
		return (ft_putstr_fd("Error: Command not found\n", 2), exit(1));
}

void	locate_and_execute_command_p(char *av, char **envp)
{
	char	**command;
	char	*full_command_path;

	command = extract_command(av);
	full_command_path = locate_command_path(command[0], envp);
	if (full_command_path == NULL)
		return (ft_putstr_fd("Error: Command not found\n", 2),
			free_arr(command), exit(1));
	if (execve(full_command_path, command, envp) == -1)
		return (ft_putstr_fd("Error: Command not found\n", 2), exit(1));
}

void	create_child_processes(char *av, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (ft_putstr_fd("Error: Broken Pipe\n", 2));
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Error: fork: resource temporarily unavailable\n",
			2));
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

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	file_in;
	int file_out;

	if (ac < 5)
		return (ft_putstr_fd("Error: Invalid input format\n", 2), 1);
	file_in = open(av[1], O_RDONLY, 0777);
	if (file_in == -1)
		return (ft_putstr_fd("Error: No such file or directory\n", 2), 1);
	file_out = open(av[ac - 1],  O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (file_out == -1)
		return (ft_putstr_fd("Error: No such file or directory\n", 2), 1);
	if (dup2(file_in, STDIN_FILENO) == -1)
		return (ft_putstr_fd("Error: Bad file descriptor\n", 2), 1);
	i = 2;
	while (i < ac - 2)
	{
		create_child_processes(av[i], envp);
		i++;
	}
	dup2(file_out, STDOUT_FILENO);
	locate_and_execute_command_p(av[ac - 2], envp);
	return (0);
}
