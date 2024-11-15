/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.com   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:05:41 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/11 12:05:41 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*namefiles(int del)
{
	char		*namefile;
	char		*num;
	static int	count;

	if (del == 0)
	{
		count++;
		num = ft_itoa(count);
		namefile = ft_strjoin(".delimiter_file_", num);
		return (namefile);
	}
	else if (del == 1)
	{
		while (count > 0)
		{
			num = ft_itoa(count);
			namefile = ft_strjoin(".delimiter_file_", num);
			unlink(namefile);
			free(namefile);
			count--;
		}
	}
	return (NULL);
}

t_pipes	*save_files(t_pipes *command, char *namefile, int fd, int i)
{
	if (ft_strcmp(command->mini->delimiters[i], command->delimiter->file) == 0)
	{
		command->delimiter->file = ft_strdup(namefile);
		command->delimiter->fd = fd;
		if (command->mini->comm_c > 1 && command->next != NULL)
		{
			command = command->next;
			while (command->delimiter->file == NULL && command->next != NULL)
				command = command->next;
		}
	}
	return (command);
}

int	del_cmp(char *delimiter, char *line)
{
	int	i;
	int	j;

	i = 0;
	while (delimiter[i] == '<')
		i++;
	while (delimiter[i] == ' ' || delimiter[i] == '	')
		i++;
	j = 0;
	while (delimiter[i] == line[j] && delimiter[i] != '\0' && line[j] != '\0')
	{
		i++;
		j++;
	}
	if (delimiter[i] == '\0' && line[j] == '\0')
		return (0);
	return (-1);
}

void	delimiters(t_mini *mini)
{
	char	*namefile;
	char	*line;
	t_pipes	*command;
	int		fd;
	int		i;

	command = mini->pipes;
	i = 0;
	while (mini->delimiters[i] != NULL)
	{
		namefile = namefiles(0);
		fd = open(namefile, O_CREAT | O_EXCL | O_RDWR);
		while (1)
		{
			line = readline("> ");
			if (del_cmp(mini->delimiters[i], line) == 0)
				break ;
			write (fd, line, ft_strlen(line));
			write (fd, "\n", 1);
			free (line);
		}
		command = save_files(command, namefile, fd, i);
		free(namefile);
		i++;
	}
}
