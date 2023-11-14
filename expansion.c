/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:07:28 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/14 18:11:28 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"


/*
AddressSanitizer:DEADLYSIGNAL
=================================================================
==89366==ERROR: AddressSanitizer: SEGV on unknown address 0x55a9e1b8a5b0 (pc 0x7f1c71bf3b46 bp 0x55a9e1b8a5c0 sp 0x7ffe237bde60 T0)
==89366==The signal is caused by a WRITE memory access.
    #0 0x7f1c71bf3b46 in bool __sanitizer::atomic_compare_exchange_strong<__sanitizer
	::atomic_uint8_t>(__sanitizer::atomic_uint8_t volatile*, __sanitizer::atomic_uint8_t
	::Type*, __sanitizer::atomic_uint8_t::Type, __sanitizer
	::memory_order) ../../../../src/libsanitizer/sanitizer_common/sanitizer_atomic_clang.h:80
	//
    #1 0x7f1c71bf3b46 in __asan::Allocator
	::AtomicallySetQuarantineFlagIfAllocated(__asan::AsanChunk*, void*, __sanitizer
	::BufferedStackTrace*) ../../../../src/libsanitizer/asan/asan_allocator.cpp:621
	//
    #2 0x7f1c71bf3b46 in __asan::Allocator::Deallocate(void*, unsigned long, unsigned long, __sanitizer
	::BufferedStackTrace*, __asan::AllocType) ../../../../src/libsanitizer/asan/asan_allocator.cpp:697
	//
    #3 0x7f1c71bf3b46 in __asan::asan_free(void*, __sanitizer
	::BufferedStackTrace*, __asan::AllocType) ../../../../src/libsanitizer/asan/asan_allocator.cpp:971
	//
    #4 0x7f1c71c7f4f4 in __interceptor_free ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:128
    #5 0x55a9e1b86cec in remove_exp /home/jteoh/minishell/expansion.c:130
    #6 0x55a9e1b8612c in expand /home/jteoh/minishell/expansion.c:59
    #7 0x55a9e1b82d74 in lexer /home/jteoh/minishell/lexer.c:41
    #8 0x55a9e1b808dd in main /home/jteoh/minishell/main.c:74
    #9 0x7f1c71978d8f  (/lib/x86_64-linux-gnu/libc.so.6+0x29d8f)
    #10 0x7f1c71978e3f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x29e3f)
    #11 0x55a9e1b80384 in _start (/home/jteoh/minishell/minishell+0x2384)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV ../../../../src/libsanitizer/sanitizer_common/sanitizer_atomic_clang.h:80 in bool __sanitizer
::atomic_compare_exchange_strong<__sanitizer::atomic_uint8_t>(__sanitizer::atomic_uint8_t volatile*, __sanitizer
::atomic_uint8_t::Type*, __sanitizer::atomic_uint8_t::Type, __sanitizer::memory_order)
==89366==ABORTING
*/


t_lexer	*expand(t_lexer *input, t_env *env)
{
	t_lexer	*lhead;
	char	*ex;
	char	*val;
	int		count;
	int		i;
	int		j;
	int		flag;
	int		dflag;

	lhead = input;
	flag = 0;
	dflag = 0;
	while (lhead)
	{
		i = 0;
		while (lhead->arg[i])
		{
			j = 0;
			while (lhead->arg[i][j])
			{
				if (lhead->arg[i][j] == '\'')
				{
					if (flag == 0)
						flag = 1;
					else
						flag = 0;
				}
				if (lhead->arg[i][j] == '"')
				{
					if (dflag == 0)
						dflag = 1;
					else
						dflag = 0;
				}
				if ((lhead->arg[i][j] == '$' && flag == 0) || (lhead->arg[i][j] == '$' && dflag == 1))
				{
					if (lhead->arg[i][j + 1] == ' ' || lhead->arg[i][j + 1] == '"' || lhead->arg[i][j + 1] == '\'' || !lhead->arg[i][j + 1])
					{
						if (lhead->arg[i][j + 1] == 0)
							break ;
						if (flag == 0 && dflag == 0 && (lhead->arg[i][j + 1] == '"' || lhead->arg[i][j + 1] == '\''))
						{
							lhead->arg[i] = remove_exp("$", lhead->arg[i]);
							j = 0;
							continue ;
						}
						j++;
						continue ;
					}
					else
					{
						count = 1;
						ex = NULL;
						val = NULL;
						while (lhead->arg[i][j] && lhead->arg[i][j] != ' ' && lhead->arg[i][j + 1] != '$' && lhead->arg[i][j] != '"' && lhead->arg[i][j] != '\'')
						{
							printf("expansion == we in\n");
							count++;
							j++;
						}
						ex = (char *)malloc(sizeof(char) * (count + 1));
						printf("expansion === count: %d == j: %d\n", count, j);
						ex[count] = 0;
						j -= count - 1;
						count = 0;
						while (ex[count])
							ex[count++] = lhead->arg[i][j++];
						val = get_env_value(ex, env);
						printf("expansion ==== %s ,,_%s_,,\n", val, ex);
						if (val == NULL)
							lhead->arg[i] = remove_exp(ex, lhead->arg[i]);
						else
							lhead->arg[i] = add_exp(ex, lhead->arg[i], val);
						// if (val != NULL)
						free(val);
						j = 0;
						continue ;
					}
				}
				j++;
			}
			i++;
		}
		lhead = lhead->next;
	}
	return (input);
}

char	*remove_exp(char *needle, char *haystack)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	ret = NULL;
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && haystack[i + j])
		{
			if (needle[j + 1] == 0 && (haystack[i + j + 1] == '\'' || haystack[i + j + 1] == '"' || haystack[i + j + 1] == ' ' || !haystack[i + j + 1]))
			{
				ret = (char *)malloc(sizeof(char) * (ft_strlen(haystack) - ft_strlen(needle) + 1));
				ret[ft_strlen(haystack) - ft_strlen(needle)] = 0;
				k = -1;
				while (++k != i)
					ret[k] = haystack[k];
				i += j;
				while (haystack[++i])
					ret[k++] = haystack[i];
				free(haystack);
				free(needle);
				return (ret);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*add_exp(char *needle, char *haystack, char *val)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	ret = NULL;
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && haystack[i + j])
		{
			if (needle[j + 1] == 0 && (haystack[i + j + 1] == '\'' || haystack[i + j + 1] == '"' || haystack[i + j + 1] == ' ' || !haystack[i + j + 1]))
			{
				ret = (char *)malloc(sizeof(char) * (ft_strlen(haystack) - ft_strlen(needle) + ft_strlen(val) + 1));
				ret[ft_strlen(haystack) - ft_strlen(needle) + ft_strlen(val)] = 0;
				k = -1;
				while (++k != i)
					ret[k] = haystack[k];
				i += j;
				j = 0;
				while (val[j])
					ret[k++] = val[j++];
				while (haystack[++i])
					ret[k++] = haystack[i];
				free(haystack);
				free(needle);
				return (ret);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

t_lexer	*reorder(t_lexer *input)
{
	char	*tmp;
	t_lexer	*head;

	head = input;
	tmp = NULL;
	while (head)
	{
		printf("\n\n-----\n\n");
		for (int i = 0; head->arg[i]; i++)
			printf("%s\n", head->arg[i]);
		printf("\n-----\n\n");
		tmp = flatten_arr_w_space(head->arg);
		printf("\n\n+++++\n%s\n+++++\n\n", tmp);
		head->arg = split2(tmp, ' ');
		free(tmp);
		head = head->next;
	}
	input = requote(input);
	return (input);
}
