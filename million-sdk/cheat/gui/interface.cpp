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

#include "gui.hpp"
#include "../input/input.hpp"
#include "../cheat.hpp"

void gui::gui_interface() {
	if (input::click(VK_INSERT))
	{
		gui::ctx.open = !gui::ctx.open;
	}

	if (!gui_init++)
	{
		ctx.add_tab(xor (L"Assistance"));
		ctx.add_tab(xor (L"Visuals"));
		ctx.add_tab(xor (L"Misc"));
		ctx.add_tab(xor (L"Settings"));
		gui_init++;

		// lol default vars here im lazy
		*config::get<color>(crc("menu:color")) = color(0, 251, 255);
		*config::get<color>(crc("esp:box:color")) = color(255, 255, 255);
		*config::get<color>(crc("esp:glow:color")) = color(255, 202, 196, 120);
		*config::get<color>(crc("ass:backtrack:color")) = color(255, 202, 196, 120);
		*config::get<color>(crc("esp:chams:color")) = color(0, 150, 255, 255);
		*config::get<float>(crc("esp:glow:alpha_override:value")) = 220.f;

		*config::get<float>(crc("misc:turn:recover_speed")) = 100.f;
		*config::get<float>(crc("misc:turn:turn_speed")) = 90.f;

		*config::get<float>(crc("esp:misc:hitsound_volume")) = 100.f;
		*config::get<color>(crc("esp:bomb:color")) = color(0, 255, 0, 255);

		*config::get<color>(crc("esp:chams:reflectivity_clr")) = color(255, 255, 255, 255);
	}
	// psychology
	if (gui::start(&gui_tab))
	{
		if (gui::gui_tab == 0)
		{ // assistance
		/* this shit is so ghetto pls help me */
			auto get_wpn_config = [&](int weapon) -> std::tuple<const wchar_t*, const char*>
			{
				switch (weapon)
				{
				case 0: return std::make_tuple(L"##:pistol", ":pistol"); break;
				case 1: return std::make_tuple(L"##:heavy_pistol", ":heavy_pistol"); break;
				case 2: return std::make_tuple(L"##:rifle", ":rifle"); break;
				case 3: return std::make_tuple(L"##:sniper", ":sniper"); break;
				case 4: return std::make_tuple(L"##:smg", ":smg"); break;
				case 5: return std::make_tuple(L"##:other", ":other"); break;
				}
			};

			int wpn_cfg = *config::get<int>(crc("aimbot:weapon:cfg"));

			gui::group(xor (L"Main"), 0.5f, 1.f);
			{
				const static wchar_t* weapon_cfg[] = { (L"Pistols"), (L"Heavy pistol"), (L"Rifle"), (L"Sniper"), (L"SMG"), (L"Other") };
				gui::combo(xor (L"Weapon configuration"), weapon_cfg, 5, config::get<int>(crc("aimbot:weapon:cfg")));

				gui::checkbox(std::wstring(L"Enabled").append(std::get<0>(get_wpn_config(wpn_cfg))).data(),
					config::get<bool>(crc(std::string("ass:aimbot:enabled").append(std::get<1>(get_wpn_config(wpn_cfg))).data())));

				//gui::checkbox( std::wstring( L"Aim at history" ).append( std::get<0>( get_wpn_config( wpn_cfg ) ) ).data( ),
				//	config::get<bool>(crc(std::string( "ass:aimbot:aim_at_bt" ).append( std::get<1>( get_wpn_config( wpn_cfg ) ) ).data( )) ) );

				gui::hotkey(std::wstring(L"Aimbot key").append(std::get<0>(get_wpn_config(wpn_cfg))).data(),
					config::get<int>(crc(std::string("ass:aimbot:key:value").append(std::get<1>(get_wpn_config(wpn_cfg))).data())));

				gui::checkbox(std::wstring(L"On key").append(std::get<0>(get_wpn_config(wpn_cfg))).data(),
					config::get<bool>(crc(std::string("ass:aimbot:key:enabled").append(std::get<1>(get_wpn_config(wpn_cfg))).data())));

				gui::slider<float>(std::wstring(L"Maximum FOV").append(std::get<0>(get_wpn_config(wpn_cfg))).data(),
					config::get<float>(crc(std::string("ass:aimbot:fov").append(std::get<1>(get_wpn_config(wpn_cfg))).data())), 0.f, 25.f, xor (L"%.1f"));

				const static wchar_t* hitboxes[] = { (L"Head"), (L"Neck"), (L"Chest"), (L"Stomach") };
				gui::combo(std::wstring(L"Hitbox").append(std::get<0>(get_wpn_config(wpn_cfg))).data(), hitboxes, 4,
					config::get<int>(crc(std::string("ass:aimbot:hitbox").append(std::get<1>(get_wpn_config(wpn_cfg))).data())));

				if (wpn_cfg == 2 || wpn_cfg == 4)
				{
					if (gui::checkbox(std::wstring(L"Recoil compensation").append(std::get<0>(get_wpn_config(wpn_cfg))).data(),
						config::get<bool>(crc(std::string("ass:aimbot:rcs:enabled").append(std::get<1>(get_wpn_config(wpn_cfg))).data()))))
					{

						/*gui::checkbox( std::wstring( L"Standalone" ).append( std::get<0>( get_wpn_config( wpn_cfg ) ) ).data( ),
							config::get<bool>(crc(std::string( "ass:aimbot:rcs:standalone" ).append( std::get<1>( get_wpn_config( wpn_cfg ) ) ).data( ) )));*/

							//pretty sure this shit was backwards, change back if i was wrong.

						gui::slider<float>(std::wstring(L"Recoil compensation (y)").append(std::get<0>(get_wpn_config(wpn_cfg))).data(),
							config::get<float>(crc(std::string("ass:aimbot:rcs:x").append(std::get<1>(get_wpn_config(wpn_cfg))).data())), 1.f, 100.f);

						gui::slider<float>(std::wstring(L"Recoil compensation (x)").append(std::get<0>(get_wpn_config(wpn_cfg))).data(),
							config::get<float>(crc(std::string("ass:aimbot:rcs:y").append(std::get<1>(get_wpn_config(wpn_cfg))).data())), 1.f, 100.f);
					}
				}

				if (gui::checkbox(std::wstring(L"Smoothing").append(std::get<0>(get_wpn_config(wpn_cfg))).data(),
					config::get<bool>(crc(std::string("ass:aimbot:smoothing:enabled").append(std::get<1>(get_wpn_config(wpn_cfg))).data()))))
				{
					gui::slider<float>(std::wstring(L"Smoothing amount").append(std::get<0>(get_wpn_config(wpn_cfg))).data(),
						config::get<float>(crc(std::string("ass:aimbot:smoothing:value").append(std::get<1>(get_wpn_config(wpn_cfg))).data())), 1.f, 100.f);
				}
			}
			gui::group(xor (L"Accuracy"), 0.5f, 0.53f);
			{
				if (gui::checkbox(xor (L"Backtrack"), config::get<bool>(crc("ass:backtrack"))))
				{
					const static wchar_t* boost_options[] = { (L"Low"), (L"Medium"), (L"High") };
					gui::combo(xor (L"Backtrack intensity"), boost_options, 3, config::get<int>(crc("ass::backtrack::intensity")));
				}
			}
			//gui::group( xor ( L"Triggerbot" ), 0.5f, 0.5f );
			//{
			//	if ( gui::checkbox( std::wstring( L"Enabled#Trigger" ).append( std::get<0>( get_wpn_config( wpn_cfg ) ) ).data( ),
			//		 config::get<bool>( crc( std::string( "ass:trigger:enabled" ).append( std::get<1>( get_wpn_config( wpn_cfg ) ) ).data( ) ) ) ) )
			//	{
			//
			//		gui::hotkey( std::wstring( L"Triggerbot key" ).append( std::get<0>( get_wpn_config( wpn_cfg ) ) ).data( ),
			//					 config::get<int>( crc( std::string( "ass:trigger:key:value" ).append( std::get<1>( get_wpn_config( wpn_cfg ) ) ).data( ) ) ) );
			//
			//		gui::checkbox( std::wstring( L"On key#trigger" ).append( std::get<0>( get_wpn_config( wpn_cfg ) ) ).data( ),
			//					   config::get<bool>( crc( std::string( "ass:trigger:key:enabled" ).append( std::get<1>( get_wpn_config( wpn_cfg ) ) ).data( ) ) ) );
			//
			//		gui::slider<float>( std::wstring( L"Triggerbot delay" ).append( std::get<0>( get_wpn_config( wpn_cfg ) ) ).data( ),
			//							config::get<float>( crc( std::string( "ass:trigger:delay" ).append( std::get<1>( get_wpn_config( wpn_cfg ) ) ).data( ) ) ), 0.f, 1.f, xor ( L"%.1fs" ) );
			//	}
			//}
		}
		if (gui::gui_tab == 1) { // visuals
			gui::group((L"Player ESP"), 0.5f, 1.f); {
				gui::color_picker(xor (L"box color"), config::get<color>(crc("esp:box:color")), !*config::get<bool>(crc("esp:glow:alpha_override")));
				gui::checkbox(xor (L"Bounding box"), config::get<bool>(crc("esp:box")));

				gui::checkbox(xor (L"Player name"), config::get<bool>(crc("esp:name")));
				gui::checkbox(xor (L"Health bar"), config::get<bool>(crc("esp:health")));
				gui::checkbox(xor (L"Active weapon text"), config::get<bool>(crc("esp:weapon")));
				gui::checkbox(xor (L"Active weapon icon"), config::get<bool>(crc("esp:weapon_icons")));
				gui::checkbox(xor (L"Ammo bar"), config::get<bool>(crc("esp:ammo")));
				gui::checkbox(xor (L"Flags"), config::get<bool>(crc("esp:flags")));
				gui::checkbox(xor (L"Skeleton"), config::get<bool>(crc("esp:skeleton")));
				gui::checkbox( xor ( L"Flash kill" ), config::get<bool>( crc( "esp:flashkill" ) ) );

				gui::color_picker(xor (L"gkliwo color"), config::get<color>(crc("esp:glow:color")));
				gui::checkbox(xor (L"Glow"), config::get<bool>(crc("esp:glow")));

				if (gui::checkbox(xor (L"ESP alpha override"), config::get<bool>(crc("esp:glow:alpha_override")))) {
					gui::slider(xor (L"Override value"), config::get<float>(crc("esp:glow:alpha_override:value")), 0.f, 255.f);
				}
			}

			gui::group(xor (L"Other ESP"), 0.5f, 0.55f); {

				gui::checkbox(xor (L"Crosshair"), config::get<bool>(crc("esp:crosshair")));
				gui::checkbox(xor (L"Dropped weapon"), config::get<bool>(crc("esp:dropped")));

				gui::color_picker(xor (L"Bomb color"), config::get<color>(crc("esp:bomb:color")));
				gui::checkbox(xor (L"Bomb"), config::get<bool>(crc("esp:bomb")));

				gui::checkbox(xor (L"No flash"), config::get<bool>(crc("esp:no_flash")));
				gui::checkbox(xor (L"No smoke"), config::get<bool>(crc("misc:remove_smoke")));
				gui::checkbox(xor (L"Grenade prediction"), config::get<bool>(crc("esp:nade_pred")));
				//gui::checkbox(xor (L"Grenade prediction 2"), config::get<bool>(crc("esp:nade_pred2")));
				gui::checkbox(xor (L"Radar"), config::get<bool>(crc("esp:radar")));
				gui::checkbox(xor (L"Spectators"), config::get<bool>(crc("esp:spectators")));

				if (gui::checkbox(xor (L"Hitsound"), config::get<bool>(crc("esp:misc:hitsound"))))
				{
					const static wchar_t* hitsound_options[] = { (L"Money"), (L"Arena switch press"), (L"Custom") };
					//gui::slider(xor (L"Hitsound volume"), config::get<float>(crc("esp:misc:hitsound_volume")), 0.f, 100.f);
					gui::combo(xor (L"Hitsound"), hitsound_options, 3, config::get<int>(crc("esp:misc:hitsound_type")));
				}
				//	gui::checkbox( xor ( L"Night-mode" ), config::get<bool>( xor ( "esp:nightmode" ) ) );
			}

			gui::group(xor (L"Player models"), 0.5f, 0.45f); {

				const static wchar_t* chams_material[] = { (L"Default"), (L"Flat") };
				gui::combo(xor (L"Material"), chams_material, 2, config::get<int>(crc("esp:chams:material")));

				gui::color_picker(xor (L"Player visible color"), config::get<color>(crc("esp:chams:color")));
				gui::checkbox(xor (L"Player"), config::get<bool>(crc("esp:chams:visible")));

				gui::color_picker(xor (L"Player invisible color"), config::get<color>(crc("esp:chams:invisible_color")));
				gui::checkbox(xor (L"Player (behind wall)"), config::get<bool>(crc("esp:chams:invisible")));

				gui::color_picker(xor (L"backtrack color"), config::get<color>(crc("ass:backtrack:color")));
				gui::checkbox(xor (L"History"), config::get<bool>(crc("esp:chams:backtrack")));

				gui::color_picker(xor (L"Reflectivity color"), config::get<color>(crc("esp:chams:reflectivity_clr")));
				gui::slider<float>(xor (L"Reflectivity"), config::get<float>(crc("esp:chams:reflectivity")), 0.f, 100.f, xor (L"\n"));
				gui::slider<float>(xor (L"Pearlescent"), config::get<float>(crc("esp:chams:pearlescent")), 0.f, 25.f, xor (L"\n"));
				gui::slider<float>(xor (L"Shine"), config::get<float>(crc("esp:chams:shine")), 0.f, 100.f, xor (L"\n"));
				//gui::slider<float>(xor (L"Rim"), config::get<float>(crc("esp:chams:rim")), 0.f, 100.f, xor (L"\n"));
			}
		}
		if (gui::gui_tab == 2) { // misc

			gui::group(L"Movement", 0.5f, 1.f);
			{
				gui::checkbox(xor (L"Bunny hop"), config::get<bool>(crc("misc:bhop")));
				//	gui::checkbox( xor ( L"Jump stats" ), config::get<bool>( xor ( "misc:jumpstats" ) ) );
				gui::checkbox(xor (L"Infinite duck"), config::get<bool>(crc("misc:infinite_duck")));


				gui::hotkey(xor (L"turn key"), config::get<int>(crc("misc:turn:key")));
				if (gui::checkbox(xor (L"Fake backwards"), config::get<bool>(crc("misc:turn:enabled"))))
				{
					if (gui::checkbox(xor (L"Turn indicator"), config::get<bool>(crc("misc:turn:indicator"))))
					{
						gui::checkbox(xor (L"Always shown"), config::get<bool>(crc("misc:turn:indicator_always")));
					}

					gui::slider(xor (L"Turn speed"), config::get<float>(crc("misc:turn:turn_speed")), 1.f, 100.f);
					if (!gui::checkbox(xor (L"Manual recovery"), config::get<bool>(crc("misc:turn:manual_recovery"))))
					{
						gui::slider(xor (L"Recovery speed"), config::get<float>(crc("misc:turn:recover_speed")), 1.f, 100.f);
					}
				}

				gui::hotkey(xor (L"jb key"), config::get<int>(crc("misc:jb:key")));
				if (gui::checkbox(xor (L"Jump bug"), config::get<bool>(crc("misc:jb"))))
				{
					gui::checkbox(xor (L"Jump bug indicator"), config::get<bool>(crc("misc:jb:indicator")));
				}

				gui::hotkey(xor (L"eb key"), config::get<int>(crc("misc:eb:key")));
				if (gui::checkbox(xor (L"Edge bug"), config::get<bool>(crc("misc:eb"))))
				{
					gui::checkbox(xor (L"Edge bug indicator"), config::get<bool>(crc("misc:eb:indicator")));
				}

				gui::hotkey(xor (L"ej key"), config::get<int>(crc("misc:ej:key")));
				if (gui::checkbox(xor (L"Edge jump"), config::get<bool>(crc("misc:ej"))))
				{
					gui::checkbox(xor (L"Long jump"), config::get<bool>(crc("misc:lj")));
					gui::checkbox(xor (L"Edge jump indicator"), config::get<bool>(crc("misc:ej:indicator")));
				}

				if (gui::checkbox(xor (L"Velocity indicator"), config::get<bool>(crc("misc:vel"))))
				{
					gui::checkbox(xor (L"Show take off"), config::get<bool>(crc("misc:vel:takeoff")));
					gui::checkbox(xor (L"Show graph"), config::get<bool>(crc("misc:vel:graph")));
				}

				gui::checkbox(xor (L"Stat Helper"), config::get<bool>(crc("misc:stathelper")));
			}

			gui::group(xor (L"Skins"), 0.5f, 0.42f);
			{
#define mxor(s) s
				const static wchar_t* knives[] = {
					mxor(L"Off"), mxor(L"Bayonet"), mxor(L"Classic"), mxor(L"Flip"),
					mxor(L"Gut"), mxor(L"Karambit"), mxor(L"M9 bayonet"), mxor(L"Huntsman"),
					mxor(L"Falchion"), mxor(L"Bowie"), mxor(L"Butterfly"), mxor(L"Daggers"),
					mxor(L"Paracord"), mxor(L"Survival"), mxor(L"Ursus"), mxor(L"Navaja"),
					mxor(L"Nomad"), mxor(L"Stiletto"), mxor(L"Talon"), mxor(L"Skeleton") };

				const static wchar_t* gloves[] = {
					mxor(L"Off"), mxor(L"Bloodhound"), mxor(L"Sport"), mxor(L"Driver"),	mxor(L"Handwraps"), mxor(L"Moto"), mxor(L"Specialist"), mxor(L"Hydra") };

				gui::combo(xor (L"Knife model"), knives, 20, config::get<int>(crc("misc:knife")));
				gui::numberbox(xor (L"Knife paintkit"), config::get<int>(crc("misc:knife_paintkit")));

				gui::combo(xor (L"Glove model"), gloves, 8, config::get<int>(crc("misc:glove_model")));


				//add hydra & driver
				const static wchar_t* glove_skins[] = {
					mxor(L"Bloodhound Black Silver"), mxor(L"Bloodhound Snake Skin Brass"), mxor(L"Bloodhound Metallic"), mxor(L"Bloodhound Guerrilla"),
					mxor(L"Handwraps Leather"), mxor(L"Handwraps Camo Grey"), mxor(L"Handwraps Fabric Orange Camo"), mxor(L"Handwraps Red Slaughter"),
					mxor(L"Slick Black"), mxor(L"Slick Military"), mxor(L"Slick Red"), mxor(L"Slick Snakeskin Yellow"),
					mxor(L"Sport Light Blue"), mxor(L"Sport Military"), mxor(L"Sport Pandora's box"), mxor(L"Sport Green"),
					mxor(L"Moto Basic Black"), mxor(L"Moto Mint Triangle"), mxor(L"Moto Mono Boom"), mxor(L"Moto Triangle Blue"),
					mxor(L"Specialist Forest DDPAT"), mxor(L"Specialist Crimson Kimono"), mxor(L"Specialist Emerald Web"), mxor(L"Specialist Orange White")
				};

				gui::combo(xor (L"Glove skin"), glove_skins, 24, config::get<int>(crc("misc:glove_skin")));
			}

			gui::group(xor (L"Other"), 0.5f, 0.58f); {
				gui::checkbox( xor ( L"Rank reveal" ), config::get<bool>( crc( "misc:rank_reveal" ) ) );
				gui::checkbox( xor ( L"Auto accept" ), config::get<bool>( crc( "misc:autoaccept" ) ) );
				gui::checkbox( xor ( L"Clantag" ), config::get<bool>( crc( "misc:clantag" ) ) );
				gui::checkbox( xor ( L"Watermark" ), config::get<bool>( crc( "esp:misc:watermark" ) ) );
				gui::checkbox( xor ( L"Disable panorama blur" ), config::get<bool>( crc( "esp:misc:panoramablur" ) ) );
				gui::checkbox( xor ( L"Disable post processing" ), config::get<bool>( crc( "esp:disable_post_processing" ) ) );
				gui::checkbox( xor ( L"Hurt info" ), config::get<bool>( crc( "esp:misc:hurtinfo" ) ) );
				gui::checkbox( xor ( L"Name spam" ), config::get<bool>( crc( "misc:name_spam" ) ) );
				gui::checkbox( xor ( L"Preserve killfeed" ), config::get<bool>( crc( "misc:preserve_killfeed" ) ) );

				if (gui::checkbox(xor (L"Viewmodel offset"), config::get<bool>(crc("misc:viewmodel_offset")))) {
					gui::slider(xor (L"x"), config::get<float>(crc("misc:viewmodel_offset_x")), -10.f, 10.f);
					gui::slider(xor (L"y"), config::get<float>(crc("misc:viewmodel_offset_y")), -10.f, 10.f);
					gui::slider(xor (L"z"), config::get<float>(crc("misc:viewmodel_offset_z")), -10.f, 10.f);
				}

				/*
				static const wchar_t* data_centers[ ] = {
					L"Don't change", L"Australia", L"Austria", L"Brazil", L"Chile", L"Dubai", L"France", L"Germany", L"Hong Kong", L"India (Chennai)", L"India (Mumbai)", L"Japan", L"Luxembourg",
					L"Netherlands", L"Peru", L"Philippines", L"Poland", L"Singapore", L"South Africa", L"Spain", L"Sweden", L"UK", L"USA (Atlanta)", L"USA (Bellevue)", L"USA (Chiraq)", L"USA (Los Angeles)", L"USA (Moses Lake)",
					L"USA (Oklahoma)", L"USA (Seattle)", L"USA (Washington DC)"
				};

				gui::combo( xor ( L"Server selector" ), data_centers, 30, config::get<int>( crc( "misc:data_center" ) ) );
				*/
			}
		}

		if (gui::gui_tab == 3) { // settings
			static const wchar_t* configs[] = { L"Slot 1", L"Slot 2", L"Slot 3", L"Slot 4", L"Slot 5", L"Slot 6" };
			static const char* file_names[] = { "1.mw", "2.mw", "3.mw", "4.mw", "5.mw", "6.mw" };

			gui::group(xor (L"Configs"), 0.5f, 1.f);

			gui::color_picker(xor (L"Menu color"), config::get<color>(crc("menu:color")));

			gui::combo(xor (L"Config"), configs, 6, config::get<int>(crc("cfg:idx")));

			gui::button(L"Save", [&]()
				{
					config::save_to_file(file_names[*config::get<int>(crc("cfg:idx"))]);
				}, false);

			gui::button(L"Load", [&]()
				{
					config::load_from_file(file_names[*config::get<int>(crc("cfg:idx"))]);

					skins::general::full_update();
				});

			gui::button(L"Unload", [&]()
				{
					cheat::revert();
				});

			// BAHABH SHUT UP

			ctx.menu_color_nigger = *config::get<color>(crc("menu:color"));
		}

		gui::end();
	}
}
