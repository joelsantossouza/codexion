/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo_scheduler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 10:00:43 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/15 09:31:21 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <pthread.h>
#include "codexion.h"

int	fifo_scheduler(uint32_t size, t_coder coders[size], uint32_t dongle_cooldown, uint32_t ncompiles_required)
{
	uint32_t	available_dongles;
	uint32_t	coders_finish_required_compiles;
	uint64_t	i;

	available_dongles = size;
	coders_finish_required_compiles = 0;
	i = -1;
	while (++i < size)
	{
		pthread_mutex_lock(&coders[i].local_mutex);
		available_dongles += coders[i].state & DONGLES_RELEASED;
		coders[i].state &= ~(DONGLES_RELEASED);
		if (coders[i].state & WAITING_TO_COMPILE)
		{
			while (!(coders[i].state & HAS_TWO_DONGLES) && available_dongles > 0)
			{
				available_dongles--;
				coders[i].state += GIVE_ONE_DONGLE;
			}
		}
		coders_finish_required_compiles += coders[i].compilations_done == ncompiles_required;
		pthread_mutex_unlock(&coders[i].local_mutex);
	}
	return (coders_finish_required_compiles == size);
}
