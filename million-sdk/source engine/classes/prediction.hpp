/*
[PREDITLE]

Jumpshot, p100, millionware on top
Awp don't need no scope, hop around don't miss a shot
7 shots in my deagle always got me lookin' evil
p100 like it's cheat-codes just need one shot never reload

I hit the edgebug jumpbug spin around and flickshot (ooh)
Didn't even see you but your skull's eating my AWP shots (ahaheahey)
I hop through vent and spin around you didn't even see me there
It's 'cause I'm rich and flexing jumping around with my millionware

[DNZ]

I'm in the sky going high
Counting seconds in the air
Catch me if you can
bouncing like a frogman
It's 778 hopping 'round with 108
I don't stand around and wait
Jumpbug and accelerate

[SONAR]

Marijuana movement trail
Hip got locked up, county jail
Sold an invite paid for bail
You be moving like a snail
interium n***as bought a rat
paid my way into nohat
you're a nothing copycat
f**king noname acrobat

khmora gave me three day ban
bhopper from pakistan
blow it up, no taliban
You wannabes are hexa stans

UID 165
Drain Gang always sleep-deprived
Autostrafing cat-to-chair
Serversiding, millionware

[STELLAR]

Hotwheels sucks gonna breakaway
Spinning on mirage (yeah)
Hit you with the 1-tap AK
Now you all applause (yuh)

Free Clifton he didn't do sh*t
All the money it's counterfeit
Never missed bench to bricks
Swerving around 64-tick
[CHORUS/PREDITLE]

Jumpshot, p100, millionware on top
Awp don't need no scope, hop around don't miss a shot
7 shots in my deagle always got me lookin' evil
p100 like it's cheat-codes just need one shot never reload

I hit the edgebug jumpbug spin around and flickshot (ooh)
Didn't even see you but your skull's eating my AWP shots (ahaheahey)
I hop through vent and spin around you didn't even see me there
It's 'cause I'm rich and flexing jumping around with my millionware

[STELLAR]

They just added in-game chat
All these n***as got my back
Getting banned like every day
Message aiden, back in black

Hitting edgebugs de_nuke
Leaving discord call me duxe
Your strafes are dog, make me puke
My Fake Backward got you juked

Sold a paste, call me woke
f**ked your momma in the throat
Your movement is a f**king joke
Kill yourself retarded bloke
Daily dose of estrogen
No autostrafe I'm genuine
Jumping shot; adrenaline
OneShot turned me feminine

[AIDEN]

Knife behind; HNS
Tracing you like GPS
I check you like it's chess
I see Brooke, she undress (I see Brooke, she undress)

Like breezetix, don't need to hear
Sound ESP, know when you're near
Bounce off your head, I disappear
I made that one jumpbug tutorial (do you guys remember that?)
*/

#pragma once
#include "../math/vector3d.hpp"
class player_t;
class c_usercmd;

using c_entity = player_t;
using c_user_cmd = c_usercmd;

class CMoveHelper
{
public:
	void SetHost( c_entity* host )
	{
		using original_fn = void( __thiscall* )( void*, c_entity* );
		return ( *( original_fn** )this )[ 1 ]( this, host );
	}
};

struct CMoveData
{
	char data[ 184 ];
};

class CGameMovement
{
public:
	virtual			~CGameMovement( void )
	{}

	virtual void	ProcessMovement( c_entity* pPlayer, CMoveData* pMove ) = 0;
	virtual void	Reset( void ) = 0;
	virtual void	StartTrackPredictionErrors( c_entity* pPlayer ) = 0;
	virtual void	FinishTrackPredictionErrors( c_entity* pPlayer ) = 0;
	virtual void	DiffPrint( char const* fmt, ... ) = 0;

	virtual vec3 const& GetPlayerMins( bool ducked ) const = 0;
	virtual vec3 const& GetPlayerMaxs( bool ducked ) const = 0;
	virtual vec3 const& GetPlayerViewOffset( bool ducked ) const = 0;

	virtual bool			IsMovingPlayerStuck( void ) const = 0;
	virtual c_entity* GetMovingPlayer( void ) const = 0;
	virtual void			UnblockPusher( c_entity* pPlayer, c_entity* pPusher ) = 0;

