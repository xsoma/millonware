#pragma once
#include "../../source engine/classes/client_class.hpp"

class i_base_client_dll
{
public:
	client_class* get_client_classes( )
	{
		using original_fn = client_class * ( __thiscall* )( i_base_client_dll* );
		return ( *( original_fn** )this )[ 8 ]( this );
	}
	bool dispatch_user_msg( int type, uint32_t a3, uint32_t len, void* msg_data )
	{
		using original_fn = bool( __thiscall* )( i_base_client_dll*, int, uint32_t, uint32_t, void* );
		return ( *( original_fn** )this )[ 38 ]( this, type, a3, len, msg_data );
	}
};

