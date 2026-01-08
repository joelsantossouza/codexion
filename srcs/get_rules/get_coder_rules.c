/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coder_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:21:57 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/08 18:02:29 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdint.h>

int	get_coder_rules(uint32_t *burnout, uint32_t *compile, uint32_t *debug, uint32_t *refactor)
{
	static uint8_t	already_initialized = FALSE;
	static uint32_t	time_to_burnout;
	static uint32_t	time_to_compile;
	static uint32_t	time_to_debug;
	static uint32_t	time_to_refactor;

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