	virtual void    SetupMovementBounds( CMoveData* pMove ) = 0;
};

class CPrediction
{
	// Construction
public:

	virtual ~CPrediction( void ) = 0;//

	virtual void Init( void ) = 0;//
	virtual void Shutdown( void ) = 0;//

									// Implement IPrediction
public:

	virtual void Update
	(
		int startframe, // World update ( un-modded ) most recently received
		bool validframe, // Is frame data valid
		int incoming_acknowledged, // Last command acknowledged to have been run by server (un-modded)
		int outgoing_command // Last command (most recent) sent to server (un-modded)
	);//

	virtual void PreEntityPacketReceived( int commands_acknowledged, int current_world_update_packet );//
	virtual void PostEntityPacketReceived( void );//5
	virtual void PostNetworkDataReceived( int commands_acknowledged );//

	virtual void OnReceivedUncompressedPacket( void );//

													// The engine needs to be able to access a few predicted values
	virtual void GetViewOrigin( vec3& org );//
	virtual void SetViewOrigin( vec3& org );//
	virtual void GetViewAngles( vec3& ang );//10
	virtual void SetViewAngles( vec3& ang );//

	virtual void GetLocalViewAngles( vec3& ang );//
	virtual void SetLocalViewAngles( vec3& ang );//

	virtual bool InPrediction( void ) const;//14
	virtual bool IsFirstTimePredicted( void ) const;//

	virtual int GetLastAcknowledgedCommandNumber( void ) const;//

#if !defined( NO_ENTITY_PREDICTION )
	virtual int GetIncomingPacketNumber( void ) const;//
#endif

	virtual void CheckMovingGround( c_entity* player, double frametime );//
	virtual void RunCommand( c_entity* player, c_user_cmd* cmd, CMoveHelper* moveHelper );//

	virtual void SetupMove( c_entity* player, c_user_cmd* cmd, CMoveHelper* pHelper, CMoveData* move );//20
	virtual void FinishMove( c_entity* player, c_user_cmd* cmd, CMoveData* move );//
	virtual void SetIdealPitch( int nSlot, c_entity* player, const vec3& origin, const vec3& angles, const vec3& viewheight );//

	virtual void CheckError( int nSlot, c_entity* player, int commands_acknowledged );//

public:
	virtual void _Update
	(
		int nSlot,
		bool received_new_world_update,
		bool validframe,            // Is frame data valid
		int incoming_acknowledged,  // Last command acknowledged to have been run by server (un-modded)
		int outgoing_command        // Last command (most recent) sent to server (un-modded)
	);

	// Actually does the prediction work, returns false if an error occurred
	bool PerformPrediction( int nSlot, c_entity* localPlayer, bool received_new_world_update, int incoming_acknowledged, int outgoing_command );

	void ShiftIntermediateDataForward( int nSlot, int slots_to_remove, int previous_last_slot );

	void RestoreEntityToPredictedFrame( int nSlot, int predicted_frame );

	int ComputeFirstCommandToExecute( int nSlot, bool received_new_world_update, int incoming_acknowledged, int outgoing_command );

	void DumpEntity( c_entity* ent, int commands_acknowledged );

	void ShutdownPredictables( void );

	void ReinitPredictables( void );

	void RemoveStalePredictedEntities( int nSlot, int last_command_packet );

	void RestoreOriginalEntityState( int nSlot );

	void RunSimulation( int current_command, float curtime, c_user_cmd* cmd, c_entity* localPlayer );

	void Untouch( int nSlot );

	void StorePredictionResults( int nSlot, int predicted_frame );

	bool ShouldDumpEntity( c_entity* ent );

	void SmoothViewOnMovingPlatform( c_entity* pPlayer, vec3& offset );

	void ResetSimulationTick( );

	void ShowPredictionListEntry( int listRow, int showlist, c_entity* ent, int& totalsize, int& totalsize_intermediate );

	void FinishPredictionList( int listRow, int showlist, int totalsize, int totalsize_intermediate );

	void CheckPredictConvar( );

#if !defined( NO_ENTITY_PREDICTION )

#endif
};