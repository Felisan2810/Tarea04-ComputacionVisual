/*
	GRUPO 01 - COMPUTACIÓN VISUAL
	PROF. GUTIERREZ

	OBJETIVO: REALIZAR EL MODELAMIENTO DE UNA ESFERA SIGUIENDO EL MODELO
	DEL EJEMPLO DEL CILINDRO Y SUS DIVISIONES.
*/	


#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

float calculoX(float R, int N, int n);
float calculoZ(float R, int N, int n);
void anillo(float R, float y, int N);
float fEsfera(float y, float H);
void esferaAlambre(int N);
void inicializaVista(void);
void display(void);
void reshape(int width, int height);
void inicializaVentana(int argc, char **argv);
void iniciaOpenGL(int argc, char **argv);


// Devuelve el valor de x del punto que gira en el plano 
float calculoX(float R, int N, int n) {
	return R * cos(n * (2 * M_PI) / N);
}

// Devuelve el valor de z 
float calculoZ(float R, int N, int n) {
	return R * sin(n * (2 * M_PI) / N);
}

// Dibuja un anillo de radio R con N divisiones
void anillo(float R, float y, int N) {
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < N; i++) {
		float x = calculoX(R, N, i);
		float z = calculoZ(R, N, i);
		glVertex3f(x, y, z);
	}
	glEnd();
}

// Calcula el radio del anillo 
float fEsfera(float y, float H) {
	float radioBase = 50.0; // Radio en el centro de la esfera
	return radioBase * sqrt(1.0f - (y * y) / (H * H / 4.0f));  //se le da forma esférica
}

// Dibujamos la esfera
void esferaAlambre(int N) {
	float H = 100.0f; // Altura total de la esfera
	for(int i = 0; i < N; i++) {
		float y = i * H / N - (H / 2); // Calcula el nivel y de cada anillo
		float r = fEsfera(y, H);       // Calcula el radio del anillo en función de y
		anillo(r, y, N);               
	}
}


// Configura el color de fondo y dibuja la esfera.
void display(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);  
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 1.0f);  //se optó por usar el color morado
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -4.0f); 
	
	/* Nota: Para este caso, como un añadido, optamos por cambiarle un poco
	la rotación de la esfera, con el objetivo de hacer notar mejor las circuenferencias*/
	
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);  //Ajustes de la rotación
	esferaAlambre(20); 
	glPopMatrix();
	glFlush();
}


void inicializaVista(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	inicializaVista();
}


void inicializaVentana(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(200, 30);
	glutCreateWindow ("Modelamiento de una esfera");
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
}

void iniciaOpenGL(int argc, char **argv) {
	inicializaVentana(argc, argv);
	inicializaVista();
	glutMainLoop();
}

// Función principal.
int main(int argc, char** argv) {
	iniciaOpenGL(argc, argv);
	return 1;
}
