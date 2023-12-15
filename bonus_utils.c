/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:14:24 by mahmoud           #+#    #+#             */
/*   Updated: 2023/12/15 16:25:53 by mahmoud          ###   ########.fr       */
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
			free_arr(command), close(fd[1]), exit(1));
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