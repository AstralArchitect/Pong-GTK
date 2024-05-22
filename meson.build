project('Pong-GTK', 'c', version : '1.0.0')

gtk_dep = dependency('gtk+-3.0', version: '>=3.22')

sources = ['Code/game.c', 'Code/main.c', 'Code/functions.c']

# Compiler les ressources uniquement sous Windows
if host_machine.system() == 'windows'
    windows = import('windows')

    # Définir les fichiers de ressources et les arguments supplémentaires
    resource_files = ['iconData/icon.rc']
    extra_args = ['-O', 'coff']
    
    compiled_targets = windows.compile_resources(resource_files, args: extra_args, depend_files: ['iconData/icon.ico'], depends: [], include_directories: ['../resources'])

    executable('Pong_launcher', sources, compiled_targets, dependencies: gtk_dep)
else
    compiled_targets = []

    executable('Pong_launcher', sources, compiled_targets, dependencies: gtk_dep)
endif