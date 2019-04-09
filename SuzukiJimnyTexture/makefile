COMP = g++
FLAG = -o
INPT = SuzukiJimnyTexture.cpp ../Util/Shader.cpp ../Util/Camera.cpp ../Util/Parser.cpp
FBCK = -lXrandr -lXrender -lXi -lGLEW -lGLU -lm -lGL -lm -lpthread -pthread -ldl -ldrm -lXdamage -lXfixes -lX11-xcb -lxcb-glx -lxcb-dri2 -lXxf86vm -lXext -lglfw3 -lrt -lm -ldl -lX11 -lpthread -lxcb -lXau -lXdmcp
OUTP = app

all : program1

program1 : SuzukiJimnyTexture.cpp ../Util/Shader.cpp ../Util/Camera.cpp ../Util/Parser.cpp
	@echo "Compile your program"
	${COMP} ${FLAG} ${OUTP} ${INPT} ${FBCK}
	@echo "Your program are ready"

clean :
	@echo "Cleaning up ..."
	rm ${OUTP}
