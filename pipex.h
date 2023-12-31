/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:45:53 by mahmoud           #+#    #+#             */
/*   Updated: 2023/12/17 06:44:17 by mabdelsa         ###   ########.fr       */
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
pid_t	pipe_and_fork(pid_t *pid, int *fd);
void	here_doc_bash_read(int *fd, char *av);
void	here_doc_close_wait(int *fd, pid_t *pid);

#endif