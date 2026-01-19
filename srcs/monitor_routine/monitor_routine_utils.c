/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:26:20 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/19 10:35:54 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "private_monitor_routine.h"
#include "mutex_log_msg.h"

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

void	stop_simulation(uint64_t size, t_coder coders[size], t_coder *burned_out_coder)
{
	while (size--)
	{
		pthread_mutex_lock(&coders[size].local_mutex);
		coders[size].execution_remaining = 0;
		pthread_mutex_unlock(&coders[size].local_mutex);
	}
	if (burned_out_coder)
		mutex_log_msg(time_elapsed(NOW), burned_out_coder->id,  BURNOUT_MSG, burned_out_coder->global_mutex);
}

int	required_compilations(t_coder *coder, uint32_t *set_ncompiles_required_per_coder, uint32_t *set_ncoders)
{
	static uint32_t	ncoders;
	static uint32_t	ncompiles_required_per_coder;
	static uint32_t	coders_finished_compilations;

	if (set_ncompiles_required_per_coder)
	{
		ncompiles_required_per_coder = *set_ncompiles_required_per_coder;
		coders_finished_compilations = 0;
	}
	if (set_ncoders)
	{
		ncoders = *set_ncoders;
		coders_finished_compilations = 0;
	}
	pthread_mutex_lock(&coder->local_mutex);
	if (coder->state & WAITING_TO_COMPILE)
		coders_finished_compilations += coder->compilations_done == ncompiles_required_per_coder;
	pthread_mutex_unlock(&coder->local_mutex);
	return (coders_finished_compilations == ncoders);
}
