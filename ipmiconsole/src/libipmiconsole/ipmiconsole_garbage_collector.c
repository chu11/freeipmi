/*****************************************************************************\
 *  $Id: ipmiconsole_garbage_collector.c,v 1.5 2007-08-28 18:26:19 chu11 Exp $
 *****************************************************************************
 *  Copyright (C) 2006 The Regents of the University of California.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Albert Chu <chu11@llnl.gov>
 *  UCRL-CODE-221226
 *  
 *  This file is part of Ipmiconsole, a set of IPMI 2.0 SOL libraries
 *  and utilities.  For details, see http://www.llnl.gov/linux/.
 *  
 *  Ipmiconsole is free software; you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by the 
 *  Free Software Foundation; either version 2 of the License, or (at your 
 *  option) any later version.
 *  
 *  Ipmiconsole is distributed in the hope that it will be useful, but 
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License 
 *  for more details.
 *  
 *  You should have received a copy of the GNU General Public License along
 *  with Ipmiconsole; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA.
\*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <stdlib.h>
#if STDC_HEADERS
#include <string.h>
#endif /* STDC_HEADERS */
#if HAVE_PTHREAD_H
#include <pthread.h>
#endif /* HAVE_PTHREAD_H */
#if TIME_WITH_SYS_TIME
#include <sys/time.h>
#include <time.h>
#else  /* !TIME_WITH_SYS_TIME */
#if HAVE_SYS_TIME_H
#include <sys/time.h>
#else /* !HAVE_SYS_TIME_H */
#include <time.h>
#endif  /* !HAVE_SYS_TIME_H */
#endif /* !TIME_WITH_SYS_TIME */
#include <assert.h>
#include <errno.h>

#include "ipmiconsole.h"
#include "ipmiconsole_defs.h"

#include "list.h"
#include "ipmiconsole_ctx.h"
#include "ipmiconsole_debug.h"
#include "ipmiconsole_engine.h"

extern List console_engine_ctxs_to_destroy;
extern pthread_mutex_t console_engine_ctxs_to_destroy_mutex;
extern int garbage_collector_notifier[2];

#define IPMICONSOLE_GARBAGE_COLLECTOR_SPIN_TIME 30

void *
ipmiconsole_garbage_collector(void *arg)
{
  while (1)
    {
      ListIterator itr = NULL;
      ipmiconsole_ctx_t c;
      struct timeval tv;
      int perr;
      int n;
      fd_set rds;

      FD_ZERO(&rds);
      FD_SET(garbage_collector_notifier[0], &rds);

      tv.tv_sec = IPMICONSOLE_GARBAGE_COLLECTOR_SPIN_TIME;
      tv.tv_usec = 0;
      
      /* What happens if anythings fails?  
       *
       * Quit - well that's bad.
       *
       * Mem-leak - that's bad too.
       *
       * For now, just log.
       */

      if ((n = select(garbage_collector_notifier[0] + 1, &rds, NULL, NULL, &tv)) < 0)
        {
          IPMICONSOLE_DEBUG(("select: %s", strerror(errno)));
          continue;
        }

      /* Signal from ipmiconsole_engine_teardown() to quit */
      if (n && FD_ISSET(garbage_collector_notifier[0], &rds))
        break;
      
      /* Note: the code in _ipmiconsole_ctx_connection_cleanup() and
       * ipmiconsole_garbage_collector() may look like it may race and
       * could deadlock.  (ABBA and BAAB deadlock situation).  However,
       * the context mutexes c->destroyed_mutex are accessed from two
       * different lists.  So the c->destroyed_mutex context can never be
       * raced against in these two functions.
       */

      if ((perr = pthread_mutex_lock(&(console_engine_ctxs_to_destroy_mutex))) != 0)
        IPMICONSOLE_DEBUG(("pthread_mutex_lock: %s", strerror(perr)));

      if (!(itr = list_iterator_create(console_engine_ctxs_to_destroy)))
        {
          IPMICONSOLE_DEBUG(("list_iterator_create: %s", strerror(errno)));
          goto end_loop;
        }
      
      while ((c = (ipmiconsole_ctx_t)list_next(itr)))
        {
          if ((perr = pthread_mutex_lock(&(c->signal.destroyed_mutex))) != 0)
            IPMICONSOLE_DEBUG(("pthread_mutex_lock: %s", strerror(perr)));

          /* Be careful, if the user requested to destroy the context, we can
           * destroy it here.  But if we destroy it, there is no mutex to
           * unlock.
           */
          if (c->signal.user_has_destroyed)
            ipmiconsole_ctx_cleanup(c);
          else
            {
              if ((perr = pthread_mutex_unlock(&(c->signal.destroyed_mutex))) != 0)
                IPMICONSOLE_DEBUG(("pthread_mutex_unlock: %s", strerror(perr)));
            }
        }

      if ((perr = pthread_mutex_unlock(&(console_engine_ctxs_to_destroy_mutex))) != 0)
        IPMICONSOLE_DEBUG(("pthread_mutex_unlock: %s", strerror(perr)));

    end_loop:
      if (itr)
        list_iterator_destroy(itr);
    }

  return NULL;
}
