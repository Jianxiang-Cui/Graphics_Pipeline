#include <ctime> 
#include <iostream> 
#include <algorithm>
#include <cmath>

#include "EShape.h"
#include "FrameBuffer.h"
#include "Raytracer.h"
#include "IScene.h"
#include "Light.h"
#include "Camera.h"
#include "Utilities.h"
#include "VertexOps.h"

PositionalLightPtr theLight = new PositionalLight(glm::vec3(2, 1, 3), pureWhiteLight);
std::vector<LightSourcePtr> lights = { theLight };


bool isMoving = false;
bool twoViewOn = false;
const float SPEED = 0.05;
// my work
const float ROTATE_UNIT = M_PI / 18.0f;
float azimuthAngle = 0.0f;
float elevationAngle = 0.0f;
float focusX = 0.0f, focusY = 1.0f, focusZ = 0.0f;
float dirOfTravel = 0.0f;
const float iniX = 0.0f, iniZ = 4.0f;
const float posY = 2.0f;
float posX = 0.0f, posZ = 4.0f;
glm::vec3 position(posX, posY, posZ);

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

//EShapeData plane = EShape::createECheckerBoard(copper, tin, 10, 10, 10);
EShapeData plane = EShape::createECheckerBoard(silver, blackPlastic, 10, 10, 10);

// Cylinder along y axis
EShapeData cylinderY = EShape::createECylinder(greenPlastic, 1.0, 1.5, 36);
// Cylinder along z axis
EShapeData cylinderZ = EShape::createECylinder(redPlastic, 0.5, 1.0, 36);
// Cone
EShapeData cone = EShape::createECone(yellowPlastic, 0.8, 2.0, 36, 20);
// Plane
//const std::vector<glm::vec4> V = { glm::vec4(-3, 3, -3, 1), glm::vec4(3, 3, -3, 1), glm::vec4(3, 6, -3, 1), glm::vec4(-3, 6, -3, 1) };
//EShapeData myPlane = EShape::createEPlanes(yellow, V);
EShapeData myPlane = EShape::createEMyPlane(gold, 3.0f, 1.5f);

void renderObjects() {
	VertexOps::render(frameBuffer, plane, lights, glm::mat3());
	VertexOps::render(frameBuffer, cylinderY, lights, T(0, 0, 0));
	VertexOps::render(frameBuffer, cylinderZ, lights, T(0, 2, 0) * Rx(M_PI_2));
	VertexOps::render(frameBuffer, cone, lights, T(-3, 0, 1));
	VertexOps::render(frameBuffer, myPlane, lights, T(0, 3.5, 0) * Rx(M_PI_2));
}

