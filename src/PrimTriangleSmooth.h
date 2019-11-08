 
#pragma once

#include "PrimTriangle.h"
#include "IShader.h"


class CPrimTriangleSmooth : public CPrimTriangle
{
public:

	CPrimTriangleSmooth(Vec3f a, Vec3f b, Vec3f c, Vec3f na, Vec3f nb, Vec3f nc, std::shared_ptr<IShader> pShader)
		: CPrimTriangle(a, b, c, pShader)
		, m_na(na)
		, m_nb(nb)
		, m_nc(nc)
	{}
	virtual ~CPrimTriangleSmooth(void) = default;

	virtual Vec3f getNormal(const Ray& ray) const override
	{
		// assume u/v coordinates in ray correspond to beta(u) and gamma(v) barycentric coordinates of 
		// hitpoint on triangle (have to be stored like this in the intersection code!)
		// --- PUT YOUR CODE HERE ---
		return normalize(ray.u * m_na + ray.v * m_nb + (1-ray.u-ray.v) * m_nc);
	}

private:
	Vec3f m_na;	///< vertex a normal
	Vec3f m_nb;	///< vertex b normal
	Vec3f m_nc; ///< vertex c normal
};


