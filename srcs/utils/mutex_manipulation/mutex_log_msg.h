/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_log_msg.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:57:14 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/18 14:14:04 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_MESSAGE_H
# define LOG_MESSAGE_H

#include <stdint.h>
#include <pthread.h>
#include <stdio.h>

# define TAKEN_DONGLE_MSG	"Has taken 1 dongle"
# define COMPILING_MSG		"Compiling"
# define DEBUGGING_MSG		"Debugging"
# define REFACTORING_MSG	"Refactoring"

static inline
void	mutex_log_msg(uint64_t timestamp_in_ms, uint32_t coder_id, const char *msg, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("%lu %d %s\n", timestamp_in_ms, coder_id, msg);
	pthread_mutex_unlock(mutex);
}

#endif
