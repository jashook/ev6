////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: user.cpp
//
// Modifications: 
//
// 26-Aug-12: Version 1.0 - Created
//
// Timeperiod: ev6 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "user.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

LAB::user::user() : _m_permission(0), _m_first_name(0), _m_last_name(0) { }

LAB::user::user(std::size_t _UserId, std::size_t _Permission) : _m_user_id(_UserId), _m_first_name(0), _m_last_name(0)
{ 
    _m_permission = new LAB::permissions(_Permission);
}

LAB::user::user(const user& _Rhs) : _m_first_name(0), _m_last_name(0), _m_permission(0)
{
    // copy constructor zeros out all pointers in case _Rhs's pointers are null to avoid dereferencing a null pointer
    
    _m_user_id = _Rhs._m_user_id;
    if (_Rhs._m_first_name != 0)_m_first_name = new std::string(*_Rhs._m_first_name);
    if (_Rhs._m_last_name != 0) _m_last_name = new std::string(*_Rhs._m_last_name);
    if (_Rhs._m_permission != 0) _m_permission = new LAB::permissions(*_Rhs._m_permission);
}

LAB::user::~user()
{
	if (_m_first_name != 0) delete _m_first_name;
	if (_m_last_name != 0) delete _m_last_name;
   if (_m_permission != 0) delete _m_permission;
}

std::size_t LAB::user::get_user_id() { return _m_user_id; }
std::vector< std::pair<std::size_t, std::string*>* > LAB::user::get_user_permissions() { return _m_permission->get_permissions(); }
std::string LAB::user::get_first_name() { return *_m_first_name; }
std::string LAB::user::get_last_name() { return *_m_last_name; }

void LAB::user::set_user_id(std::size_t _UserId) { _m_user_id = _UserId; }

void LAB::user::set_user_permission(std::size_t _Permission) 
{ 
    if (_m_permission != 0) delete _m_permission;
    _m_permission = new LAB::permissions(_Permission);
}

void LAB::user::set_first_name(std::string& _FirstName)
{
    if (_m_first_name != 0) delete _m_first_name;
    _m_first_name = new std::string(_FirstName);
}

void LAB::user::set_last_name(std::string& _LastName)
{
    if (_m_last_name != 0) delete _m_last_name;
    _m_last_name = new std::string(_LastName);
}

LAB::user& LAB::user::operator=(const LAB::user& _Rhs) { return _assign(_Rhs); }
bool LAB::user::operator==(const LAB::user& _Rhs) const { return _equal_to(_Rhs); }
bool LAB::user::operator!=(const LAB::user& _Rhs) const { return !_equal_to(_Rhs); }
bool LAB::user::operator<(const LAB::user& _Rhs) const { return _less_than(_Rhs); }
bool LAB::user::operator>(const LAB::user& _Rhs) const { return !_less_than(_Rhs); }

LAB::user& LAB::user::_assign(const LAB::user& _Rhs)
{
    if (*this != _Rhs)
    {
        _m_first_name, _m_last_name, _m_permission = 0;
        _m_user_id = _Rhs._m_user_id;
        if (_Rhs._m_first_name != 0)_m_first_name = new std::string(*_Rhs._m_first_name);
        if (_Rhs._m_last_name != 0) _m_last_name = new std::string(*_Rhs._m_last_name);
        if (_Rhs._m_permission != 0) _m_permission = new LAB::permissions(*_Rhs._m_permission);
    }
}

bool LAB::user::_equal_to(const LAB::user& _Rhs) const
{
    if (_m_first_name == _Rhs._m_first_name && _m_last_name == _Rhs._m_last_name && _m_permission == _Rhs._m_permission) return true;
    return false;
}

bool LAB::user::_less_than(const LAB::user& _Rhs) const
{
	if (*_m_last_name < *_Rhs._m_last_name) 
	{
		return true;
	}

	else if (*_m_last_name == *_Rhs._m_last_name)
	{	
		bool _Return = false;

		if (*_m_first_name < *_Rhs._m_first_name) _Return = true;

		else if (*_m_first_name == *_Rhs._m_first_name)
		{
			_Return = (_m_user_id < _Rhs._m_user_id);
		}

		else if (*_m_first_name > *_Rhs._m_first_name) _Return = false;
		
		return _Return;
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// end of user definitions

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

