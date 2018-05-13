#ifndef GWORK_RENDERERS_OPENGLCORE_H
#define GWORK_RENDERERS_OPENGLCORE_H


#include <Gwork/BaseRender.h>
#include <glm/glm.hpp>

namespace Gwk
{
    namespace Renderer
    {
        //! Default resource loader for opengl.
        class OpenGLResourceLoader : public ResourceLoader
        {
            ResourcePaths& m_paths;
        public:
            OpenGLResourceLoader(ResourcePaths& paths) : m_paths(paths) {}

            Font::Status LoadFont(Font& font) override;
            void FreeFont(Font& font) override;

            Texture::Status LoadTexture(Texture& texture) override;
            void FreeTexture(Texture& texture) override;
        };

        //
        //! Renderer for [OpenGL](https://www.opengl.org/) Core Profile.
        //
        class GWK_EXPORT OpenGLCore : public Gwk::Renderer::Base
        {
        public:

            OpenGLCore(ResourceLoader& loader, const Gwk::Rect& viewRect);
            virtual ~OpenGLCore();

            void Init() override;

            void Begin() override;
            void End() override;

            void SetDrawColor(Gwk::Color color) override;
            void DrawFilledRect(Gwk::Rect rect) override;

            void StartClip() override;
            void EndClip() override;

            void DrawTexturedRect(Gwk::Texture* texture, Gwk::Rect targetRect, float u1 = 0.0f,
                                  float v1 = 0.0f, float u2 = 1.0f, float v2 = 1.0f) override;

            Gwk::Color PixelColor(Gwk::Texture* texture,
                                  unsigned int x, unsigned int y,
                                  const Gwk::Color& col_default) override;

            void RenderText(Gwk::Font* font,
                            Gwk::Point pos,
                            const Gwk::String& text) override;

            Gwk::Point MeasureText(Gwk::Font* font, const Gwk::String& text) override;

            bool InitializeContext(Gwk::WindowProvider* window) override;
            bool ShutdownContext(Gwk::WindowProvider* window) override;
            bool PresentContext(Gwk::WindowProvider* window) override;
            bool ResizedContext(Gwk::WindowProvider* window, int w, int h) override;
            bool BeginContext(Gwk::WindowProvider* window) override;
            bool EndContext(Gwk::WindowProvider* window) override;

            void*   m_context;

        protected:

            Rect m_viewRect;
            Color m_color;

        private:
            glm::mat4 m_projectionMatrix;
            glm::mat4 m_viewMatrix;
            glm::mat4 m_modelMatrix;
        };


    }
}

#endif //GWORK_RENDERERS_OPENGLCORE_H
