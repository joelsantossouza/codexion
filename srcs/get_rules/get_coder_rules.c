/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coder_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:21:57 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/06 21:23:19 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	get_coder_rules(int *burnout, int *compile, int *debug, int *refactor)
{
	static int	already_initialized = FALSE;
	static int	time_to_burnout;
	static int	time_to_compile;
	static int	time_to_debug;
	static int	time_to_refactor;

	if (already_initialized == FALSE)
	{
		already_initialized = TRUE;
		time_to_burnout = *burnout;
		time_to_compile = *compile;
		time_to_debug = *debug;
		time_to_refactor = *refactor;
		return (FALSE);
	}
	*burnout = time_to_burnout;
	*compile = time_to_compile;
	*debug = time_to_debug;
	*refactor = time_to_refactor;
	return (TRUE);
}
