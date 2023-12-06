/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:45:53 by mahmoud           #+#    #+#             */
/*   Updated: 2023/12/06 20:56:53 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "./libft/libft.h"
#include "./sys/wait.h"

void	free_arr(char **arr);
char	*filter_envp(char **envp);
char	*locate_command_path(char *command, char **envp);
char    **extract_command(char *av);
void    error_msg();

#endif