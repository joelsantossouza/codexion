/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:58:46 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/06 16:04:48 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <string.h>

int	is_str_numeric(const char *str)
{
	str += *str == '-' || *str == '+';
	if (!*str)
		return (FALSE);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

int	nbrcmp(const char *nbr1, const char *nbr2)
{
	int	cmp;
	int	sign;

	while (*nbr1 == ' ' || (*nbr1 >= '\t' && *nbr1 <= '\r'))
		nbr1++;
	while (*nbr2 == ' ' || (*nbr2 >= '\t' && *nbr2 <= '\r'))
		nbr2++;
	cmp = (*nbr2 == '-') - (*nbr1 == '-');
	if (cmp != 0)
		return (cmp);
	sign = 1 - 2 * (*nbr1 == '-');
	nbr1 += *nbr1 == '-' || *nbr1 == '+';
	nbr2 += *nbr2 == '-' || *nbr2 == '+';
	while (*nbr1 == '0')
		nbr1++;
	while (*nbr2 == '0')
		nbr2++;
	while (*nbr1 == *nbr2 && *nbr1 && (nbr1++, nbr2++))
		;
	cmp = strlen(nbr1) - strlen(nbr2);
	if (cmp != 0)
		return (cmp * sign);
	return ((*nbr1 - *nbr2) * sign);
}
