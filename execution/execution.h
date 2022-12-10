/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:38:21 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/10 06:04:27 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include "../parsing/parsing.h"

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
int		builtins(t_cmd *cmd);
void	do_pwd(t_cmd *cmd);
void	do_env(t_cmd *cmd);
void	do_echo(t_cmd *cmd);
int		do_cd(t_cmd *cmd);
void	update_pwd(char *old_pwd, char *pwd);
char	*go_home(char *pwd);
int		do_export(t_cmd *cmd);
char	*env_name(char *str, int *add);
char	*env_value(char *str);
int		exist_env(char *name);
int		valid(char	*str);
int		is_valid(char	*str);
void	display_export(t_cmd *cmd);
int		do_unset(t_cmd *cmd);
void	remove_node(char *str);
void	supprimer_node(int pos);
int		do_exit(t_cmd *cmd);

		// EXECUTION FUNCTIONS //
char	*check_path(char *cmd_name);
void	free_path(char **path);
char	**add_slash(char **path, char *cmd_name);
char	*get_path(void);
int		count_path(char *str);
int		lst_size(t_env *env);
int		is_builtin(char *cmd);
int		ft_pipe(t_cmd *cmd);
int		previous(t_cmd *cmd);
void	wait_for_proccess(void);
int		exit_status(void);

#endif