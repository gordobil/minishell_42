/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:57:09 by mafarto-          #+#    #+#             */
/*   Updated: 2025/02/03 10:52:11 by mafarto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	building_execute(t_mini *mini, t_pipes *pipe, t_envp *envp, int i)
{
	if (pipe != NULL && pipe->command != NULL && pipe->command[i] != NULL)
	{
		if (ft_strcmp(pipe->command[i], "cd") == 0)
			ms_cd(pipe, envp, i);
		else if (ft_strcmp(pipe->command[i], "echo") == 0)
			ms_echo(pipe, i);
		else if (ft_strcmp(pipe->command[i], "pwd") == 0)
			ms_pwd(envp, pipe);
		else if (ft_strcmp(pipe->command[i], "env") == 0)
			ms_env(envp, pipe, i, 0);
		else if (ft_strcmp(pipe->command[i], "export") == 0
			&& pipe->command[i + 1] == NULL)
			ms_env(envp, pipe, i, 1);
		else if (ft_strcmp(pipe->command[i], "export") == 0
			&& pipe->command[i + 1] != NULL)
			ms_export(pipe, envp);
		else if (ft_strcmp(pipe->command[i], "unset") == 0)
			ms_unset(pipe, envp, i);	
		else if (pipe->args == pipe->var_c)
			return (add_vars(pipe, mini), 0);
		return (-1);
	}
	return (0);
}

void	execveloop(char **str, char **path, char **term)
{
	char	*bin;
	int		count;

	while (is_it_a_var(*str) > 0)
		*str++;
	count = 0;
	while (path[count] != 0)
	{
		bin = ft_strcat(path[count], *str);
		execve(bin, str, term);
		free (bin);
		count++;
	}
	execve(*str, str, 0);
	ft_printf("%s: command not found\n", *str);
	exit(127);
}

int	comand_size(t_pipes	*pipes)
{
	int	command_count;

	command_count = 0;
	while (pipes)
	{
		pipes = pipes->next;
		command_count++;
	}
	return (command_count);
}

int	is_text(t_pipes *pipe, t_envp *envp)
{
	if (ft_strcmp(pipe->command[0], "cd") == 0)
		return (0);
	else if (ft_strcmp(pipe->command[0], "echo") == 0)
		return (0);
	else if (ft_strcmp(pipe->command[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(pipe->command[0], "env") == 0)
		return (1);
	else if (ft_strcmp(pipe->command[0], "export") == 0)
		return (0);
	else if (ft_strcmp(pipe->command[0], "unset") == 0)
		return (0);
	return (1);
}

void	pipex(t_pipes *pipes, t_envp *envp)
{
	int		status;
	int		id;
	char	**path;

	if (!pipes || !pipes->command || !pipes->command[0] || envp == NULL)
		return ;
	path = get_pathsenv(envp);
	envp = get_edge_node(pipes->mini->envp, 's');
	if (comand_size(pipes) == 1 && is_text(pipes, envp) == 0)
		building_execute(pipes->mini, pipes, envp, var_jump(pipes->command));
	else
		execute_pipeline(pipes, envp);
	free_matrix(path);
}
