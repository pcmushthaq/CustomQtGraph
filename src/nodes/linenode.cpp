
#include "linenode.h"
#include <iostream>
#include <QtGui/QColor>

#include <QtQuick/QSGMaterial>

class LineShader : public QSGMaterialShader
{
public:
    LineShader() {
        setShaderFileName(VertexStage, QLatin1String("://shaders/line.vert.qsb"));
        setShaderFileName(FragmentStage, QLatin1String("://shaders/line.frag.qsb"));
    }

    bool updateUniformData(RenderState &state, QSGMaterial *newMaterial, QSGMaterial *oldMaterial) override;
};

class LineMaterial : public QSGMaterial
{
public:
    LineMaterial()
    {
        setFlag(Blending);
    }

    QSGMaterialType *type() const override
    {
        static QSGMaterialType type;
        return &type;
    }

    QSGMaterialShader *createShader(QSGRendererInterface::RenderMode) const override
    {
        return new LineShader;
    }

    int compare(const QSGMaterial *m) const override
    {
        const LineMaterial *other = static_cast<const LineMaterial *>(m);

        if (int diff = int(state.color.rgb()) - int(other->state.color.rgb()))
            return diff;

        if (int diff = state.size - other->state.size)
            return diff;

        if (int diff = state.spread - other->state.spread)
            return diff;

        return 0;
    }

    struct {
        QColor color;
        float size;
        float spread;
    } state;
};

bool LineShader::updateUniformData(RenderState &state, QSGMaterial *newMaterial, QSGMaterial *)
{
    /// Uniform data is the data which is uniform throughout the shader
    /// This does not change depending on the vertex
    ///
    /// This is received in the shader in the following format
    /// layout(std140, binding = 0) uniform buf {
    /// mat4 qt_Matrix;
    /// vec4 color;
    /// float qt_Opacity;
    /// float size;
    /// float spread;
    /// }

    QByteArray *buf = state.uniformData();
    Q_ASSERT(buf->size() >= 92);

    if (state.isMatrixDirty()) {
        const QMatrix4x4 m = state.combinedMatrix();
        memcpy(buf->data(), m.constData(), 64);
    }

    if (state.isOpacityDirty()) {
        const float opacity = state.opacity();
        memcpy(buf->data() + 80, &opacity, 4);
    }

    LineMaterial *mat = static_cast<LineMaterial *>(newMaterial);
    float c[4];
    mat->state.color.getRgbF(&c[0], &c[1], &c[2], &c[3]);
    memcpy(buf->data() + 64, c, 16);
    memcpy(buf->data() + 84, &mat->state.size, 4);
    memcpy(buf->data() + 88, &mat->state.spread, 4);

    return true;
}

struct LineVertex {
    float x;
    float y;
    float t;
    inline void set(float xx, float yy, float tt) { x = xx; y = yy; t = tt; }
};

static const QSGGeometry::AttributeSet &attributes()
{
    /// Attribute data is data which is different for every vertex. See uniforms
    /// This is used to specify how the data is sent there
    static QSGGeometry::Attribute attr[] = {
        /// This creates the "in" parameters for the vertex shader
        /// 0 - pos, 2- size ( x and y ),float, true indicates that this is a position argument
        QSGGeometry::Attribute::create(0, 2, QSGGeometry::FloatType, true),
        /// 1 - position (not index) , 1 - size (t paramete), true is not specified since this is not indicating position
        QSGGeometry::Attribute::create(1, 1, QSGGeometry::FloatType)
    };

    /// This indicates the number of input, total size and the data.
    /// Note that this does not contain the actual data. The actual data will be updated in the updatePaintNode function.
    static QSGGeometry::AttributeSet set = { 2, 3 * sizeof(float), attr };
    return set;
}

LineNode::LineNode(float size, float spread, const QColor &color)
    : m_geometry(attributes(), 0)
{
    setGeometry(&m_geometry);
    m_geometry.setDrawingMode(QSGGeometry::DrawTriangleStrip);

    LineMaterial *m = new LineMaterial;
    m->state.color = color;
    m->state.size = size;
    m->state.spread = spread;

    setMaterial(m);
    setFlag(OwnsMaterial);
}

/* 
 * When xAxis and yAxis are given,
 * The graph x points will be starting from min and ending at max
 * x value of max means that the point will be at the width
 * Similarly for y axis
 */
void LineNode::updateGeometry(const QRectF &bounds,
                              const QList<XYPoint *> &samples,
                              ValueAxis *xAxis,
                              ValueAxis *yAxis)
{
    m_geometry.allocate(samples.size() * 2);

    float x = bounds.x();
    float y = bounds.y();
    float w = bounds.width();
    float h = bounds.height();

    double xMin = 0.0, yMin = 0.0, xMax = 0.0, yMax = 0.0;

    if (xAxis != nullptr) {
        xMin = xAxis->min();
        xMax = xAxis->max();
    }
    if (yAxis != nullptr) {
        yMin = yAxis->min();
        yMax = yAxis->max();
    }

    LineVertex *v = (LineVertex *) m_geometry.vertexData();
    for (int i = 0; i < samples.size(); ++i) {
        auto xValue = samples.at(i)->x();
        if (xMin != xMax) {
            xValue = (xValue - xMin) / (xMax - xMin);
        }
        auto yValue = samples.at(i)->y();
        if (yMin != yMax) {
            yValue = (yValue - yMin) / (yMax - yMin);
        }
        auto newX = x + xValue * w;
        auto newY = y + yValue * h;
        v[i * 2 + 0].set(newX, newY, 0);
        v[i * 2 + 1].set(newX, newY, 1);
    }

    markDirty(QSGNode::DirtyGeometry);
}
