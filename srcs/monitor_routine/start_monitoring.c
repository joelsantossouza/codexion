/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:37:06 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/15 09:32:48 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "codexion.h"

void	*start_monitoring(t_coder coders[])
{
	uint32_t	ncoders;
	uint32_t	dongle_cooldown;
	uint32_t	ncompiles_required;
	t_scheduler	scheduler;

	get_monitor_rules(&ncoders, &dongle_cooldown, &ncompiles_required, &scheduler);
	while (TRUE)
		if (scheduler(ncoders, coders, dongle_cooldown, ncompiles_required) != 0)
			break ;
	return (0);
}
