/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:49:47 by mahmoud           #+#    #+#             */
/*   Updated: 2023/12/13 13:09:47 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	**extract_command(char *av)
{
	char	**args;
	char	**command;
	char	*joined_args;
	int		i;

	joined_args = NULL;
	args = ft_split(av, ' ');
	i = 1;
	while (args[i] != NULL)
	{
		joined_args = ft_strjoin(joined_args, args[i]);
		if (args[i + 1] != NULL)
			joined_args = ft_strjoin(joined_args, " ");
		i++;
	}
	command = (char **)malloc(sizeof(char *) * 3);
	if (command == NULL)
		return (NULL);
	command[0] = ft_strdup(args[0]);
	command[1] = ft_strdup(joined_args);
	command[2] = NULL;
	free(joined_args);
	free_arr(args);
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
