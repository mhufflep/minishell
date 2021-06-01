#include "minishell.h"

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

void	skip_spaces(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

int		parse_redirect(char **str, t_cmd *cmd)
{
	int			i;
	// int index;
	char		separator;
	t_bd_lst	*new;
	char		*filename;

	separator = ' ';

	cmd->filenames = NULL;
	i = 0;
	cmd->is_redirect = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '>' && !is_slash(*str, i - 1))
		{
			cmd->is_redirect = TRUNC;
			*str = remove_from(*str, i);

			if ((*str)[i] == '>' && !is_slash(*str, i - 1))
			{
				cmd->is_redirect = APPEND;
				*str = remove_from(*str, i);
			}
			else if ((*str)[i] == '>' && is_slash(*str, i - 1))
				*str = remove_from(*str, i - 1);

			skip_spaces(*str, &i);
			filename = ft_substr(*str, i, read_str(str, i, " >") - i);
			new = bd_lstnew(filename);
			if (!new)
				throw_error(BAD_ALLOC, 10);
			bd_lstadd_back(&cmd->filenames, new);
			replace_by(str, i, read_str(str, i, " >") - i, "", free);
		}
		else if ((*str)[i] == '>' && is_slash(*str, i - 1))
			*str = remove_from(*str, i - 1);
		else
			i++;
	}
	return (1);
}
