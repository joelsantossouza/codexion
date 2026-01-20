/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:26:20 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/20 23:03:36 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "private_monitor_routine.h"
#include "private_coder_routine.h"

const t_monitor_config	*monitor_config(const uint32_t *ncoders, const uint32_t *dongle_cooldown, const uint32_t *ncompiles_required, const t_scheduler *scheduler)
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

void	*stop_simulation(uint32_t size, t_coder coders[size], t_coder *burned_out_coder)
{
	while (size--)
	{
		pthread_mutex_lock(&coders[size].local_mutex);
		coders[size].execution_remaining = 0;
		pthread_mutex_unlock(&coders[size].local_mutex);
		printf("Stoping_simulation of %d\n", size);
	}
	if (burned_out_coder)
		log_coder_activity(burned_out_coder, BURNOUT_MSG);
	return (NULL);
}
