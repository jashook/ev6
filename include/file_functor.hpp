////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        file_functor
//
// Version:       1.0
//
// Modifications: 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __FILE_FUNCTOR_HPP__
#define __FILE_FUNCTOR_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <string>

#include "base.hpp"
#include "file.hpp"
#include "file_reader.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <std::size_t __Size = 1> class file_functor
{
   private:   // member variables

      std::size_t _m_count;
      
      ev4::vector<file*, __Size> _m_vec;

      file_reader fr;

   public:   // member operators

      #ifdef _WIN32

         void operator() (WIN32_FIND_DATA& _FirstArg, LARGE_INTEGER& _SecondArg, std::string& _Path) 
         { 
            ++_m_count;

            file* f = new file(_Path.c_str(), _FirstArg.cFileName);

            _m_vec.push_back(f);
         }

      #else

         void operator() () 
         { 
            ++_m_count; 
         }

      #endif

   public:   // constructor | destructor

      file_functor() : _m_count(0) { }

      ~file_functor() 
      {

      }

   public: // member functions

      void add(void* _Arg) 
      { 
         ev4::vector<ev4::file*, __Size>* _Vec = static_cast< ev4::vector<ev4::file*, __Size>* >(_Arg);
         _Vec->size();
         for (std::size_t i = 0; i < _Vec->size(); ++i) 
         { 
            _m_vec.push_back(_Vec->at(i)); 
            ++_m_count; 
         } 
      }

      std::size_t get_count() { return _m_count; }
      vector<file*, __Size>* get_vec() { return &_m_vec; }

};   // end of class file_functor

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev4)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __FILE_FUNCTOR_HPP__