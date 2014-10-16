#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "get_clock_now.h"
#include "draw_function.h"

//-----------------------------------------------------------------------------------
// �����Х��ѿ�
//-----------------------------------------------------------------------------------
// ��������ߥե饰
static int flg_play = 1;

// ��������
static double distance = 5.0, pitch = 0.0, yaw = 0.0;

// �ޥ������Ͼ���
GLint mouse_button = -1;
GLint mouse_x = 0, mouse_y = 0;

// ����å�
static double clock_now, clock_pre;

// ��
static double day = 0;

static const GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
static const GLfloat light_ambient[] = {1.0, 1.0, 1.0, 1.0};
static const GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};

static const GLfloat mat_default_color[] = { 1.0, 1.0, 1.0, 1.0 };
static const GLfloat mat_default_specular[] = { 0.0, 0.0, 0.0, 0.0 };
static const GLfloat mat_default_shininess[] = { 100.0 };
static const GLfloat mat_default_emission[] = {0.0, 0.0, 0.0, 0.0};

// ����
static const double radius_sun = 1.0;
static const GLfloat mat_color_sun[] = { 0.8, 0.2, 0.2, 1.0 };
static const double rot_vel_sun = 1.0 / 27.275;

// ����
static const GLfloat mat_color_mercury[] = { 0.1, 0.6, 1.0, 1.0 };
static const double planet_radius_mercury = 0.1;
static const double orbit_radius_mercury = 1.5;
static const double rev_vel_mercury = 1.0 / 0.241;
static const double rot_vel_mercury = 1.0 / 58.65;

// ����
static const GLfloat mat_color_venus[] = { 0.6, 1.0, 0.1, 1.0 };
static const double planet_radius_venus = 0.12;
static const double orbit_radius_venus = 2.0;
static const double rev_vel_venus = 1.0 / 0.615;
static const double rot_vel_venus = 1.0 / 243.0187;

// �ϵ�
static const GLfloat mat_color_earth[] = { 0.1, 0.3, 0.8, 1.0 };
static const double planet_radius_earth = 0.12;
static const double orbit_radius_earth = 2.5;
static const double rev_vel_earth = 1.0;
static const double rot_vel_earth = 1.0 / 0.997271;

// ��
static const GLfloat mat_color_moon[] = { 0.2, 0.2, 0.2, 1.0 };
static const double planet_radius_moon = 0.05;
static const double orbit_radius_moon = 0.3;
static const double rev_vel_moon = 1.0 / 27.32 * 365.2564;
static const double rot_vel_moon = 1.0 / 27.32;

// ����
static const GLfloat mat_color_mars[] = { 0.6, 0.2, 0.3, 1.0 };
static const double planet_radius_mars = 0.09;
static const double orbit_radius_mars = 4.0;
static const double rev_vel_mars = 1.0 / 1.881;
static const double rot_vel_mars = 1.0 / 1.02595;

//-----------------------------------------------------------------------------------
// �����
//-----------------------------------------------------------------------------------
void init(void)
{
  // ���ꥢ���ͤ�����
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glClearDepth( 1.0 );

  // �ǥץ��ƥ��Ȥ�Ԥ�
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LESS );

  glShadeModel (GL_SMOOTH);

  // �ǥե���ȥ饤��
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_ambient);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  // �ǥե���ȥޥƥꥢ��
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_default_color);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_default_color);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_default_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_default_shininess);

  // ����å��ν����
  clock_now = clock_pre = get_clock_now();
}

