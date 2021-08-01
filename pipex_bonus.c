/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narakely <narakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:37:47 by narakely          #+#    #+#             */
/*   Updated: 2021/07/07 18:10:29 by narakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
/*
pipex bonus pordzel
./pipex_bonus here_doc infile "cat" "ls" outfile
cat << infile | ls >> outfile 
voncvor te nuyn banna anum
*/
void	free_(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
void	child_process(int *pipe_fd, char *cmd_path, char** argv)//argv[1] - infile, argv[4] - outfile,,, pipe_fd[0] read end, pipe_fd[1] write end
{
	int file_des;
	char **cmd_;
	
	close(pipe_fd[0]);
	file_des = open(argv[1], O_RDONLY);
	if (file_des == -1)
	{
		perror("file open error");
		close(pipe_fd[1]);
		free(cmd_path);
		exit(1);
	}
	if (dup2(file_des, 0) == -1)
	{
		perror("dup2 error");
		close(pipe_fd[1]);
		close(file_des);
		free(cmd_path);
		exit(1);
	}
	if (dup2(pipe_fd[1], 1) == -1)
	{
		perror("dup2 error");
		close(pipe_fd[1]);
		close(file_des);
		free(cmd_path);
		exit(1);
	}
	cmd_ = ft_split(argv[2], ' ');
	if (execve(cmd_path, cmd_, NULL) == -1)
	{
		perror("execve error");
		close(pipe_fd[1]);
		close(file_des);
		free(cmd_path);
		free_(cmd_);
		exit(1);
	}
	close(file_des);
	close(pipe_fd[1]);
}
void	child_process_bonus(int *pipe_fd, char *cmd_path, char** argv, char *limiter)//argv[1] - infile, argv[4] - outfile,,, pipe_fd[0] read end, pipe_fd[1] write end
{
	// int file_des;
	char **cmd_;
	char *line;
	
	close(pipe_fd[0]);
	// file_des = open(argv[bonus == 1 ? 2 : 1], O_RDONLY);
	// if (file_des == -1)
	// {
	// 	perror("file open error");
	// 	close(pipe_fd[1]);
	// 	free(cmd_path);
	// 	exit(1);
	// }
	// if (dup2(pipe_fd[0], 0) == -1)
	// {
	// 	perror("dup2 error");
	// 	close(pipe_fd[1]);
	// 	// close(file_des);
	// 	free(cmd_path);
	// 	exit(1);
	// }
	while (get_next_line(0, &line) != 0)
	{
		if (ft_strncmp(limiter, line, ft_strlen(line)) == 0)
		break;
	}
	if (dup2(pipe_fd[1], 1) == -1)
	{
		perror("dup2 error");
		close(pipe_fd[1]);
		// close(file_des);
		free(cmd_path);
		exit(1);
	}
	char *s = ft_strjoin(argv[3], "<< ");//cat<< infile
	s = ft_strjoin(s, limiter);
	// printf("%s\n", s);
	cmd_ = ft_split(s, ' ');
	free(s);
	// printf("hi %s\n", cmd_path);
	// while (get_next_line(pipe_fd[0], &line) != 0 && ft_strncmp(limiter, line, ft_strlen(line)) != 0)
	// {
		if (execve(cmd_path, cmd_, NULL) == -1)
		{
			// printf("hi %s\n", cmd_path);
			perror("hello execve error");
			close(pipe_fd[1]);
			// close(file_des);
			free(cmd_path);
			free_(cmd_);
			exit(1);
		}
	// }
	// while (get_next_line(0, &line) != 0 && ft_strncmp(limiter, line, ft_strlen(line)) != 0)
	
	// close(file_des);
	close(pipe_fd[1]);
}
void	parent_process(int *pipe_fd, char *cmd_path, char** argv, int bonus)
{
	int file_des;
	char **cmd_;

	close(pipe_fd[1]);
	wait(0);//spasuma lyuboy docherniy process prcni
	if (bonus == 1)
		file_des = open(argv[5], O_RDWR | O_CREAT | O_APPEND, S_IRWXG | S_IRWXU | S_IRWXO);
	else 
		file_des = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, S_IRWXG | S_IRWXU | S_IRWXO);
	if (file_des== -1)
	{
		perror("file open error");
		close(pipe_fd[0]);
		free(cmd_path);
		exit(1);
	}
	if (dup2(file_des, 1) == -1)//argv[4]-y darcnum enq output
	{
		perror("dup2 error");
		close(pipe_fd[0]);
		close(file_des);
		free(cmd_path);
		exit(1);
	}
	if (dup2(pipe_fd[0], 0) == -1)//pipe_fd[0] darcnum enq input
	{
		perror("dup2 error");
		close(pipe_fd[0]);
		close(file_des);
		free(cmd_path);
		exit(1);
	}
	// printf("hi\n");
	cmd_ = ft_split(argv[bonus == 1 ? 4 : 3], ' ');
	if (execve(cmd_path, cmd_, NULL) == -1)
	{
		printf("hi %s\n", cmd_path);
		perror("execve error");
		close(pipe_fd[0]);
		close(file_des);
		free(cmd_path);
		free_(cmd_);
		exit(1);
	}
	close(file_des);
	close(pipe_fd[1]);
}
int	main(int argc, char **argv, char **envp)
{
	int bonus;
	int p_id;
	int pipe_fd[2];
   	char **bin_path;
	char *cmd1_path;
	char *cmd2_path;
	char *limiter;
	
	bonus = 0;
	if (argc != 6 && argc != 5)
	{
		ft_putstr_fd("Invalid arguments\nUsage: here_doc file1 cmd1 cmd2 file2 or file1 cmd1 cmd2 file2", 1);
		return (1);
	}
	if (argc == 6)
	{
		bonus = 1;
		if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1]) != 0))
		{
			ft_putstr_fd("Invalid arguments\nUsage: here_doc file1 cmd1 cmd2 file2 or file1 cmd1 cmd2 file2", 1);
			return (1);
		}
	}
	limiter = argv[2];
	bin_path = get_path(envp);
	cmd1_path = get_cmd_path(bin_path, argv[bonus == 1 ? 3 : 2]);
	cmd2_path = get_cmd_path(bin_path, argv[bonus == 1 ? 4 : 3]);
	free_(bin_path);
	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe error");
		return (1);
	}
	p_id = fork();
	if (p_id == -1)
	{
		perror("Fork error");
		return (1);
	}
	if (p_id == 0)//docherniy process
		bonus == 1 ? child_process_bonus(pipe_fd, cmd1_path, argv, limiter) : child_process(pipe_fd, cmd1_path, argv);
	else
		parent_process(pipe_fd, cmd2_path, argv, bonus);
	return (0);
}