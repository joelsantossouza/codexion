/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:37:06 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/14 19:29:04 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "codexion.h"

void	*start_monitoring(t_coder coders[])
{
	uint32_t	ncoders;
	uint32_t	dongle_cooldown;
	uint32_t	ncompiles_required;
	t_monitor	monitor;

	get_monitor_rules(&ncoders, &dongle_cooldown, &ncompiles_required, &monitor);
	while (TRUE)
		if (monitor(ncoders, coders, dongle_cooldown, ncompiles_required) != 0)
			break ;
	return (0);
}
