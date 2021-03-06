#define _CRT_SECURE_NO_WARNINGS
#ifndef OpenGLText_H__
#define OpenGLText_H__

#include <vector>
#include "GL/glew.h"

class OpenGLText
{
public:
    //
    // Header and structure for what is in the .bin file of the font
    //
    struct GlyphInfo
    {
        struct Pix // pixel oriented data
        {
            int u, v;
            int width, height;
            int advance;
            int offX, offY;
        };
        struct Norm // normalized data
        {
            float u, v; // position in the map in normalized coords
            float width, height;
            float advance;
            float offX, offY;
        };
        Pix  pix;
        Norm norm;
    };
    struct FileHeader
    {
        int texwidth, texheight;
        struct Pix
        {
            int ascent;
            int descent;
            int linegap;
        };
        struct Norm
        {
            float ascent;
            float descent;
            float linegap;
        };
        Pix  pix;
        Norm norm;
        GlyphInfo glyphs[256];
    };

    OpenGLText();
    ~OpenGLText();
    static void BackupStates();
    static void RestoreStates();
    void beginString();
    void endString();
    void stringSize(const char* text, float* sz);
    float drawString(int x, int y, const char* text, int nbLines, unsigned long color);
    float drawString(int x, int y, const char* text, int nbLines, float* color4f);
    bool init(const char* fontName, int w, int h);
    bool init(unsigned char* imageData, FileHeader* glyphInfos, int w, int h);
    void changeCanvas(int w, int h);
    void changeSize(int w, int h);
private:
    bool init(int w, int h);
    static const char* cWidgetVSSource2;
    static const char* cWidgetFSSource2;
    unsigned int        c_fontNbChars;
    unsigned int        c_fontHeight;
    unsigned int        c_fontWidth;
    unsigned int        m_widgetProgram;
    unsigned int        m_vShader;
    unsigned int        m_fShader;
    unsigned int        m_canvasVar;
    unsigned int        m_color;
    unsigned int        m_depthNFRSVar;
    unsigned int        m_fontTex;
    float               m_vertexDepth;
    int                 m_indexOffset;
    unsigned int        m_vbo;
    unsigned int        m_vbosz;
#ifdef USE_FONT_METRIC_AS_TBO
    unsigned int        m_GlyphTexOffset;
    unsigned int        m_boGlyphTexOffset;
    unsigned int        m_texGlyphTexOffset;
    unsigned int        m_locGlyphTexOffset;
#else
    unsigned int        locTc;
#endif
#ifdef USE_PSEUDO_INSTANCING
    unsigned int        m_locQuads;
    unsigned int        m_texQuads;
#else
    unsigned int        locPos;
    unsigned int        locGlyph;
#endif
    struct TCanvas
    {
        float w, h;
        float winw, winh;
        float ratio;
    };
    TCanvas             m_canvas;

    struct Vertex
    {
        float pos[4];
#ifndef USE_FONT_METRIC_AS_TBO
        float tc[4];
#endif
#ifdef USE_PSEUDO_INSTANCING
        float  iattr;
        float  dummy[3]; // to align with the fact we do 2 texelFetch over vec4
#else
        int   iattr;
#endif
        Vertex()
        {
            memset(this, 0, sizeof(Vertex));
        }

        void setPos(float fx, float fy, float fz, float fw)
        {
            pos[0] = fx; pos[1] = fy; pos[2] = fz; pos[3] = fw;
        }

#ifndef USE_FONT_METRIC_AS_TBO
        void setTC(float fx, float fy, float fz, float fw)
        {
            tc[0] = fx; tc[1] = fy; tc[2] = fz; tc[3] = fw;
        }
#endif
    };

    std::vector<Vertex>       m_vertices;

    FileHeader* glyphInfos;
    bool        allocated;

    GLuint CompileGLSLShader(GLenum target, const char* shader);
    GLuint LinkGLSLProgram(GLuint vertexShader, GLuint fragmentShader);
    void pushVertex(Vertex* v);
};

#endif