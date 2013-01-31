////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: main.cpp
//
// Modifications: 
//
// 26-Aug-12: Version 1.0 - Created
//
// Timeperiod: ev6
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include "user.hpp"

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////// 

bool check(const LAB::user*, const LAB::user*);
std::vector< std::size_t > find_permissions(std::size_t);
std::vector< LAB::user* > parse(const char*);
std::size_t search(std::vector< LAB::user* >&, std::size_t);

int main(int argc, char** argv)
{
    
        if (argc == 3)
        {
            std::vector< LAB::user* > _Users = parse(argv[1]);

            std::ofstream _Fout(argv[2]);

            for (std::size_t i = 0; i < _Users.size(); ++i)
            {
                    _Fout << "User " << _Users[i]->get_user_id() << " (" << _Users[i]->get_first_name()
                            << " " << _Users[i]->get_last_name() << ") can perform the following actions:" << std::endl;
                    std::vector< std::pair<std::size_t, std::string*>* > _Permissions = _Users[i]->get_user_permissions();
                    if (_Permissions.size() == 0) _Fout << "     " << "ERROR" << std::endl;
                    for (int j = _Permissions.size() - 1; j >= 0; --j) _Fout << "     " << *_Permissions[j]->second << std::endl;
                    for (int j = 0; j < _Permissions.size(); ++j) { delete _Permissions[j]->second; delete _Permissions[j]; }
                    _Fout << std::endl;
            }
            
            for (std::size_t i = 0; i < _Users.size(); ++i) delete _Users[i];  // deletes each user to avoid a memory leak
            
        }
        
        else
        {
            std::cout << "Error with Command Arguements" << std::endl;
        }
        
}

bool check(const LAB::user* _Lhs, const LAB::user* _Rhs) { return *_Lhs < *_Rhs; }

std::vector< LAB::user* > parse(const char* _InputFile)
{
	char _Buffer[80];

	std::size_t _UserAmount;
	std::size_t _UserId;
	std::size_t _UserPermission;

	std::vector< LAB::user* > _Users;

	std::ifstream _Fin(_InputFile);
	_Fin >> _UserAmount;

	for (std::size_t i = 0; i < _UserAmount; ++i)
	{

		_Fin >> _UserId >> _UserPermission;
                
                //LAB::user _TempUser(_UserId, _UserPermission);
	
		_Users.push_back(new LAB::user(_UserId, _UserPermission));

	}

	_Fin >> _UserAmount;
        
	for (std::size_t i = 0; i < _UserAmount; ++i)
	{
		_Fin >> _UserId >> _Buffer;
		
		std::string _FirstName(_Buffer);
		_Fin >> _Buffer;
		
		std::string _LastName(_Buffer);
		
		std::size_t _Index = search(_Users, _UserId);
		
		_Users[_Index]->set_first_name(_FirstName);
		_Users[_Index]->set_last_name(_LastName);
	}
        
	std::sort(_Users.begin(), _Users.end(), check);
        
	return _Users;
}

std::size_t search(std::vector< LAB::user* >& _Users, std::size_t _UserId)
{
 	// linear search through a vector of pairs

	std::size_t _Index = 0;

	for (std::size_t i = 0; i < _Users.size(); ++i)
	{
		if (_Users[i]->get_user_id() == _UserId) break;
		++_Index;
	}
	
	return _Index;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// end of main

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
