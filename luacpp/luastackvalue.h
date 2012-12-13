#pragma once
#include "luacpp.h"

namespace lua
{
	class LuaStackValue
	{
	public:
		LuaStackValue( lua_State* state, int index);

		bool IsNil() const;
		bool IsFunction() const;
		bool IsCFunction() const;
		bool IsNumber() const;
		bool IsString() const;
		bool IsBoolean() const;
		bool IsUserData() const;
		bool IsLightUserData() const;
		bool IsTable() const;

		LuaNumber_t GetNumber() const;
		LuaNumber_t CheckNumber() const;
		LuaNumber_t OptNumber( LuaNumber_t default ) const;

		const char* GetString() const; 
		const char* CheckString() const; 
		const char* OptString( const char* default ) const; 

		bool GetBoolean() const;
		void* GetUserData() const;
		void* GetLightUserData() const;

		int ArgError( const char* errMsg );

		int Index() const;
		void PushValue();

	private:
		lua_State* m_state;
		int m_index;
	};
}