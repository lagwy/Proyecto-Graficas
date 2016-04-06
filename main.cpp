/*
 *  Proyecto_Graficas.cpp
 *
 *  Proyecto de la clase de Graficas Computacionales
 *
 *  @author Luis Angel Martinez     A00813485
 *  @author Andres Alvarez Chavez   A00813787
 *  @date 15/03/2016
 *
 *  Referencia al proyecto TexturaSencillo proporcionado por la profesora Ma. Guadalupe Roque
 */
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "imageloader.h"
#include <assert.h>
#include <fstream>
using namespace std;
//__FILE__ is a preprocessor macro that expands to full path to the current file.
string fullPath = __FILE__;
const int TEXTURE_COUNT=4;

using namespace std;
int angulo=0;
static GLuint texName[TEXTURE_COUNT];
int z=1;
int iPlayerX = 0;
int xSpawn = rand()% 5 + (-2);
bool enJuego = false, bInstrucciones = false;
int tiempo = glutGet(GLUT_ELAPSED_TIME);;

//le borramos el exceso para solo obtener el Path padre
void getParentPath()
{
    for (int i = (int)fullPath.length()-1; i>=0 && fullPath[i] != '\\'; i--)
    {
        fullPath.erase(i,1);
    }
}


void timer(int value)
{
    if(enJuego){
            tiempo +=100;
        angulo = angulo +1;
        if (angulo == TEXTURE_COUNT) angulo =0;
        glutPostRedisplay();
    }
    glutTimerFunc(100,timer,0);
}

//Makes the image into a texture, and returns the id of the texture
void loadTexture(Image* image,int k)
{

    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Filtros de ampliacion y reduciÛn con c·lculo mas cercano no es tan bueno pero es r·pido
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);

    //Filtros de ampliacion y reduciÛn con c·lculo lineal es mejo pero son m·s calculos
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
}

void initRendering()
{
    //Declaraci√≥n del objeto Image
    Image* image;
    GLuint i=0;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(TEXTURE_COUNT, texName); //Make room for our texture

    char  ruta[200];
    /*
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/EducacionSexual.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);

    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/eligePersonaje.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);

    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/higiene_.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);

    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/paginaInicio.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);

    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/ParqueBonito.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
    */
    /*sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/orange_flat.bmp");
    image = loadBMP(ruta);
    loadTexture(image,i++);

    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/Instrucciones_temporal.bmp");
    image = loadBMP(ruta);
    loadTexture(image,i++);

    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/Menu_temporal.bmp");
    image = loadBMP(ruta);
    loadTexture(image,i++);*/

    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/Menu_temporal.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/Instrucciones_temporal.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/orange_flat.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/pacman.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);

    delete image;
}

void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    //Esc
    case 27: //Escape key
        exit(0);
        break;
    case 8: //Escape key
        bInstrucciones = false;
        enJuego = false;
        break;
    case '1':
        enJuego = true;
        break;
    case '2':
        bInstrucciones = true;
        break;
    }
}


void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(69.0, (float)w / (float)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // if (!enJuego)
    gluLookAt(0, 0,15 , 0, 0, 0, 0, 1, 0);
}

void specialkey (int key, int mouseX, int mouseY)
{
    switch(key)
    {
    case GLUT_KEY_RIGHT:
        if (iPlayerX != 2)
            iPlayerX += 1;
        break;
    case GLUT_KEY_LEFT:
        if (iPlayerX != -2)
            iPlayerX -= 1;
        break;
    case GLUT_KEY_UP:
        enJuego = true;
    }
    glutPostRedisplay();
}

