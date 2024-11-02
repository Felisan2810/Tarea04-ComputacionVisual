	/*
	GRUPO 01 - COMPUTACIÓN VISUAL
	PROF. GUTIERREZ

	OBJETIVO: REALIZAR EL MODELAMIENTO DE UN CONO SIGUIENDO EL MODELO
	DEL EJEMPLO DEL CILINDRO Y SUS DIVISIONES
	*/	

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

float CalculoX(float R, int N, int n);
float CalculoZ(float R, int N, int n);
void anillo(float R, float y, int N);
float fCono(float y);
void conoAlambre(int N);
void formaAlambre(float H, int N, float(*f)(float y));
void ReduceToUnit(float vector[3]);
void RenderShaft(void);

//#define M_PI 3.141516

float CalculoX(float R, int N, int n) 
{
	float x = (float) R * cos(n * (2 * M_PI) / N);
	return x;
}

float CalculoZ(float R, int N, int n) 
{
	float z = (float) R * sin(n * (2 * M_PI) / N);
	return z;
}

void anillo(float R, float y, int N) 
{
	int i;
	float x, z;
	
	glBegin(GL_LINE_LOOP);
	for(i = 0; i < N; i++) 
	{
		x = CalculoX(R, N, i);
		z = CalculoZ(R, N, i);
		glVertex3f(x, y, z);
	}
	glEnd();
}

// Cambia la función para un cono, disminuyendo el radio conforme la altura
float fCono(float y) 
{
	float H = 100.0f; // Altura total del cono
	return 50.0f * (1.0f - (y + H/2) / H); // Reduce el radio conforme aumenta la altura
}

void conoAlambre(int N) 
{
	formaAlambre(100.0f, N, fCono);
}

void formaAlambre(float H, int N, float(*f)(float y)) 
{
	int i;
	float y, r;
	
	/* Nota: Para una mayor visualización del cono, se optó por 
	duplicarle las divisiones, con el objetivo de que haya menos espacios en
	blanco al momento de la ejecución y las circunferencias estén más juntas
	*/
	int finerN = 2 * N;  //Duplicamos las divisiones
	
	for(i = 0; i < finerN; i++) 
	{ 
		y = i * H / finerN - (H / 2);  // Más divisiones a lo largo de la altura
		r = f(y);           // obtenemos el radio
		anillo(r, y, N);    // y dibujamos un anillo
	}
}

void ReduceToUnit(float vector[3])
{
	float length;
	length = (float)sqrt((vector[0]*vector[0]) + (vector[1]*vector[1]) + (vector[2]*vector[2]));
	if(length == 0.0f)
		length = 1.0f;
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
}



void display(void) 
{
	glClearColor (1.0,1.0,1.0, 1.0);
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f); //usamos el color rojo
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -4.0f); 
	
	/* Nota: Para este caso, como un añadido, optamos por cambiarle un poco
	la rotación de la esfera, con el objetivo de hacer notar mejor las circuenferencias*/
	
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);  //Ajustes de la rotación
	conoAlambre(20); 
	glPopMatrix();
	glFlush();
}

void inicializaVista(void) 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(int width, int height) 
{
	glViewport (0, 0, width, height);
	inicializaVista ();
}

void inicializaVentana(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (700, 700);
	glutInitWindowPosition (200, 30);
	glutCreateWindow ("Modelamiento de un cono");
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
}

void iniciaOpenGL(int argc, char **argv) 
{
	inicializaVentana (argc, argv);
	inicializaVista ();
	glutMainLoop();
}

int main (int argc, char** argv) 
{
	iniciaOpenGL(argc, argv);
	return (1);
}
