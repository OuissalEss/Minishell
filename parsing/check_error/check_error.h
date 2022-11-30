/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:48:22 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/29 09:01:52 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_ERROR_H
# define CHECK_ERROR_H

typedef struct s_heredoc
{
	char				*dlmt;
	struct s_heredoc	*next;
}			t_heredoc;

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

int		quotes(const char *str, int x);
char	*remove_quotes(char *str);
int		skip_white_spaces(char *str, int i, t_errflags *flags);
void	set_flags(t_errflags *flags, char *s, int i);
void	set_flags2(t_errflags *flags, char *s, int i);
int		free_flags(t_errflags *f, int r);
void	init_flags(t_errflags **f);
char	*ft_charjoin(char *str, char x);
char	*join_two_str(char *s1, char const *s2, int l1);
char	*get_name(char *str, int *j);
void	open_hdocs(t_errflags *f);
char	*expand_dollar(char *str);
char	*get_name(char *str, int *j);

#endif
