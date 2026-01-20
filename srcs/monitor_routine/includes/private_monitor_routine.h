/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_monitor_routine.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:46:00 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/20 19:17:12 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_ROUTINE_H
# define MONITOR_ROUTINE_H

# include <stdint.h>
# include "time_manipulation.h"
# include "public_coder_routine.h"

enum
{
	CONTINUE_SIMULATION,
	STOP_SIMULATION
};

typedef struct s_monitor_config t_monitor_config;
typedef int	(*t_scheduler)(t_coder coders[], const t_monitor_config *config, uint32_t *available_dongles, t_coder **priority_coder);

typedef struct s_monitor_config
{
	uint32_t	ncoders;
	uint32_t	dongle_cooldown;
	uint32_t	ncompiles_required;
	t_scheduler	scheduler;
}	t_monitor_config;

const t_monitor_config	*monitor_config(const uint32_t *ncoders, const uint32_t *dongle_cooldown, const uint32_t *ncompiles_required, const t_scheduler *scheduler);
void					*stop_simulation(uint32_t size, t_coder coders[size], t_coder *burned_out_coder);
int						schedule_fifo(t_coder coders[], const t_monitor_config *config, uint32_t *available_dongles, t_coder **priority_coder);

static inline
__attribute__((always_inline))
uint32_t	collect_released_dongles(t_queue *compilations_history, uint32_t dongle_cooldown)
{
	uint64_t	oldest_compilation;

	if (queue_peek(compilations_history, &oldest_compilation) == EMPTY_QUEUE_ERROR)
		return (0);
	if (millis() - oldest_compilation < dongle_cooldown)
		return (0);
	compilations_history->first = (compilations_history->first + 1) % BUFFER_SIZE;
	return (TWO_DONGLES);
}

#endif
