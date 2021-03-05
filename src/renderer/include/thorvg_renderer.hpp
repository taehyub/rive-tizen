#ifndef _RIVE_THORVG_RENDERER_HPP_
#define _RIVE_THORVG_RENDERER_HPP_

#include <thorvg.h>
#include <vector>
#include "renderer.hpp"

namespace rive
{
   enum ThorvgPathType 
   {
      MoveTo,
      LineTo,
      CubicTo,
      Close
   };

   struct ThorvgPoint
   {
      int x, y;
      ThorvgPoint(int _x, int _y) : x(_x), y(_y) { };
   };

	class ThorvgRenderPath : public RenderPath
	{
	private:
		tvg::Shape *m_Path;
      std::vector<ThorvgPathType> m_PathType;
      std::vector<ThorvgPoint> m_PathPoints;

	public:
      ThorvgRenderPath();
		tvg::Shape* path() { return m_Path; }
		void reset() override;
		void addRenderPath(RenderPath* path, const Mat2D& transform) override;
		void fillRule(FillRule value) override;
		void moveTo(float x, float y) override;
		void lineTo(float x, float y) override;
		void cubicTo(float ox, float oy, float ix, float iy, float x, float y) override;
		virtual void close() override;
	};

/*
	struct GradientStop
	{
		unsigned int color;
		float stop;
		GradientStop(unsigned int color, float stop) : color(color), stop(stop)
		{
		}
	};

	class SkiaGradientBuilder
	{
	public:
		std::vector<GradientStop> stops;
		float sx, sy, ex, ey;
		virtual ~SkiaGradientBuilder() {}
		SkiaGradientBuilder(float sx, float sy, float ex, float ey) :
		    sx(sx), sy(sy), ex(ex), ey(ey)
		{
		}

		virtual void make(SkPaint& paint) = 0;
	};

	class SkiaRadialGradientBuilder : public SkiaGradientBuilder
	{
	public:
		SkiaRadialGradientBuilder(float sx, float sy, float ex, float ey) :
		    SkiaGradientBuilder(sx, sy, ex, ey)
		{
		}
		void make(SkPaint& paint) override;
	};

	class SkiaLinearGradientBuilder : public SkiaGradientBuilder
	{
	public:
		SkiaLinearGradientBuilder(float sx, float sy, float ex, float ey) :
		    SkiaGradientBuilder(sx, sy, ex, ey)
		{
		}
		void make(SkPaint& paint) override;
	};
*/

	class ThorvgRenderPaint : public RenderPaint
	{
	private:
//		SkPaint m_Paint;
//		SkiaGradientBuilder* m_GradientBuilder;

	public:
//		const SkPaint& paint() const { return m_Paint; }
		ThorvgRenderPaint();
		void style(RenderPaintStyle style) override;
		void color(unsigned int value) override;
		void thickness(float value) override;
		void join(StrokeJoin value) override;
		void cap(StrokeCap value) override;
		void blendMode(BlendMode value) override;

		void linearGradient(float sx, float sy, float ex, float ey) override;
		void radialGradient(float sx, float sy, float ex, float ey) override;
		void addStop(unsigned int color, float stop) override;
		void completeGradient() override;
	};

	class ThorvgRenderer : public Renderer
	{
	private:
		tvg::Canvas* m_Canvas;
      bool pushed;

	public:
		ThorvgRenderer(tvg::Canvas* canvas) : m_Canvas(canvas) {}
		void save() override;
		void restore() override;
		void transform(const Mat2D& transform) override;
		void drawPath(RenderPath* path, RenderPaint* paint) override;
		void clipPath(RenderPath* path) override;
	};
} // namespace rive
#endif
