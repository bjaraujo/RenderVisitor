#pragma once

namespace geo
{

	class Color {
	
	private:
		double m_r, m_g, m_b;

	public:
		Color(double r, double g, double b);

		double r();
		double g();
		double b();

	};

}
