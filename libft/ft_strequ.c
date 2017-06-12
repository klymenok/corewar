/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhlopov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 16:39:12 by dkhlopov          #+#    #+#             */
/*   Updated: 2016/11/28 19:03:30 by dkhlopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strequ(char const *s1, char const *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2 && (*s1 == *s2))
	{
		if (*(++s1) != *(++s2))
			return (0);
	}
	if ((*s1 == *s2) && !*s1 && !*s2)
		return (1);
	else
		return (0);
}