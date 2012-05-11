#include "line.h"

#include <cmath>
#include <iostream>


namespace bmp
{
	bool line::draw(Bitmap24& p_target, AbsoluteCoordinate p_from, AbsoluteCoordinate p_to, Color24 p_color)
	{
		if(!p_from.refersTo(p_target) || !p_to.refersTo(p_target))
		{
			return false;
		}


		int delta_X = std::abs((int)p_from.getX() - (int)p_to.getX());
		int delta_Y = std::abs((int)p_from.getY() - (int)p_to.getY());

		int Number_of_Steps = delta_Y > delta_X ? delta_Y : delta_X;

		double dX = delta_X*1.0/Number_of_Steps;
		double dY = delta_Y*1.0/Number_of_Steps;

		//std::cout << "X: " << p_to.getX() << " Y: " << p_to.getY() << std::endl;
		//std::cout << "Number: " << Number_of_Steps << std::endl;

		for(int i=0;i<=Number_of_Steps;i++) {
			p_target.setPixel((int)(i*dX + p_from.getX()+0.5), (int)(i*dY + p_from.getY()+0.5), p_color);
		}
		//p_target.setPixel(p_from.getX(), p_from.gety(), p_color);

		// please IMPLEMENT here!!

		return true;
	}




	lineto::lineto(bmp::RelativeCoordinate p_to)
		: to( p_to )
	{}

	lineto::~lineto()
	{
		/* does not require to do anything special in this implementation */
	}

	bool lineto::applyTo(bmp::BatchBitmap24& p)
	{
		line lineObj;
		AbsoluteCoordinate absTo = to.convert(p);

		if( ! lineObj.draw(p, p.getCurrentPos(), absTo, p.getCurrentColor()) )
		{
			return false;
		}

		return p.setCurrentPos( absTo );
	}
}
