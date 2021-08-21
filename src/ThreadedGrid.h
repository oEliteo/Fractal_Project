#ifndef _THREADEDGRID_H_
#define _THREADEDGRID_H_
#include "ThreadedVector.h"
#include "NumberGrid.h"
#include <thread>
#include <mutex>

class Task{
	public:
		Task(const int& rows, const int& cols);
		int getEndRows() const;
		int getStartRows() const;
		int getCols() const;
		void setStartRows(const int& rows);
		void setEndRows(const int& rows);
		void setCols(const int& cols);
	private:
		int mStartRows;
		int mEndRows;
		int mCols;
};


class ThreadedGrid: public NumberGrid {
	public:
		ThreadedGrid();
		ThreadedGrid(const int& height, const int& width);
		virtual ~ThreadedGrid();
		virtual void calculateAllNumbers();
		virtual void worker();
	private:
		ThreadedVector<Task> mTasks;
};


#endif //_THREADEDGRID_H_