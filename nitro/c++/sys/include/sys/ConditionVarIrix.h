/* =========================================================================
 * This file is part of sys-c++ 
 * =========================================================================
 * 
 * (C) Copyright 2004 - 2009, General Dynamics - Advanced Information Systems
 *
 * sys-c++ is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this program; If not, 
 * see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef __SYS_CONDITION_VAR_IRIX_H__
#define __SYS_CONDITION_VAR_IRIX_H__

#if defined(__sgi) && defined(_REENTRANT) && !defined(__POSIX)

#include <vector>
#include "sys/SyncFactoryIrix.h"
#include "sys/ConditionVarInterface.h"
#include "sys/MutexIrix.h"


namespace sys
{
/*!
 *  \class ConditionVarIrix
 *  \brief The Netscape Portable Runtime condition variable 
 *  implementation
 *
 *  Class using PRCondVar* to implement a condition variable
 */
class ConditionVarIrix :
            public ConditionVarInterface < std::vector< pid_t >,
            MutexIrix >
{
public:
    typedef ConditionVarInterface < std::vector< pid_t >, MutexIrix > Parent_T;


    /*!
     *  This constructor means that you are creating the lock
     *  that you will use inside of the condition variable.
     *  The base class destructor will remove this mutex when we
     *  are destroyed.
     */
    ConditionVarIrix()
    {
        dbg_ln("Creating a default condition variable");
        mMutex = new MutexIrix();
    }

    /*!
     *  This is the sharing constructor.  In synchronized buffers, etc.,
     *  it is often desirable to share the lock that you use.  Here,
     *  we implement such a means.
     *
     *  \param theLock  This is an existing lock that you wish to
     *  use for synchronization purposes
     *
     *  \param isOwner This defaults to false, which means that your
     *  condition variable is not responsible for the deletion of the 
     *  mutex (in other words, you must delete the mutex explicitly.
     *  If you set this parameter to true, you may actually be sharing
     *  a lock, but this class will STILL delete it.
     *
     */
    ConditionVarIrix(MutexIrix *theLock, bool isOwner = false) :
            Parent_T(theLock, isOwner)
    {
        dbg_ln("Creating a cv given a mutex");
    }

    /*!
     *  Destroy the native CV
    B
     */
    virtual ~ConditionVarIrix();

    /*!
     *  Signal a condition
     *  \return true upon success, false on failure
     */
    virtual bool signal();

    /*!
     *  Wait on a condition
     *  \return true upon success, false on failure
     *
     *  WARNING: The user is responsible for locking the mutex prior 
     *           to using this method. There will be no check and on 
     *           certain systems, undefined/unfavorable behavior may 
     *           result.
     */
    virtual bool wait();

    /*!
     *  Timed wait on a condition
     *  \param seconds  The number of seconds to wait as a fraction
     *
     *  WARNING: The user is responsible for locking the mutex prior 
     *           to using this method. There will be no check and on 
     *           certain systems, undefined/unfavorable behavior may 
     *           result.
     */
    virtual bool wait(double seconds);


    /*!
     *  Broadcast operation
     *  \return bool true on success, false on failure
     */
    virtual bool broadcast();

};

}

#  endif
#endif
