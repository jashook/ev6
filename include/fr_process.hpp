////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        fr_process
//
// Version:       1.0
//
// Modifications: 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __FR_PROCESS_HPP__
#define __FR_PROCESS_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

#include "thread.hpp"
#include "utility.hpp"

#include "vector.hpp"
#include "brokered_queue.hpp"
#include "file.hpp"
#include "wss.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {
namespace mts {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class fr_process : public mts::thread<fr_process>
{

   public:   // member functions

      std::size_t _m_start_index;
      std::size_t _m_end_index;
      std::size_t _m_tag;
   
   public:   // overloaded operators

      int operator() (void* _StartArg) { return _run(_StartArg); }

   public:   // constructor | destructor

      fr_process(std::size_t _Start, std::size_t _End, std::size_t _Number) : _m_start_index(_Start), _m_end_index(_End), _m_tag(_Number) { }

      ~fr_process() { }

   private:   // helper functions

      int _run(void* _StartArg = NULL)
      {
         std::pair< ev4::vector<ev4::file*, 20000>*, ev4::mts::brokered_queue< ev4::vector<char>*, 500 >* >* _Pair = static_cast<std::pair< ev4::vector<ev4::file*, 20000>*, ev4::mts::brokered_queue< ev4::vector<char>*, 500 >* >*>(_StartArg);

         ev4::vector<ev4::file*, 20000>* _Vec = _Pair->first;
         ev4::mts::brokered_queue< ev4::vector<char>*, 500 >* _Queue = _Pair->second;

         for (std::size_t i = _m_start_index; i < _m_end_index; ++i)
         {
            ev4::vector<char>* _Raw_String = _Vec->at(i)->read();

            _Queue->push(_Raw_String);
            //std::cout << "Read: " << i << std::endl;
         }

         _Queue->flush();
         std::cout << "Fr_Process: " << _m_tag << " Ended" << std::endl;

         return 0;
      }

};   // end of class fr_process

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev4)
}   // end namespace(mts)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __FR_PROCESS_HPP__