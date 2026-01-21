/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schedule_fifo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 10:00:43 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/21 22:25:48 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <pthread.h>
#include "private_monitor_routine.h"

int	schedule_fifo(t_coder coders[], const t_monitor_config *config, uint32_t *available_dongles, t_coder **priority_coder)
{
	const uint32_t	ncoders = config->ncoders;
	const uint32_t	ncompiles_required = config->ncompiles_required;
	const uint32_t	dongle_cooldown = config->dongle_cooldown;
	uint32_t		coders_with_required_compilations;
	uint32_t		i;

	// *priority_coder = &coders[priority_coder_idx];
	// pthread_mutex_lock(&(*priority_coder)->local_mutex);
	// priority_coder_idx += ((*priority_coder)->state & WAITING_TO_COMPILE) == 0;
	// priority_coder_idx %= config->ncoders;
	// pthread_mutex_unlock(&(*priority_coder)->local_mutex);
	coders_with_required_compilations = 0;
	i = -1;
	while (++i < ncoders)
	{
		pthread_mutex_lock(&coders[i].local_mutex);
		if (coders[i].execution_remaining == 0)
		{
			pthread_mutex_unlock(&coders[i].local_mutex);
			return (*priority_coder = &coders[i], STOP_SIMULATION);
		}
		coders_with_required_compilations += coders[i].compilations_done >= ncompiles_required;
		*available_dongles += collect_released_dongles(&coders[i].compilations_history, dongle_cooldown);
		pthread_mutex_unlock(&coders[i].local_mutex);
	}
	if (coders_with_required_compilations == ncoders)
		return (*priority_coder = NULL, STOP_SIMULATION);
	return (CONTINUE_SIMULATION);
}
