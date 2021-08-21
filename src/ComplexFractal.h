#ifndef _COMPLEXFRACTAL_H_
#define _COMPLEXFRACTAL_H_
#include "NumberGrid.h"
#include "ThreadedGrid.h"

class ComplexFractal: public ThreadedGrid{
	public:
		ComplexFractal();
		ComplexFractal( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y );
		virtual ~ComplexFractal( );
		double getMinX( ) const;
		double getMaxX( ) const;
		double getMinY( ) const;
		double getMaxY( ) const;
		virtual void setGridSize(const int& height, const int& width);
		void setPlaneSize( const double& min_x, const double& max_x, const double& min_y, const double& max_y );
		double getDeltaX( ) const;
		double getDeltaY( ) const;
		void setDeltas( const double& delta_x, const double& delta_y );
		double calculateDeltaY( ) const;
		double calculateDeltaX( ) const;
		double calculatePlaneXFromPixelColumn( const int& column ) const;
		double calculatePlaneYFromPixelRow( const int& row ) const;
		void calculatePlaneCoordinatesFromPixelCoordinates( const int& row, const int& column, double& x, double& y ) const;
		virtual int calculateNumber( const int& row, const int& column ) const;
	private:
		double mMin_x;
		double mMax_x;
		double mMin_y;
		double mMax_y;
		double mDeltaX;
		double mDeltaY;
};

#endif //_COMPLEXFRACTAL_H_