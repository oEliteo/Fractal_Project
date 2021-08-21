#ifndef _ACTIONDATA_H_
#define _ACTIONDATA_H_
#include <iostream>
#include "PPM.h"
#include "NumberGrid.h"
#include "ColorTable.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"

class ActionData {
  public:
  	ActionData(std::istream& is, std::ostream& os);
  	std::istream& getIS();
  	std::ostream& getOS();
  	PPM& getInputImage1();
    PPM& getInputImage2();
  	PPM& getOutputImage();
  	bool getDone() const;
  	void setDone();
    NumberGrid& getGrid();
    void setGrid(NumberGrid *grid);
    ~ActionData();
    ColorTable& getTable();

  private:
  	std::istream& mIS;
  	std::ostream& mOS;
  	PPM mImageIn1;
    PPM mImageIn2;
  	PPM mImageOut;
  	bool mDone;
    NumberGrid *mGridPointer;
    ColorTable mColorTable;
};

#endif //_ACTIONDATA_H_