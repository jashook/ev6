////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: queue.hpp
//
// Modifications:
//
// 22-Jan-13: Version 1.2: Cleaned and updated to namespace ev6
// 4-Jan-12 : Version 1.1: Cleaned and changed namespaces
//
// Timeperiod: ev6
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __QUEUE_HPP__
#define __QUEUE_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "linked_list.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {
namespace mta {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template< typename __Type > class queue
{
   private:   // member variables

      linked_list<__Type> _m_list;

      bool _m_finished_flag;

   public:   // member functions

      bool can_pop() { return _can_pop(); }
      bool is_empty() { return _is_empty(); }
      bool finished() { return _finished(); }
      __Type pop() { return _pop(); }
      void push(const __Type& _Data) { _push(const_cast<__Type&>(_Data)); }
      void set_finished_flag(bool _Bool) { _set_finished_flag(_Bool); }
      std::size_t size() { return _size(); }

   public:   // constructor | destructor

      queue() : _m_finished_flag(false) { }

      ~queue() { }

   private:   // helper functions

      bool _can_pop() { return ((_m_list.size() > 5 || _finished()) && _size() > 0 )? true : false; }

      bool _is_empty() { return _m_list.size() == 0; }

      bool _finished() { return _m_finished_flag; }

      __Type _pop() { return _m_list.pop_back(); }

      void _push(__Type& _Data) { _m_list.push_front(_Data); }

      void _set_finished_flag(bool _Bool) { _m_finished_flag = _Bool; }

      std::size_t _size() { return _m_list.size(); }

};   // end of class queue

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end of namespace(ev6)
}   // end of namespace(el)
}   // end of namespace(mta)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __QUEUE_HPP__