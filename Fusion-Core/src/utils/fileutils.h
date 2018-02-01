#ifndef _FILEUTILS
#define _FILEUTILS

#include <cstring>
#include <fstream>
#include <iostream>

namespace fusion { namespace core { namespace utils {

    class FileUtils {

        public:
        static std::string read_file(const char* filepath) {

                FILE* file = fopen(filepath, "rt");
                if(file == NULL) std::cout << "FILE IS NULL" << std::endl;
                fseek(file, (long)0, SEEK_END);
                unsigned long length = ftell(file);
                char *data = new char[length + 1];
                memset(data, 0, length + 1);
                fseek(file, (long)0, SEEK_SET);
                fread(data, 1, length, file);
                fclose(file);

                std::string result(data);
                delete[] data;
                return result;
            }
    };
}}}

#endif
