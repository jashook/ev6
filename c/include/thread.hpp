////////////////////////////////////////////////////////////////////////////////
// FraudPlus (C) Copyright 2008 Verizon Wireless. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////
//
// Module:        thread
//
// Version:       1.00
//
// Modifications: 16-NOV-2008 -- SHOOKJA (Original development)
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __THREAD_HPP__
#define __THREAD_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <sstream>

#ifndef WIN32
#ifdef sun
#include <thread.h>   // thr_stksegment
#endif
#endif

#include <memory.h>

#include "base.hpp"
#include "lock.hpp"
#include "lock_sentry.hpp"
#include "utility.hpp"
#include "system.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
   typedef unsigned start_thread_return_t;

   extern unsigned __stdcall _start_thread(void* _ThreadArg);
#else   // POSIX
   typedef void* start_thread_return_t;

   extern "C" void* _start_thread(void* _ThreadArg);
#endif

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace vzw {   // Verizon Wireless
namespace fp {    // FraudPlus

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
   typedef std::size_t tid_t;
#else   // POSIX
   typedef pthread_t tid_t;
#endif

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class thread
{
   private:   // Member variables

      int          _m_exit_code;
      bool         _m_is_active;
      bool         _m_is_alive;
      std::size_t  _m_id;
      std::string* _m_name;
      lock*        _m_lock;
      tid_t        _m_tid;

      #ifdef WIN32
         HANDLE _m_handle;
      #endif

   private:   // Helper functions (platform specific)

      ///////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////
      #ifdef WIN32
      ///////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////

      std::string _os_format_error(DWORD _ErrorCode) const throw()
      {
         assert(_ErrorCode != 0);

         LPVOID lpvBuffer = NULL;

         FormatMessage
         (
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            _ErrorCode,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &lpvBuffer,
            0,
            NULL
         );

         std::string _String(static_cast<char*>(lpvBuffer), strlen(static_cast<char*>(lpvBuffer)));

         _String.erase(_String.rfind("\r\n"));   // Remove CR-LF

         LocalFree(lpvBuffer);

         return _String;
      }

      void _os_join() throw(std::exception)
      {
         #ifndef NDEBUG
            assert(WaitForSingleObject(_m_handle, INFINITE) == WAIT_OBJECT_0);
         #else
            WaitForSingleObject(_m_handle, INFINITE);
         #endif

         DWORD _ExitCode = 0;

         if (!GetExitCodeThread(_m_handle, &_ExitCode))
         {
            std::string _FormattedError = _os_format_error(GetLastError());

            std::ostringstream _SStream;

            _SStream << "[vzw::fp::thread::start::_start::_os_start] GetExitCodeThread failed (" << _FormattedError << ")";

            throw std::runtime_error(_SStream.str());
         }

         _set_exit_code(static_cast<int>(_ExitCode));
      }

      //static std::size_t _stack_size() throw(std::exception)
      //{
      //   return 0;  // Not supported
      //}

      void _os_start(void* _StartArg, std::size_t _StackSize) throw(std::exception)
      {
         _m_handle = (HANDLE) _beginthreadex(NULL, (unsigned int) _StackSize, _start_thread, (void*) _StartArg, (unsigned) 0, (unsigned*) &_m_tid);

         if (_m_handle == NULL)
         {
            std::string _FormattedError = _os_format_error(GetLastError());

            std::ostringstream _SStream;

            _SStream << "[vzw::fp::thread::start::_start::_os_start] _beginthreadex failed (" << _FormattedError << ")";

            throw std::runtime_error(_SStream.str());
         }
      }

      ///////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////
      #else   // UNIX/POSIX
      ///////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////

      void _os_join() throw(std::exception)
      {
         void* _ExitCode = NULL;

         if (pthread_join(_m_tid, &_ExitCode) != 0)
         {
            std::ostringstream _SStream;

            _SStream << "[vzw::fp::thread::start::_start::_os_start] pthread_join failed (" << strerror(errno) << ")";

            throw std::runtime_error(_SStream.str());
         }

         _set_exit_code(static_cast<int>(reinterpret_cast<long long>(_ExitCode)));
      }

      static std::size_t _stack_size() throw(std::exception)
      {
         std::size_t _StackSize = 0;

         #ifdef sun
            stack_t _StackSegment;

            if (thr_stksegment(&_StackSegment) != 0)
            {
               std::ostringstream _SStream;

               _SStream << "[vzw::fp::thread::start::_start::_stack_size] thr_stksegment failed (" << strerror(errno) << ")";

               throw std::runtime_error(_SStream.str());
            }

            _StackSize = _StackSegment.ss_size;
         #endif

         return _StackSize;
      }

      void _os_start(void* _StartArg, std::size_t _StackSize) throw(std::exception)
      {
         if (_StackSize > 0)
         {
            pthread_attr_t _Attributes;

            if (pthread_attr_init(&_Attributes) != 0)
            {
               std::ostringstream _SStream;

               _SStream << "[vzw::fp::thread::start::_start::_os_start] pthread_attr_init failed (" << strerror(errno) << ")";

               throw std::runtime_error(_SStream.str());
            }

            if (pthread_attr_setstacksize(&_Attributes, _StackSize) != 0)
            {
               std::ostringstream _SStream;

               _SStream << "[vzw::fp::thread::start::_start::_os_start] pthread_attr_setstacksize failed (" << strerror(errno) << ")";

               throw std::runtime_error(_SStream.str());
            }

            if (pthread_create(&_m_tid, &_Attributes, _start_thread, (void*) _StartArg) != 0)
            {
               std::ostringstream _SStream;

               _SStream << "[vzw::fp::thread::start::_start::_os_start] pthread_create failed (" << strerror(errno) << ")";

               throw std::runtime_error(_SStream.str());
            }

            if (pthread_attr_destroy(&_Attributes) != 0)
            {
               std::ostringstream _SStream;

               _SStream << "[vzw::fp::thread::start::_start::_os_start] pthread_attr_destroy failed (" << strerror(errno) << ")";

               throw std::runtime_error(_SStream.str());
            }
         }
         else
         {
            if (pthread_create(&_m_tid, (pthread_attr_t*) NULL, _start_thread, (void*) _StartArg) != 0)
            {
               std::ostringstream _SStream;

               _SStream << "[vzw::fp::thread::start::_start::_os_start] pthread_create failed (" << strerror(errno) << ")";

               throw std::runtime_error(_SStream.str());
            }
         }
      }

      ///////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////
      #endif
      ///////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////

   private:   // Helper functions

      void _ctor() throw()
      {
         ::memset(this, 0, sizeof(*this));

         assert(_m_exit_code == EXIT_SUCCESS);
         assert(!_m_is_active);
         assert(!_m_is_alive);
         assert(_m_id == 0);

         _m_name = new std::string("");
         _m_lock = new lock;

         assert(_m_name != NULL);
         assert(_m_lock != NULL);

         #ifdef WIN32
            assert(_m_tid == 0);
            assert(_m_handle == 0);
         #endif
      }

      void _dtor() throw()
      {
         if (_m_name != NULL)
         {
            delete _m_name;

            _m_name = NULL;
         }

         if (_m_lock != NULL)
         {
            delete _m_lock;

            _m_lock = NULL;
         }

         #ifndef NDEBUG
            ::memset(this, 0, sizeof(*this));

            assert(_m_exit_code == EXIT_SUCCESS);
            assert(!_m_is_active);
            assert(!_m_is_alive);
            assert(_m_id == 0);
            assert(_m_name == NULL);
            assert(_m_lock == NULL);

            #ifdef WIN32
               assert(_m_tid == 0);
               assert(_m_handle == 0);
            #endif
         #endif
      }

      bool _get_active_flag() const throw() { return _m_is_active; }
      bool _get_alive_flag() const throw() { return _m_is_alive; }
      int _get_exit_code() const throw() { return _m_exit_code; }
      std::size_t _get_id() const throw() { return _m_id; }
      std::string& _get_name() const throw() { return *_m_name; }

      bool _is_active() throw()
      {
         lock_sentry _Sentry(_m_lock);

         return _m_is_active;
      }

      bool _is_alive() const throw() { return _m_is_alive; }

      void _set_active_flag(bool _Value) throw()
      {
         lock_sentry _Sentry(_m_lock);

         _m_is_active = _Value;
      }

      void _set_alive_flag(bool _Value) throw() { _m_is_alive = _Value; }
      void _set_exit_code(int _Value) throw() { _m_exit_code = _Value; }
      void _set_id(std::size_t _Value) throw() { _m_id = _Value; }

      void _set_name(const std::string& _Value) throw()
      {
         if (_m_name != NULL) delete _m_name;

         _m_name = new std::string(_Value);

         assert(_m_name != NULL);
      }

      void _start(void* _StartArg, std::size_t _StackSize) throw(std::exception)
      {
         try
         {
            std::pair<vzw::fp::thread*, void*>* _Pair = new std::pair<vzw::fp::thread*, void*>(this, _StartArg);

            assert(_Pair != NULL);

            return _os_start(reinterpret_cast<void*>(_Pair), _StackSize);
         }
         catch (...)
         {
            throw;
         }
      }

      void _stop() throw() { _set_active_flag(false); }

   public:   // Constructors and destructor

      thread() throw() { _ctor(); }

      virtual ~thread() { _dtor(); }

   public:   // Attributes

      bool get_active_flag() throw() { return _get_active_flag(); }
      bool get_alive_flag() const throw() { return _get_alive_flag(); }
      int get_exit_code() const throw() { return _get_exit_code(); }
      std::size_t get_id() const throw() { return _get_id(); }
      std::string get_name() const throw() { return _get_name(); }

      void set_active_flag(bool _Value) throw() { _set_active_flag(_Value); }
      void set_alive_flag(bool _Value) throw() { _set_alive_flag(_Value); }
      void set_id(std::size_t _Value) throw() { _set_id(_Value); }
      void set_name(const char* _Value) throw() { _set_name(std::string(_Value)); }
      void set_name(const std::string& _Value) throw() { _set_name(_Value); }

   public:   // Member functions

      bool is_active() throw() { return _is_active(); }
      bool is_alive() const throw() { return _is_alive(); }
      bool is_not_active() throw() { return !_is_active(); }
      bool is_not_alive() throw() { return !_is_alive(); }
      bool is_not_running() throw() { return !_is_active(); }
      bool is_running() throw() { return _is_active(); }
      void join() throw(std::exception) { try { _os_join(); } catch (...) { throw; } }
      virtual int run(void* _StartArg = NULL) = 0;
      void sleep(std::size_t _Milliseconds) const throw() { utility::sleep(_Milliseconds); }
      //static std::size_t stack_size() throw(std::exception) { try { return _stack_size(); } catch (...) { throw; } }
      void start(void* _StartArg = NULL, std::size_t _StackSize = 0) throw(std::exception) { try { return _start(_StartArg, _StackSize); } catch (...) { throw; } }
      void stop() throw() { return _stop(); }
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Non-member functions
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

inline tid_t get_current_thread_id() throw()
{
   #ifdef WIN32
      return static_cast<tid_t>(GetCurrentThreadId());
   #else   // POSIX
      return pthread_self();
   #endif
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // End of namespace (fp)
}   // End of namespace (vzw)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __THREAD_HPP__
