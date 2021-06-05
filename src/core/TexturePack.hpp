#pragma once
class TexturePack
{
public:
	TexturePack(Texture2D textureData, float textureColumns, float textureRows);
	~TexturePack();
	Rectangle GetTextureFrame(float x, float y);
	Texture2D data;
private:
	float cols;
	float rows;
	float dataWidth;
	float dataHeight;
	float frameWidth;
	float frameHeight;
};
