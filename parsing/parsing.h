/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:48:22 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/27 13:43:28 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

int		check_error(char *str);
int		ft_isalnum(int c);
void	*ft_calloc(size_t count, size_t size);
void	init_data(char **envp);
int		check_error(char *str);
void	start_parsing(char *str);
void	cmd_add_back(t_cmd *new);
t_cmd	*cmd_get_last(t_cmd *lst);
void	add_cmd(void);
char	*ft_charjoin(char *str, char x);
char	*get_varvalue(char *var_name);
char	*get_varname(char *str, int i);
char	*ft_itoa(int n);
void	red_add_back(t_red **r, t_red *new);
void	set_arr(char *str, int **array);
char	*handle_expansion(char **str, int **arr);
void	handle_quotes(char **str, int **arr);
t_red	*handle_redirection(char **str, int **arr, t_red *red);
char	**split_cmds(char *str, int *arr);
int		open_red(void);
int 	expand_exit(char *str, char **new);
int		expand(char *str, char **new);
void	env_add_back(t_env **lst, t_env *new);
void	init_data(char **envp);
void	expand_red(void);

#endif
