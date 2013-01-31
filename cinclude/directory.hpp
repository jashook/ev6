////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        directory
//
// Version:       1.0
//
// Modifications: 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __DIRECTORY_HPP__
#define __DIRECTORY_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <string>

#ifndef _WIN32

   #include <dirent.h>

#else

   #include <Windows.h>
   #include <tchar.h>
   #include <strsafe.h>

#endif

#include "base.hpp"
#include "file.hpp"
#include"file_functor.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template<std::size_t __Size = 1, typename __File_Functor = file_functor, bool __Parse_Subfolder = true> class directory
{
   private:   // member variables

      std::string* _m_file_name;

      #ifdef _WIN32
         // names based on windows example

         WIN32_FIND_DATA _m_ffd;
         LARGE_INTEGER _m_filesize;
         TCHAR _m_dir[MAX_PATH];
         HANDLE _m_handle;
         DWORD _m_error;

      #else

      #endif

   public:   // member functions

      __File_Functor* traverse_directory() { return _os_specific_traverse_directory(); }
      void set_file_name(std::string& _File_Name) { _os_specific_set_file_name(_File_Name); }

   public:   // constructor | destructor

      directory(std::string& _File_Name) : _m_file_name(0), _m_handle(INVALID_HANDLE_VALUE), _m_error(0) { _os_specific_ctor(_File_Name); }

      directory(const char* _File_Name) : _m_file_name(0), _m_handle(INVALID_HANDLE_VALUE), _m_error(0) { _os_specific_ctor(_File_Name); }


      ~directory() { _os_specific_dtor(); }

   private:   // helper functions

      #ifdef _WIN32

         void _os_specific_ctor(std::string& _File_Name) 
         {
            _m_file_name = new std::string();
            *_m_file_name = _File_Name;
         }

         void _os_specific_ctor(const char* _File_Name) 
         {
            _m_file_name = new std::string(_File_Name);
         }

         void _os_specific_dtor() 
         {
            delete _m_file_name;
         }

         __File_Functor* _os_specific_traverse_directory()
         {
            assert(!(_m_file_name->size() > (MAX_PATH - 3)));

            __File_Functor* _File = new __File_Functor();

            ::StringCchCopy(_m_dir, MAX_PATH, _m_file_name->c_str());
            ::StringCchCat(_m_dir, MAX_PATH, TEXT("\\*"));

            _m_handle = FindFirstFile(_m_dir, &_m_ffd);

            std::size_t _Count = 0;

            do
            {
               // bitwise TEST to see if the file is a folder
               if (_m_ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
               {
                  ++_Count;
                  if (__Parse_Subfolder == true && _Count >= 3) _os_specific_traverse_subfolder(_m_ffd, _File);
               }

               else
               {
                  (*_File)(_m_ffd, _m_filesize, *_m_file_name);
               }

            } while (FindNextFile (_m_handle, &_m_ffd) != 0);

            FindClose(_m_handle);

            return _File;
         }

         void _os_specific_set_file_name(std::string& _File_Name)
         {
            *_m_file_name = _File_Name;
         }

         void _os_specific_traverse_subfolder(WIN32_FIND_DATA& _FirstArg, __File_Functor* _Functor)
         {
            
            std::string _Temp = *_m_file_name;
            _Temp.append("\\");
            _Temp.append(_FirstArg.cFileName);

            directory<__Size, __File_Functor, __Parse_Subfolder> d(_Temp);

            __File_Functor* _Pair = d.traverse_directory();

            ev4::vector<file*, __Size>* l = _Pair->get_vec();

            l->size();

            _Functor->add(l);
         }

      #else

         void _os_specific_ctor(std::string& _File_Name) 
         {
            if (_m_file_name != NULL) _m_file_name = new std::string();
            _m_file_name = _File_Name;
         }

         void _os_specific_dtor() 
         {
            delete _m_file_name;
         }

         size_t _os_specific_amount_of_files_in_directory()
         {

         }

      #endif

};   // end of class directory

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev4)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __DIRECTORY_HPP__