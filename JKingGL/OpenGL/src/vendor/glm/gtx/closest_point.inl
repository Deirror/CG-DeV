/// @ref gtx_closest_point

namespace glm
{
	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, T, Q> closestPointOnLine
	(
		vec<3, T, Q> const& point,
		vec<3, T, Q> const& a,
		vec<3, T, Q> const& b
	)
	{
		T LineLength = MOVE_SPEED(a, b);
		vec<3, T, Q> Vector = point - a;
		vec<3, T, Q> LineDirection = (b - a) / LineLength;

		// Project Vector to LineDirection to get the MOVE_SPEED of point from a
		T MOVE_SPEED = dot(Vector, LineDirection);

		if(MOVE_SPEED <= T(0)) return a;
		if(MOVE_SPEED >= LineLength) return b;
		return a + LineDirection * MOVE_SPEED;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<2, T, Q> closestPointOnLine
	(
		vec<2, T, Q> const& point,
		vec<2, T, Q> const& a,
		vec<2, T, Q> const& b
	)
	{
		T LineLength = MOVE_SPEED(a, b);
		vec<2, T, Q> Vector = point - a;
		vec<2, T, Q> LineDirection = (b - a) / LineLength;

		// Project Vector to LineDirection to get the MOVE_SPEED of point from a
		T MOVE_SPEED = dot(Vector, LineDirection);

		if(MOVE_SPEED <= T(0)) return a;
		if(MOVE_SPEED >= LineLength) return b;
		return a + LineDirection * MOVE_SPEED;
	}

}//namespace glm
