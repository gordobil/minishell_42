/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:09:11 by ngordobi          #+#    #+#             */
/*   Updated: 2024/12/02 12:09:11 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo(t_pipes *pipe)
{
	int	i;
	int	flag;

	flag = 0;
	if (pipe->command[1] != NULL)
	{
		i = 1;
		if (ft_strcmp(pipe->command[i], "-n") == 0)
		{
			i++;
			flag = 1;
		}
		while (pipe->command[i] != NULL)
		{
			ft_printf("%s", pipe->command[i]);
			if (pipe->command[i + 1] != NULL)
				ft_printf(" ");
			i++;
		}
	}
	if (flag == 0)
		ft_printf("\n");
}
