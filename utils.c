/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:49:47 by mahmoud           #+#    #+#             */
/*   Updated: 2023/12/06 21:01:05 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_msg(void)
{
	perror("Error");
	exit(1);
}

void	free_arr(char **arr)
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

char	*filter_envp(char **envp)
{
	while (*envp++ != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp += 5);
	}
	return (NULL);
}

char **extract_command(char *av)
{
	char **command;
	
	command = ft_split(av, ' ');
	return (command);
}

char	*locate_command_path(char *command, char **envp)
{
	int		i;
	char	*path_check;
	char	**filtered_path;
	char	*command_path;

	i = 0;
	path_check = NULL;
	filtered_path = ft_split(filter_envp(envp), ':');
	while (filtered_path[i] != NULL)
	{
		command_path = ft_strjoin("/", command);
		path_check = ft_strjoin(filtered_path[i], command_path);
		free(command_path);
		if (access(path_check, F_OK) == 0)
			return (path_check);
		free(path_check);
		i++;
	}
	free_arr(filtered_path);
	return (NULL);
}
