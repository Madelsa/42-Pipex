/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:14:24 by mahmoud           #+#    #+#             */
/*   Updated: 2023/12/17 06:46:57 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	here_doc_close_wait(pid_t *pid, int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(*pid, NULL, 0);
}

pid_t	pipe_and_fork(pid_t *pid, int *fd)
{
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Error: Broken Pipe\n", 2);
		exit(1);
	}
	*pid = fork();
	if (*pid == -1)
	{
		ft_putstr_fd("Error: resource temporarily unavailable\n", 2);
		close(fd[0]);
		close(fd[1]);
		exit(1);
	}
	return (*pid);
}

void	here_doc_bash_read(int *fd, char *av)
{
	char	*line;

	close(fd[0]);
	line = get_next_line(0);
	while (line != NULL)
	{
		if (ft_strncmp(line, av, ft_strlen(av)) == 0)
			return (free(line), close(fd[1]), exit(0));
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	close(fd[1]);
}

void	locate_and_execute_command_c(char *av, char **envp, int *fd)
{
	char	**command;
	char	*full_command_path;

	close(fd[0]);
	command = extract_command(av);
	full_command_path = locate_command_path(command[0], envp);
	if (full_command_path == NULL)
		return (ft_putstr_fd("Error: Command not found\n", 2),
			free_arr(command), close(fd[1]), exit(1));
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (ft_putstr_fd("Error: Bad file descriptor\n", 2),
			close(fd[1]), exit(1));
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
