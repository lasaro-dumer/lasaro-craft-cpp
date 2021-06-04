#pragma once

// NOTE: Cube position is the center position
void DrawVoxel(Texture2D texture, Rectangle source, Vector3 position, float width, float height, float length, int faces[], Color color)
{
    //Start from DrawTexturePro region
    float texWidth = (float)texture.width;
    float texHeight = (float)texture.height;

    bool flipX = false;

    if (source.width < 0) { flipX = true; source.width *= -1; }
    if (source.height < 0) source.y -= source.height;
    //End from DrawTexturePro region

    float x = position.x;
    float y = position.y;
    float z = position.z;

    rlCheckRenderBatchLimit(36);

    //rlPushMatrix();
    // NOTE: Transformation is applied in inverse order (scale -> rotate -> translate)
    //rlTranslatef(2.0f, 0.0f, 0.0f);
    //rlRotatef(45, 0, 1, 0);
    //rlScalef(2.0f, 2.0f, 2.0f);

    rlBegin(RL_QUADS);
    rlColor4ub(color.r, color.g, color.b, color.a);
    // Front Face
    rlSetTexture(texture.id);
    if (faces[0]) {
        rlNormal3f(0.0f, 0.0f, 1.0f);                  // Normal Pointing Towards Viewer
        if (flipX) rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        else rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
        if (flipX) rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        else rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
        if (flipX) rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        else rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Top Right Of The Texture and Quad
        if (flipX) rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        else rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Top Left Of The Texture and Quad
    }
    // Back Face
    if (faces[1]) {
        rlNormal3f(0.0f, 0.0f, -1.0f);                  // Normal Pointing Away From Viewer
        if (flipX) rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        else rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Bottom Right Of The Texture and Quad
        if (flipX) rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        else rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
        if (flipX) rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        else rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
        if (flipX) rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        else rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Bottom Left Of The Texture and Quad
    }
    // Top Face
    if (faces[2]) {
        rlNormal3f(0.0f, 1.0f, 0.0f);                  // Normal Pointing Up
        if (flipX) rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        else rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
        if (flipX) rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        else rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
        if (flipX) rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        else rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
        if (flipX) rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        else rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
    }
    // Bottom Face
    if (faces[3]) {
        rlNormal3f(0.0f, -1.0f, 0.0f);                  // Normal Pointing Down
        if (flipX) rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        else rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Top Right Of The Texture and Quad
        if (flipX) rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        else rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Top Left Of The Texture and Quad
        if (flipX) rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        else rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
        if (flipX) rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        else rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
    }
    // Right face
    if (faces[4]) {
        rlNormal3f(1.0f, 0.0f, 0.0f);                  // Normal Pointing Right
        if (flipX) rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        else rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Bottom Right Of The Texture and Quad
        if (flipX) rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        else rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
        if (flipX) rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        else rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Top Left Of The Texture and Quad
        if (flipX) rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        else rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
    }
    // Left Face
    if (faces[5]) {
        rlNormal3f(-1.0f, 0.0f, 0.0f);                  // Normal Pointing Left
        if (flipX) rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        else rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Bottom Left Of The Texture and Quad
        if (flipX) rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        else rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
        if (flipX) rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        else rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Top Right Of The Texture and Quad
        if (flipX) rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        else rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
    }
    rlEnd();
    //rlPopMatrix();

    rlSetTexture(0);
}
