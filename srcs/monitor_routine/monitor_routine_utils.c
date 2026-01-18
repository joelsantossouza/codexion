/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:26:20 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/18 20:15:26 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "private_monitor_routine.h"

const t_monitor_config	*monitor_config(uint32_t *ncoders, uint32_t *dongle_cooldown, uint32_t *ncompiles_required, t_scheduler *scheduler)
{
	static t_monitor_config	monitor_config;

	if (ncoders)
		monitor_config.ncoders = *ncoders;
	if (dongle_cooldown)
		monitor_config.dongle_cooldown = *dongle_cooldown;
	if (ncompiles_required)
		monitor_config.ncompiles_required = *ncompiles_required;
	if (scheduler)
		monitor_config.scheduler = *scheduler;
	return ((const t_monitor_config *)&monitor_config);
}
