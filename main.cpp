#include <iostream>
#include <raylib.h>
#include "Entity.h"


using namespace std;



int main () {

    const int screenWidth = 800;
    const int screenHeight = 600;
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");


    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 90.0f, 350.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 90.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
   
    Vector3 player1Start = {-50.f,0.f,0.f};
    Vector3 player2Start = {50.f,0.f,0.f};
    Entity entities[2];
    entities[0] = Entity();
    entities[0].position = player1Start;
    entities[1] = Entity();
    entities[1].position = player2Start;

    entities[0].otherEntity = &entities[1];
    entities[1].otherEntity = &entities[0];

    Vector3 cubePosition = {0.f,0.f,0.f};
    const int MAX_PLAYERS = 2;

    
    SetTargetFPS(60);

    while (!WindowShouldClose())
    { 
        for(int i = 0; i < MAX_PLAYERS; i++)
        {
            entities[i].Update();
            entities[i].GatherInput();
        }
        //entities[0].GatherInput();

        // if(IsKeyDown(KEY_LEFT))
        // {
        //     cubePosition.x += 2;
        // }
        // else if(IsKeyDown(KEY_RIGHT))
        // {
        //     cubePosition.x -= 2;
        // }

        

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

        for(int i = 0; i < MAX_PLAYERS; i++)
        {
            entities[i].Draw();
        }
        DrawCube(cubePosition, 1.f,1.f,1.f, RED);
        DrawGrid(10, 1.0f); 

        EndMode3D();
        EndDrawing();
    }

    for(auto t: entities)
    {
        UnloadModel(t.entityModel); //unload the model from memory     
    };
    
    CloseWindow();
    return 0;
}