void display()
{
    if (!enJuego)
    {
        glClearColor(1.0,1.0,1.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //Habilitar el uso de texturas
        glEnable(GL_TEXTURE_2D);

        //Elegir la textura del Quads: angulo cambia con el timer
        if (bInstrucciones)
        glBindTexture(GL_TEXTURE_2D, texName[1]);
        else
        glBindTexture(GL_TEXTURE_2D, texName[0]);

        glBegin(GL_QUADS);
        //Asignar la coordenada de textura 0,0 al vertice
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-10.0f, -10.0f, 0);
        //Asignar la coordenada de textura 1,0 al vertice
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(10.0f, -10.0f, 0);
        //Asignar la coordenada de textura 1,1 al vertice
        glTexCoord2f(1.0f,1.0f);
        glVertex3f(10.0f, 10.0f, 0);
        //Asignar la coordenada de textura 0,1 al vertice
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-10.0f, 10.0f, 0);
        glEnd();
    }

    if(enJuego)
    {
        glLoadIdentity();
        const double t = tiempo / 1000.0;
        const double a = t*90.0;
        double y = t*-1;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);
        glColor3d(0,0.35,1);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texName[3]);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glPushMatrix();
        glTranslated(iPlayerX,-2.5,-6);
        glRotated(75,-1,0,0);
        glRotated(a,0,0,1);
        glutSolidCube(0.4);
        glPopMatrix();


        glBindTexture(GL_TEXTURE_2D, texName[2]);
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glPushMatrix();
        glColor3d(1, 1, 0);
        glTranslated(xSpawn, y, 0);
        glTranslated(0, 2.5, -6);
        glutSolidSphere(0.2, 16, 16);
        glPopMatrix();
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);

        // Las lineas del carril
        glPushMatrix();
        glBegin(GL_LINES);
        // eje x
        glVertex2i(-2, 0); // V1
        glVertex2i(2, 0); // V2
        // eje y
        glVertex2i(0, -2); // V3
        glVertex2i(0, 2); // V4
        glEnd();
        glPopMatrix();
        glPopMatrix();

    }


    glutSwapBuffers();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(512,512);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Avoid the drugs");
    //Obtener el path de los archivos
    getParentPath();
    initRendering();
    glutDisplayFunc(display);
    glutSpecialFunc(specialkey);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    glutTimerFunc(100,timer,0);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


    glutMainLoop();
    return 0;
}

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h)
{

}

Image::~Image()
{
    delete[] pixels;
}

namespace
{
    //Converts a four-character array to an integer, using little-endian form
    int toInt(const char* bytes)
    {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8) |
                     (unsigned char)bytes[0]);
    }

    //Converts a two-character array to a short, using little-endian form
    short toShort(const char* bytes)
    {
        return (short)(((unsigned char)bytes[1] << 8) |
                       (unsigned char)bytes[0]);
    }

    //Reads the next four bytes as an integer, using little-endian form
    int readInt(ifstream &input)
    {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }

    //Reads the next two bytes as a short, using little-endian form
    short readShort(ifstream &input)
    {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }

    //Just like auto_ptr, but for arrays
    template<class T>
    class auto_array
    {
    private:
        T* array;
        mutable bool isReleased;
    public:
        explicit auto_array(T* array_ = NULL) :
        array(array_), isReleased(false)
        {
        }

        auto_array(const auto_array<T> &aarray)
        {
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        ~auto_array()
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
        }

        T* get() const
        {
            return array;
        }

        T &operator*() const
        {
            return *array;
        }

        void operator=(const auto_array<T> &aarray)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        T* operator->() const
        {
            return array;
        }

        T* release()
        {
            isReleased = true;
            return array;
        }

        void reset(T* array_ = NULL)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = array_;
        }

        T* operator+(int i)
        {
            return array + i;
        }

        T &operator[](int i)
        {
            return array[i];
        }
    };
}

Image* loadBMP(const char* filename)
{
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"Could not find file");
    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    input.ignore(8);
    int dataOffset = readInt(input);

    //Read the header
    int headerSize = readInt(input);
    int width;
    int height;
    switch (headerSize)
    {
        case 40:
            //V3
            width = readInt(input);
            height = readInt(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            assert(readShort(input) == 0 || !"Image is compressed");
            break;
        case 12:
            //OS/2 V1
            width = readShort(input);
            height = readShort(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            break;
        case 64:
            //OS/2 V2
            assert(!"Can't load OS/2 V2 bitmaps");
            break;
        case 108:
            //Windows V4
            assert(!"Can't load Windows V4 bitmaps");
            break;
        case 124:
            //Windows V5
            assert(!"Can't load Windows V5 bitmaps");
            break;
        default:
            assert(!"Unknown bitmap format");
    }

    //Read the data
    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);

    //Get the data into the right format
    auto_array<char> pixels2(new char[width * height * 3]);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                pixels2[3 * (width * y + x) + c] =
                pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }

    input.close();
    return new Image(pixels2.release(), width, height);
}
