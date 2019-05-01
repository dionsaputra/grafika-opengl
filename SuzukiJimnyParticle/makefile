COMP = g++
FLAG = -o
INPT = SuzukiJimnyParticle.cpp ParticleGenerator.cpp ../Util/Shader.cpp ../Util/Camera.cpp ../Util/Parser.cpp
FBCK = -lGLEW -lGL -lglfw -lm
OUTP = app

all : program1

program1 : SuzukiJimnyParticle.cpp ParticleGenerator.cpp ../Util/Shader.cpp ../Util/Camera.cpp ../Util/Parser.cpp
	@echo "Compile your program"
	${COMP} ${FLAG} ${OUTP} ${INPT} ${FBCK}
	@echo "Your program are ready"

clean :
	@echo "Cleaning up ..."
	rm ${OUTP}
