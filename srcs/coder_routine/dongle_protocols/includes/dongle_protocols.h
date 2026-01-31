/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_protocols.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:32:28 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/31 16:15:03 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_PROTOCOLS_H
# define DONGLE_PROTOCOLS_H

# include <stdint.h>
# include "dongle_queue.h"
# include "simulation_control.h"

typedef struct s_coder t_coder;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	const uint64_t	*cooldown;
	uint64_t		cooldown_end_ms;
	t_dongle_queue	queue;
}	t_dongle;

int							init_dongles(uint32_t ndongles, t_dongle dongles[ndongles]);
int							destroy_dongles(uint32_t ndongles, t_dongle dongles[ndongles]);
enum e_simulation_status	request_two_dongles(t_coder *coder);
void						release_two_dongles(t_coder *coder);

#endif
