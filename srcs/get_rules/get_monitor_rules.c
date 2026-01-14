/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_monitor_rules.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:26:20 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/14 10:10:18 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdint.h>

int	get_monitor_rules(uint32_t *ncoders, uint32_t *cooldown, uint32_t *ncompiles_required, t_monitor *monitor_func)
{
	static uint8_t		already_initialized = FALSE;
	static uint32_t		number_of_coders;
	static uint32_t		dongle_cooldown;
	static uint32_t		number_of_compiles_required;
	static t_monitor	monitor;

	if (already_initialized == FALSE)
	{
		already_initialized = TRUE;
		number_of_coders = *ncoders;
		dongle_cooldown = *cooldown;
		number_of_compiles_required = *ncompiles_required;
		monitor = *monitor_func;
		return (FALSE);
	}
	*ncoders = number_of_coders;
	*cooldown = dongle_cooldown;
	*ncompiles_required = number_of_compiles_required;
	*monitor_func = monitor;
	return (TRUE);
}
