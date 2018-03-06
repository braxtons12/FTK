/**
 * Datatype encapsulating texture data and OpenGL texture functionality
 * 
 * Header File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#ifndef _TEXTURE
#define _TEXTURE

#include <string>
#include <GL/glew.h>
#include <FreeImage.h>
#include "utils/imageload.h"

namespace fusion { namespace core { namespace graphics {

	class Texture {

		private:
			std::string m_Path;
			GLuint m_TID;
		 	GLsizei m_Width, m_Height;

			/**
			 * Load the texture from file
			 * 
			 **/
			GLuint load();


		public:
			/**
			 * Constructor
			 * 
			 **/
			Texture(const std::string& path);

			/**
			 * Destructor
			 * 
			 **/
			~Texture();

			/**
			 * Bind the texture in OpenGL
			 * 
			 **/
			inline void bind() const { glBindTexture(GL_TEXTURE_2D, m_TID); }

			/**
			 * Unbind the texture in OpenGL
			 * 
			 **/
			inline void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

			//getters
			inline const unsigned int getID() const { return m_TID; }
			inline const unsigned int getWidth() const { return m_Width; }
			inline const unsigned int getHeight() const { return m_Height; }

	};
}}}

#endif
