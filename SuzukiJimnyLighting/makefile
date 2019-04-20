COMP = g++
FLAG = -o
INPT = SuzukiJimnyLighting.cpp ../Util/Shader.cpp ../Util/Camera.cpp ../Util/Parser.cpp
FBCK = -lGLEW -lGL -lglfw
OUTP = app

all : program1

program1 : SuzukiJimnyLighting.cpp ../Util/Shader.cpp ../Util/Camera.cpp ../Util/Parser.cpp
	@echo "Compile your program"
	${COMP} ${FLAG} ${OUTP} ${INPT} ${FBCK}
	@echo "Your program are ready"

clean :
	@echo "Cleaning up ..."
	rm ${OUTP}
