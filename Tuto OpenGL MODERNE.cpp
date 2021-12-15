/*

        Copyright 2021 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Tutorial 18 - Loading models with Assimp

    Modified in order to add lights by Brice Conraux
*/

#include"mainIncludes.h"

#define WINDOW_WIDTH  2560
#define WINDOW_HEIGHT 1440

bool FS = false;



class Tutorial18
{
public:
    Tutorial18();
    ~Tutorial18();

    bool Init();

    void RenderSceneCB();
    void KeyboardCB(unsigned char key, int mouse_x, int mouse_y);
    void SpecialKeyboardCB(int key, int mouse_x, int mouse_y);
    void PassiveMouseCB(int x, int y);

private:

    GLuint WVPLocation;
    GLuint SamplerLocation;
    Camera* pGameCamera = NULL;
    BasicMesh* pMesh = NULL;
    Matrix4f projection;
    LightingTechnique* pLightingTech = NULL;
    DirectionalLight dirLight;
};


Tutorial18::Tutorial18()
{
    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

    float FOV = 45.0f;
    float zNear = 1.0f;
    float zFar = 100.0f;

    projection.InitPersProjTransform(FOV, WINDOW_WIDTH, WINDOW_HEIGHT, zNear, zFar);

    dirLight.AmbientIntensity = 0.1f;
    dirLight.DiffuseIntensity = 1.0f;
    dirLight.WorldDirection = Vector3f(1.0f, 0.0f, 0.0f);

}


Tutorial18::~Tutorial18()
{
    if (pGameCamera) {
        delete pGameCamera;
    }

    if (pMesh) {
        delete pMesh;
    }
}


bool Tutorial18::Init()
{
    Vector3f CameraPos(0.0f, 0.0f, -1.0f);
    Vector3f CameraTarget(0.0f, 0.0f, 1.0f);
    Vector3f CameraUp(0.0f, 1.0f, 0.0f);

    pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, CameraPos, CameraTarget, CameraUp);

    pMesh = new BasicMesh();

    if (!pMesh->LoadMesh("wine_barrel_01_4k.obj")) {
        return false;
    }

    pLightingTech = new LightingTechnique();

    if (!pLightingTech->Init()) {
        return false;
    }

    pLightingTech->Enable();

    pLightingTech->SetTextureUnit(COLOR_TEXTURE_UNIT_INDEX); //argument défini dans enginecommon.h
    pLightingTech->SetSpecularExponentTextureUnit(SPECULAR_EXPONENT_UNIT_INDEX); //idem

    return true;
}


void Tutorial18::RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    pGameCamera->OnRender();

#ifdef _WIN64
    float YRotationAngle = 1.0f;
#else
    float YRotationAngle = 1.0f;
#endif

    WorldTrans& worldTransform = pMesh->GetWorldTransform();

    worldTransform.SetScale(1.0f);
    worldTransform.SetPosition(0.0f, 0.0f, 2.0f);
    worldTransform.Rotate(0.0f, YRotationAngle, 0.0f);

    Matrix4f World = worldTransform.GetMatrix();

    dirLight.CalcLocalDirection(World);

    Matrix4f View = pGameCamera->GetMatrix();

    Matrix4f WVP = projection * View * World;

    pLightingTech->SetWVP(WVP);
    pLightingTech->SetDirectionalLight(dirLight);
    pLightingTech->SetMaterial(pMesh->GetMaterial());

    //Dans les lignes suivantes, on récupère la position locale de la caméra pour 
    //pouvoir l'utiliser dans notre implémentation de l'éclairage spéculaire 

    Matrix4f CameraToLocalTranslation = worldTransform.GetReversedTranslationMatrix(); //Les fonctions sont ajoutées dans world transform

    Matrix4f CameraToLocalRotation = worldTransform.GetReversedRotationMatrix();

    Matrix4f CameraToLocalTransformation = CameraToLocalRotation * CameraToLocalTranslation;

    Vector4f CameraWorldPos = Vector4f(pGameCamera->GetPos(), 1.0f);

    Vector4f CameraLocalPos = CameraToLocalTransformation * CameraWorldPos;

    Vector3f CameraLocalPos3f= CameraLocalPos.to3f();

    pLightingTech->SetCameraLocalPos(CameraLocalPos3f);

    pMesh->Render();

    glutPostRedisplay();

    glutSwapBuffers();
}


void Tutorial18::KeyboardCB(unsigned char key, int mouse_x, int mouse_y)
{
    switch (key) {
    case 'q':
    case 27:    // escape key code
        exit(0);
        break;
    case 'f':
        if (!FS) {
            glutFullScreen();
            FS = !FS;
        }
        else {
            glutLeaveFullScreen();
            FS = !FS;
        }
        break;
    }


    pGameCamera->OnKeyBoard(key);
}


void Tutorial18::SpecialKeyboardCB(int key, int mouse_x, int mouse_y)
{
    pGameCamera->OnKeyBoard(key);
}


void Tutorial18::PassiveMouseCB(int x, int y)
{
    pGameCamera->OnMouse(x, y);
}


Tutorial18* pTutorial18 = NULL;


void RenderSceneCB()
{
    pTutorial18->RenderSceneCB();
}


void KeyboardCB(unsigned char key, int mouse_x, int mouse_y)
{

    pTutorial18->KeyboardCB(key, mouse_x, mouse_y);
}


void SpecialKeyboardCB(int key, int mouse_x, int mouse_y)
{
    pTutorial18->SpecialKeyboardCB(key, mouse_x, mouse_y);
}


void PassiveMouseCB(int x, int y)
{
    pTutorial18->PassiveMouseCB(x, y);
}


void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
    glutKeyboardFunc(KeyboardCB);
    glutSpecialFunc(SpecialKeyboardCB);
    glutPassiveMotionFunc(PassiveMouseCB);
}

int main(int argc, char** argv)
{
#ifdef _WIN64
    srand(GetCurrentProcessId());
#else
    srandom(getpid());
#endif

    glutInit(&argc, argv);
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    int x = 200;
    int y = 100;
    glutInitWindowPosition(x, y);
    int win = glutCreateWindow("Tutorial 18");
    printf("window id: %d\n", win);


    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    InitializeGlutCallbacks();

    pTutorial18 = new Tutorial18();

    if (!pTutorial18->Init()) {
        return 1;
    }

    glutMainLoop();

    return 0;
}