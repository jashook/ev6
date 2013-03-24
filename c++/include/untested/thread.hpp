////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        thread
//
// Version:       1.0
//
// Modifications: 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __THREAD_HPP__
#define __THREAD_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <string>

#ifdef _WIN32
   #include <Windows.h>
   #include <WinDef.h>
#endif

#include "base.hpp"
#include "entry_point.hpp"
#include "triad.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {
namespace mts {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
   typedef std::size_t tid_t;
#else   // POSIX
   typedef std::size_t tid_t;
   typedef pthread_t tid_t;
#endif
   
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template<typename __Type> class thread
{
   public:   // type definitions and constants

      typedef int (*f_general_function)(void*);

   private:   // member variables

      int _m_exit_code;
      volatile bool _m_is_active;
      volatile bool _m_is_alive;

      tid_t _m_tid;

      #ifdef _WIN32
         HANDLE _m_handle;
      #endif

   protected:

      void* _m_start_arg;

   public:   // member functions

      void* get_start_arg() { return _get_start_arg(); }
      bool is_active() { return _is_active(); }
      bool is_alive() { return _is_alive(); }
      void join() throw(std::exception) { try { _os_specific_join(); } catch (...) { throw; } }
      int run(void* _StartArg = NULL);
      void set_active(bool _Value) { _set_active(_Value); }
      void set_alive(bool _Value) { _set_alive(_Value); }
      void sleep(std::size_t _Milliseconds) const throw() { try { _sleep(_Milliseconds); } catch (...) { throw; } }
      void start(f_general_function _Function, std::size_t _StackSize = 0) throw(std::exception) { try { return _start(_Function, _StackSize); } catch (...) { throw; } }
      void start(__Type& _Functor, void* _StartArg, std::size_t _StackSize = 0) throw(std::exception) { try { return _start(_Functor, _StartArg, _StackSize); } catch (...) { throw; } }

   public:   // constructor | destructor
      

      thread(void* _StartArg) { _ctor(_StartArg); }

      thread() { }

      ~thread() { _dtor(); }

   private:   // os specific helper functions

      #ifdef _WIN32

         void _os_specific_join()
         {
            WaitForSingleObject(_m_handle, INFINITE);
         }

         void _os_specific_start(void* _StartArg, std::size_t _StackSize) throw(std::exception)
         {
            _m_handle = (HANDLE) _beginthreadex(NULL, _StackSize, ev6::el::mts::_start_thread<__Type>, (void*) _StartArg, (unsigned) 0, (unsigned*) &_m_tid);

            if (_m_handle == NULL)
            {
               // error
               throw std::runtime_error("");
            }
         }

      #else   // POSIX
         
         void _os_join() throw(std::exception)
         {
            void* _ExitCode = NULL;

            if (pthread_join(_m_tid, &_ExitCode != 0))
            { 
               throw std::runtime_error("[ev6::el::mts::start::_os_join] pthread_join failed");
            }

            _set_exit_code(static_cast<int>(reinterpret_cast<long long>(_ExitCode)));
         }

         void _os_start(void* _StartArg, std::size_t _StackSize) throw(std::exception)
         {
            if (_StackSize > 0)
            {
               pthread_attr_t _Attributes;

               if (pthread_attr_init(&_Attributes) != 0)
               {
                  throw std::runtime_error("[ev6::el::mts::start::_os_start] pthread_attr_init failed");
               }

               if (pthread_attr_setstacksize(&_Attributes, _StackSize) != 0)
               {
                  throw std::runtime_error("[ev6::el::mts::start::_start::_os_start] pthread_attr_setstacksize failed");
               }

               if (pthread_create(&_m_tid, &_Attributes, ev6::el::mts::_start_thread<__Type>, (void*) _StartArg) != 0)
               {
                  throw std::runtime_error("[ev6::el::mts::start::_start::_os_start] pthread_create failed");
               }

               if (pthread_attr_destroy(&_Attributes) != 0)
               {
                  throw std::runtime_error("[ev6::el::mts::start::_start::_os_start] pthread_attr_destroy failed");
               
               }

            }

            else
            {
               if (pthread_create(&_m_tid, (pthread_attr_t*) NULL, ev6::el::mts::_start_thread<__Type>, (void*) _StartArg) != 0)
               {
                  throw std::runtime_error("[ev6::el::mts::start::_start::_os_start] pthread create failed");
               }
            }

         }

      #endif

   private:   // helper functions

      void _ctor(void* _StartArg) { _m_start_arg = _StartArg; }
      void _dtor() { }

      void* _get_start_arg() { return _m_start_arg; }
      bool _is_active() { return _m_is_active; }
      bool _is_alive() { return _m_is_alive; }
      void _set_active(bool _Value) { _m_is_active = _Value; }
      void _set_alive(bool _Value) { _m_is_alive = _Value; }

      void _start(f_general_function _Function, std::size_t _StackSize) throw(std::exception)
      {
         try
         {
            std::pair<ev6::el::mts::thread<__Type>*, void*>* _Pair = new std::pair<ev6::el::mts::thread<__Type>*, void*>(this, _Function);

            return _os_specific_start(reinterpret_cast<void*>(_Pair), _StackSize);
         }
         catch (...)
         {
            throw;
         }
      }

      void _start(__Type& _Functor, void* _StartArg, std::size_t _StackSize) throw(std::exception)
      {
         try
         {
            ev6::el::triad<ev6::el::mts::thread<__Type>*, __Type, void*>* _Triad = new ev6::el::triad<ev6::el::mts::thread<__Type>*, __Type, void*>(this, _Functor, _StartArg);

            return _os_specific_start(reinterpret_cast<void*>(_Triad), _StackSize);
         }
         catch (...)
         {
            throw;
         }
      }

};   // end of class thread

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end of namespace(ev6)
}   // end of namespace(el)
}   // end namesapce(mts)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __THREAD_HPP__
