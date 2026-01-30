#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glut.h> 
#include <vector>
#include <cmath>
#include <string>
using namespace std;

float screenwidth = 1600.0f;
float screenheight = 1000.0f;
struct Star {
    float x, y;
    float size;
    float r, g, b;
};

vector<Star> stars;

class planet {
public:
    vector <float> position;
    vector <float> vitesse;
    vector <pair<float, float>> orbite;
    float radius;
    float mass;
    float r, g, b;
    planet(vector <float> position, vector <float> vitesse, float radius, float mass, float red, float green, float blue) {
        this->position = position;
        this->vitesse = vitesse;
        this->radius = radius;
        this->mass = mass;
        r = red;
        g = green;
        b = blue;
    }
    void updatepos() {
        this->position[0] += vitesse[0];
        this->position[1] += vitesse[1];
        orbite.push_back({ position[0], position[1] });
        if (orbite.size() > 9000) {
            orbite.erase(orbite.begin());
        }
    }
    void Circle() {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2d(position[0], position[1]);
        for (int i = 0; i <= 100;++i) {
            float angle = 2.0f * 3.14159265359f * (static_cast<float>(i) / 100);
            float x = position[0] + cos(angle) * radius;
            float y = position[1] + sin(angle) * radius;
            glVertex2d(x, y);
        }
        glEnd();
    }
    void Lesorbites() {
        if (orbite.empty()) return;
        glBegin(GL_LINE_STRIP);
        for (auto& p : orbite) {
            glVertex2d(p.first, p.second);
        }
        glEnd();
    }
    bool operator== (const planet& p) {
        if (radius == p.radius && mass == p.mass && position == p.position && vitesse == p.vitesse) {
            return true;
        }
        else { return false; }
    }
};

void drawText(float x, float y, string text) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void initStars(int count) {
    for (int i = 0; i < count; ++i) {
        Star s;
        s.x = rand() % static_cast<int>(screenwidth);
        s.y = rand() % static_cast<int>(screenheight);
        s.size = 1.0f + rand() % 3;
        int colorType = rand() % 3;
        if (colorType == 0) { s.r = 1; s.g = 1; s.b = 1; }
        else if (colorType == 1) { s.r = 0.7; s.g = 0.7; s.b = 1; }
        else { s.r = 1; s.g = 0.9; s.b = 0.7; }
        stars.push_back(s);
    }
}

void drawStars() {
    glBegin(GL_POINTS);
    for (auto& s : stars) {
        glColor3f(s.r, s.g, s.b);
        glVertex2f(s.x, s.y);
    }
    glEnd();
}

int main() {
    const float G = 0.5f;
    planet sun(vector <float> {1000.0f, 500.0f}, vector <float> {0.0f, 0.0f }, 30.0f, 1000.0f, 1.0f, 1.0f, 0.0f);
    vector <planet> plan = {
        planet(vector <float> {1099.0f, 500.0f}, vector <float> {0.0f, 0.5f }, 3.0f, 0.2f, 0.6f, 0.6f, 0.6f), //Mercure
        planet(vector <float> {1140.0f, 500.0f}, vector <float> {0.0f, 0.5f }, 5.0f, 0.5f, 1.0f, 0.85f, 0.7f), //Venus
        planet(vector <float> {1170.0f, 500.0f}, vector <float> {0.0f, 0.5f }, 6.0f, 1.0f, 0.0f, 0.5f, 1.0f), //Terre
        planet(vector <float> {1198.0f, 500.0f}, vector <float> {0.0f, 0.5f }, 4.0f, 0.3f, 1.0f, 0.3f, 0.0f), //Mars
        planet(vector <float> {1229.0f, 500.0f}, vector <float> {0.0f, 0.5f }, 12.0f, 5.0f, 0.9f, 0.7f, 0.5f), //jupiter
        planet(vector <float> {1250.0f, 500.0f}, vector <float> {0.0f, 0.5f }, 10.0f, 4.0f, 0.9f, 0.85f, 0.6f), //Saturne
        planet(vector <float> {1275.0f, 500.0f}, vector <float> {0.0f, 0.5f }, 8.0f, 1.5f, 0.5f, 1.0f, 1.0f), //Uranus
        planet(vector <float> {1292.0f, 500.0f}, vector <float> {0.0f, 0.5f }, 8.0f, 1.5f, 0.0f, 0.0f, 0.8f) //Neptune
    };
    if (!glfwInit())
        return -1;
    GLFWwindow* window = glfwCreateWindow(screenwidth, screenheight, "Solar system", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screenwidth, 0, screenheight, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0, 0, 0, 1);


    int argc = 1;
    char* argv[1] = { (char*)"Something" };
    glutInit(&argc, argv);
    initStars(500);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        drawStars();
        glColor3f(sun.r, sun.g, sun.b);
        sun.Circle();
        for (auto& elem : plan) {
            float dx = sun.position[0] - elem.position[0];
            float dy = sun.position[1] - elem.position[1];
            float distance = sqrt(dx * dx + dy * dy);
            vector <float> direction = { dx / distance, dy / distance };
            float forceG = (G * elem.mass * sun.mass) / (distance * distance);
            float acc1 = forceG / elem.mass;
            vector <float> acc = { acc1 * direction[0], acc1 * direction[1] };
            elem.vitesse[0] += acc[0] * 0.1f;
            elem.vitesse[1] += acc[1] * 0.1f;
            elem.updatepos();
            glColor3f(elem.r, elem.g, elem.b);
            elem.Circle();
            sun.vitesse[0] += 0.00000001f;
            sun.position[0] += sun.vitesse[0];
            if (sun.position[0] <= 0 || sun.position[0] >= screenwidth) {
                sun.vitesse[0] *= -1.0f;
            }
            glColor3f(0.5f, 0.5f, 0.5f);
            //elem.Lesorbites();//
        }

        // Affichage des vitesses en haut à droite
        glColor3f(1.0f, 1.0f, 1.0f);
        float yoffset = screenheight - 20;
        for (int i = 0; i < plan.size(); ++i) {
            float speed_pixels = sqrt(plan[i].vitesse[0] * plan[i].vitesse[0] + plan[i].vitesse[1] * plan[i].vitesse[1]);
            float speed_km_s = speed_pixels * 1e6 / 86400.0f;
            drawText(screenwidth - 200, yoffset - i * 20, "Planet " + to_string(i + 1) + ": " + to_string(speed_km_s) + " km/s");

        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}