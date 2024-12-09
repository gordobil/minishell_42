/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:11:38 by ngordobi          #+#    #+#             */
/*   Updated: 2024/12/09 15:27:28 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	nodes_envp(t_envp *envp_p, t_envp *prev, int i, char **envp)
{
	if (i == 0)
		envp_p->prev = NULL;
	else
	{
		envp_p->prev = prev;
		envp_p->prev->next = envp_p;
	}
	if (envp[i + 1] == NULL)
		envp_p->next = NULL;
}

void	load_content(char **envp, t_envp *envp_p, int i, int j)
{
	int	k;

	k = j;
	while (envp[i][j] != '\0')
		j++;
	envp_p->content = malloc((j - k + 1) * sizeof(char));
	j = 0;
	while (envp[i][k] != '\0')
	{
		envp_p->content[j] = envp[i][k];
		j++;
		k++;
	}
	envp_p->content[j] = '\0';
}

int	load_variable(char **envp, t_envp *envp_p, int i)
{
	int	j;

	j = 0;
	while (envp[i][j] != '=')
		j++;
	envp_p->variable = malloc((j + 1) * sizeof(char));
	j = 0;
	while (envp[i][j] != '=')
	{
		envp_p->variable[j] = envp[i][j];
		j++;
	}
	envp_p->variable[j] = '\0';
	j++;
	return (j);
}

void	load_envp(t_mini *mini, char **envp)
{
	int		i;
	int		j;
	t_envp	*prev;
	t_envp	*envp_p;

	i = 0;
	mini->envp = malloc(sizeof(t_envp));
	if (!mini->envp)
		return ;
	envp_p = mini->envp;
	while (envp[i] != NULL)
	{
		envp_p->position = i;
		envp_p->exported = 1;
		j = load_variable(envp, envp_p, i);
		load_content(envp, envp_p, i, j);
		nodes_envp(envp_p, prev, i, envp);
		prev = envp_p;
		i++;
		envp_p = envp_p->next;
		envp_p = malloc (sizeof(t_envp));
	}
	free(envp_p);
}

int	add_vars(t_mini *mini)
{
	int		i;
	int		j;
	t_envp	*envp;

	if (!mini->vars)
		return (-1);
	envp = mini->envp;
	while (envp->next != NULL)
		envp = envp->next;
	i = 0;
	while (mini->vars[i] != NULL)
	{
		envp->next = malloc(sizeof(t_envp));
		if (!envp->next)
			return (-1);
		j = load_variable(mini->vars, envp->next, i);
		load_content(mini->vars, envp->next, i, j);
		envp->next->position = envp->position + 1;
		envp->next->exported = 0;
		envp->next->prev = envp;
		envp->next->next = NULL;
		envp = envp->next;
		i++;
	}
	return (0);
}
