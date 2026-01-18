/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:37:06 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/18 14:25:50 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include "codexion.h"
#include "monitor_routine.h"

void	*start_monitoring(t_coder coders[])
{
	const t_monitor_config	*config = monitor_config(NULL, NULL, NULL, NULL);
	uint32_t				available_dongles;

	available_dongles = config->ncoders;
	while (TRUE)
	{
		if (scheduler(&available_dongles, ncoders, coders, dongle_cooldown) >= ncompiles_required)
			break ;
	}
	return (0);
}