static void render() {
	frameBuffer.clearColorAndDepthBuffers();
	int width = frameBuffer.getWindowWidth();
	int height = frameBuffer.getWindowHeight();
	//VertexOps::viewingTransformation = glm::lookAt(position, ORIGIN3D, Y_AXIS);
	// my work
	// viewing left right up down
	computeXYZFromAzimuthAndElevation(1.0f, dirOfTravel + azimuthAngle, elevationAngle, focusX, focusY, focusZ);
	//glm::vec3 focusPt(focusX + posX - iniX, focusY + posY, focusZ + posZ - iniZ);
	glm::vec3 focusPt = glm::vec3(focusX, focusY, focusZ) + position;
	VertexOps::viewingTransformation = glm::lookAt(position, focusPt, Y_AXIS);
	// debug
	std::cout << "azimuthAngle = " << azimuthAngle << std::endl;
	std::cout << "focus point = " << focusPt << std::endl;
	std::cout << "position = " << position << std::endl;
	//std::cout << "azimuth angle = " << glm::degrees(azimuthAngle) << std::endl;
	//std::cout << "position.z = " << position.z << std::endl;
	//std::cout << "posZ = " << posZ << std::endl;

	float AR = (float)width / height;
	//VertexOps::projectionTransformation = glm::perspective(glm::radians(125.0), 2.0, 0.1, 5.0);
	VertexOps::projectionTransformation = glm::perspective(glm::radians(90.0f), 2.0f, 0.5f, 50.0f);
	VertexOps::setViewport(0, width - 1, 0, height - 1);
	renderObjects();
	frameBuffer.showColorBuffer();
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	float AR = (float)width / height;

	VertexOps::setViewport(0, width - 1, 0, height - 1);
	VertexOps::projectionTransformation = glm::perspective(M_PI_3, AR, 0.5f, 80.0f);
	//VertexOps::projectionTransformation = glm::perspective(glm::radians(90.0f), 2.0f, 0.5f, 50.0f);

	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) {
	const float INC = 0.5;
	switch (key) {
	case 'X':
	case 'x': theLight->lightPosition.x += (isupper(key) ? INC : -INC);
				std::cout << theLight->lightPosition << std::endl;
				break;
	case 'Y':
	case 'y': theLight->lightPosition.y += (isupper(key) ? INC : -INC);
				std::cout << theLight->lightPosition << std::endl;
				break;
	case 'Z':
	case 'z':	theLight->lightPosition.z += (isupper(key) ? INC : -INC);
				std::cout << theLight->lightPosition << std::endl;
				break;
	case 'P':
	case 'p':	isMoving = !isMoving;
				break;
	case 'C':	// Do something here
	case 'c':	dirOfTravel += azimuthAngle;
				azimuthAngle = 0.0;
				break;
	case '?':	twoViewOn = !twoViewOn;
				break;
	case ESCAPE:
		glutLeaveMainLoop();
		break;
	default:
		std::cout << (int)key << "unmapped key pressed." << std::endl;
	}

	glutPostRedisplay();
}

static void special(int key, int x, int y) {
	static const double rotateInc = glm::radians(10.0);
	static const double minEL = -glm::radians(80.0);
	static const double maxEL = glm::radians(80.0);
	std::cout << key << std::endl;
	switch (key) {
		// my work
	case(GLUT_KEY_LEFT):	if (azimuthAngle - ROTATE_UNIT >= glm::radians(-90.0f))
								azimuthAngle -= ROTATE_UNIT; 
		break;
	case(GLUT_KEY_RIGHT):	if (azimuthAngle + ROTATE_UNIT <= glm::radians(90.0f))
								azimuthAngle += ROTATE_UNIT;
		break;
	case(GLUT_KEY_DOWN):	if (elevationAngle - ROTATE_UNIT >= glm::radians(-80.0f))
								elevationAngle -= ROTATE_UNIT;
		break;
	case(GLUT_KEY_UP):		if (elevationAngle + ROTATE_UNIT <= glm::radians(80.0f))
								elevationAngle += ROTATE_UNIT;
		break;
	}
	glutPostRedisplay();
}

static void timer(int id) {
	// You should change this.
	if (isMoving) {
		//angle += glm::radians(5.0);
		// my work
		// move forward
		//posX += glm::sin(dirOfTravel) * SPEED;
		//posZ -= glm::cos(dirOfTravel) * SPEED;
		//position = glm::vec3(posX, posY, posZ);

		position.x += glm::sin(dirOfTravel) * SPEED;
		position.z -= glm::cos(dirOfTravel) * SPEED;
	}
	glutTimerFunc(100, timer, 0);
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	float x, y, z;
	computeXYZFromAzimuthAndElevation(1.0f, 0.0f, 0.0f, x, y, z);
	std::cout << x << " " << y << " " << z << std::endl;
	computeXYZFromAzimuthAndElevation(1.0f, M_PI_2, 0, x, y, z);
	std::cout << x << " " << y << " " << z + x << std::endl;
	//return 0;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	GLuint world_Window = glutCreateWindow(extractBaseFilename(__FILE__).c_str());
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutTimerFunc(100, timer, 0);
	glutMouseFunc(mouseUtility);

	frameBuffer.setClearColor(lightGray);

	glutMainLoop();

	return 0;
}
