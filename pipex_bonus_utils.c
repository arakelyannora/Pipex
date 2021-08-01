/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narakely <narakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:24:16 by narakely          #+#    #+#             */
/*   Updated: 2021/07/07 15:38:03 by narakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char**	get_path(char **env)
{
	while (*env != NULL && ft_strncmp(*env, "PATH=", 5))
		env++;
	if (*env == NULL)
	{
		perror("Cannot find binary of the given command");
		exit(1);
	}
	return (ft_split(*env + 5, ':'));
}
char	*get_cmd_path(char **bin_path, char *cmd)
{
	int i;
	char **cmd_;
	char *cmd_path;
	
	i = 0;
	cmd_ = ft_split(cmd, ' ');
	while (bin_path[i])
	{
		cmd_path = ft_strjoin(bin_path[i], "/");
		cmd_path = ft_strjoin(cmd_path, cmd_[0]);
		// printf("%s\n", cmd_path);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}