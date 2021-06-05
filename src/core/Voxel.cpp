#include "raylib.h"
#include "rlgl.h"
#include "TexturePack.hpp"
#include "Voxel.hpp"

Voxel::Voxel(TexturePack* texturePack, Vector3 position)
    : Voxel(texturePack, position, 1.0f)
{
}

Voxel::Voxel(TexturePack* texturePack, Vector3 position, float edgesSize)
    : Voxel(texturePack, position, edgesSize, {1.0f, 1.0f})
{
}

Voxel::Voxel(TexturePack* texturePack, Vector3 position, float edgesSize, Vector2 textureFramePos)
    : texPack(texturePack), pos(position), width(edgesSize), height(edgesSize), length(edgesSize), texFramePos(textureFramePos)
{
}

Voxel::~Voxel()
{
}

void Voxel::Draw(int faces[])
{
    DrawCubeWires(pos, width, height, length, BLACK);

    //int faces[], Color color
    //Start from DrawTexturePro region
    float texWidth = (float)texPack->data.width;
    float texHeight = (float)texPack->data.height;
    Rectangle textureFrame = texPack->GetTextureFrame(texFramePos.x, texFramePos.y);

    bool flipX = false;

    if (textureFrame.width < 0) { flipX = true; textureFrame.width *= -1; }
    if (textureFrame.height < 0) textureFrame.y -= textureFrame.height;
    //End from DrawTexturePro region

    float x = pos.x;
    float y = pos.y;
    float z = pos.z;

    rlCheckRenderBatchLimit(36);

    //rlPushMatrix();
    // NOTE: Transformation is applied in inverse order (scale -> rotate -> translate)
    //rlTranslatef(2.0f, 0.0f, 0.0f);
    //rlRotatef(45, 0, 1, 0);
    //rlScalef(2.0f, 2.0f, 2.0f);

    rlBegin(RL_QUADS);
    rlColor4ub(color.r, color.g, color.b, color.a);
    // Front Face
    rlSetTexture(texPack->data.id);
    if (faces[0]) {
        rlNormal3f(0.0f, 0.0f, 1.0f);                  // Normal Pointing Towards Viewer
        if (flipX) rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        else rlTexCoord2f(textureFrame.x / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
        if (flipX) rlTexCoord2f(textureFrame.x / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        else rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
        if (flipX) rlTexCoord2f(textureFrame.x / texWidth, textureFrame.y / texHeight);
        else rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, textureFrame.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Top Right Of The Texture and Quad
        if (flipX) rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, textureFrame.y / texHeight);
        else rlTexCoord2f(textureFrame.x / texWidth, textureFrame.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Top Left Of The Texture and Quad
    }
    // Back Face
    if (faces[1]) {
        rlNormal3f(0.0f, 0.0f, -1.0f);                  // Normal Pointing Away From Viewer
        if (flipX) rlTexCoord2f(textureFrame.x / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        else rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Bottom Right Of The Texture and Quad
        if (flipX) rlTexCoord2f(textureFrame.x / texWidth, textureFrame.y / texHeight);
        else rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, textureFrame.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
        if (flipX) rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, textureFrame.y / texHeight);
        else rlTexCoord2f(textureFrame.x / texWidth, textureFrame.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
        if (flipX) rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        else rlTexCoord2f(textureFrame.x / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Bottom Left Of The Texture and Quad
    }
    // Top Face
    if (faces[2]) {
        rlNormal3f(0.0f, 1.0f, 0.0f);                  // Normal Pointing Up
        if (flipX) rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, textureFrame.y / texHeight);
        else rlTexCoord2f(textureFrame.x / texWidth, textureFrame.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
        if (flipX) rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        else rlTexCoord2f(textureFrame.x / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
        if (flipX) rlTexCoord2f(textureFrame.x / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        else rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
        if (flipX) rlTexCoord2f(textureFrame.x / texWidth, textureFrame.y / texHeight);
        else rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, textureFrame.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
    }
    // Bottom Face
    if (faces[3]) {
        rlNormal3f(0.0f, -1.0f, 0.0f);                  // Normal Pointing Down
        if (flipX) rlTexCoord2f(textureFrame.x / texWidth, textureFrame.y / texHeight);
        else rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, textureFrame.y / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Top Right Of The Texture and Quad
        if (flipX) rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, textureFrame.y / texHeight);
        else rlTexCoord2f(textureFrame.x / texWidth, textureFrame.y / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Top Left Of The Texture and Quad
        if (flipX) rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        else rlTexCoord2f(textureFrame.x / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
        if (flipX) rlTexCoord2f(textureFrame.x / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        else rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
    }
    // Right face
    if (faces[4]) {
        rlNormal3f(1.0f, 0.0f, 0.0f);                  // Normal Pointing Right
        if (flipX) rlTexCoord2f(textureFrame.x / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        else rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Bottom Right Of The Texture and Quad
        if (flipX) rlTexCoord2f(textureFrame.x / texWidth, textureFrame.y / texHeight);
        else rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, textureFrame.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
        if (flipX) rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, textureFrame.y / texHeight);
        else rlTexCoord2f(textureFrame.x / texWidth, textureFrame.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Top Left Of The Texture and Quad
        if (flipX) rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        else rlTexCoord2f(textureFrame.x / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
    }
    // Left Face
    if (faces[5]) {
        rlNormal3f(-1.0f, 0.0f, 0.0f);                  // Normal Pointing Left
        if (flipX) rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        else rlTexCoord2f(textureFrame.x / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Bottom Left Of The Texture and Quad
        if (flipX) rlTexCoord2f(textureFrame.x / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        else rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, (textureFrame.y + textureFrame.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
        if (flipX) rlTexCoord2f(textureFrame.x / texWidth, textureFrame.y / texHeight);
        else rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, textureFrame.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Top Right Of The Texture and Quad
        if (flipX) rlTexCoord2f((textureFrame.x + textureFrame.width) / texWidth, textureFrame.y / texHeight);
        else rlTexCoord2f(textureFrame.x / texWidth, textureFrame.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
    }
    rlEnd();
    //rlPopMatrix();

    rlSetTexture(0);
}
