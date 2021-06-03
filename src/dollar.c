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
	replace_by(s, start, len, var->val, free);			
}

void			parse_dollar(char **s, int code)
{
	int		i;
	char	*exit_;

	i = 0;
	while ((*s)[i])
	{	
		if ((*s)[i] == '$' && !is_slash(*s, i) && (*s)[i + 1] != '?')
		{
			if (ft_isdigit((*s)[i + 1]))
				replace_by(s, i, 2, "", free);
			else
				insert_value(s, i);
		}
		else if ((*s)[i] == '$' && !is_slash(*s, i) && (*s)[i + 1] == '?')
		{
			replace_by(s, i, 2, exit_ = ft_itoa(code), free);
			free(exit_);
		}
		i++;
	}
}
