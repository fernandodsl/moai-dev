// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIPLATFORMERDYNAMICS2D_H
#define	MOAIPLATFORMERDYNAMICS2D_H

#include <moaicore/MOAIAction.h>

class MOAIPlatformerBody2D;

//================================================================//
// MOAIPlatformerDynamics2D
//================================================================//
// TODO: doxygen
class MOAIPlatformerDynamics2D :
	public virtual MOAIAction {
private:
	
	USVec2D		mJumpMidHandle;
	USVec2D		mJumpTopHandle;
	float		mJumpDuration;
	
	USVec2D		mFallMidHandle;
	USVec2D		mFallTopHandle;
	float		mFallDuration;
	
	u32			mState;
	float		mStateTimer;
	float		mStateY;
	
	enum {
		STATE_NONE,
		STATE_JUMPING,
		STATE_FALLING,
	};
	
	float		mWalkAcceleration;
	float		mWalkMax;
	float		mWalkDrag;
	
	float		mXMove;
	
	MOAILuaSharedPtr < MOAIPlatformerBody2D > mBody;
	
	//----------------------------------------------------------------//
	static int		_drawJumpArc					( lua_State* L );
	static int		_drawJumpHull					( lua_State* L );
	static int		_drawJumpPoints					( lua_State* L );
	static int		_jump							( lua_State* L );
	static int		_setBody						( lua_State* L );
	static int		_setFallParams					( lua_State* L );
	static int		_setJumpParams					( lua_State* L );
	static int		_setWalkParams					( lua_State* L );

	//----------------------------------------------------------------//
	static float	ApplyDrag						( float n, float d );
	void			SetState						( u32 state );

public:
	
	DECL_LUA_FACTORY ( MOAIPlatformerDynamics2D )
	
	//----------------------------------------------------------------//
	void			DrawJumpArc						( u32 resolution, float xMove );
	void			DrawJumpHull					( float xMove );
	void			DrawJumpPoints					( float xMove );
	float			EvalCurve1D						( const USVec2D& v0, const USVec2D& v1, float t );
	USVec2D			EvalCurve2D						( const USVec2D& v0, const USVec2D& v1, float t );
	float			FindYForX						( const USVec2D& v0, const USVec2D& v1, float x );
	bool			IsDone							();
					MOAIPlatformerDynamics2D		();
					~MOAIPlatformerDynamics2D		();
	void			OnUpdate						( float step );
	void			RegisterLuaClass				( MOAILuaState& state );
	void			RegisterLuaFuncs				( MOAILuaState& state );
};

#endif
