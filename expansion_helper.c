/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:09:27 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/09 14:11:47 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	*get_to_replace(char *str, int pos)
{
	int		i;
	int		j;
	char	*ret;

	if (str[pos + 1] == '?')
		return (ft_strdup("$?"));
	else if (str[pos + 1] == ' ' || str[pos + 1] == '\"')
		return (ft_strdup("$"));
	i = pos + 1;
	j = 0;
	while (str[i] && ft_isalpha(str[i]))
		i++;
	ret = malloc (sizeof(char) * (i - pos + 1));
	while (pos < i)
		ret[j++] = str[pos++];
	ret[j] = 0;
	return (ret);
}

char	*get_new_value(char *to_r, t_env *env)
{
	char *new_value;

	new_value = NULL;
	if (!ft_strncmp(to_r, "$?", 3))
		new_value = ft_itoa(g_status_code);
	else
		new_value = get_env_value(to_r, env);
	return (new_value);
}

int	ft_strlen_checknull(char *str)
{
	int	len;

	if (!str)
		len = 0;
	else
		len = ft_strlen(str);
	return (len);
}

char	*replace_expand_helper(char *str, char *to_r,
	char *new_value, char *ret)
{
	int	i;
	int	j;
	int	k;
	int	once;

	i = 0;
	j = 0;
	k = 0;
	once = 0;
	while (str[i])
	{
		if (yes_expand(str[i], str[i + 1]) && !once)
		{
			if (new_value)
				while (new_value[k])
					ret[j++] = new_value[k++];
			i += ft_strlen(to_r);
			once = 1;
		}
		else
			ret[j++] = str[i++];
	}
	return (ret);
}
