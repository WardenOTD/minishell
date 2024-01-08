/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:07:20 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/08 17:18:38 by jutong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	yes_expand(char c1, char c2)
{
	if (c1 != '$')
		return (0);
	if (c2 == ' ' || c2 == '$' || c2 == 0 || c2 == '\"' || c2 == '\'')
		return (0);
	return (1);
}

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
	{
		ret[j++] = str[pos++];
	}
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

char	*replace_expand(char *str, int pos, char *to_r, t_env *env)
{
	char	*new_value;
	char	*ret;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	new_value = get_new_value(to_r, env);
	ret = malloc (sizeof(char) * (ft_strlen(str) - ft_strlen(to_r) + ft_strlen_checknull(new_value) + 1));
	while (i < pos)
		ret[j++] = str[i++];
	if (new_value)
		while (new_value[k])
			ret[j++] = new_value[k++];
	i += ft_strlen(to_r);
	while (str[i])
		ret[j++] = str[i++];
	ret[j] = 0;
	if (new_value)
		free(new_value);
	free(str);
	return (ret);
}
