/* sudo apt-get install libglm-dev */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <bits/stdc++.h>
using namespace std;

int main() {
    vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    mat4 trans = mat4(1.0f);
    trans = translate(trans, vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    cout<<vec.x<<vec.y<<vec.z<<endl;
}