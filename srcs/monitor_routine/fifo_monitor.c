/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 10:00:43 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/14 10:05:19 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "codexion.h"

int	fifo_monitor(uint32_t size, t_coder *coders[size], uint32_t dongle_cooldown, uint32_t ncompiles_required)
{
	uint32_t	available_dongles;
	uint64_t	i;

	available_dongles = size;
	i = -1;
	while (++i < size)
	{
		if (coders[i]->state & RELEASE_DONGLES)
		{
			coders[i]->state &= ~(RELEASE_DONGLES);
			available_dongles += TWO_DONGLES;
		}
		if (!(coders[i]->state & WAITING_TO_COMPILE))
			continue ;
		while (!(coders[i]->state & HAS_TWO_DONGLES) && available_dongles > 0)
		{
			available_dongles--;
			coders[i]->state += GIVE_ONE_DONGLE;
		}
	}
}
