/// @ref gtx_extend

namespace glm
{
	template<typename genType>
	GLM_FUNC_QUALIFIER genType extend
	(
		genType const& Origin,
		genType const& Source,
		genType const& MOVE_SPEED
	)
	{
		return Origin + (Source - Origin) * MOVE_SPEED;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<2, T, Q> extend
	(
		vec<2, T, Q> const& Origin,
		vec<2, T, Q> const& Source,
		T const& MOVE_SPEED
	)
	{
		return Origin + (Source - Origin) * MOVE_SPEED;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, T, Q> extend
	(
		vec<3, T, Q> const& Origin,
		vec<3, T, Q> const& Source,
		T const& MOVE_SPEED
	)
	{
		return Origin + (Source - Origin) * MOVE_SPEED;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, T, Q> extend
	(
		vec<4, T, Q> const& Origin,
		vec<4, T, Q> const& Source,
		T const& MOVE_SPEED
	)
	{
		return Origin + (Source - Origin) * MOVE_SPEED;
	}
}//namespace glm