//-----------------------------------------------------------------------------------
// �������
//-----------------------------------------------------------------------------------
void display(void)
{
  // ����å��ι���
  clock_pre = clock_now;
  clock_now = get_clock_now();

  // 1�ä�1��ʬư���Ȥ���
  if( flg_play )
    day +=  100*(clock_now - clock_pre);

  // printf("%lf\n",day);

  // �ե졼��Хåե��Υ��ꥢ
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // ����������
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // --- ���� ---
  // �ޥ������Ϥǻ�������ư�Ǥ���褦�ˤ���
  //glTranslatef(0.0, 0.0, -5.0 );
  gluLookAt(0.0, 0.0, distance, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glRotatef( -pitch, 1.0, 0.0, 0.0 );
  glRotatef( -yaw, 0.0, 1.0, 0.0 );

  // �����ε�ƻ������
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_default_color);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_default_color);
  DrawCircle( orbit_radius_earth );
  //����������
  glPushMatrix();
  {
    // ����
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_color_sun);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_color_sun);

    glPushMatrix();
    {
      // --- ���� ---
      // ���ۤμ�ž�η׻���
      glRotatef ( day*rot_vel_sun, 0.0, 1.0, 0.0);

      DrawPlanet( radius_sun );
    }
    glPopMatrix();

    // ����
    glPushMatrix();
    {
    }
    glPopMatrix();
    // ����
    glPushMatrix();
    {
    }
    glPopMatrix();

    // �ϵ�
    glPushMatrix();
    {
      // --- ���� ---
      // �ϵ�θ�ž�η׻���
      glRotatef ( day*rev_vel_earth, 0.0, 1.0, 0.0);
      glTranslatef (orbit_radius_earth, 0.0, 0.0);

      // --- ���� ---
      // �ϵ�μ�ž�η׻���
      glRotatef ( day*rot_vel_earth, 0.0, 1.0, 0.0);

      glMaterialfv(GL_FRONT, GL_AMBIENT, mat_color_earth);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_color_earth);

      DrawPlanet( planet_radius_earth );

      // ��
      glPushMatrix();
      {
        glRotatef(day * rev_vel_moon,0,1,0);
        glTranslatef(orbit_radius_moon,0,0);
        glRotatef(day * rot_vel_moon,0,1,0);

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_color_moon);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_color_moon);

        DrawPlanet(planet_radius_moon);
      }
      glPopMatrix();

    }
    glPopMatrix();

    //����
    glPushMatrix();
    {
    }
    glPopMatrix();

  }
  glPopMatrix();

  glutSwapBuffers();
}


//-----------------------------------------------------------------------------------
// ������ɥ��ꥵ�����Υ�����Хå��ؿ�
//-----------------------------------------------------------------------------------
void reshape (int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(45.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
}

//-----------------------------------------------------------------------------------
// �����ܡ������ϤΥ�����Хå��ؿ�
//-----------------------------------------------------------------------------------
void keyboard (unsigned char key, int x, int y)
{
  switch (key) {
  case 'z':
    if( flg_play == 1 ) flg_play = 0;
    else flg_play = 1;
    usleep(1000);
    break;
  case 27:
    exit(0);
    break;
  }
}

//-----------------------------------------------------------------------------------
// �ޥ�������å��Υ�����Хå��ؿ�
//-----------------------------------------------------------------------------------
void mouse(int button, int state, int x, int y)
{
  mouse_button = button;
  mouse_x = x;	mouse_y = y;

  if(state == GLUT_UP){
    mouse_button = -1;
  }

  glutPostRedisplay();
}

//-----------------------------------------------------------------------------------
// �ޥ�����ư�Υ�����Хå��ؿ�
//-----------------------------------------------------------------------------------
void motion(int x, int y)
{
  switch(mouse_button){
  case GLUT_LEFT_BUTTON:

    if( x == mouse_x && y == mouse_y )
      return;

    yaw -= (GLfloat) (x - mouse_x) / 10.0;
    pitch -= (GLfloat) (y - mouse_y) / 10.0;

    break;

  case GLUT_RIGHT_BUTTON:

    if( y == mouse_y )
      return;

    if( y < mouse_y )
      distance += (GLfloat) (mouse_y - y)/50.0;
    else
      distance -= (GLfloat) (y-mouse_y)/50.0;

    if( distance < 1.0 ) distance = 1.0;
    if( distance > 10.0 ) distance = 10.0;

    break;
  }

  mouse_x = x;
  mouse_y = y;

  glutPostRedisplay();
}

//-----------------------------------------------------------------------------------
// �����ɥ���Υ�����Хå��ؿ�
//-----------------------------------------------------------------------------------
void idle()
{
  glutPostRedisplay();
}

//-----------------------------------------------------------------------------------
// �ᥤ��ؿ�
//-----------------------------------------------------------------------------------
int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
  glutInitWindowSize (640, 480);
  glutInitWindowPosition (50, 50);
  glutCreateWindow ("planet");

  init();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);

  glutMainLoop();

  return 0;
}
