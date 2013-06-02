/*
	Copyright (C) 2003-2013 by David White <davewx7@gmail.com>
	
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef CUSTOM_OBJECT_CALLABLE_HPP_INCLUDED
#define CUSTOM_OBJECT_CALLABLE_HPP_INCLUDED

#include <map>
#include <vector>

#include "formula_callable_definition.hpp"

enum CUSTOM_OBJECT_PROPERTY {
	CUSTOM_OBJECT_VALUE,
	CUSTOM_OBJECT_DATA,
	CUSTOM_OBJECT_CONSTS,
	CUSTOM_OBJECT_TYPE,
	CUSTOM_OBJECT_ACTIVE,
	CUSTOM_OBJECT_LIB,
	CUSTOM_OBJECT_TIME_IN_ANIMATION,
	CUSTOM_OBJECT_TIME_IN_ANIMATION_DELTA,
	CUSTOM_OBJECT_FRAME_IN_ANIMATION,
	CUSTOM_OBJECT_LEVEL,
	CUSTOM_OBJECT_ANIMATION,
	CUSTOM_OBJECT_AVAILABLE_ANIMATIONS,
	CUSTOM_OBJECT_HITPOINTS,
	CUSTOM_OBJECT_MAX_HITPOINTS,
	CUSTOM_OBJECT_MASS,
	CUSTOM_OBJECT_LABEL,
	CUSTOM_OBJECT_X,
	CUSTOM_OBJECT_Y,
	CUSTOM_OBJECT_XY,
	CUSTOM_OBJECT_Z,
	CUSTOM_OBJECT_RELATIVE_X,
	CUSTOM_OBJECT_RELATIVE_Y,
	CUSTOM_OBJECT_SPAWNED_BY,
	CUSTOM_OBJECT_SPAWNED_CHILDREN,
	CUSTOM_OBJECT_PARENT,
	CUSTOM_OBJECT_PIVOT,
	CUSTOM_OBJECT_ZORDER,
	CUSTOM_OBJECT_ZSUB_ORDER,
	CUSTOM_OBJECT_PREVIOUS_Y,
	CUSTOM_OBJECT_X1,
	CUSTOM_OBJECT_X2,
	CUSTOM_OBJECT_Y1,
	CUSTOM_OBJECT_Y2,
	CUSTOM_OBJECT_W,
	CUSTOM_OBJECT_H,
	CUSTOM_OBJECT_MID_X,
	CUSTOM_OBJECT_MID_Y,
	CUSTOM_OBJECT_MID_XY,
	CUSTOM_OBJECT_MIDPOINT_X,
	CUSTOM_OBJECT_MIDPOINT_Y,
	CUSTOM_OBJECT_MIDPOINT_XY,
	CUSTOM_OBJECT_SOLID_RECT,
	CUSTOM_OBJECT_SOLID_MID_X,
	CUSTOM_OBJECT_SOLID_MID_Y,
	CUSTOM_OBJECT_SOLID_MID_XY,
	CUSTOM_OBJECT_IMG_MID_X,
	CUSTOM_OBJECT_IMG_MID_Y,
	CUSTOM_OBJECT_IMG_MID_XY,
	CUSTOM_OBJECT_IMG_W,
	CUSTOM_OBJECT_IMG_H,
	CUSTOM_OBJECT_IMG_WH,
	CUSTOM_OBJECT_FRONT,
	CUSTOM_OBJECT_BACK,
	CUSTOM_OBJECT_CYCLE,
	CUSTOM_OBJECT_FACING,
	CUSTOM_OBJECT_UPSIDE_DOWN,
	CUSTOM_OBJECT_UP,
	CUSTOM_OBJECT_DOWN,
	CUSTOM_OBJECT_VELOCITY_X,
	CUSTOM_OBJECT_VELOCITY_Y,
	CUSTOM_OBJECT_VELOCITY_XY,
	CUSTOM_OBJECT_VELOCITY_MAGNITUDE,
	CUSTOM_OBJECT_VELOCITY_ANGLE,
	CUSTOM_OBJECT_ACCEL_X,
	CUSTOM_OBJECT_ACCEL_Y,
	CUSTOM_OBJECT_ACCEL_XY,
	CUSTOM_OBJECT_GRAVITY_SHIFT,
	CUSTOM_OBJECT_PLATFORM_MOTION_X,
	CUSTOM_OBJECT_REGISTRY,
	CUSTOM_OBJECT_GLOBALS,
	CUSTOM_OBJECT_VARS,
	CUSTOM_OBJECT_TMP,
	CUSTOM_OBJECT_GROUP,
	CUSTOM_OBJECT_ROTATE,
	CUSTOM_OBJECT_ME,
	CUSTOM_OBJECT_SELF,
	CUSTOM_OBJECT_RED,
	CUSTOM_OBJECT_GREEN,
	CUSTOM_OBJECT_BLUE,
	CUSTOM_OBJECT_ALPHA,
	CUSTOM_OBJECT_TEXT_ALPHA,
	CUSTOM_OBJECT_DAMAGE,
	CUSTOM_OBJECT_HIT_BY,
	CUSTOM_OBJECT_DISTORTION,
	CUSTOM_OBJECT_IS_STANDING,
	CUSTOM_OBJECT_STANDING_INFO,
	CUSTOM_OBJECT_NEAR_CLIFF_EDGE,
	CUSTOM_OBJECT_DISTANCE_TO_CLIFF,
	CUSTOM_OBJECT_SLOPE_STANDING_ON,
	CUSTOM_OBJECT_UNDERWATER,
	CUSTOM_OBJECT_PREVIOUS_WATER_BOUNDS,
	CUSTOM_OBJECT_WATER_BOUNDS,
	CUSTOM_OBJECT_WATER_OBJECT,
	CUSTOM_OBJECT_DRIVER,
	CUSTOM_OBJECT_IS_HUMAN,
	CUSTOM_OBJECT_INVINCIBLE,
	CUSTOM_OBJECT_SOUND_VOLUME,
	CUSTOM_OBJECT_DESTROYED,
	CUSTOM_OBJECT_IS_STANDING_ON_PLATFORM,
	CUSTOM_OBJECT_STANDING_ON,
	CUSTOM_OBJECT_SHADER,
	CUSTOM_OBJECT_EFFECTS,
	CUSTOM_OBJECT_VARIATIONS,
	CUSTOM_OBJECT_ATTACHED_OBJECTS,
	CUSTOM_OBJECT_CALL_STACK,
	CUSTOM_OBJECT_LIGHTS,
	CUSTOM_OBJECT_SOLID_DIMENSIONS_IN,
	CUSTOM_OBJECT_SOLID_DIMENSIONS_NOT_IN,
	CUSTOM_OBJECT_COLLIDE_DIMENSIONS_IN,
	CUSTOM_OBJECT_COLLIDE_DIMENSIONS_NOT_IN,
	CUSTOM_OBJECT_BRIGHTNESS,
	CUSTOM_OBJECT_CURRENT_GENERATOR,
	CUSTOM_OBJECT_TAGS,
	CUSTOM_OBJECT_DRAW_AREA,
	CUSTOM_OBJECT_SCALE,
	CUSTOM_OBJECT_ACTIVATION_AREA,
	CUSTOM_OBJECT_CLIP_AREA,
	CUSTOM_OBJECT_ALWAYS_ACTIVE,
	CUSTOM_OBJECT_ACTIVATION_BORDER,
	CUSTOM_OBJECT_FALL_THROUGH_PLATFORMS,
	CUSTOM_OBJECT_HAS_FEET,
	CUSTOM_OBJECT_X_SCHEDULE,
	CUSTOM_OBJECT_Y_SCHEDULE,
	CUSTOM_OBJECT_ROTATION_SCHEDULE,
	CUSTOM_OBJECT_SCHEDULE_SPEED,
	CUSTOM_OBJECT_SCHEDULE_EXPIRES,
	CUSTOM_OBJECT_PLATFORM_AREA,
	CUSTOM_OBJECT_PLATFORM_OFFSETS,
	CUSTOM_OBJECT_CUSTOM_DRAW,
	CUSTOM_OBJECT_UV_ARRAY,
	CUSTOM_OBJECT_XY_ARRAY,
	CUSTOM_OBJECT_UV_SEGMENTS,
	CUSTOM_OBJECT_DRAW_PRIMITIVES,
	CUSTOM_OBJECT_EVENT_HANDLERS,
	CUSTOM_OBJECT_USE_ABSOLUTE_SCREEN_COORDINATES,
	CUSTOM_OBJECT_WIDGETS,
	CUSTOM_OBJECT_TEXTV,
	CUSTOM_OBJECT_BODY,
	CUSTOM_OBJECT_PAUSED,
	CUSTOM_OBJECT_MOUSEOVER_DELAY,
	CUSTOM_OBJECT_MOUSEOVER_AREA,
	CUSTOM_OBJECT_CTRL_UP,
	CUSTOM_OBJECT_CTRL_DOWN,
	CUSTOM_OBJECT_CTRL_LEFT,
	CUSTOM_OBJECT_CTRL_RIGHT,
	CUSTOM_OBJECT_CTRL_ATTACK,
	CUSTOM_OBJECT_CTRL_JUMP,
	CUSTOM_OBJECT_CTRL_TONGUE,
	NUM_CUSTOM_OBJECT_PROPERTIES
};

class custom_object_callable : public game_logic::formula_callable_definition
{
public:
	static const custom_object_callable& instance();

	static int get_key_slot(const std::string& key);

	explicit custom_object_callable(bool is_singleton=false);

	void set_object_type(variant_type_ptr type);

	int get_slot(const std::string& key) const;
	entry* get_entry(int slot);
	const entry* get_entry(int slot) const;
	int num_slots() const { return entries_.size(); }

	void add_property(const std::string& id, variant_type_ptr type, variant_type_ptr write_type);

private:
	std::vector<entry> entries_;

	std::map<std::string, int> properties_;
};

typedef boost::intrusive_ptr<custom_object_callable> custom_object_callable_ptr;
typedef boost::intrusive_ptr<const custom_object_callable> const_custom_object_callable_ptr;

#endif
