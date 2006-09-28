/*  object_stack.h - this file is part of MediaTomb.
                                                                                
    Copyright (C) 2005 Gena Batyan <bgeradz@deadlock.dhs.org>,
                       Sergey Bostandzhyan <jin@deadlock.dhs.org>
                                                                                
    MediaTomb is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
                                                                                
    MediaTomb is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
                                                                                
    You should have received a copy of the GNU General Public License
    along with MediaTomb; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __ZMMF_OBJECT_STACK_H__
#define __ZMMF_OBJECT_STACK_H__

#include "zmm/zmm.h"
#include "memory.h"
#include "base_stack.h"

namespace zmm
{
    template <class T>
    class ObjectStack : public BaseStack<Object *>
    {
    public:
        ObjectStack(int initialCapacity) : BaseStack<Object *>(initialCapacity, NULL)
        {
        }
        
        ~ObjectStack()
        {
            Object *obj;
            while(NULL != (obj = BaseStack<Object *>::pop()))
            {
                log_debug("releasing!\n");
                obj->release();
            }
        }
        
        inline void push(Ref<T> element)
        {
            Object *obj = element.getPtr();
            obj->retain();
            BaseStack<Object *>::push(obj);
        }
        
        inline Ref<T> pop()
        {
            Object *obj = BaseStack<Object *>::pop();
            if (obj == NULL)
                return nil;
            Ref<T> ret((T *)obj);
            obj->release();
            return ret;
        }
    };
}

#endif // __ZMMF_OBJECT_STACK_H__
