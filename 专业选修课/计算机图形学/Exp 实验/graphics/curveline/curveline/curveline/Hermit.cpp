#include<gl/glut.h>
#include<math.h>
#include<windows.h>
#include<algorithm>
using namespace std;
struct Vertex
{
	GLfloat x, y;
	Vertex(GLfloat tx, GLfloat ty)
	{
		x = tx;
		y = ty;
	}
};

Vertex p0(0, 1);        //��ֵ��
Vertex p1(3, 0);
Vertex c0(0, 2);        //���Ƶ�
Vertex c1(0, 0);

GLsizei W;
GLsizei H;

bool mouseLeftIsDown = false;
bool mouseRightIsDown = false;

void ChangeMouse(Vertex &a)
{
	a.x = a.x / W * 20 - 10;
	a.y = - (a.y / H * 20 * (W / H) - 10 * (W / H));
}

GLfloat caculateSquareDistance(Vertex &a, Vertex b)
{
	

	//b.x = (b.x + 10) / 20 * W;
	//b.y = (b.y + 10 / (W / H)) / (20 / (W / H)) *H;
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y);
}
void Hermite(int n)     //����
{
	//�������ڿ��Ƶ�����������ߣ�
	//������е�ĳ�����Ϊ����4�������ߵ�Ч����Ϊ���ԣ�ʵ���ϲ����ϼ�����Ĺ�ʽ��
	Vertex tempC0((c0.x - p0.x) * 4, (c0.y - p0.y) * 4);
	Vertex tempC1((c1.x - p1.x) * 4, (c1.y - p1.y) * 4);

	double delTa = 1.0 / n;
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < n; i++)
	{
		double t = i * delTa;

		double t1 = 2 * pow(t, 3) - 3 * pow(t, 2) + 1;
		double t2 = -2 * pow(t, 3) + 3 * pow(t, 2);
		double t3 = pow(t, 3) - 2 * pow(t, 2) + t;
		double t4 = pow(t, 3) - pow(t, 2);

		glVertex2d(p0.x*t1 + p1.x*t2 + tempC0.x*t3 + tempC1.x*t4, p0.y*t1 + p1.y*t2 + tempC0.y*t3 + tempC1.y*t4);
	}
	glEnd();
}
void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);       //�����GL_COLOR_BUFFER_BIT��ʾ�����ɫ

	glPointSize(10.0f);
	glColor3f(0, 0, 1);
	//������ֵ��Ϳ��Ƶ㣨��ɫ��
	glBegin(GL_POINTS);
	glVertex2d(p0.x, p0.y);
	glVertex2d(p1.x, p1.y);
	glVertex2d(c0.x, c0.y);
	glVertex2d(c1.x, c1.y);
	glEnd();

	//�������Ƶ�����ֵ������ߣ���ɫ��
	glColor3f(1, 0, 0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2d(p0.x, p0.y);    glVertex2d(c0.x, c0.y);
	glVertex2d(p1.x, p1.y);    glVertex2d(c1.x, c1.y);
	glEnd();

	Hermite(200);

	glFlush();
	glutSwapBuffers();
}
void mouse(int button, int state, int x, int y)       //������궯��
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseLeftIsDown = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		mouseLeftIsDown = false;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		mouseRightIsDown = true;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		mouseRightIsDown = false;
	}
}
void motion(int x, int y)       //�ƶ���
{
	GLfloat x0 = x;
	GLfloat y0 = y;
	Vertex mouse{ x0,y0 };
	ChangeMouse(mouse);
	if (mouseLeftIsDown)        //����ƶ����Ƶ�
	{
		if (caculateSquareDistance(mouse, c0) < 0.6)     //��ֹ����ƶ������λ�޷���ʱ��ȡ�������ԣ�400Ϊһ�����ʺϵ�ֵ
		{
			c0.x = mouse.x;
			c0.y = mouse.y;
		}
		else if (caculateSquareDistance(mouse, c1) < 0.6)
		{
			c1.x = mouse.x;
			c1.y = mouse.y;
		}
	}
	else if (mouseRightIsDown)      //�Ҽ��ƶ���ֵ��
	{
		if (caculateSquareDistance(mouse, p0) < 0.6)
		{
			p0.x = mouse.x;
			p0.y = mouse.y;
		}
		else if (caculateSquareDistance(mouse, p1) < 0.6)
		{
			p1.x = mouse.x;
			p1.y = mouse.y;
		}
	}
	glutPostRedisplay();        //���¹�ͼ
}
void ChangeSize(GLsizei w, GLsizei h)
{
	/*
	GLfloat aspectRatio;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	
	if (w <= h)
		glOrtho(-400.0, 500.0, -400.0 / aspectRatio, 500.0 / aspectRatio, 1.0, -1.0);
	else
		glOrtho(-400.0*aspectRatio, 500.0*aspectRatio, -400.0, 500.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/
	W = w;
	H = h;
	glViewport(0, 0, w, h);
	double aspectRatio = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10/aspectRatio, 10/aspectRatio);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


int main(int argc, char *argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Hermit");

	puts("\n\tʹ��Hermite�㷨���������������Ƶ�����������ߡ�");
	puts("\t����ƶ����Ƶ㣬�Ҽ��ƶ���ֵ��");

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glutMainLoop();

	return 0;
}