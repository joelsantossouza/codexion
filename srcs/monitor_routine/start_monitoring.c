/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:37:06 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/15 21:25:51 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "codexion.h"

void	*start_monitoring(t_coder coders[])
{
	uint32_t	available_dongles;
	uint32_t	ncoders;
	uint32_t	dongle_cooldown;
	uint32_t	ncompiles_required;
	t_scheduler	scheduler;

	get_monitor_rules(&ncoders, &dongle_cooldown, &ncompiles_required, &scheduler);
	available_dongles = ncoders;
	while (TRUE)
		if (scheduler(&available_dongles, ncoders, coders, dongle_cooldown) >= ncompiles_required)
			break ;
	return (0);
}
