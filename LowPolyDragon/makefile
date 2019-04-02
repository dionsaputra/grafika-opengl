COMP = g++
FLAG = -o
INPT = LowPolyDragon.cpp
<<<<<<< HEAD
UTIL = ../Util/Parser.cpp ../Util/Shader.cpp
FBCK = -lGL -lGLEW -lglfw
=======
UTIL = ../Util/Parser.cpp ../Util/Shader.cpp ../Util/Core.cpp 
FBCK = -lXrandr -lXrender -lXi -lGLEW -lGLU -lm -lGL -lm -lpthread -pthread -ldl -ldrm -lXdamage -lXfixes -lX11-xcb -lxcb-glx -lxcb-dri2 -lXxf86vm -lXext -lglfw3 -lrt -lm -ldl -lX11 -lpthread -lxcb -lXau -lXdmcp

>>>>>>> 22fe4ecbc51588ed81c59c35fb5a4b3d870fa4d2
OUTP = app

all : program1

program1 : 
	@echo "Compile your program"
	${COMP} ${FLAG} ${OUTP} ${INPT} ${UTIL} ${FBCK}
	@echo "Your program are ready"

clean :
	@echo "Cleaning up ..."
	rm ${OUTP}
