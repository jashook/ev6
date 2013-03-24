////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: entry_point.hpp
//
// Modifications: 
//
// 21-March-13: Version 1.5: Updated to ev6 and cleaned up code
// 20-July-12: Version 1.0: Created
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef __ENTRY_POINT_HPP__
#define __ENTRY_POINT_HPP__

#include "rti.hpp"
#include "thread.hpp"
#include "triad.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {
namespace mts {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
typedef unsigned start_thread_return_t;
template <typename __Type> unsigned __stdcall _start_thread(void* _StartArg)
#else   // POSIX
typedef void* start_thread_return_t;
template <typename __Type> void* _start_thread(void* _StartArg)
#endif
{
   // step into from OS

   if(ev6::el::are_same_type<ev6::el::mts::thread<__Type>::f_general_function, __Type>())
   {
      std::pair<ev6::el::mts::thread<__Type>*, ev6::el::mts::thread<__Type>::f_general_function> _Pair = *(reinterpret_cast<std::pair<ev6::el::mts::thread<__Type>*, ev6::el::mts::thread<__Type>::f_general_function>*>(_StartArg));

      delete _StartArg;

      ev6::el::mts::thread<__Type>* _Thread = _Pair.first;

      _Thread->set_active(true);
      _Thread->set_alive(true);

      _StartArg = _Thread->get_start_arg();

      ev6::el::mts::thread<__Type>::f_general_function _Function = _Pair.second;

      int _ExitCode = _Function(_StartArg);

      _Thread->set_active(false);
      _Thread->set_alive(false);

      return (start_thread_return_t) _ExitCode;
   }

   else
   {
      ev6::el::triad<ev6::el::mts::thread<__Type>*, __Type, void*> _Triad = *(reinterpret_cast<ev6::el::triad<ev6::el::mts::thread<__Type>*, __Type, void*>*>(_StartArg));

      delete _StartArg;

      ev6::el::mts::thread<__Type>* _Thread = _Triad.first;

      _Thread->set_active(true);
      _Thread->set_alive(true);

      _StartArg = _Triad.third;

      int _ExitCode = _Triad.second(_StartArg);

      _Thread->set_active(false);
      _Thread->set_alive(false);

      return (start_thread_return_t) _ExitCode;
   }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end of namespace mts
}   // end of namespace el
}   // end of namespace ev6

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __ENTRY_POINT_HPP__
