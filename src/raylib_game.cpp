
#include "raylib.h"

#if defined(PLATFORM_WEB)
    #define CUSTOM_MODAL_DIALOGS            // Force custom modal dialogs usage
    #include <emscripten/emscripten.h>      // Emscripten library - LLVM to JavaScript compiler
#endif

#include <stdio.h>                          // Required for: printf()
#include <stdlib.h>                         // Required for: 
#include <string.h>                         // Required for: 

#define SUPPORT_LOG_INFO
#if defined(SUPPORT_LOG_INFO)
    #define LOG(...) printf(__VA_ARGS__)
#else
    #define LOG(...)
#endif

typedef enum { 
    SCREEN_LOGO = 0, 
    SCREEN_TITLE, 
    SCREEN_GAMEPLAY, 
    SCREEN_ENDING
} GameScreen;


static const int screenWidth = 1280;
static const int screenHeight = 720;

static RenderTexture2D target = { 0 };  // Render texture to render our game

static void UpdateDrawFrame(void);      // Update and Draw one frame

int main(void)
{
    if(!defined(_DEBUG)){
        SetTraceLogLevel(LOG_NONE);         // Disable raylib trace log messages
    }

    InitWindow(screenWidth, screenHeight, "raylib gamejam template");
    
    
    target = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

    if(PLATFORM_WEB){
        emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
    }else{
        SetTargetFPS(60);     // Set our game frames-per-second

        // Main game loop
        while (!WindowShouldClose())    // Detect window close button
        {
            UpdateDrawFrame();
        }
    }

    UnloadRenderTexture(target);
    

    CloseWindow();        // Close window and OpenGL context

    return 0;
}

void UpdateDrawFrame(void)
{
    BeginTextureMode(target);
        ClearBackground(RAYWHITE);
        
        DrawRectangle(10, 10, screenWidth - 20, screenHeight - 20, SKYBLUE);
        
    EndTextureMode();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawTexturePro(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, -(float)target.texture.height }, (Rectangle){ 0, 0, (float)target.texture.width, (float)target.texture.height }, (Vector2){ 0, 0 }, 0.0f, WHITE);


    EndDrawing();
}