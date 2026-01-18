/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:37:06 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/18 13:04:33 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "codexion.h"
#include "monitor_routine.h"

void	*start_monitoring(t_coder coders[])
{
	t_scheduler	scheduler;
	uint32_t	ncoders;
	uint32_t	dongle_cooldown;
	uint32_t	ncompiles_required;
	uint32_t	available_dongles;

	monitor_config(&ncoders, &dongle_cooldown, &ncompiles_required, &scheduler);
	available_dongles = ncoders;
	while (TRUE)
		if (scheduler(&available_dongles, ncoders, coders, dongle_cooldown) >= ncompiles_required)
			break ;
	return (0);
}
