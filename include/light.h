#ifndef GEMA_LIGHT_H
# define GEMA_LIGHT_H

namespace Gema
{
	enum class LightType { POINT };
	class Light
	{
	private:
		LightType	_type = LightType::POINT;

	public:
		explicit	Light() = default;
		virtual		~Light() noexcept = default;

		inline void	setType(LightType type) noexcept {
			this->_type = type;
		}

	};
}

#endif