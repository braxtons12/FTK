/**
 * Utility class used to load an image to an OpenGL BYTE array
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#ifndef _IMAGE_LOAD
#define _IMAGE_LOAD

#include <string>
#include <GL/glew.h>
#include <FreeImage.h>

namespace fusion { namespace core { namespace utils {

	class ImageLoad {
		
		public:
			static BYTE* load_image(const char* path, GLsizei* width, GLsizei* height) {

			//image format
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			//pointer to the image, once loaded
			FIBITMAP* dib = nullptr;
			//check the file signature and deduce its FREE_IMAGE_FORMAT
			fif = FreeImage_GetFileType(path, 0);
			//if still unkown, try to guess the file format from the file extension
			if (fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename(path);
			//if still unkown, return failure
			if (fif == FIF_UNKNOWN) return nullptr;

			if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, path);
			if (!dib) return nullptr;

			//retrieve the image data
			BYTE* result = FreeImage_GetBits(dib);
			//get the image width and height
			*width = FreeImage_GetWidth(dib);
			*height = FreeImage_GetHeight(dib);

			return result;

		}
	};
}}}

#endif
