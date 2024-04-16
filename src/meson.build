zlib = dependency('zlib')
exec = executable('astellie', ['main.c', 'types.c', 'server.c'], include_directories: i, dependencies: [zlib])
typesobj = exec.extract_objects('types.c')
