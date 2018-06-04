#pragma once

#include "Renderer.h"

class Texture {
private:
	uint renderer_id;
	std::string filepath;
	unsigned char* localBuf;
	int width, height, bpp; // bits per pixel
public:
	Texture(const std::string& path);
	~Texture();
	void Bind(uint slot = 0) const;
	void Unbind() const;
	inline int GetWidth() { return width; }
	inline int GetHigh() { return height; }
};