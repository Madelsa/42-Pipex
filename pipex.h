/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:45:53 by mahmoud           #+#    #+#             */
/*   Updated: 2023/12/14 17:15:57 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include "./sys/wait.h"

void	free_arr(char **arr);
char	*filter_envp(char **envp);
char	*locate_command_path(char *command, char **envp);
char	**extract_command(char *av);
void	locate_and_execute_command_c(char *av, char **envp, int *fd);
void	locate_and_execute_command_p(char *av, char **envp);

#endif