#pragma once
class Voxel
{
	public:
		Voxel(TexturePack* texturePack, Vector3 position);
		Voxel(TexturePack* texturePack, Vector3 position, float edgesSize);
		Voxel(TexturePack* texturePack, Vector3 position, float edgesSize, Vector2 textureFramePos);
		~Voxel();
		void Draw(int faces[]);
	private:
		TexturePack* texPack;
		Vector3 pos;
		float width;
		float height;
		float length;
		Vector2 texFramePos;
		Color color = WHITE;
};
