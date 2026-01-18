/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:46:00 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/18 14:07:04 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_ROUTINE_H
# define MONITOR_ROUTINE_H

# include <stdint.h>
# include "codexion.h"

typedef struct s_monitor_config
{
	uint32_t	ncoders;
	uint32_t	dongle_cooldown;
	uint32_t	ncompiles_required;
	t_scheduler	scheduler;
}	t_monitor_config;

const t_monitor_config	*monitor_config(uint32_t *ncoders, uint32_t *dongle_cooldown, uint32_t *ncompiles_required, t_scheduler *scheduler);

#endif
