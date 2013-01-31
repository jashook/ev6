////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        lock
//
// Version:       1.0
//
// Modifications: 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __LOCK_HPP__
#define __LOCK_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "base.hpp"
#include "utility.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {
namespace mts {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class lock
{
   public:   // type definitions and constants

      enum ERROR_CODE
      {
         EC_SUCCESS                = 0,
         EC_COULD_NOT_DESTROY_LOCK = 1,
         EC_COULD_NOT_GET_LOCK     = 2,
         EC_COULD_NOT_INIT_LOCK    = 3,
         EC_COULD_NOT_RELEASE_LOCK = 4
      };

      static const std::size_t _SPIN_COUNT = 4000;   // Based on Microsoft's default

      #ifdef _WIN32
         typedef CRITICAL_SECTION lock_t;
      #else
         typedef pthread_mutext_t lock_t;
      #endif

   private:   // member variables

      lock_t _m_lock;

   public:   // member functions

      void get_lock() throw(ERROR_CODE) { _get_lock(); }
      void release_lock() throw(ERROR_CODE) { _release_lock(); }
      bool try_lock(bool _Wait = true) throw() { return _try_lock(_Wait); }

   public:   // constructor | destructor

      lock() throw(ERROR_CODE) { _ctor(); }

      ~lock() throw(ERROR_CODE) { _dtor(); }

   private:   // os specific helper functions

      #ifdef _WIN32

         bool _os_specific_get_lock() throw()
         {
            EnterCriticalSection(&_m_lock);

            return true;
         }

         bool _os_specific_destroy_lock() throw()
         {
            DeleteCriticalSection(&_m_lock);

            return true;
         }

         std::pair<std::size_t, std::size_t> _os_specific_get_version() const throw()
         {
            OSVERSIONINFO _VersionInfo;

            ::memset(&_VersionInfo, 0, sizeof(OSVERSIONINFO));

            _VersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

            GetVersionEx(&_VersionInfo);

            return std::pair<std::size_t, std::size_t>(_VersionInfo.dwMajorVersion, _VersionInfo.dwMinorVersion);
         }

         bool _os_specific_initialize_lock() throw()
         {
            if (_os_specific_get_version().first >= 5)   // Spin lock support started with Windows 2000
            {
               if (InitializeCriticalSectionAndSpinCount(&_m_lock, _SPIN_COUNT)) return true;
            }

            InitializeCriticalSection(&_m_lock);

            return true;
         }

         bool _os_specific_release_lock() throw()
         {
            LeaveCriticalSection(&_m_lock);

            return true;
         }

         bool _os_specific_try_lock(bool _Wait) throw()
         {
            if (_Wait)   // Same as _get_lock, but more efficient
            {
               for (int _Count = 0; _Count <= _SPIN_COUNT; ++_Count)
               {
                  if (TryEnterCriticalSection(&_m_lock)) return true;   // Got lock

                  //ev4::mta::sleep(0);
               }

               return false;   // Could not gain lock within spin count
            }

            return TryEnterCriticalSection(&_m_lock) ? true : false;
         }

      #else   // POSIX

      #endif

   private:   // helper functions

      void _ctor() throw(ERROR_CODE) { if (!_os_specific_initialize_lock()) throw EC_COULD_NOT_INIT_LOCK; }

      void _dtor() throw(ERROR_CODE) { if (!_os_specific_destroy_lock()) throw EC_COULD_NOT_DESTROY_LOCK; }

      void _get_lock() throw(ERROR_CODE) { if (!_os_specific_get_lock()) throw EC_COULD_NOT_GET_LOCK; }

      void _release_lock() { if (!_os_specific_release_lock()) throw EC_COULD_NOT_RELEASE_LOCK; }

      bool _try_lock(bool _Wait = true) { return _os_specific_try_lock(_Wait); }


};   // end of class lock

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev4)
}   // end namespace(mts)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __LOCK_HPP__