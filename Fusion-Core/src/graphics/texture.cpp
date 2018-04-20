/**
 * Datatype encapsulating texture data and OpenGL texture functionality
 * 
 * Implementation File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#include "texture.h"

namespace fusion { namespace core { namespace graphics {

	/**
	 * Constructor
	 * 
	 **/
	Texture::Texture(const std::string& path)
		: m_Path(path)
	{

		m_TID = load();
	}

	/**
	 * Destructor
	 * 
	 **/
	Texture::~Texture() {

	}

	/**
	 * Load the texture from file
	 * 
	 **/
	GLuint Texture::load() {

		BYTE* pixels = utils::ImageLoad::load_image(m_Path.c_str(), &m_Width, &m_Height);

		GLuint result;
		glGenTextures(1, &result);
		glBindTexture(GL_TEXTURE_2D, result);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
		glBindTexture(GL_TEXTURE_2D, 0);

		//delete[] pixels; ???

		return result;
	}

}}}
