#Build all executables
all: hello questions_3 ascii_image image_file four_square simple_squares_ascii ppm_menu



#________________________________________________________Compile Class Files______________________________________________________
Image.o: Image.cpp image_menu.h MenuData.h ComplexFractal.h ThreadedGrid.h
	g++ -c -lpthread -std=c++11 $<

ActionData.o: ActionData.cpp ActionData.h image_menu.h MenuData.h ComplexFractal.h ThreadedGrid.h
	g++ -c -lpthread -std=c++11 $<

PPM.o: PPM.cpp Image.h image_menu.h PPM.h MenuData.h ComplexFractal.h ThreadedGrid.h
	g++ -c -lpthread -std=c++11 $<

MenuData.o: MenuData.cpp image_menu.h MenuData.h ComplexFractal.h ThreadedGrid.h
	g++ -c -lpthread -std=c++11 $<

NumberGrid.o: NumberGrid.cpp image_menu.h MenuData.h PPM.h ComplexFractal.h JuliaSet.h ThreadedGrid.h
	g++ -c -lpthread -std=c++11 $<

ColorTable.o: ColorTable.cpp image_menu.h MenuData.h PPM.h JuliaSet.h ThreadedGrid.h
	g++ -c -lpthread -std=c++11 $<

ComplexFractal.o: ComplexFractal.cpp image_menu.h MenuData.h PPM.h ThreadedGrid.h
	g++ -c -lpthread -std=c++11 $<

JuliaSet.o: JuliaSet.cpp image_menu.h MenuData.h PPM.h ComplexFractal.h ThreadedGrid.h
	g++ -c -lpthread -std=c++11 $<

MandelbrotSet.o: MandelbrotSet.cpp MandelbrotSet.h image_menu.h MenuData.h PPM.h ComplexFractal.h ThreadedGrid.h
	g++ -c -lpthread -std=c++11 $<

ThreadedGrid.o: ThreadedGrid.cpp ThreadedGrid.h MandelbrotSet.h image_menu.h MenuData.h PPM.h ComplexFractal.h ThreadedVector.h
	g++ -c -lpthread -std=c++11 $<
#________________________________________________________End Compile Class Files__________________________________________________



#________________________________________________________Compile Files With Main Calls______________________________________________________
hello.o: hello.cpp
	g++ -c -lpthread -std=c++11 $<

questions_3.o: questions_3.cpp image_menu.h MenuData.h
	g++ -c -lpthread -std=c++11 $<

ascii_image.o: ascii_image.cpp image_menu.h MenuData.h
	g++ -c -lpthread -std=c++11 $<

image_file.o: image_file.cpp Image.h image_menu.h PPM.h MenuData.h
	g++ -c -lpthread -std=c++11 $<

four_square.o: four_square.cpp image_menu.h MenuData.h
	g++ -c -lpthread -std=c++11 $<

simple_squares_ascii.o: simple_squares_ascii.cpp image_menu.h MenuData.h
	g++ -c -lpthread -std=c++11 $<

ppm_menu.o: ppm_menu.cpp image_menu.h MenuData.h
	g++ -c -lpthread -std=c++11 $<
#________________________________________________________End Compile Files With Main Calls__________________________________________________



#________________________________________________________Build Executable Files______________________________________________________
hello: hello.o
	g++ -o hello $^

simple_squares_ascii: simple_squares_ascii.o Image.o user_io.o controllers.o PPM.o image_drawing.o image_output.o ActionData.o image_menu.h MenuData.h MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o MandelbrotSet.h ThreadedGrid.o
	g++ -o simple_squares_ascii $^ -lpthread

four_square: four_square.o Image.o user_io.o controllers.o PPM.o image_drawing.o image_output.o ActionData.o image_menu.h MenuData.h MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o MandelbrotSet.h ThreadedGrid.o
	g++ -o four_square $^ -lpthread

image_file: PPM.o Image.o user_io.o controllers.o PPM.o image_file.o image_drawing.o image_output.o ActionData.o image_menu.h MenuData.h MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o MandelbrotSet.h ThreadedGrid.o
	g++ -o image_file $^ -lpthread

ascii_image: ascii_image.o Image.o user_io.o controllers.o PPM.o image_drawing.o image_output.o ActionData.o image_menu.h MenuData.h MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o MandelbrotSet.h ThreadedGrid.o
	g++ -o ascii_image $^ -lpthread

questions_3: questions_3.o Image.o user_io.o controllers.o PPM.o image_drawing.o image_output.o ActionData.o image_menu.h MenuData.h MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o MandelbrotSet.h ThreadedGrid.o 
	g++ -o questions_3 $^ -lpthread

ppm_menu: ppm_menu.o Image.o user_io.o controllers.o PPM.o image_drawing.o image_output.o ActionData.o image_menu.h MenuData.h MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o MandelbrotSet.h ThreadedGrid.o
	g++ -o ppm_menu $^ -lpthread
#________________________________________________________End Build Executable Files__________________________________________________



#________________________________________________________Compile Utility/Function Files______________________________________________________
controllers.o: controllers.cpp image_menu.h image_output.o ActionData.h Image.h PPM.h image_drawing.o MenuData.h ComplexFractal.h ComplexFractal.o JuliaSet.o JuliaSet.h MandelbrotSet.o MandelbrotSet.h ThreadedGrid.o ThreadedGrid.h
	g++ -c -lpthread -std=c++11 $<

user_io.o: user_io.cpp image_menu.h MenuData.h JuliaSet.h MandelbrotSet.h ThreadedGrid.o
	g++ -c -lpthread -std=c++11 $<

image_output.o: image_output.cpp image_menu.h MenuData.h JuliaSet.h ThreadedGrid.o
	g++ -c -lpthread -std=c++11 $<

image_drawing.o: image_drawing.cpp image_menu.h MenuData.h JuliaSet.h ThreadedGrid.o
	g++ -c -lpthread -std=c++11 $<

image_filters.o: image_filters.cpp image_menu.h MenuData.h JuliaSet.h
	g++ -c -lpthread -std=c++11 $<
#________________________________________________________End Compile Utility/Function Files__________________________________________________

#Clean up unecessary files.
clean:
	-rm -f *.o *~ *.ppm