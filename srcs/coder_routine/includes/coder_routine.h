/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:58:30 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/09 16:04:04 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_ROUTINE_H
# define CODER_ROUTINE_H

# include <stdint.h>
# include <pthread.h>

# define COMPILING_MSG		"Compiling"
# define DEBUGGING_MSG		"Debugging"
# define REFACTORING_MSG	"Refactoring"

void	log_message(uint64_t timestamp_in_ms, uint32_t coder_id, const char *msg, pthread_mutex_t *mutex);

#endif
