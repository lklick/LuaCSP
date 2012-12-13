#pragma once

struct lua_State;

namespace lua
{
	class LuaState;
	class LuaStackValue;
}

namespace csp
{
	class Host;
	class Process;
	class Channel;

	struct ChannelArgument;
}

namespace csp
{
	typedef float time_t;

	namespace WorkResult
	{
		enum Enum
		{
			  FINISH = 0
			, YIELD
		};
	}

	class GcObject
	{
	public:
		GcObject();
		virtual ~GcObject();
	};

	struct ChannelAttachment_i
	{
		virtual Process& ProcessToEvaluate() = 0;
	};

	struct ChannelAttachmentIn_i : ChannelAttachment_i
	{
		virtual void MoveChannelArguments( Channel& channel, ChannelArgument* arguments, int numArguments ) = 0;
	};

	struct ChannelAttachmentOut_i : ChannelAttachment_i
	{
		virtual void MoveChannelArguments() = 0;
	};

	struct FunctionRegistration
	{
		const char* name;
		int (*function)( lua_State* L );
	};

	void RegisterFunctions( lua::LuaState& state, lua::LuaStackValue& value, const FunctionRegistration registrations[] );
	void UnregisterFunctions( lua::LuaState& state, lua::LuaStackValue& value, const FunctionRegistration registrations[] );

	void InitializeCspObject( lua::LuaState& state, const FunctionRegistration memberFunctions[], const FunctionRegistration globalFunctions[] );
	void ShutdownCspObject( lua::LuaState& state, const FunctionRegistration memberFunctions[], const FunctionRegistration globalFunctions[] );

	void PushGcObject( lua_State* luaState, GcObject& gcObject, void* metatableRegistryKey );
	void PushGcObject( lua_State* luaState, GcObject& gcObject, const FunctionRegistration memberFunctions[] );
	int GcObject_Gc( lua_State* luaState );

    Host& Initialize();
    void Shutdown(Host& host);
}