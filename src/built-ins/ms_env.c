/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:54:47 by ngordobi          #+#    #+#             */
/*   Updated: 2024/12/11 23:54:47 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_env(t_envp *envp)
{
	t_envp	*var;

	var = envp;
	while (var != NULL)
	{
		if (var->exported == 1 && var->variable != NULL
			&& var->content != NULL)
			ft_printf("%s=%s\n", var->variable, var->content);
		var = var->next;
	}
}
