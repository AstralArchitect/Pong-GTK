project('Pong-GTK', 'c', version : '1.0.0')

gtk_dep = dependency('gtk+-3.0', version: '>=3.22')

game = library('game', 'Code/game.c', dependencies : gtk_dep)
info = library('info', 'Code/info.c', dependencies : gtk_dep)

windows = import('windows')

# Définir les fichiers de ressources et les arguments supplémentaires
resource_files = ['iconData/icon.rc']
extra_args = ['-O', 'coff']

# Compiler les ressources
compiled_targets = windows.compile_resources(
    resource_files,
    args: extra_args,
    depend_files: ['iconData/icon.ico'],
    depends: [],
    include_directories : ['../resources']
)

executable('Pong_launcher', 'Code/main.c', compiled_targets, dependencies : gtk_dep, install : true, link_with : [ game, info ])
