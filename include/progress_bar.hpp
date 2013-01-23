////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        progress_bar
//
// Version:       1.0
//
// Modifications: 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __PROGRESS_BAR_HPP__
#define __PROGRESS_BAR_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template<typename __Data_Structure> class progress_bar
{
   private:   // constants and type definitions

      static const std::size_t MAX_CHAR = 50;

      typedef void (*f_general_function)(__Data_Structure*, std::size_t);

   private:   // member variables

      char _m_bar[MAX_CHAR];
      char _m_empty_bar[MAX_CHAR];

      double _m_last_tick;

      __Data_Structure* _m_container;

      std::size_t _m_position;
      std::size_t _m_size;
      std::size_t _m_update_tick;

   public:   // member functions

      void start(f_general_function _Function) { _start(_Function); }

   public:   // constructor | destructor

      progress_bar(__Data_Structure* _Container) : _m_container(_Container), _m_position(0), _m_last_tick(1) { _ctor(); }


   private:   // helper functions

      void _ctor()
      {
         std::memset(_m_bar, 0, static_cast<int>(sizeof(_m_bar)));
         std::memset(_m_empty_bar, 32, static_cast<int>(sizeof(_m_bar)));
         _m_empty_bar[MAX_CHAR - 1] = 0;
         _m_size = _m_container->size();
         _m_update_tick = _m_size / MAX_CHAR;
      }

      void _dtor()
      {
         std::memset(_m_bar, 0, static_cast<int>(sizeof(_m_bar)));
      }

      void _print()
      {
         if (_m_last_tick == 0) return;
         
         std::cout << '\r' << _m_bar;
      }

      void _start(f_general_function _Function, bool _Print = true)
      {

         std::cout << std::endl;

         std::cout << "::::::::::::::::PROGRESS BAR START:::::::::::::::" << std::endl;
         std::cout << std::endl;

         for (std::size_t i = 0; i < _m_size; ++i)
         {
            if (_update(i)) 
            { 
               _m_bar[_m_position] = ':'; 
               ++_m_position;
               if (_Print) _print();
            }

            _Function(_m_container, i);
         }

         std::cout << std::endl;
         std::cout << std::endl;
         std::cout << ":::::::::::::::::::::::END:::::::::::::::::::::::" << std::endl;
      }

      bool _update(std::size_t _At)
      {
         double check = (double)_At / (double)_m_size;
         if (_m_last_tick < (check * (double)MAX_CHAR))  { ++_m_last_tick; return true; }
         return false;
      }

};   // end of class progress_bar

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev4)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __PROGRESS_BAR_HPP__