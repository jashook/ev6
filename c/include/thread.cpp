////////////////////////////////////////////////////////////////////////////////
// FraudPlus (C) Copyright 2008 Verizon Wireless. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////
//
// Module:        thread
//
// Version:       1.00
//
// Modifications: 14-NOV-2008 -- SHOOKJA (Original development)
//
////////////////////////////////////////////////////////////////////////////////

#include <iosfwd>
#include <iostream>
#include <iomanip>
#include <string>
#include <typeinfo>

#include "thread.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace vzw {
namespace fp {

class test_thread : public thread
{
   public:   // Member variables

      bool _m_some_variable;

   public:   // Constructor and destructor

      test_thread() throw() : _m_some_variable(false) { }

      ~test_thread() throw() { }

   public:   // Attributes

      bool get_some_variable() const throw() { return _m_some_variable; }

      void set_some_variable(bool _Value) throw() { _m_some_variable = _Value; }

   public:   // Member functions

      int run(void* _StartArgs = NULL) throw()
      {
         return static_cast<int>(reinterpret_cast<long long>(_StartArgs));
      }
};

}   // End of namespace (fp)
}   // End of namespace (vzw)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main()
{
   std::cout << "Verizon Wireless (C) Copyright 2008. All Rights Reserved." << std::endl << std::endl;
   std::cout << "FraudPlus Unit Test - thread.hpp v1.00" << std::endl << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   // TEST 1: Typenames

   try
   {
      std::cout << "*** TEST 1 ***" << std::endl << std::endl;
      std::cout << "Testing: Typenames" << std::endl << std::endl;

      #if !defined WIN32 || defined NDEBUG
         std::cout << "vzw::fp::test_thread: \"" << typeid(vzw::fp::test_thread).name() << "\"" << std::endl << std::endl;
      #endif

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   // TEST 2: Sizes

   try
   {
      std::cout << "*** TEST 2 ***" << std::endl << std::endl;
      std::cout << "Testing: Sizes" << std::endl << std::endl;

      std::cout << "sizeof(vzw::fp::test_thread): " << sizeof(vzw::fp::test_thread) << std::endl;
      std::cout << std::endl;

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////
   // Constructors/Destructor
   /////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////

   /////////////////////////////////////////////////////////////////////////////
   // TEST 3: Constructor

   try
   {
      std::cout << "*** TEST 3 ***" << std::endl << std::endl;
      std::cout << "Testing: Constructor" << std::endl << std::endl;

      vzw::fp::test_thread _Thread1;

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   // TEST 4: Destructor

   try
   {
      std::cout << "*** TEST 4 ***" << std::endl << std::endl;
      std::cout << "Testing: Destructor" << std::endl << std::endl;

      // Construct on stack

      {
         vzw::fp::test_thread _Thread1;

      }   // <-- dtor called here !

      // Construct via placement new

      char _Buffer1[sizeof(vzw::fp::test_thread)];

      vzw::fp::test_thread* _Thread2 = new (static_cast<void*>(_Buffer1)) vzw::fp::test_thread;

      assert(sizeof(*_Thread2) == sizeof(vzw::fp::test_thread));

      _Thread2->vzw::fp::thread::~thread();   // <-- dtor called here !

      _Thread2 = NULL;

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////
   // Attributes
   /////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////

   /////////////////////////////////////////////////////////////////////////////
   // TEST 5: get_active_flag and set_active_flag

   try
   {
      std::cout << "*** TEST 5 ***" << std::endl << std::endl;
      std::cout << "Testing: get_active_flag and set_active_flag" << std::endl << std::endl;

      vzw::fp::test_thread _Thread1;

      assert(!_Thread1.get_active_flag());

      _Thread1.set_active_flag(true);

      assert(_Thread1.get_active_flag());

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   // TEST 6: get_alive_flag and set_alive_flag

   try
   {
      std::cout << "*** TEST 6 ***" << std::endl << std::endl;
      std::cout << "Testing: get_alive_flag and set_alive_flag" << std::endl << std::endl;

      vzw::fp::test_thread _Thread1;

      assert(!_Thread1.get_alive_flag());

      _Thread1.set_alive_flag(true);

      assert(_Thread1.get_alive_flag());

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   // TEST 7: get_exit_code

   try
   {
      std::cout << "*** TEST 7 ***" << std::endl << std::endl;
      std::cout << "Testing: get_exit_code" << std::endl << std::endl;

      vzw::fp::test_thread _Thread1;

      assert(_Thread1.get_exit_code() == EXIT_SUCCESS);

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   // TEST 8: get_id and set_id

   try
   {
      std::cout << "*** TEST 8 ***" << std::endl << std::endl;
      std::cout << "Testing: get_id and set_id" << std::endl << std::endl;

      vzw::fp::test_thread _Thread1;

      assert(_Thread1.get_id() == 0);

      _Thread1.set_id(1);

      assert(_Thread1.get_id() == 1);

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   // TEST 9: get_name and set_name

   try
   {
      std::cout << "*** TEST 9 ***" << std::endl << std::endl;
      std::cout << "Testing: get_name and set_name" << std::endl << std::endl;

      vzw::fp::test_thread _Thread1;

      const char* _Name = "MyThread";

      _Thread1.set_name(_Name);

      assert(_Thread1.get_name() == _Name);

      _Thread1.set_name(std::string(_Name));

      assert(_Thread1.get_name() == _Name);

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////
   // Member functions
   /////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////

   /////////////////////////////////////////////////////////////////////////////
   // TEST 10: is_active and is_not_active

   try
   {
      std::cout << "*** TEST 10 ***" << std::endl << std::endl;
      std::cout << "Testing: is_active and is_not_active" << std::endl << std::endl;

      vzw::fp::test_thread _Thread1;

      assert(!_Thread1.get_active_flag());
      assert(!_Thread1.is_active());
      assert(_Thread1.is_not_active());

      _Thread1.set_active_flag(true);

      assert(_Thread1.get_active_flag());
      assert(_Thread1.is_active());
      assert(!_Thread1.is_not_active());

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   // TEST 11: is_alive and is_not_alive

   try
   {
      std::cout << "*** TEST 11 ***" << std::endl << std::endl;
      std::cout << "Testing: is_alive and is_not_alive" << std::endl << std::endl;

      vzw::fp::test_thread _Thread1;

      assert(!_Thread1.get_alive_flag());
      assert(!_Thread1.is_alive());
      assert(_Thread1.is_not_alive());

      _Thread1.set_alive_flag(true);

      assert(_Thread1.get_alive_flag());
      assert(_Thread1.is_alive());
      assert(!_Thread1.is_not_alive());

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   // TEST 12: is_running and is_not_running

   try
   {
      std::cout << "*** TEST 12 ***" << std::endl << std::endl;
      std::cout << "Testing: is_running and is_not_running" << std::endl << std::endl;

      vzw::fp::test_thread _Thread1;

      assert(!_Thread1.is_running());
      assert(_Thread1.is_not_running());

      _Thread1.set_active_flag(true);

      assert(_Thread1.is_running());
      assert(!_Thread1.is_not_running());

      _Thread1.set_active_flag(false);

      assert(!_Thread1.is_running());
      assert(_Thread1.is_not_running());

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   // TEST 13: join

   try
   {
      std::cout << "*** TEST 13 ***" << std::endl << std::endl;
      std::cout << "Testing: join" << std::endl << std::endl;

      vzw::fp::test_thread _Thread1;

      _Thread1.start();
      _Thread1.join();

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   // TEST 14: run

   try
   {
      std::cout << "*** TEST 14 ***" << std::endl << std::endl;
      std::cout << "Testing: run" << std::endl << std::endl;

      // Direct call

      vzw::fp::test_thread _Thread1;

      int _ExitCode1;

      _ExitCode1 = _Thread1.run(reinterpret_cast<void*>(1));

      assert(_ExitCode1 == 1);   // Same as start arg

      int _ExitCode2 = 0;

      _ExitCode2 = _Thread1.run(reinterpret_cast<void*>(2));

      assert(_ExitCode2 == 2);   // Same as start arg

      // Indirect call

      vzw::fp::test_thread _Thread2;

      _Thread2.start(reinterpret_cast<void*>(3));
      _Thread2.join();

      int _ExitCode3 = 0;

      _ExitCode3 = _Thread2.get_exit_code();

      assert(_ExitCode3 == 3);   // Same as start arg

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   // TEST 15: sleep

   try
   {
      std::cout << "*** TEST 15 ***" << std::endl << std::endl;
      std::cout << "Testing: sleep" << std::endl << std::endl;

      vzw::fp::test_thread _Thread1;

      _Thread1.sleep(1000);   // [this] thread will sleep for 1 second

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   // TEST 16: start (default stack size)

   try
   {
      std::cout << "*** TEST 16 ***" << std::endl << std::endl;
      std::cout << "Testing: start (default stack size)" << std::endl << std::endl;

      // Direct call

      vzw::fp::test_thread _Thread1;

      int _ExitCode1;

      _ExitCode1 = _Thread1.run(reinterpret_cast<void*>(1));

      assert(_ExitCode1 == 1);   // Same as start arg

      int _ExitCode2 = 0;

      _ExitCode2 = _Thread1.run(reinterpret_cast<void*>(2));

      assert(_ExitCode2 == 2);   // Same as start arg

      // Indirect call

      vzw::fp::test_thread _Thread2;

      _Thread2.start(reinterpret_cast<void*>(3));
      _Thread2.join();

      int _ExitCode3 = 0;

      _ExitCode3 = _Thread2.get_exit_code();

      assert(_ExitCode3 == 3);   // Same as start arg

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   // TEST 17: start (stack size)

   try
   {
      std::cout << "*** TEST 17 ***" << std::endl << std::endl;
      std::cout << "Testing: start (stack size)" << std::endl << std::endl;

      // Direct call

      vzw::fp::test_thread _Thread1;

      const std::size_t _STACK_SIZE_PAGE_COUNT = 512;   // Windows == 2MB (512 * 4096); Solaris == 4MB (512 * 8192)

      std::size_t _StackSize = _STACK_SIZE_PAGE_COUNT * vzw::fp::system::page_size();

      _Thread1.start(reinterpret_cast<void*>(0), _StackSize);   // <-- Stack size is 2 MB on Windows and 4 MB on Solaris
      _Thread1.join();

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   // TEST 18: stop

   try
   {
      std::cout << "*** TEST 18 ***" << std::endl << std::endl;
      std::cout << "Testing: stop" << std::endl << std::endl;

      vzw::fp::test_thread _Thread1;

      _Thread1.set_active_flag(true);

      assert(_Thread1.get_active_flag());   // <-- Active

      _Thread1.stop();

      assert(!_Thread1.get_active_flag());   // <-- Not active

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////
   // Member functions
   /////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////

   /////////////////////////////////////////////////////////////////////////////
   // TEST 19: get_current_thread_id

   try
   {
      std::cout << "*** TEST 19 ***" << std::endl << std::endl;
      std::cout << "Testing: get_current_thread_id" << std::endl << std::endl;

      vzw::fp::test_thread _Thread1;

      vzw::fp::tid_t _ThreadId;

      _ThreadId = vzw::fp::get_current_thread_id();

      std::cout << "SUCCESS" << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cout << "Exception caught: unknown" << std::endl << std::endl;
      std::cout << "FAILURE" << std::endl;

      return EXIT_FAILURE;
   }

   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////
   // Dump C Runtime memory statistics
   /////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////

   #if defined WIN32 && !defined NDEBUG
      _RPT0(_CRT_WARN, "Dumping memory statistics ...\n");

      _CrtMemState _State;
      _CrtMemCheckpoint(&_State);
      _CrtMemDumpStatistics(&_State);
      _CrtDumpMemoryLeaks();
   #endif

   return EXIT_SUCCESS;
}
