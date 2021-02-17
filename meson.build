project('rive_tizen',
        'cpp',
        default_options : ['cpp_std=c++17'],
        version : '0.1.0',
        license : 'MIT')


#thorvg_dep = dependency('thorvg', required : true)

cc = meson.get_compiler('cpp')

pthread_lib = cc.find_library('pthread')
dl_lib = cc.find_library('dl')
gl_lib = cc.find_library('GL')

skia_lib = cc.find_library('skia', dirs:[meson.current_source_dir()+'/submodule/skia/dependencies/skia/out/Static'])
skia_header_files = [
   'submodule/skia/dependencies/skia',
   'submodule/skia/dependencies/skia/include/core',
   'submodule/skia/dependencies/skia/include/effects',
   'submodule/skia/dependencies/skia/include/gpu',
   'submodule/skia/dependencies/skia/include/config',
]

glfw_lib = cc.find_library('glfw3', dirs:[meson.current_source_dir()+'/submodule/skia/dependencies/glfw_build/src'])
glfw_header_files = [
   'submodule/skia/dependencies/glfw/include'
]

run_command('script/install.sh')

headers = [include_directories('inc')]

rive_tizen_src = [
   'src/rive_tizen.cpp',
]

install_headers([
                 'inc/rive_tizen.hpp',
                ])

rive_tizen_dep = declare_dependency(
   include_directories : include_directories('.'),
   sources : rive_tizen_src
)

rive_src = [
   'submodule/src/math/aabb.cpp',
   'submodule/src/math/vec2d.cpp',
   'submodule/src/math/mat2d.cpp',
   'submodule/src/animation/cubic_interpolator.cpp',
   'submodule/src/animation/keyed_object.cpp',
   'submodule/src/animation/keyed_property.cpp',
   'submodule/src/animation/keyframe.cpp',
   'submodule/src/animation/keyframe_color.cpp',
   'submodule/src/animation/keyframe_double.cpp',
   'submodule/src/animation/keyframe_id.cpp',
   'submodule/src/animation/linear_animation.cpp',
   'submodule/src/animation/linear_animation_instance.cpp',
   'submodule/src/core/binary_reader.cpp',
   'submodule/src/core/field_types/core_bool_type.cpp',
   'submodule/src/core/field_types/core_color_type.cpp',
   'submodule/src/core/field_types/core_double_type.cpp',
   'submodule/src/core/field_types/core_string_type.cpp',
   'submodule/src/core/field_types/core_uint_type.cpp',
   'submodule/src/shapes/clipping_shape.cpp',
   'submodule/src/shapes/cubic_mirrored_vertex.cpp',
   'submodule/src/shapes/metrics_path.cpp',
   'submodule/src/shapes/path.cpp',
   'submodule/src/shapes/points_path.cpp',
   'submodule/src/shapes/shape.cpp',
   'submodule/src/shapes/straight_vertex.cpp',
   'submodule/src/shapes/cubic_asymmetric_vertex.cpp',
   'submodule/src/shapes/cubic_vertex.cpp',
   'submodule/src/shapes/path_composer.cpp',
   'submodule/src/shapes/polygon.cpp',
   'submodule/src/shapes/shape_paint_container.cpp',
   'submodule/src/shapes/triangle.cpp',
   'submodule/src/shapes/cubic_detached_vertex.cpp',
   'submodule/src/shapes/ellipse.cpp',
   'submodule/src/shapes/parametric_path.cpp',
   'submodule/src/shapes/path_vertex.cpp',
   'submodule/src/shapes/rectangle.cpp',
   'submodule/src/shapes/star.cpp',
   'submodule/src/shapes/paint/color.cpp',
   'submodule/src/shapes/paint/fill.cpp',
   'submodule/src/shapes/paint/gradient_stop.cpp',
   'submodule/src/shapes/paint/linear_gradient.cpp',
   'submodule/src/shapes/paint/radial_gradient.cpp',
   'submodule/src/shapes/paint/shape_paint.cpp',
   'submodule/src/shapes/paint/shape_paint_mutator.cpp',
   'submodule/src/shapes/paint/solid_color.cpp',
   'submodule/src/shapes/paint/stroke.cpp',
   'submodule/src/shapes/paint/trim_path.cpp',
   'submodule/src/bones/bone.cpp',
   'submodule/src/bones/root_bone.cpp',
   'submodule/src/bones/skin.cpp',
   'submodule/src/bones/skinnable.cpp',
   'submodule/src/bones/tendon.cpp',
   'submodule/src/bones/weight.cpp',
   'submodule/src/artboard.cpp',
   'submodule/src/component.cpp',
   'submodule/src/dependency_sorter.cpp',
   'submodule/src/draw_rules.cpp',
   'submodule/src/draw_target.cpp',
   'submodule/src/drawable.cpp',
   'submodule/src/file.cpp',
   'submodule/src/layout.cpp',
   'submodule/src/node.cpp',
   'submodule/src/transform_component.cpp',
]

skia_dep = declare_dependency(
	include_directories : [skia_header_files],
   dependencies : [skia_lib, pthread_lib],
)

skia_renderer_dep = declare_dependency(
   include_directories : include_directories(['submodule/skia/renderer/include', skia_header_files]),
   sources : ['submodule/skia/renderer/src/skia_renderer.cpp'],
   dependencies : skia_dep
)

rive_dep = declare_dependency(
   include_directories : include_directories(['submodule/include']),
   sources : rive_src,
   dependencies : skia_renderer_dep
)

rive_tizen_lib = library(
	'rive_tizen',
	include_directories : [headers],
	version             : meson.project_version(),
	dependencies        : [rive_tizen_dep, rive_dep],
	install             : true,
	cpp_args            : ['-fno-exceptions', '-fno-rtti'],
	gnu_symbol_visibility : 'hidden',
)

rive_tizen_lib_dep = declare_dependency(
	include_directories : [headers],
	link_with : rive_tizen_lib
)

pkg_mod = import('pkgconfig')

pkg_mod.generate(
        libraries    : rive_tizen_lib,
        version      : meson.project_version(),
        name         : 'librive_tizen',
        filebase     : 'rive_tizen',
        description  : 'A Rive Animation Tizen Runtime Engine'
)

subdir('example')

rive_viewer_dep = declare_dependency(
	include_directories : [skia_header_files, glfw_header_files],
   dependencies : [skia_lib, glfw_lib, dl_lib, gl_lib],
)

rive_viewer_src = [
  'submodule/skia/viewer/src/main.cpp'
]

executable('rive_viewer',
           rive_viewer_src,
           dependencies : [rive_viewer_dep, skia_renderer_dep, rive_dep],
           install : true)
