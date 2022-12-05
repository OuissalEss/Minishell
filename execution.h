/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:38:21 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/05 06:19:19 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

		// EXEC //
void	start_executing(void);
void	ft_lstadd_back(t_env **lst, t_env *new);
void	set_env(char **envp);
char	*get_var(char *str);
char	*get_value(char *str);
void	env_add_back(t_env **lst, t_env *new);

		// MINISHELL UTILS //
int		ft_strcmp(char *s1, char *s2);
void	ft_putstr(char *str);
int		is_alpha(char c);
size_t	ft_strlen(char *str);
int		ft_isalnum(int c);
int		ft_strncmp(char *s1, char *s2, int n);

		//   BUILTINS FUNCTIONS   //
void	builtins(void);
void	do_pwd(void);
void	do_env(void);
void	do_echo(void);
void	do_cd(void);
void	update_pwd(char *old_pwd, char *pwd);
void	go_home(char *pwd);
void	do_export(void);
int		is_valid(char	*str);
void	display_export(void);
void	do_unset(void);
void	remove_node(char *str);
void	supprimer_node(int pos);
void	do_exit(void);

#endif