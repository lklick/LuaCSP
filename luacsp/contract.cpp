/**
 * This file is a part of LuaCSP library.
 * Copyright (c) 2012-2013 Alexey Baskakov
 * Project page: http://github.com/loyso/LuaCSP
 * This library is distributed under the GNU General Public License (GPL), version 2.
 * The above copyright notice shall be included in all copies or substantial portions of the Software.
 */
#include "contract.h"

#include <luacpp/luastack.h>
#include <luacpp/luastackvalue.h>

#include "channel.h"

namespace csp
{
	int Contract_table( lua_State* luaState );
	int Contract_new( lua_State* luaState );

	const csp::FunctionRegistration contractGlobals[] =
	{
		"table", csp::Contract_table
		, NULL, NULL
	};

	const csp::FunctionRegistration contractFunctions[] =
	{
		"new", csp::Contract_new
		, NULL, NULL
	};
}

int csp::Contract_table( lua_State* luaState )
{
	lua::LuaStack stack( luaState );
	stack.PushTable();
	CspSetMetatable( luaState, stack.GetTopValue(), contractFunctions );
	return 1;
}

int csp::Contract_new( lua_State* luaState )
{
	lua::LuaStack stack( luaState );
	lua::LuaStackValue table = stack[1];
	if( !table.IsTable() )
		return table.ArgError( "contract table expected." );

	lua::LuaStackValue contractInstance = stack.PushTable();

	for ( lua::LuaStackTableIterator it( table ); it; it.Next() )
	{
		lua::LuaStackValue channelName = it.Key();
		lua::LuaStackValue value = it.Value();

		if( !channelName.IsString() )
			return stack.ArgError( 1, "channel name must be a string." );
		if( !value.IsTable() )
			return stack.ArgError( 1, "channel name must refer to Channel table." );

		channelName.PushValue();

		Channel* pChannel = CORE_NEW Channel();
		PushChannel( luaState, *pChannel );

		stack.RawSet( contractInstance );
	}

	return 1;
}


void csp::InitializeContracts( lua::LuaState& state )
{
	InitializeCspObject( state, "Contract", contractGlobals, contractFunctions );
}

void csp::ShutdownContracts( lua::LuaState& state )
{
	ShutdownCspObject( state, "Contract", contractGlobals, contractFunctions );
}
