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

typedef struct s_flags
{
	int			c;
	int			pipe;
	int			in;
	int			out;
	int			app;
	int			hdoc;
	int			dlmt;
	int			hdoc_count;
	int			id_command;
	t_heredoc	*hdocs;
}				t_errflags;

typedef struct s_args
{
	char			*str;
	struct s_args	*next;
}				t_args;

int		ft_isalnum(int c);
void	*ft_calloc(size_t count, size_t size);
int		quotes(const char *str, int x);
char	*remove_quotes(char *str);
int		skip_white_spaces(char *str, int i, t_errflags *flags);
void	init_data(char **envp);
int		check_error(char *str);
int		handle_redirections(char *str, int i);
void	set_flags(t_errflags *flags, char *s, int i);
void	set_flags2(t_errflags *flags, char *s, int i);
int		free_flags(t_errflags *f, int r);
void	start_parsing(char *str);
void	cmd_add_back(t_cmd *new);
t_cmd	*get_last(t_cmd *lst);
void	hdoc_add_back(t_heredoc **lst, t_heredoc *new);
int		add_heredoc(char *str, int i);
void	add_cmd(void);
char	*ft_charjoin(char *str, char x);
char	*join_two_str(char *s1, char const *s2, int l1);
char	*ft_strjoin(char *s1, char *s2);
int		skip_whitespace(char *str, int i);
char	*get_name(char *str, int *j);
int		add_infile(char *str, int i);
int		add_outfile(char *str, int i);
int		add_append(char *str, int i);
int		handle_redirections(char *str, int i);
void	init_flags(t_errflags **f);
char	*get_varvalue(char *var_name);
char	*get_varname(char *str, int i);
void	open_hdocs(t_errflags *f);
char	*expand_dollar(char *str);
char	*ft_itoa(int n);
void	rm_quotes(void);

#endif
