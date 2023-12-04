/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:48:57 by mahmoud           #+#    #+#             */
/*   Updated: 2023/12/04 21:49:45 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *locate_command_path(char **av, char **envp)
{
    int i;
    char *path_check;
    char **filtered_path;
    char *command_path;
    
    i = 0;
    path_check = NULL;
    while (*envp++ != NULL) 
    {
            if (ft_strncmp(*envp, "PATH=", 5) == 0) 
            {
                *envp += 5;
                break;
            }
    }
    filtered_path = ft_split(*envp, ':');
    while (filtered_path[i] != NULL)
    {
        command_path = ft_strjoin("/", av[1]);
        path_check = ft_strjoin(filtered_path[i], command_path);
        free(command_path);
        if (access(path_check, F_OK) == 0)
           return(path_check);
        i++;
    }
    return (NULL);
}

int main(int ac, char **av, char **envp)
{
    pid_t pid;
    char *command_path;

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
