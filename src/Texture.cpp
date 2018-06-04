#include "Texture.h"
#include "vendor/stb/stb_image.h"

Texture::Texture(const std::string& path) :
	renderer_id(0), bpp(0),
	filepath(path), localBuf(nullptr), width(0), height(0)
{
	stbi_set_flip_vertically_on_load(1);
	localBuf = stbi_load(path.c_str(), &width, &height, &bpp, 4); // 4 for rgba
	GlCall(glGenTextures(1, &renderer_id));
	GlCall(glBindTexture(GL_TEXTURE_2D, renderer_id));

	// essential 4 parameters for not having black screen
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, 
		GL_UNSIGNED_BYTE, localBuf));
	GlCall(glBindTexture(GL_TEXTURE_2D, 0));
	if (localBuf) {
		stbi_image_free(localBuf);
	}
}

Texture::~Texture()
{
	GlCall(glDeleteTextures(1, &renderer_id));
}

void Texture::Bind(uint slot /*= 0*/) const
{
	GlCall(glActiveTexture(GL_TEXTURE0 + slot));
	GlCall(glBindTexture(GL_TEXTURE_2D, renderer_id));
}

void Texture::Unbind() const
{
	GlCall(glBindTexture(GL_TEXTURE_2D, 0));
}

