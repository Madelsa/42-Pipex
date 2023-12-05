/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:48:57 by mahmoud           #+#    #+#             */
/*   Updated: 2023/12/05 18:05:28 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*filter_envp(char **envp)
{
	while (*envp++ != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			*envp += 5;
			break ;
		}
	}
	return (*envp);
}

char	*locate_command_path(char **av, char **envp)
{
	int		i;
	char	*path_check;
	char	**filtered_path;
	char	*command_path;
	char	*filtered_envp;

	filtered_envp = filter_envp(envp);
	i = 0;
	path_check = NULL;
	filtered_path = ft_split(filtered_envp, ':');
	while (filtered_path[i] != NULL)
	{
		command_path = ft_strjoin("/", av[1]);
		path_check = ft_strjoin(filtered_path[i], command_path);
		free(command_path);
		if (access(path_check, F_OK) == 0)
			return (path_check);
		i++;
	}
	return (NULL);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid;
	char	*command_path;

	(void)ac;
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("Error\n", 2);
	else if (pid == 0)
	{
		command_path = locate_command_path(av, envp);
		execve(command_path, &av[1], envp);
	}
	return (0);
}
