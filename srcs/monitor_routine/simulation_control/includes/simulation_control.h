/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_control.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:13:34 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/30 15:57:22 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_CONTROL_H
# define SIMULATION_CONTROL_H

# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>

enum e_simulation_status
{
	SIMULATION_RUNNING,
	SIMULATION_STOPPED,
};

enum e_simulation_status	monitored_wait_until(uint64_t wait_until_ms, uint64_t limit_ms);
bool						simulation_control(const bool *set_state);
void						stop_simulation(void);

static inline
bool	is_simulation_running(void)
{
	return (simulation_control(NULL));
}

#endif
