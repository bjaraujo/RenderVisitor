
#include <GL/glut.h>

#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer(int width, int height)
{

	OpenGLRenderer::m_width = width;
	OpenGLRenderer::m_height = height;

}

void OpenGLRenderer::initRendering(int *argc, char** argv) {

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(m_width, m_height);

}

void OpenGLRenderer::createRenderingWindow(const char* title) {

	glutCreateWindow(title);

}

void OpenGLRenderer::renderScene() {

	glutDisplayFunc(display);
	glutIdleFunc(update);
	//glutMouseFunc(mouse);
	glutReshapeFunc(reshape);

	glClearColor(0, 0, 0, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);

	glutMainLoop();

}

void OpenGLRenderer::update()
{

	// redraw
	glutPostRedisplay();

}

void OpenGLRenderer::display()
{

	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	// setup 2d pixel plotting camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, (GLfloat)m_width, 0.0f, (GLfloat)m_height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, m_width, m_height);
	glDepthRange(0.0f, 1.0f);

	// C++11 auto and range
	for (auto s : m_shapes)
		drawShape(s);

	glPopMatrix();

	glutSwapBuffers();

}

void OpenGLRenderer::drawShape(geo::Shape* aShape)
{

	aShape->draw(m_renderer);

}

void OpenGLRenderer::draw(geo::Triangle* aTriangle)
{

	glColor3d(aTriangle->color().r(), aTriangle->color().g(), aTriangle->color().b());

	glBegin(GL_TRIANGLES);
	
	glVertex2d(aTriangle->vertex(0).x(), aTriangle->vertex(0).y());
	glVertex2d(aTriangle->vertex(1).x(), aTriangle->vertex(1).y());
	glVertex2d(aTriangle->vertex(2).x(), aTriangle->vertex(2).y());

	glEnd();

}

void OpenGLRenderer::draw(geo::Rectangle* aRectangle)
{

	glColor3d(aRectangle->color().r(), aRectangle->color().g(), aRectangle->color().b());

	glBegin(GL_QUADS);

	glVertex2d(aRectangle->vertex(0).x(), aRectangle->vertex(0).y());
	glVertex2d(aRectangle->vertex(1).x(), aRectangle->vertex(1).y());
	glVertex2d(aRectangle->vertex(2).x(), aRectangle->vertex(2).y());
	glVertex2d(aRectangle->vertex(3).x(), aRectangle->vertex(3).y());

	glEnd();

}

void OpenGLRenderer::reshape(int width, int height)
{

	m_width = width;
	m_height = height;

}



