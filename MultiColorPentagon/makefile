COMP = g++
FLAG = -o
INPT = MultiColorPentagon.cpp
UTIL = ../Util/Parser.cpp ../Util/Shader.cpp ../Util/Core.cpp 
FBCK = -lGL -lGLEW -lglfw
OUTP = app

all : program1

program1 : 
	@echo "Compile your program"
	${COMP} ${FLAG} ${OUTP} ${INPT} ${UTIL} ${FBCK}
	@echo "Your program are ready"

clean :
	@echo "Cleaning up ..."
	rm ${OUTP}
