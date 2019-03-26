/* sudo apt-get install libglm-dev */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <bits/stdc++.h>
using namespace std;

const float screenWidth = 800;
const float screenHeight = 800;

int main() {
    GLFWwindow* window = Core::createWindow(screenWidth, screenHeight, "Multicolor Pentagon");
    Shader shader("VertexShader.glsl", "FragmentShader.glsl");

    mat4 model = mat4(1);
    model = rotate(model, radians(-55), vec3(1,0,0));

    mat4 view = mat4(1);
    view = translate(view, vec3(0,0,-3));

    mat4 projection;
    projection = perspective(radians(45), screenWidth/screenHeight, 0.1, 100);

    int modelLoc = glGetUniformLocation(shader.id, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
}