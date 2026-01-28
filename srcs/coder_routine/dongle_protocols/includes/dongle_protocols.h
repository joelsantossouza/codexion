/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_protocols.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:32:28 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/28 12:38:56 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_PROTOCOLS_H
# define DONGLE_PROTOCOLS_H

# include <stdint.h>

# define QUEUE_SIZE	3

typedef struct s_dongle_queue
{
	t_coder		*coders[QUEUE_SIZE];
	uint32_t	head;
	uint32_t	tail;
}	t_dongle_queue;

typedef struct s_dongle
{
	uint64_t		last_release_ms;
	t_dongle_queue	queue;
}	t_dongle;

#endif
