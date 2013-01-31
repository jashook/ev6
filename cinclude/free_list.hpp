////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        free_list
//
// Version:       1.0
//
// Modifications: 28-Jul-12 Fixed major manipulation bug, changed to a malloc approach
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef __FREE_LIST_HPP__
#define __FREE_LIST_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <cassert>

#include "sp_node.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {
namespace fl {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template<typename __Type, std::size_t __Update_Size = 1024 > class free_list
{
   private:   // member variables

      sp_node<__Type>* _m_head;

   public:   // member functions

      void return_to_list(void* _Data) { return _return_to_list(_Data); }

      void* remove_from_list() { return _remove_from_list(); }

   public:   // constructor | destructor

      free_list(std::size_t _Size = 1024)
      {
         _m_head = 0;
         _expand(_Size);
      }

      ~free_list() { _dtor(); }

   private:   // helper functions

      void _dtor()
      { 
         for (sp_node<__Type>* _Node = _m_head; _Node != 0; _Node = _m_head)
         {
            _m_head = _m_head->m_next;
            delete _Node;
         }
      }

      void _expand(std::size_t _UpdateSize = __Update_Size)
      {
         std::size_t _Size = (sizeof(__Type) > sizeof(sp_node<__Type>*)) ? sizeof(__Type) : sizeof(sp_node<__Type>*);

         sp_node<__Type>* _Node = reinterpret_cast<sp_node<__Type>*>(new char[_Size]);

         _m_head = _Node;
         for (std::size_t i = 0; i < _UpdateSize; ++i) 
         {
            _Node->m_next = reinterpret_cast< sp_node<__Type>* >(new char[_Size]);
            _Node = _Node->m_next;
         }

         _Node->m_next = 0;

      }

      void _return_to_list(void* _Return)
      {
         sp_node<__Type>* _Node = static_cast< sp_node<__Type>* >(_Return);
         _Node->m_next = _m_head;
         _m_head = _Node;
      }

      void* _remove_from_list()
      {
         if (_m_head->m_next == 0) _expand();

         sp_node<__Type>* _Node = _m_head;
         _m_head = _Node->m_next;

         return _Node;
      }

};   // end of class path

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev4)
}   // end namespace(fl)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __FREE_LIST_HPP__