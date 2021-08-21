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
#include "recv_props.hpp"

class client_class;

class i_client_networkable
{
public:
	void pre_data_update( int type )
	{
		using original_fn = void( __thiscall* )( i_client_networkable*, int );
		return ( *( original_fn** )this )[ 6 ]( this, type );
	}
	void set_destroyed_on_recreate_entities( )
	{
		using original_fn = void( __thiscall* )( i_client_networkable* );
		return ( *( original_fn** )this )[ 13 ]( this );
	}
	void release( )
	{
		using original_fn = void( __thiscall* )( i_client_networkable* );
		return ( *( original_fn** )this )[ 1 ]( this );
	}
};

typedef i_client_networkable* ( *create_client_class_fn )( int ent_number, int serial_number );
typedef i_client_networkable* ( *create_event_fn )( );

enum class_ids
{
	ctesttraceline = 196,
	cteworlddecal = 197,
	ctespritespray = 194,
	ctesprite = 193,
	ctesparks = 192,
	ctesmoke = 191,
	cteshowline = 189,
	cteprojecteddecal = 186,
	cfeplayerdecal = 61,
	cteplayerdecal = 185,
	ctephysicsprop = 182,
	cteparticlesystem = 181,
	ctemuzzleflash = 180,
	ctelargefunnel = 178,
	ctekillplayerattachments = 177,
	cteimpact = 176,
	cteglowsprite = 175,
	cteshattersurface = 188,
	ctefootprintdecal = 172,
	ctefizz = 171,
	cteexplosion = 169,
	cteenergysplash = 168,
	cteeffectdispatch = 167,
	ctedynamiclight = 166,
	ctedecal = 164,
	cteclientprojectile = 163,
	ctebubbletrail = 162,
	ctebubbles = 161,
	ctebspdecal = 160,
	ctebreakmodel = 159,
	ctebloodstream = 158,
	ctebloodsprite = 157,
	ctebeamspline = 156,
	ctebeamringpoint = 155,
	ctebeamring = 154,
	ctebeampoints = 153,
	ctebeamlaser = 152,
	ctebeamfollow = 151,
	ctebeaments = 150,
	ctebeamentpoint = 149,
	ctebasebeam = 148,
	ctearmorricochet = 147,
	ctemetalsparks = 179,
	csteamjet = 142,
	csmokestack = 135,
	dusttrail = 246,
	cfiretrail = 64,
	sporetrail = 252,
	sporeexplosion = 251,
	rockettrail = 249,
	smoketrail = 250,
	cpropvehicledriveable = 122,
	particlesmokegrenade = 248,
	cparticlefire = 100,
	movieexplosion = 247,
	ctegaussexplosion = 174,
	cenvquadraticbeam = 56,
	cembers = 46,
	cenvwind = 60,
	cprecipitation = 116,
	cprecipitationblocker = 117,
	cbasetempentity = 18,
	nextbotcombatcharacter = 0,
	ceconwearable = 45,
	cbaseattributableitem = 4,
	ceconentity = 44,
	cweaponxm1014 = 244,
	cweapontaser = 239,
	csmokegrenade = 133,
	cweaponsg552 = 236,
	csensorgrenade = 129,
	cweaponsawedoff = 232,
	cweaponnova = 228,
	cincendiarygrenade = 87,
	cmolotovgrenade = 97,
	cweaponm3 = 220,
	cknifegg = 108,
	cknife = 107,
	chegrenade = 84,
	cflashbang = 66,
	cweaponelite = 211,
	cdecoygrenade = 40,
	cdeagle = 39,
	cweaponusp = 243,
	cweaponm249 = 219,
	cweaponump45 = 242,
	cweapontmp = 241,
	cweapontec9 = 240,
	cweaponssg08 = 238,
	cweaponsg556 = 237,
	cweaponsg550 = 235,
	cweaponscout = 234,
	cweaponscar20 = 233,
	cscar17 = 127,
	cweaponp90 = 231,
	cweaponp250 = 230,
	cweaponp228 = 229,
	cweaponnegev = 227,
	cweaponmp9 = 226,
	cweaponmp7 = 225,
	cweaponmp5navy = 224,
	cweaponmag7 = 223,
	cweaponmac10 = 222,
	cweaponm4a1 = 221,
	cweaponhkp2000 = 218,
	cweaponglock = 217,
	cweapongalilar = 216,
	cweapongalil = 215,
	cweapong3sg1 = 214,
	cweaponfiveseven = 213,
	cweaponfamas = 212,
	cweaponbizon = 207,
	cweaponawp = 205,
	cweaponaug = 204,
	cak47 = 1,
	cweaponcsbasegun = 209,
	cweaponcsbase = 208,
	cc4 = 29,
	cweaponbaseitem = 206,
	cbasecsgrenade = 8,
	csmokegrenadeprojectile = 134,
	csensorgrenadeprojectile = 130,
	cmolotovprojectile = 98,
	citem_healthshot = 91,
	citemdogtags = 92,
	cdecoyprojectile = 41,
	cfirecrackerblast = 62,
	cinferno = 88,
	cchicken = 31,
	cfootstepcontrol = 68,
	ccsgamerulesproxy = 34,
	cweaponcubemap = 0,
	cweaponcycler = 210,
	cteplantbomb = 183,
	ctefirebullets = 170,
	cteradioicon = 187,
	cplantedc4 = 108,
	ccsteam = 38,
	ccsplayerresource = 36,
	ccsplayer = 35,
	ccsragdoll = 37,
	cteplayeranimevent = 184,
	chostage = 85,
	chostagecarriableprop = 86,
	cbasecsgrenadeprojectile = 9,
	chandletest = 83,
	cteamplayroundbasedrulesproxy = 146,
	cspritetrail = 140,
	cspriteoriented = 139,
	csprite = 138,
	cragdollpropattached = 125,
	cragdollprop = 124,
	cpredictedviewmodel = 118,
	cposecontroller = 114,
	cgamerulesproxy = 82,
	cinfoladderdismount = 89,
	cfuncladder = 74,
	ctefoundryhelpers = 173,
	cenvdetailcontroller = 52,
	cworld = 245,
	cwaterlodcontrol = 203,
	cwaterbullet = 202,
	cvotecontroller = 201,
	cvguiscreen = 200,
	cpropjeep = 121,
	cpropvehiclechoreogeneric = 0,
	ctriggersoundoperator = 199,
	cbasevphysicstrigger = 22,
	ctriggerplayermovement = 198,
	cbasetrigger = 20,
	ctest_proxytoggle_networkable = 195,
	ctesla = 190,
	cbaseteamobjectiveresource = 17,
	cteam = 145,
	csunlightshadowcontrol = 144,
	csun = 143,
	cparticleperformancemonitor = 101,
	cspotlightend = 137,
	cspatialentity = 136,
	cslideshowdisplay = 132,
	cshadowcontrol = 131,
	csceneentity = 128,
	cropekeyframe = 126,
	cragdollmanager = 123,
	cphysicspropmultiplayer = 106,
	cphysboxmultiplayer = 104,
	cpropdoorrotating = 120,
	cbasepropdoor = 16,
	cdynamicprop = 43,
	cprop_hallucination = 119,
	cpostprocesscontroller = 115,
	cpointworldtext = 113,
	cpointcommentarynode = 112,
	cpointcamera = 111,
	cplayerresource = 110,
	cplasma = 109,
	cphysmagnet = 107,
	cphysicsprop = 105,
	cstatueprop = 141,
	cphysbox = 103,
	cparticlesystem = 102,
	cmoviedisplay = 99,
	cmaterialmodifycontrol = 96,
	clightglow = 95,
	citemassaultsuituseable = 0,
	citem = 0,
	cinfooverlayaccessor = 90,
	cfunctracktrain = 81,
	cfuncsmokevolume = 80,
	cfuncrotating = 79,
	cfuncreflectiveglass = 78,
	cfuncoccluder = 77,
	cfuncmovelinear = 76,
	cfuncmonitor = 75,
	cfunc_lod = 70,
	ctedust = 165,
	cfunc_dust = 69,
	cfuncconveyor = 73,
	cfuncbrush = 72,
	cbreakablesurface = 28,
	cfuncareaportalwindow = 71,
	cfish = 65,
	cfiresmoke = 63,
	cenvtonemapcontroller = 59,
	cenvscreeneffect = 57,
	cenvscreenoverlay = 58,
	cenvprojectedtexture = 55,
	cenvparticlescript = 54,
	cfogcontroller = 67,
	cenvdofcontroller = 53,
	ccascadelight = 30,
	cenvambientlight = 51,
	centityparticletrail = 50,
	centityfreezing = 49,
	centityflame = 48,
	centitydissolve = 47,
	cdynamiclight = 42,
	ccolorcorrectionvolume = 33,
	ccolorcorrection = 32,
	cbreakableprop = 27,
	cbeamspotlight = 25,
	cbasebutton = 5,
	cbasetoggle = 19,
	cbaseplayer = 15,
	cbaseflex = 12,
	cbaseentity = 11,
	cbasedoor = 10,
	cbasecombatcharacter = 6,
	cbaseanimatingoverlay = 3,
	cbonefollower = 26,
	cbaseanimating = 2,
	cai_basenpc = 0,
	cbeam = 24,
	cbaseviewmodel = 21,
	cbaseparticleentity = 14,
	cbasegrenade = 13,
	cbasecombatweapon = 7,
	cbaseweaponworldmodel = 23
};

class client_class
{
public:
	create_client_class_fn create_fn;
	create_event_fn create_event_fn;
	char* network_name;
	recv_table* recvtable_ptr;
	client_class* next_ptr;
	class_ids class_id;
};