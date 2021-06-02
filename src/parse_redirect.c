#include "minishell.h"

void	skip_spaces(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

static	int		check_quote(char **s, int i, char quote_mark)
{
	// т.к. ф-ия вызывается, когда встречается кавычка, мы уже икрементируем счетчик,
	// чтобы войти в цикл и дойти до закрывающей кавычки
	// Пока текущий символ не равняется кавычке или текущий символ равняется кавычке, но перед ним слэш,
	// и пока текущий символ не равняется концу строки
	while ((*s)[i] && ((*s)[i] != quote_mark || ((*s)[i] == quote_mark && is_slash(*s, i - 1))))
		i++;
	// Если текущий символ - кавычка и она не экранирована, то значит кавычки закрыты,
	// возвращаем следующий от нее индекс строки
	if ((*s)[i] == quote_mark && !is_slash(*s, i - 1))
	{
		*s = remove_from(*s, i);
		return (i);
	}
	else
		throw_error(QUOTE_NOT_FOUND, 21);
	return (0);
}

static size_t	read_str(char **s, int i, char *separators)
{
	while ((*s)[i] && !ft_strchr(separators, (*s)[i]))
	{
		if ((*s)[i] == QUOTE && !is_slash(*s, i - 1))
		{
			*s = remove_from(*s, i);
			i = check_quote(s, i, QUOTE);
		}
		else if ((*s)[i] == D_QUOTE && !is_slash(*s, i - 1))
		{
			*s = remove_from(*s, i);
			escape_pair(s);
			i = check_quote(s, i, D_QUOTE);
		}
		else
			i++;
	}
	return (i);
}

t_redir 	*redir_alloc(void)
{
	t_redir *redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (redir == NULL)
		throw_error(BAD_ALLOC, 9999);
	ft_memset(redir, 0, sizeof(t_redir));
	return (redir);
}

void		write_out(t_cmd *cmd, char **str, int *i)
{
	char		*copy_str;
	t_redir		*redir;
	t_bd_lst	*new;

	redir = redir_alloc();
	redir->s_id = OUT;
	redir->flag = O_TRUNC;
	*str = remove_from(*str, *i);

	if ((*str)[*i] == '>' && !is_slash(*str, *i - 1))
	{
		redir->flag = O_APPEND;
		*str = remove_from(*str, *i);
	}
	else if ((*str)[*i] == '>' && is_slash(*str, *i - 1))
		*str = remove_from(*str, *i - 1);

	skip_spaces(*str, i);
	copy_str = ft_strdup(*str);
	redir->filename = ft_substr(copy_str, *i, read_str(&copy_str, *i, " ><") - *i);
	
	new = bd_lstnew(redir);
	if (!new)
		throw_error(BAD_ALLOC, 10);
	bd_lstadd_back(&cmd->out, new);
	replace_by(str, *i, read_str(str, *i, " ><") - *i, "", free);
	free(copy_str);
}

void		write_in(t_cmd *cmd, char **str, int *i)
{
	char		*copy_str;
	t_redir		*redir;
	t_bd_lst	*new;

	redir = redir_alloc();
	redir->s_id = IN;
	redir->flag = O_TRUNC;
	*str = remove_from(*str, *i);

	if ((*str)[*i] == '<' && !is_slash(*str, *i - 1))
	{
		redir->flag = O_APPEND;
		*str = remove_from(*str, *i);
	}
	else if ((*str)[*i] == '<' && is_slash(*str, *i - 1))
		*str = remove_from(*str, *i - 1);

	skip_spaces(*str, i);
	copy_str = ft_strdup(*str);
	redir->filename = ft_substr(copy_str, *i, read_str(&copy_str, *i, " ><") - *i);
	
	new = bd_lstnew(redir);
	if (!new)
		throw_error(BAD_ALLOC, 10);
	bd_lstadd_back(&cmd->in, new);
	replace_by(str, *i, read_str(str, *i, " ><") - *i, "", free);
	free(copy_str);
}

int		parse_redirect(t_cmd *cmd, char **str)
{
	int			i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '>' && !is_slash(*str, i - 1))
			write_out(cmd, str, &i);
		else if ((*str)[i] == '>' && is_slash(*str, i - 1))
			*str = remove_from(*str, i - 1);
		else if ((*str)[i] == '<' && !is_slash(*str, i - 1))
			write_in(cmd, str, &i);
		else if ((*str)[i] == '<' && is_slash(*str, i - 1))
			*str = remove_from(*str, i - 1);
		else
			i++;
	}
	return (1);
}
