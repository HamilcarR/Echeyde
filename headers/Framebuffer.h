#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include "Constants.h"
#include "Texture.h"
class Framebuffer
{
public:
	Framebuffer(); 
	Framebuffer(const unsigned width , const unsigned height);
	virtual ~Framebuffer();
	
	void clean(); 
	void Bind();
	void Unbind(); 
	void BindDepth(); 
	void UnbindDepth(); 

	const GLuint getFrameBufferID()  const { return fb_id;  }
	const GLuint getRenderBufferID() const { return rb_id;  }
	const GLuint getColorTexture()  const { return color_texture; }
	const GLuint getDepthTexture()  const { return depth_texture; }

	
private:
	GLuint fb_id; 
	GLuint rb_id;
	GLuint color_texture;
	GLuint depth_texture;
	unsigned W, H; 
};

#endif
