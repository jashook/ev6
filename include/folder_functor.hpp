////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        folder_functor
//
// Version:       1.0
//
// Modifications: 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __FOLDER_FUNCTOR_HPP__
#define __FOLDER_FUNCTOR_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <string>

#include "directory.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class folder_functor
{
   private:   // member variables

      std::vector<std::string>* _m_vec;

   public:   // member operators

      void operator() (WIN32_FIND_DATA& _FirstArg, LARGE_INTEGER& _SecondArg) 
      { 
         directory<> d(_FirstArg.cFileName);

         std::pair<ev4::file_functor, ev4::folder_functor>* _Pair = d.traverse_directory();

         std::vector<std::string>* l = _Pair->first.get_vec();

         for (std::size_t i = 0; i < l->size(); ++i) _m_vec->push_back(l->operator[](i));
      }

   public:   // constructor | destructor

      folder_functor(std::vector<std::string>* _Vec) : _m_vec(_Vec) { }

      ~folder_functor() { }

};   // end of class folder_functor

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev4)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __FOLDER_FUNCTOR_HPP__