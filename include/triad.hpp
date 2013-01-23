////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        triad
//
// Version:       1.0
//
// Modifications: 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __TRIAD_HPP__
#define __TRIAD_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template<typename __Type, typename __Second_Type, typename __Third_Type> struct triad
{
   public:   // member variables

      __Type first;
      __Second_Type second;
      __Third_Type third;

   public:   // constructor | destructor

      triad() { }

      triad(const __Type& _First, const __Second_Type& _Second, const __Third_Type& _Third) : first(const_cast<__Type&>(_First)), second(const_cast<__Second_Type&>(_Second)), third(const_cast<__Third_Type&>(_Third)) { }

      ~triad() { }

};   // end of class triad

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev4)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __TRIAD_HPP__