#include "ThreadedGrid.h"
#include <thread>
#include <iostream>
#include <exception>
#include <mutex>

ThreadedGrid::ThreadedGrid(): NumberGrid(){

}

ThreadedGrid::ThreadedGrid(const int& height, const int& width): NumberGrid(height, width){

}

ThreadedGrid::~ThreadedGrid(){
	(void)0;
}

void ThreadedGrid::calculateAllNumbers(){
	//break up the problem size into "tasks" then create a thread that calls the worker function
	int height, width, i;
	unsigned int j;
	Task task(0,0);

	height = this->getHeight();
	width = this->getWidth();
	for(i = 0; i < height; i += 1){
		task.setStartRows(i);
		task.setCols(width);
		mTasks.push_back(task);
	}
	task.setCols(width);

//std::cout << "The total height is: " << height << "\n\n\nThe height cut into quarters = " << split << "\n\n\n";

	std::vector<std::thread> threads;
	unsigned int max_threads;
	max_threads = std::thread::hardware_concurrency();
	try{
		for(j = 0; j < max_threads; j += 1){
			threads.push_back(std::thread(&ThreadedGrid::worker, this));
		}
	}
	catch(std::system_error& e){
		std::cerr << "Unable to spawn thread!" << std::endl;
	}
	unsigned int k;
	try{
		for(k = 0; k < threads.size(); k += 1){
			threads[k].join();
		}
	}
	catch(std::system_error& e){
		std::cerr << "Unable to join thread!" << std::endl;
	}

}

void ThreadedGrid::worker(){
	std::vector<Task> my_tasks;
	int row, col, max_col;
	unsigned int i;
	while(!mTasks.empty()){
		my_tasks.clear();
		mTasks.pop_back(my_tasks, 1);
		for(i = 0; i < my_tasks.size(); i += 1){
			max_col = my_tasks[i].getCols();
			row = my_tasks[i].getStartRows();
			for(col = 0; col < max_col; col += 1){
				setNumber(row, col, calculateNumber(row, col));
			}
		}
	}
}



Task::Task(const int& rows, const int& cols): mStartRows(rows), mCols(cols){

}

int Task::getStartRows() const{
	return this->mStartRows;
}

int Task::getEndRows() const{
	return this->mEndRows;
}

int Task::getCols() const{
	return this->mCols;
}

void Task::setStartRows(const int& rows){
	this->mStartRows = rows;
}

void Task::setEndRows(const int& rows){
	this->mEndRows = rows;
}

void Task::setCols(const int& cols){
	this->mCols = cols;
}
