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

#include "vel_graph.hpp"
#include "../../engine/utilities/config.hpp"
#include "../input/input.hpp"
#include "../hooks/hooks.hpp"
#include "../renderer/renderer.hpp"

#include "../../engine/utilities/xorstring.hpp"

#define vel_graph_size 65 // make it a config nigger shit later
#define vel_graph_scale 7.5f

void velocity_graph::gather_data() {
	// Get our local player
	const auto local_player = interfaces::entity_list->get<player_t>(interfaces::engine->get_local_player());

	// Check if we should draw the graph
	if (!local_player->sane(false, false) || !*config::get<bool>(crc("misc:vel:graph"))) {
		if (!data.empty()) {
			data.clear();
		}

		return;
	}

	// Check if our vector reached the maximum capacity and, if so, delete the last value. 
	// PS: You can choose how much data to use in your chart. For this example I'll be using 90 hello.
	if (data.size() > vel_graph_size) {
		data.pop_back();
	}

	// Create our velocity_data_t object.
	velocity_data_t current_data;

	// Get our local player's velocity vector and get it's 2D length.
	vec3_t velocity = local_player->velocity();
	float speed = velocity.length_2d();

	// Get our local player's flags and check if we're on the ground.
	int flags = local_player->flags();
	bool on_ground = flags & fl_onground;

	// Update our velocity_data_t object.
	current_data.speed = speed;
	current_data.on_ground = on_ground;

	// Insert the new data at the beggining of our vector.
	data.insert(data.begin(), current_data);
}

void velocity_graph::draw() {
	// Get our local player
	const auto local_player = interfaces::entity_list->get<player_t>(interfaces::engine->get_local_player());

	// Check if we should draw the graph
	if (!local_player->sane(false, false) || !*config::get<bool>(crc("misc:vel:graph"))) {
		if (!data.empty()) {
			data.clear();
		}

		return;
	}

	// Get our current speed to draw the speed indicator
	vec3_t velocity = local_player->velocity();
	float current_speed = velocity.length_2d();

	// Check if we have enough data to draw a graph
	if (data.size() < 2) {
		return;
	}

	// Gather our screen width and height
	int x, y;
	interfaces::engine->get_screen_size(x, y);

	// Loop for each element of our data vector.
	for (auto i = 0ul; i < data.size() - 1; i++) {
		// Gather the needed data
		const auto current = data[i];
		const auto next = data[i + 1];
		const auto landed = !current.on_ground && next.on_ground;

		// You can make this adaptive, however, I will just clamp it to 450 since you rarely will be achieving this speed on match making.
		const auto clamped_current_speed = std::clamp(current.speed, 0, 450);
		const auto clamped_next_speed = std::clamp(next.speed, 0, 450);

		const auto graph_pos = point(x / 2 + vel_graph_size * (vel_graph_scale / 2.f), y / 1.2 + 130);

		float current_speed = (clamped_current_speed * 75 / 320);
		float next_speed = (clamped_next_speed * 75 / 320);

		float max_val = (int)data.size() - 1;
		float val = (int)i;

		int alpha = fabs(max_val - fabs(val - max_val / 2) * 2.f);

		// Render each line of the graph
		render::line(
			point(graph_pos.x - (i - 1) * vel_graph_scale,
				graph_pos.y - current_speed),

			point(graph_pos.x - i * vel_graph_scale,
				graph_pos.y - next_speed),

			color(255, 255, 255, alpha)
		);
	}
}