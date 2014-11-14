#include "camera.h"

using Gema::Camera;

void	Camera::update() noexcept
{
	if (this->_move.z() > 0)
		this->_pos = this->_pos.add(this->_forward.mul(this->_speed));
	else if (this->_move.z() < 0)
		this->_pos = this->_pos.add(this->_forward.mul(this->_speed).negate());
	if (this->_move.x() > 0)
		this->_pos = this->_pos.add(this->_left.mul(this->_speed).negate());
	else if (this->_move.x() < 0)
		this->_pos = this->_pos.add(this->_left.mul(this->_speed));
	this->_look = this->_pos.add(this->_forward);
}

void 	Camera::onMouseMove(int16_t xRel, int16_t yRel) noexcept
{
	this->_phi += -yRel * this->_sensitivity;
	this->_theta += -xRel * this->_sensitivity;

	if (this->_phi > 89.0)
		this->_phi = 89.0;
	else if (this->_phi < -89.0)
		this->_phi = -89.0;

	float	phi = this->_phi * M_PI / 180.0;
	float	theta = this->_theta * M_PI / 180.0;

	float	phicos = cos(phi);

	this->_forward.x() = phicos * sin(theta);
	this->_forward.y() = sin(phi);
	this->_forward.z() = phicos * cos(theta);

	this->_left = vec3::cross(this->_up, this->_forward).normalize();
	this->_look = this->_pos.add(this->_forward);
}

void 	Camera::onMousePressed(uint8_t button) noexcept
{
	(void)button;
}

void 	Camera::onMouseReleased(uint8_t button) noexcept
{
	(void)button;
}

bool 	Camera::onKeyPressed(SDL_Scancode code) noexcept
{
	switch(code)
	{
		case SDL_SCANCODE_W:
		{
			this->_move.z() += 1;
			break ;
		}
		case SDL_SCANCODE_S:
		{
			this->_move.z() -= 1;
			break ;
		}
		case SDL_SCANCODE_A:
		{
			this->_move.x() -= 1;
			break ;
		}
		case SDL_SCANCODE_D:
		{
			this->_move.x() += 1;
			break ;
		}
		default:
			break ;
	}
	return (true);
}

bool 	Camera::onKeyReleased(SDL_Scancode code) noexcept
{
	switch(code)
	{
		case SDL_SCANCODE_W:
		{
			this->_move.z() -= 1;
			break ;
		}
		case SDL_SCANCODE_S:
		{
			this->_move.z() += 1;
			break ;
		}
		case SDL_SCANCODE_A:
		{
			this->_move.x() += 1;
			break ;
		}
		case SDL_SCANCODE_D:
		{
			this->_move.x() -= 1;
			break ;
		}
		default:
			break ;
	}
	return (true);
}