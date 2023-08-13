/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:52:44 by eunwolee          #+#    #+#             */
/*   Updated: 2023/04/22 14:58:31 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_split(char const *s, char c);
static int	cnt_str(char const *s, int c);
static int	exe_split(char **dest, const char *s, char c, int *idx);
static int	cnt_len(char const *s, char c);
static char	**clear(char **dest, int idx);

char	**ft_split(char const *s, char c)
{
	int		idx;
	int		cnt;
	char	**dest;

	cnt = cnt_str(s, c);
	dest = (char **)ft_calloc(cnt + 1, sizeof(char *));
	if (!dest)
		return (0);
	if (!cnt)
		dest[0] = ft_strdup("");
	else
	{
		idx = 0;
		if (exe_split(dest, s, c, &idx) == -1)
			return (clear(dest, idx));
	}
	return (dest);
}

static int	cnt_str(char const *s, int c)
{
	int	cnt;
	int	len;

	cnt = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			len = cnt_len(s, c);
			cnt++;
			s += len;
		}
	}
	return (cnt);
}

static int	exe_split(char **dest, const char *s, char c, int *idx)
{
	int	size;

	*idx = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			size = cnt_len(s, c);
			dest[*idx] = ft_substr(s, 0, size);
			if (!dest[*idx])
				return (-1);
			s += size;
			*idx += 1;
		}
	}
	return (0);
}

static int	cnt_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	return (len);
}

static char	**clear(char **dest, int idx)
{
	while (idx--)
		free (dest[idx]);
	free (dest);
	return (0);
}
