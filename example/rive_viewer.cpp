#include <thread>
#include <Evas_GL.h>
#include <Elementary.h>
#include <rive_tizen.hpp>
#include "thorvg_renderer.hpp"

using namespace std;


#define WIDTH 700
#define HEIGHT 700

static uint32_t buffer[WIDTH * HEIGHT];
static unique_ptr<tvg::SwCanvas> swCanvas;
Eo *gView;

void win_del(void *data, Evas_Object *o, void *ev)
{
   elm_exit();
}

void drawSwView(void* data, Eo* obj)
{
    if (swCanvas && swCanvas->draw() == tvg::Result::Success) {
        swCanvas->sync();
    }
}

void tvgDrawCmds(tvg::Canvas* canvas)
{
    if (!canvas) return;

    //Prepare a Shape (Rectangle + Rectangle + Circle + Circle)
    auto shape1 = tvg::Shape::gen();
    shape1->appendRect(0, 0, 200, 200, 0, 0);          //x, y, w, h, rx, ry
    shape1->appendRect(100, 100, 300, 300, 100, 100);  //x, y, w, h, rx, ry
    shape1->appendCircle(400, 400, 100, 100);          //cx, cy, radiusW, radiusH
    shape1->appendCircle(400, 500, 170, 100);          //cx, cy, radiusW, radiusH
    shape1->fill(255, 255, 0, 255);                    //r, g, b, a

    canvas->push(move(shape1));
}

void tvgSwTest(uint32_t* buffer)
{
    //Create a Canvas
    swCanvas = tvg::SwCanvas::gen();
    swCanvas->target(buffer, WIDTH, WIDTH, HEIGHT, tvg::SwCanvas::ARGB8888);

    /* Push the shape into the Canvas drawing list
       When this shape is into the canvas list, the shape could update & prepare
       internal data asynchronously for coming rendering.
       Canvas keeps this shape node unless user call canvas->clear() */
    tvgDrawCmds(swCanvas.get());
}

static Eo* createSwView()
{
    Eo* win = elm_win_util_standard_add(NULL, "Rive Viewer");
    evas_object_smart_callback_add(win, "delete,request", win_del, 0);

    Eo* view = evas_object_image_filled_add(evas_object_evas_get(win));
    evas_object_image_size_set(view, WIDTH, HEIGHT);
    evas_object_image_data_set(view, buffer);
    evas_object_image_pixels_get_callback_set(view, drawSwView, nullptr);
    evas_object_image_pixels_dirty_set(view, EINA_TRUE);
    evas_object_image_data_update_add(view, 0, 0, WIDTH, HEIGHT);
    evas_object_size_hint_weight_set(view, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_show(view);

    elm_win_resize_object_add(win, view);
    evas_object_resize(win, WIDTH, HEIGHT);
    evas_object_show(win);

    tvgSwTest(buffer);

    return view;
}

int main(int argc, char **argv)
{
    rive_tizen_print();
    rive::ThorvgRenderPath *path = new rive::ThorvgRenderPath();

    tvg::CanvasEngine tvgEngine = tvg::CanvasEngine::Sw;

    auto threads = std::thread::hardware_concurrency();

    if (tvg::Initializer::init(tvgEngine, threads) == tvg::Result::Success)
    {
        elm_init(argc, argv);

        gView = createSwView();

        elm_run();
        elm_shutdown();

        tvg::Initializer::term(tvgEngine);

    }
    else
    {
        cout << "engine is not supported" << endl;
    }

    return 0;
}
