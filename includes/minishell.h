/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:39 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/16 19:14:40 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include "./libft.h"

//COLORS
# define BLUE "\033[1;34m"
# define YELLOW "\033[0;32m"
# define WHITE "\033[0m"

typedef struct s_mini
{
	char	*rdline;
	char	**args;
	int		arg_c;
}				t_mini;

//MAIN
int		parser(char *rdline);

//RDL_UTILS
void	rdl_signals(int sig);
char	*mini_title(void);
int		arg_errors(int error);

//SPLIT_ARGS
int		split_args(const char *s, t_mini *mini);
int		arg_count(const char *s);
int		arg_len(const char *s, int j);
int		arg_jump(const char *s, int i);
int		quote_count(const char *s, int j);

#endif
