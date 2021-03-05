#include "thorvg_renderer.hpp"
#include "math/vec2d.hpp"
#include "shapes/paint/color.hpp"

using namespace rive;

ThorvgRenderPath::ThorvgRenderPath()
{
	this->m_Path = tvg::Shape::gen().release();
}

void ThorvgRenderPath::fillRule(FillRule value)
{
	switch (value)
	{
		case FillRule::evenOdd:
			m_Path->fill(tvg::FillRule::EvenOdd);
			break;
		case FillRule::nonZero:
			break;
	}
}

void ThorvgRenderPath::addRenderPath(RenderPath* path, const Mat2D& transform)
{
   std::vector<ThorvgPathType> &m_PathType = reinterpret_cast<ThorvgRenderPath*>(path)->m_PathType;
   std::vector<ThorvgPoint> & m_PathPoints = reinterpret_cast<ThorvgRenderPath*>(path)->m_PathPoints;

   for (int i = 0; i < m_PathType.size(); i++)
   {
      ThorvgPathType type = m_PathType[i];
      switch(type)
      {
         case ThorvgPathType::MoveTo:
            break;
         case ThorvgPathType::LineTo:
            break;
         case ThorvgPathType::CubicTo:
            break;
         case ThorvgPathType::Close:
            break;
      }
   }
}

void ThorvgRenderPath::reset()
{
//   m_Path->reset();
   m_PathType.clear();
   m_PathPoints.clear();
}

void ThorvgRenderPath::moveTo(float x, float y)
{
//   m_Path->moveTo(x, y);
   m_PathType.push_back(ThorvgPathType::MoveTo);
   m_PathPoints.push_back(ThorvgPoint(x, y));
}

void ThorvgRenderPath::lineTo(float x, float y)
{
   m_PathType.push_back(ThorvgPathType::LineTo);
   m_PathPoints.push_back(ThorvgPoint(x, y));
}

void ThorvgRenderPath::cubicTo(float ox, float oy, float ix, float iy, float x, float y)
{
//   m_Path->cubicTo(ox, oy, ix, iy, x, y);
   m_PathType.push_back(ThorvgPathType::CubicTo);
   m_PathPoints.push_back(ThorvgPoint(ox, oy));
   m_PathPoints.push_back(ThorvgPoint(ix, iy));
   m_PathPoints.push_back(ThorvgPoint(x, y));
}

void ThorvgRenderPath::close()
{
//   m_Path->close();
   m_PathType.push_back(ThorvgPathType::Close);
}

void ThorvgRenderer::save()
{

}

void ThorvgRenderer::restore()
{

}

void ThorvgRenderer::transform(const Mat2D& transform)
{

}

void ThorvgRenderer::drawPath(RenderPath* path, RenderPaint* paint)
{
}

void ThorvgRenderer::clipPath(RenderPath* path)
{

}

ThorvgRenderPaint::ThorvgRenderPaint()
{

}

void ThorvgRenderPaint::style(RenderPaintStyle style)
{
	switch (style)
	{
		case RenderPaintStyle::fill:
			break;
		case RenderPaintStyle::stroke:
			break;
	}
}
void ThorvgRenderPaint::color(unsigned int value)
{

}

void ThorvgRenderPaint::thickness(float value)
{
}

void ThorvgRenderPaint::join(StrokeJoin value)
{

}

void ThorvgRenderPaint::cap(StrokeCap value)
{

}

void ThorvgRenderPaint::linearGradient(float sx, float sy, float ex, float ey)
{

}

void ThorvgRenderPaint::radialGradient(float sx, float sy, float ex, float ey)
{
}

void ThorvgRenderPaint::addStop(unsigned int color, float stop)
{
}

void ThorvgRenderPaint::completeGradient()
{

}

void ThorvgRenderPaint::blendMode(BlendMode value)
{

}

namespace rive
{
   RenderPath* makeRenderPath() { return new ThorvgRenderPath();}
   RenderPaint* makeRenderPaint() { return new ThorvgRenderPaint();}
}
