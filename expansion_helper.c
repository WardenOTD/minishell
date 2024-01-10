/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:09:27 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/10 17:44:48 by jteoh            ###   ########.fr       */
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
	char	*new_value;

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

char	*replace_expand_helper(char *str, int pos,
	char *new_value, char *ret)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (i == pos)
		{
			if (new_value == NULL)
				break ;
			else
				while (new_value[j])
					ret[i++] = new_value[j++];
			break ;
		}
		i++;
	}
	return (ret);
}

char	*copy_backwards(char *str, int pos, int *size, char *ret)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (i == pos)
		{
			i += size[0];
			j += size[1];
			continue ;
		}
		ret[j] = str[i];
		j++;
		i++;
	}
	return (ret);
}
