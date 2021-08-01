/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narakely <narakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:28:50 by narakely          #+#    #+#             */
/*   Updated: 2021/07/06 17:49:06 by narakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			length;
	char		*newstr;

	length = ft_strlen(s1) + ft_strlen(s2);
	newstr = (char*)malloc(length + 1);
	if (newstr != NULL)
	{
		while (*s1)
		{
			*newstr = *s1;
			s1++;
			newstr++;
		}
		while (*s2)
		{
			*newstr = *s2;
			s2++;
			newstr++;
		}
		*newstr = '\0';
		return (newstr - length);
	}
	return (NULL);
}
