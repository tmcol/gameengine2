CPPFLAGS=-DGLM_FORCE_RADIANS -I. --std=c++11
OUTPUT_OPTION=-MMD -MP -o $@
LDLIBS=-lglfw3 -lGLEW -lGL -lX11 -lXxf86vm -lpthread -lXrandr -lXi -lopenal `libpng-config --ldflags` -lalut -lavformat -lavcodec -lavutil -lportaudio -lboost_filesystem -lboost_system -lXinerama -lXcursor
 
SOURCES=$(shell find . -name "*.cpp")
CSOURCES=$(shell find . -name "*.c")

OBJECTS=$(SOURCES:%.cpp=%.o)
COBJECTS=$(CSOURCES:%.cpp=%.o)

DEPS=$(SOURCES:%.cpp=%.d)
CDEPS=$(CSOURCES:%.c=%.d)
TARGET=foo

$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(COBJECTS) $(LDLIBS)

%.o: %.cpp
	g++ -g -c -MMD -MP $< -o $@ $(CPPFLAGS)
	
%.o: %.c
	gcc -g -c -MMD -MP $< -o $@


 
.PHONY: clean
 
clean:
	rm -f $(TARGET) $(OBJECTS) $(DEPS)


-include $(DEPS)
-include $(CDEPS)
