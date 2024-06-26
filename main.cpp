#include <iostream>
#include <raylib.h>
#include "Entity.h"


using namespace std;



int main () {

    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");


    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 1.0f, 5.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
   
    Entity enitites[2];
    enitites[0] = Entity();
    enitites[1] = Entity();

    
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        BeginDrawing();

        ClearBackground(RAYWHITE);

        for(auto t: enitites)
        {
            t.Update();
        }

        BeginMode3D(camera);

        for(auto t: enitites)
        {
            t.Draw();   
        };

        DrawGrid(10, 1.0f); 

        EndMode3D();
        EndDrawing();
    }

    for(auto t: enitites)
    {
        UnloadModel(t.entityModel); //unload the model from memory     
    };
    
    CloseWindow();
    return 0;
}