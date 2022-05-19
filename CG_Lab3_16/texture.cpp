#include <iostream>
#include "texture.h"

Texture::Texture(GLenum TextureTarget, const std::string& FileName)
{
    m_textureTarget = TextureTarget;
    m_fileName = FileName;
    m_pImage = NULL;
}

bool Texture::Load()
{
    //использование GraphicsMagick для загрузки из файла и подготовки памяти для загрузки в OpenGL
    try {
        m_pImage = new Magick::Image(m_fileName);
        m_pImage->write(&m_blob, "RGBA");
    }
    catch (Magick::Error& Error) {
        std::cout << "Error loading texture '" << m_fileName << "': " << Error.what() << std::endl;
        return false;
    }
    //генерирует указанное число объектов текстур и помещает их в указатель на массив GLuint (второй параметр)
    glGenTextures(1, &m_textureObj);
    glBindTexture(m_textureTarget, m_textureObj);
    //функция для загрузки главной части объекта текстуры
    glTexImage2D(m_textureTarget, 0, GL_RGB, m_pImage->columns(), m_pImage->rows(), -0.5, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
    //указываются фильтры, которые будут использованы для увеличения и минимализации
    glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

/*принимает модуль текстуры как параметр типа enum (GL_TEXTURE0, GL_TEXTURE1 и т.д.). 
Тем самым он станет активным через glActiveTexture() и затем привязываем объект текстур к модулю. 
Связь будет до тех пор, пока для этого модуля не будет вызвана Texture::Bind() для другой текстуры.*/
void Texture::Bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(m_textureTarget, m_textureObj);
}