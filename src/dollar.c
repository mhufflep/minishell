#include "minishell.h"

static	void	insert_value(char **s, int i)
{
	int		start;
	int		len;
	t_env	*var;

	len = 0;
	start = 0;
	*s = remove_from(*s, i);
	start = i;
	while ((*s)[i] && (ft_isalnum((*s)[i]) || (*s)[i] == '_'))
	{
		len++;
		i++;
	}
	var = env_get_local(ft_substr(*s, start, len));
	if (var)
		replace_by(s, start, len, var->val, free);
	else
		replace_by(s, start, len, "", free);
}

void			parse_dollar(char **s, int code)
{
	int		i;
	char	*exit_;

	i = 0;
	while ((*s)[i])
	{	
		// в строгих кавычках все символы экранируются, соответственно здесь пропускаем key
		if ((*s)[i] == QUOTE && !is_slash(*s, i - 1))
			i = skip_in_quote(s, i, QUOTE);
		else if ((*s)[i] == '$' && !is_slash(*s, i - 1) && (*s)[i + 1] != '?')
		{
			if (ft_isdigit((*s)[i + 1]))
				replace_by(s, i, 2, "", free);
			else
				insert_value(s, i);
		}
		else if ((*s)[i] == '$' && !is_slash(*s, i - 1) && (*s)[i + 1] == '?')
		{
			replace_by(s, i, 2, exit_ = ft_itoa(code), free);
			i += ft_strlen(exit_);
			free(exit_);
		}
		else
			i++;
	}
}
