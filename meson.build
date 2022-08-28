project('CodeJam2022', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20']
)

external_deps = [dependency('threads'), dependency('gl')]
cpp = meson.get_compiler('cpp')

if host_machine.system() == 'windows'
  # no platform specific dependencies
elif host_machine.system() == 'darwin'
  external_deps += [
    dependency('libpng'),
    dependency('appleframeworks', modules: ['GLUT'])
  ]
else
  external_deps += [
    dependency('libpng'),
    dependency('x11'),
    cpp.find_library('stdc++fs', required: false)
  ]
endif

sources = [
  'main.cpp',
  'Engine.cpp',
  'NodeSystem/Node.cpp',
  'NodeSystem/StartNode.cpp',
  'AssetSystem/SpriteManager.cpp',
]

include_dir = include_directories('include')

exe = executable('codejam2022', sources,
  install : true,
  dependencies: external_deps,
  include_directories: include_dir,
  cpp_args: ['-std=c++17']
)

test('basic', exe)
