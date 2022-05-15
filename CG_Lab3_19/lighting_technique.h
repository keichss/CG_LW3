#ifndef LIGHTINGTECHNIQUE_H
#define LIGHTINGTECHNIQUE_H

#include "technique.h"
#include "math_3d.h"

struct DirectionLight //нова€ структура направленного света.
{
    Vector3f Color;
    float AmbientIntensity;
    Vector3f Direction;
    float DiffuseIntensity;
};

class LightingTechnique : public Technique //LightingTechnique наследует этот класс, и представл€ет собой инвентарь света
{
    public:
        LightingTechnique();
        virtual bool Init();

        void SetWVP(const Matrix4f& WVP);
        void SetWorldMatrix(const Matrix4f& WVP);
        void SetTextureUnit(unsigned int TextureUnit);
        void SetDirectionalLight(const DirectionLight& Light);

        void SetEyeWorldPos(const Vector3f& EyeWorldPos);
        void SetMatSpecularIntensity(float Intensity);
        void SetMatSpecularPower(float Power);

    private:
        GLuint m_WVPLocation;
        GLuint m_WorldMatrixLocation;
        GLuint m_samplerLocation;

        GLuint m_eyeWorldPosition;
        GLuint m_matSpecularIntensityLocation;
        GLuint m_matSpecularPowerLocation;
        //3 новых свойства у LightingTechnique - позици€ глаза, интенсивность отражени€ и коэффициент материала
        struct {
            GLuint Color;
            GLuint AmbientIntensity;
            GLuint Direction;
            GLuint DiffuseIntensity;
        } m_dirLightLocation;
};

#endif // LIGHTINGTECHNIQUE_H
