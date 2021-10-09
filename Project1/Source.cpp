#include <stdio.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

const int numberOfColors = 4; //количество цветов
int currentColor = 0; //индекс текущего цвета

struct Color { //структура для представления цвета
	float Red, Green, Blue;
	Color(float R, float G, float B) : Red(R), Green(G), Blue(B) {}
};
Color colorArray[numberOfColors] = { // массив цветоа
	Color(0.0f, 0.0f, 0.0f), //black
	Color(1.0f, 1.0f, 1.0f), //white
	Color(0.0f, 0.0f, 1.0f), //blue
	Color(1.0f, 0.0f, 0.0f), //red
};
void Reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void Display(void)
{
	// отчищаем буфер цвета
	glClearColor(0.22, 0.88, 0.11, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 5, 7.5, 0, 0, 0, 0, 1, 0);
	// выводим объект ‐ красный (1,0,0) чайник
	glColor3f(colorArray[currentColor].Red, colorArray[currentColor].Green, colorArray[currentColor].Blue);
	glutWireTeapot(1.0);
	// смена переднего и заднего буферов
	glutSwapBuffers();
};
void nextColor() {
	currentColor++;
	if (currentColor == numberOfColors)
		currentColor = 0;
}
int counter = 0;
const int interval = 20;
// функция вызывается каждые 20 мс
void Simulation(int value)
{
	if (counter == 1000) {
		nextColor();
		counter = 0;
		
	}
	counter += interval;
	// устанавливаем признак того, что окно нуждается в перерисовке
	
	glutPostRedisplay();
	// эта же функция будет вызвана еще раз через 20 мс
	glutTimerFunc(20, Simulation, 0);
	

};
//char spaceKey = 32;
// Функция обработки нажатия клавиш
void KeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", (unsigned int)key);
	//if (key == spaceKey)
	//	nextColor();
};

void main(int argc, char** argv)
{
	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// создание окна:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(600, 600);
	// 3. создаем окно
	glutCreateWindow("Lab1");

	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(Display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(Reshape);
	// устанавливаем функцию которая будет вызвана через 20 мс
	glutTimerFunc(20, Simulation, 0);
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(KeyboardFunc);

	// основной цикл обработки сообщений ОС
	glutMainLoop();
	return;
}