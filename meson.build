project('mysha256', 'cpp')

add_global_arguments('-std=c++11', language : 'cpp')
add_global_arguments('-Wall', language : 'cpp')
add_global_arguments('-Wno-error=unused-local-typedefs', language : 'cpp')
add_global_arguments('-Wno-unused-local-typedefs', language : 'cpp')
add_global_arguments('-Wno-error=pedantic', language : 'cpp')

top_inc = include_directories('.')
src_inc = include_directories('src')

sha_lib = static_library('myshalib', [
    'src/boxes.cpp',
    'src/message.cpp',
    'src/hash.cpp'
    ]
)

executable('mysha256', [
    'src/main.cpp'
    ],
    include_directories: [
        top_inc,
        src_inc,
    ],
    link_with: [
         sha_lib
    ]
)

test_exe = executable('test-mysha256', [
    'test/test.cpp',
    ],
    include_directories: [
        top_inc,
        src_inc,
    ],
    link_with: [
         sha_lib
    ]
)

benchmark_exe = executable('benchmark-mysha256', [
    'test/benchmark.cpp',
    ],
    include_directories: [
        top_inc,
        src_inc,
    ],
    link_with: [
         sha_lib
    ]
)

test('test-mysha256', test_exe)
