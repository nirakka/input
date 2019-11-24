CPPUNIT_PATH=/usr/local
GCC = g++ -std=c++14 -g

TARGET = checkwarntest
SRCS   = checkwarntest.cpp checkwarn.cpp
OBJS   = $(SRCS:.cpp=.o) main.o

all : $(TARGET)

$(TARGET): $(OBJS)
	$(GCC) -o $@ $(OBJS) -L${CPPUNIT_PATH}/lib -lstdc++ -lcppunit -ldl

main.o : main.cpp
checkwarntest.o : checkwarntest.cpp
checkwarn.o : checkwarn.cpp

%.o: %.cpp
	$(GCC) -c $*.cpp -I${CPPUNIT_PATH}/include

clean:
	-rm *.exe $(OBJS) $(TARGET)
