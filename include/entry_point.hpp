////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        entry_point
//
// Version:       1.0
//
// Modifications: 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef ENTRY_POINT_HPP
#define ENTRY_POINT_HPP

#include "rti.hpp"
#include "thread.hpp"
#include "triad.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {
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

   if(ev4::are_same_type<ev4::mts::thread<__Type>::f_general_function, __Type>())
   {
      std::pair<ev4::mts::thread<__Type>*, ev4::mts::thread<__Type>::f_general_function> _Pair = *(reinterpret_cast<std::pair<ev4::mts::thread<__Type>*, ev4::mts::thread<__Type>::f_general_function>*>(_StartArg));

      delete _StartArg;

      ev4::mts::thread<__Type>* _Thread = _Pair.first;

      _Thread->set_active(true);
      _Thread->set_alive(true);

      _StartArg = _Thread->get_start_arg();

      ev4::mts::thread<__Type>::f_general_function _Function = _Pair.second;

      int _ExitCode = _Function(_StartArg);

      _Thread->set_active(false);
      _Thread->set_alive(false);

      return (start_thread_return_t) _ExitCode;
   }

   else
   {
      ev4::triad<ev4::mts::thread<__Type>*, __Type, void*> _Triad = *(reinterpret_cast<ev4::triad<ev4::mts::thread<__Type>*, __Type, void*>*>(_StartArg));

      delete _StartArg;

      ev4::mts::thread<__Type>* _Thread = _Triad.first;

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

}
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif