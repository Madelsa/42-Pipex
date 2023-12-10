/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:48:57 by mahmoud           #+#    #+#             */
/*   Updated: 2023/12/10 16:28:11 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void child_process(char **av, char **envp, int *fd)
{
	char	*full_command_path;
	char	**command;
	int 	file_in;
	
	file_in = open(av[1], O_RDONLY, 0777);
	if (file_in == -1)
		return (ft_putstr_fd("Error: No such file or directory\n", 2));
	close(fd[0]);
	command = extract_command(av[2]);
	full_command_path = locate_command_path(command[0], envp);
	if (full_command_path == NULL)
		return (ft_putstr_fd("Error: Command not found\n", 2), free_arr(command));
	if (dup2(file_in, STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
		return (ft_putstr_fd("Error: Bad file descriptor\n", 2));
	if (execve(full_command_path, command, envp) == -1)
		return (ft_putstr_fd("Error: Command not found\n", 2));
}


void parent_process(pid_t pid, char **av, char **envp, int *fd)
{	
	char *full_command_path;
	char **command;
	int file_out;
	
	waitpid(pid, NULL, 0);
	file_out = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (file_out == -1)
		return (ft_putstr_fd("Error: No such file or directory\n", 2));
	close(fd[1]);
	command = extract_command(av[3]);
	full_command_path = locate_command_path(command[0], envp);
	if (full_command_path == NULL)
		return (ft_putstr_fd("Error: Command not found\n", 2), free_arr(command));
	if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(file_out, STDOUT_FILENO) == -1)
		return (ft_putstr_fd("Error: Bad file descriptor\n", 2));
	if (execve(full_command_path, command, envp) == -1)
		return (ft_putstr_fd("Error: Command not found\n", 2));
}


int	main(int ac, char **av, char **envp)
{
	pid_t	pid;
	int		fd[2];
	if (ac != 5)
		return (ft_putstr_fd("Error: Invalid input format\n", 2), 1);
	if (pipe(fd) == -1)
		return (ft_putstr_fd("Error: Broken Pipe\n", 2), 1);
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Error: fork: resource temporarily unavailable\n", 2), 1);
	else if (pid == 0)
		child_process(av, envp, fd);
	else
		parent_process(pid, av, envp, fd);
	return (0);
}
