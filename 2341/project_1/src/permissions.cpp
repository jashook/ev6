////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: permissions.cpp
//
// Modifications: 
//
// 26-Aug-12: Version 1.0: Created
//
// Timeperiod: ev6
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "permissions.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

const char* const LAB::permissions::m_actions[] = { "no access", "read user's email", "organize user's email", "send user's email", "view calendar events", "update calendar events",
"add new calendar events", "read another user's email", "send email in another user's name", "add new calendar event in another user's name" };

const std::size_t LAB::permissions::m_permissions[] = { 0, 1, 2, 4, 8, 16, 32, 64, 128, 256 };

const std::size_t LAB::permissions::m_size = 10;

LAB::permissions::permissions(std::size_t _Permission) : _m_permission(_Permission) { }

std::vector< std::pair<std::size_t, std::string*>* > LAB::permissions::get_permissions()
{

    if (_m_permission > 511) return _m_permissions;

    for (int i = m_size - 1; i >= 0; --i)
    {
        if (_m_permission < m_permissions[i]) continue;
        if (i == 0) if (_m_permissions.size() > 0) continue;
        _m_permissions.push_back( new std::pair< std::size_t, std::string* >(m_permissions[i], new std::string(m_actions[i])) );
        _m_permission -= m_permissions[i];
    }

    if (_m_permission != 0) _m_permissions.clear();
    
    return _m_permissions;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// end of permissions definitions

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
