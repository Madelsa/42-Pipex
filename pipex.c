/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:48:57 by mahmoud           #+#    #+#             */
/*   Updated: 2023/12/06 20:42:51 by mahmoud          ###   ########.fr       */
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
		error_msg();
	close(fd[0]);
	command = extract_command(av[2]);
	full_command_path = locate_command_path(command[0], envp);
	if (full_command_path == NULL)
	{
		free_arr(command);
		error_msg();
	}
	dup2(file_in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	if (execve(full_command_path, command, envp) == -1)
		error_msg();
}


void parent_process(pid_t pid, char **av, char **envp, int *fd)
{	
	char *full_command_path;
	char **command;
	int file_out;
	
	waitpid(pid, NULL, 0);
	file_out = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (file_out == -1)
		error_msg();
	close(fd[1]);
	command = extract_command(av[3]);
	full_command_path = locate_command_path(command[0], envp);
	if (full_command_path == NULL)
	{
		free_arr(command);
		error_msg();
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(file_out, STDOUT_FILENO);
	if (execve(full_command_path, command, envp) == -1)
		error_msg();
}


int	main(int ac, char **av, char **envp)
{
	pid_t	pid;
	int		fd[2];
	if (ac != 5)
		return (ft_putstr_fd("Error: Invalid input format", 2), 1);
	if (pipe(fd) == -1)
		error_msg();
	pid = fork();
	if (pid == -1)
		error_msg();
	else if (pid == 0)
		child_process(av, envp, fd);
	else
		parent_process(pid, av, envp, fd);
	return (0);
}
