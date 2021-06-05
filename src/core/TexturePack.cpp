#include "raylib.h"
//#include "rlgl.h"
#include "TexturePack.hpp"

TexturePack::TexturePack(Texture2D textureData, float textureColumns, float textureRows)
	: data(textureData), cols(textureColumns), rows(textureRows),
        dataWidth((float)data.width), dataHeight((float)data.height),
        frameWidth(dataWidth / cols), frameHeight(dataHeight / rows)
{
}

TexturePack::~TexturePack()
{
}

Rectangle TexturePack::GetTextureFrame(float x, float y)
{
    return { dataWidth * x / cols, dataHeight * y / rows, frameWidth, frameHeight };
}
