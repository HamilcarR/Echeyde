#include "../headers/Framebuffer.h"
#include "../headers/Material.h"


Framebuffer::Framebuffer()
{
}

static GLuint createFrameBuffer(){
	GLuint id = 0; 
	glGenFramebuffers(1, &id);
	assert(id != 0); 
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glDrawBuffer(GL_COLOR_ATTACHMENT0); 
	return id;

}

static GLuint createTexture(const unsigned W, const unsigned H){
	GLuint render_texture = 0; 
	glGenTextures(1, &render_texture);
	glBindTexture(GL_TEXTURE_2D, render_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, render_texture, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		std::cout << " FB COLOR PROBLEM" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0); 
	}
	return render_texture; 
}

static GLuint createDepthTexture(const unsigned W, const unsigned H){
	GLuint render_texture = 0;
	glGenTextures(1, &render_texture);
	glBindTexture(GL_TEXTURE_2D, render_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, W, H, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D, render_texture, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		std::cout << " FB DEPTH PROBLEM" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}
	return render_texture; 
}

static GLuint createRenderBuffer(const unsigned W, const unsigned H){
	GLuint id = 0;
	glGenRenderbuffers(1, &id);
	glBindRenderbuffer(GL_RENDERBUFFER, id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, W, H); /*MSAA ?*/
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, id);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	return id; 
}
Framebuffer::Framebuffer(const unsigned width , const unsigned height)
{
	fb_id = createFrameBuffer(); 
	rb_id = createRenderBuffer(width, height);
	color_texture = createTexture(width, height);
	depth_texture = createDepthTexture(width, height);
	W = width; 
	H = height; 
	Unbind(); 
}

Framebuffer::~Framebuffer()
{
}

void Framebuffer::clean(){
	glDeleteFramebuffers(1, &fb_id);
	glDeleteRenderbuffers(1, &rb_id); 
	glDeleteTextures(1, &color_texture);
	glDeleteTextures(1, &depth_texture);
}

void Framebuffer::Bind(){
	
	glViewport(0, 0, W, H);
	glBindFramebuffer(GL_FRAMEBUFFER, fb_id);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawBuffer(GL_COLOR_ATTACHMENT0);
}

void Framebuffer::Unbind(){


	glBindFramebuffer(GL_FRAMEBUFFER, 0); 

	glViewport(0, 0, WIDTH, HEIGHT);

}


void Framebuffer::BindDepth(){
	glViewport(0, 0, W, H);
	glBindFramebuffer(GL_FRAMEBUFFER, fb_id);
	glClear(GL_DEPTH_BUFFER_BIT);
	glDrawBuffer(GL_NONE); 
	glReadBuffer(GL_NONE); 
}


void Framebuffer::UnbindDepth(){

	glBindFramebuffer(GL_FRAMEBUFFER, 0); 

	glViewport(0, 0, WIDTH, HEIGHT);
}
