COMP = g++
FLAG = -o
INPT = SuzukiJimny.cpp
UTIL = ../Util/Parser.cpp ../Util/Shader.cpp ../Util/Camera.cpp
FBCK = -lGLEW -lGL -lglfw
OUTP = app

all : program1

program1 : 
	@echo "Compile your program"
	${COMP} ${FLAG} ${OUTP} ${INPT} ${UTIL} ${FBCK}
	@echo "Your program are ready"

clean :
	@echo "Cleaning up ..."
	rm ${OUTP}
