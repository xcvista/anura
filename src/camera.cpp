#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.hpp"
#include "preferences.hpp"
#include "variant_utils.hpp"

camera_callable::camera_callable()
	: fov_(45.0f), horizontal_angle_(float(M_PI)), vertical_angle_(0.0f),
	speed_(0.1f), mouse_speed_(0.005f)
{
	up_ = glm::vec3(0.0f, 1.0f, 0.0f);
	position_ = glm::vec3(0.0f, 0.0f, 10.0f); 

	compute_view();
}

camera_callable::camera_callable(const variant& node)
	: fov_(45.0f), horizontal_angle_(float(M_PI)), vertical_angle_(0.0f),
	speed_(0.1f), mouse_speed_(0.005f)
{
	position_ = glm::vec3(0.0f, 0.0f, 10.0f); 
	if(node.has_key("fov")) {
		fov_ = std::min(90.0f, std::max(15.0f, float(node["fov"].as_decimal().as_float())));
	}
	if(node.has_key("horizontal_angle")) {
		horizontal_angle_ = float(node["horizontal_angle"].as_decimal().as_float());
	}
	if(node.has_key("vertical_angle")) {
		vertical_angle_ = float(node["vertical_angle"].as_decimal().as_float());
	}
	if(node.has_key("speed")) {
		speed_ = float(node["speed"].as_decimal().as_float());
	}
	if(node.has_key("mouse_speed")) {
		mouse_speed_ = float(node["mouse_speed"].as_decimal().as_float());
	}

	if(node.has_key("position")) {
		ASSERT_LOG(node["position"].is_list() && node["position"].num_elements() == 3, 
			"position must be a list of 3 decimals.");
		position_ = glm::vec3(float(node["position"][0].as_decimal().as_float()),
			float(node["position"][1].as_decimal().as_float()),
			float(node["position"][2].as_decimal().as_float()));
	}

	compute_view();
}

camera_callable::~camera_callable()
{
}

variant camera_callable::write()
{
	variant_builder res;
	if(fov_ != 45.0) {
		res.add("fov", fov_);
	}
	if(horizontal_angle_ != float(M_PI)) {
		res.add("horizontal_angle", horizontal_angle_);
	}
	if(vertical_angle_ != 0.0f) {
		res.add("vertical_angle", vertical_angle_);
	}
	if(speed_ != 0.1f) {
		res.add("speed", speed_);
	}
	if(mouse_speed_ != 0.005f) {
		res.add("mouse_speed", mouse_speed_);
	}
	res.add("position", position_.x);
	res.add("position", position_.y);
	res.add("position", position_.z);
	return res.build();
}

void camera_callable::compute_view()
{
	glm::vec3 direction(
		cos(vertical_angle_) * sin(horizontal_angle_), 
		sin(vertical_angle_),
		cos(vertical_angle_) * cos(horizontal_angle_)
	);
	glm::vec3 right = glm::vec3(
		sin(horizontal_angle_ - float(M_PI)/2.0f), 
		0,
		cos(horizontal_angle_ - float(M_PI)/2.0f)
	);
	
	// Up vector
	up_ = glm::cross(right, direction);
	target_ = position_ + direction;

	view_ = glm::lookAt(position_, target_, up_);
	projection_ = glm::perspective(fov_, float(preferences::actual_screen_width())/float(preferences::actual_screen_height()), 0.01f, 1000.0f);
}

variant camera_callable::get_value(const std::string& key) const
{
	if(key == "position") {
		std::vector<variant> v;
		v.push_back(variant(position().x));
		v.push_back(variant(position().y));
		v.push_back(variant(position().z));
		return variant(&v);
	} else if(key == "speed") {
		return variant(speed());
	} else if(key == "right") {
		std::vector<variant> v;
		glm::vec3 right = glm::vec3(
			sin(hangle() - float(M_PI)/2.0f), 
			0,
			cos(hangle() - float(M_PI)/2.0f)
		);
		v.push_back(variant(right.x));
		v.push_back(variant(right.y));
		v.push_back(variant(right.z));
		return variant(&v);
	} else if(key == "direction") {
		std::vector<variant> v;
		glm::vec3 direction(
			cos(vangle()) * sin(hangle()), 
			sin(vangle()),
			cos(vangle()) * cos(hangle())
		);
		v.push_back(variant(direction.x));
		v.push_back(variant(direction.y));
		v.push_back(variant(direction.z));
		return variant(&v);
	} else if(key == "horizontal_angle" || key == "hangle") {
		return variant(hangle());
	} else if(key == "vertical_angle" || key == "vangle") {
		return variant(vangle());
	}
	return variant();
}

void camera_callable::set_value(const std::string& key, const variant& value)
{
	if(key == "position") {
		ASSERT_LOG(value.is_list() && value.num_elements() == 3, "position must be a list of 3 elements");
		set_position(glm::vec3(float(value[0].as_decimal().as_float()),
			float(value[1].as_decimal().as_float()),
			float(value[2].as_decimal().as_float())));
		compute_view();
	}
}


void camera_callable::look_at(glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
	position_ = position;
	target_ = target_;
	up_ = up;
	view_ = glm::lookAt(position_, target_, up_);
}


