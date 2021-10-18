/*
 * Copyright (C) 2015 Niek Linnenbank
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Log.h>
#include "Kernel.h"
#include "Scheduler.h"

Scheduler::Scheduler()
{
    DEBUG("");
}

Size Scheduler::count() const
{
    Size size; 
    size = m_queue_min.count() + m_queue_default.count() + m_queue_max.count();
    return size;
}

Scheduler::Result Scheduler::enqueue(Process *proc, bool ignoreState)
{
    if (proc->getState() != Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " not in Ready state");
        return InvalidArgument;
    }

    int priority = proc->getPriority(); 
    Scheduler::Result result; 

    switch (priority)
    {
    case 1:
        m_queue_min.push(proc);
        result = Success;
        break;
    case 3:
        m_queue_default.push(proc);
        result = Success;
        break;
    case 5:
        m_queue_max.push(proc);
        result = Success;
        break;
    default:
        break;
    }

    return result;
}

Scheduler::Result Scheduler::dequeue(Process *proc, bool ignoreState)
{
    if (proc->getState() == Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " is in Ready state");
        return InvalidArgument;
    }

    Size min_count = m_queue_min.count();
    Size default_count = m_queue_default.count();
    Size max_count = m_queue_max.count();

    // Traverse the min Queue to remove the Process
    for (Size i = 0; i < min_count; i++)
    {
        Process *p = m_queue_min.pop();

        if (p == proc)
            return Success;
        else
            m_queue_min.push(p);
    }

    // Traverse the default Queue to remove the Process
    for (Size i = 0; i < default_count; i++)
    {
        Process *p = m_queue_default.pop();

        if (p == proc)
            return Success;
        else
            m_queue_default.push(p);
    }

    // Traverse the max Queue to remove the Process
    for (Size i = 0; i < max_count; i++)
    {
        Process *p = m_queue_max.pop();

        if (p == proc)
            return Success;
        else
            m_queue_max.push(p);
    }

    FATAL("process ID " << proc->getID() << " is not in the schedule");
    return InvalidArgument;
}

Process * Scheduler::select()
{
    Process *p; 

    if(m_queue_max.count() > 0){
        p = m_queue_max.pop();
        m_queue_max.push(p);
        return p; 
    }else if(m_queue_default.count() > 0){
        p = m_queue_default.pop(); 
        m_queue_default.push(p);
        return p; 
    }else if(m_queue_min.count() > 0 ){
        p = m_queue_min.pop(); 
        m_queue_min.push(p);
        return p; 
    }

    return (Process *) NULL;
}
