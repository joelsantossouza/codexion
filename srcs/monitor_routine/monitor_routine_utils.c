/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:26:20 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/20 10:00:39 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "private_monitor_routine.h"
#include "mutex_log_msg.h"

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
	}
	if (burned_out_coder)
		mutex_log_msg(time_elapsed(NULL), burned_out_coder->id,  BURNOUT_MSG, burned_out_coder->global_mutex);
	return (NULL);
}

// int	required_compilations(t_coder *coder, const t_monitor_config *new_config)
// {
// 	static uint32_t	total_coders;
// 	static uint32_t	compiles_required;
// 	static uint32_t	finished_coders_count;
// 
// 	if (new_config)
// 	{
// 		total_coders = new_config->ncoders;
// 		compiles_required = new_config->ncompiles_required;
// 		finished_coders_count = 0;
// 	}
// 	pthread_mutex_lock(&coder->local_mutex);
// 	if (coder->state & WAITING_TO_COMPILE)
// 		finished_coders_count += coder->compilations_done == compiles_required;
// 	pthread_mutex_unlock(&coder->local_mutex);
// 	return (finished_coders_count == total_coders);
// }
