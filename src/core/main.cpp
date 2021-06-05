#include "raylib.h"
#include "rlgl.h"
#include "main.h"
#include "TexturePack.hpp"
#include "Voxel.hpp"

void DrawAxisTarget(Camera camera)
{
    // Center - BLACK
    DrawSphere({ camera.target.x, camera.target.y, camera.target.z }, 0.05f, BLACK);
    // X-axis - RED
    DrawLine3D({ camera.target.x - 1.0f, camera.target.y, camera.target.z }, { camera.target.x + 1.0f, camera.target.y, camera.target.z }, RED);
    DrawSphere({ camera.target.x + 1.0f, camera.target.y, camera.target.z }, 0.05f, RED);
    // Y-axis - GREEN
    DrawLine3D({ camera.target.x, camera.target.y - 1.0f, camera.target.z }, { camera.target.x, camera.target.y + 1.0f, camera.target.z }, GREEN);
    DrawSphere({ camera.target.x, camera.target.y + 1.0f, camera.target.z }, 0.05f, GREEN);
    // Z-axis - BLUE
    DrawLine3D({ camera.target.x, camera.target.y, camera.target.z - 1.0f }, { camera.target.x, camera.target.y, camera.target.z + 1.0f }, BLUE);
    DrawSphere({ camera.target.x, camera.target.y, camera.target.z + 1.0f }, 0.05f, BLUE);
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D texturePackData = LoadTexture("resources/texture_default.png"); // Texture loading
    TexturePack* texturePack = new TexturePack(texturePackData, 12, 8);

    Camera camera = { 0 };
    camera.position = { 10.0f, 10.0f, 8.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetCameraMode(camera, CAMERA_THIRD_PERSON);

    Vector3 cubePosition = {0};
    Vector3 cubePositionGreen = {2.0f, 0.0f, 0.0f};
    Vector3 cubePositionBlue = {-2.0f, 0.0f, 0.0f};
    Vector3 cubePositionBlack = {0.0f, 2.0f, 0.0f};
    float verticesLength = 1.0f;
    float cameraMovement = 0.1f;
    //Vector3 voxelPosition = {1.0f, 1.0f, 1.0f};
    int voxelFaces[6] = {1, 1, 1, 1, 1, 1};

    Voxel* v1 = new Voxel(texturePack, { 1.0f, 1.0f, 1.0f });
    Voxel* v2 = new Voxel(texturePack, { 1.0f, 2.0f, 1.0f });
    const int chunkSize = 10;
    Voxel* voxels[chunkSize][chunkSize][chunkSize];

    for (int x = 0; x < chunkSize; x++)
    {
        for (int y = 0; y < chunkSize; y++)
        {
            for (int z = 0; z < chunkSize; z++)
            {
                voxels[x][y][z] = new Voxel(texturePack, { (float)x, (float)y, (float)z });
            }
        }
    }

    SetTargetFPS(120);               // Set our game to run at 120 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_A)){ camera.position.x += cameraMovement; camera.target.x += cameraMovement; }
        if (IsKeyDown(KEY_D)){ camera.position.x -= cameraMovement; camera.target.x -= cameraMovement; }
        if (IsKeyDown(KEY_S)){ camera.position.z -= cameraMovement; camera.target.z -= cameraMovement; }
        if (IsKeyDown(KEY_W)){ camera.position.z += cameraMovement; camera.target.z += cameraMovement; }
        if (IsKeyPressed(KEY_Q)){ camera.position.y -= 1.0f; camera.target.y -= 1.0f; }
        if (IsKeyPressed(KEY_E)){ camera.position.y += 1.0f; camera.target.y += 1.0f; }
        if (IsKeyPressed(KEY_KP_1)){ voxelFaces[0] = !voxelFaces[0]; }
        if (IsKeyPressed(KEY_KP_2)){ voxelFaces[1] = !voxelFaces[1]; }
        if (IsKeyPressed(KEY_KP_3)){ voxelFaces[2] = !voxelFaces[2]; }
        if (IsKeyPressed(KEY_KP_4)){ voxelFaces[3] = !voxelFaces[3]; }
        if (IsKeyPressed(KEY_KP_5)){ voxelFaces[4] = !voxelFaces[4]; }
        if (IsKeyPressed(KEY_KP_6)){ voxelFaces[5] = !voxelFaces[5]; }
        UpdateCamera(&camera);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

            DrawAxisTarget(camera);
            //DrawVoxel(texturePackData, texturePack->GetTextureFrame(4.0f, 5.0f), voxelPosition, 1.0f, 1.0f, 1.0f, voxelFaces, WHITE);
            //DrawCubeWires(voxelPosition, verticesLength, verticesLength, verticesLength, BLACK);
            //v1->Draw(voxelFaces);
            //v2->Draw(voxelFaces);

            for (int x = 0; x < chunkSize; x++)
            {
                for (int y = 0; y < chunkSize; y++)
                {
                    for (int z = 0; z < chunkSize; z++)
                    {
                        voxels[x][y][z]->Draw(voxelFaces);
                    }
                }
            }
            // DrawCube(cubePosition, verticesLength, verticesLength, verticesLength, RED);
            // DrawCubeWires(cubePosition, verticesLength, verticesLength, verticesLength, MAROON);
            // DrawCube(cubePositionGreen, verticesLength, verticesLength, verticesLength, GREEN);
            // DrawCubeWires(cubePositionGreen, verticesLength, verticesLength, verticesLength, BLACK);
            // DrawCube(cubePositionBlue, verticesLength, verticesLength, verticesLength, BLUE);
            // DrawCubeWires(cubePositionBlue, verticesLength, verticesLength, verticesLength, BLACK);
            // DrawCube(cubePositionBlack, verticesLength, verticesLength, verticesLength, BLACK);
            // DrawCubeWires(cubePositionBlack, verticesLength, verticesLength, verticesLength, WHITE);
            DrawGrid(20, 1.0f);
            //DrawTextureRec();
            EndMode3D();

            DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);
            //Texture debugging labels
            // DrawText(TextFormat("frameRec={%02.02f, %02.02f, %02.02f, %02.02f}", frameRec.x, frameRec.y, frameRec.height, frameRec.width), 10, 60, 20, DARKGRAY);
            // DrawText(TextFormat("texWidth=%02.02f, texHeight=%02.02f}", texWidth, texHeight), 10, 80, 20, DARKGRAY);
            // DrawText(TextFormat("source.x/texWidth=%02.02f, source.y/texHeight=%02.02f}", frameRec.x / texWidth, frameRec.y / texHeight), 10, 100, 20, DARKGRAY);
            //voxel faces debugging label
            // DrawText(TextFormat("voxelFaces: %s, %s, %s, %s, %s, %s", voxelFaces[0] ? "true" : "false", voxelFaces[1] ? "true" : "false", voxelFaces[2] ? "true" : "false",
            //                                                           voxelFaces[3] ? "true" : "false", voxelFaces[4] ? "true" : "false", voxelFaces[5] ? "true" : "false"), 10, 120, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
