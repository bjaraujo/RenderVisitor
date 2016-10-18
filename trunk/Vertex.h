#pragma once

namespace geo
{

	class Vertex {
	
	private:
		double m_x, m_y;

	public:
		Vertex(double x, double y);

		double x();
		double y();

	};

}
