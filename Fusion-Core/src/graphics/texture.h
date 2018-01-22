#ifndef _TEXTURE
#define _TEXTURE

#include <string>
#include <GL/glew.h>
#include <FreeImage.h>
#include "../../src/utils/imageload.h"

namespace fusion { namespace core { namespace graphics {

	class Texture {

		private:
			std::string m_Path;
			GLuint m_TID;
		 	GLsizei m_Width, m_Height;

			GLuint load();


		public:
			Texture(const std::string& path);
			~Texture();
			void bind() const;
			void unbind() const;

			inline const GLsizei getWidth() const { return m_Width; }
			inline const GLsizei getHeight() const { return m_Height; }

	};
}}}
#endif
