libenv = Environment(CPPPATH=['include/'], CXXFLAGS='')

libenv.Install('include/ooo', Glob('ooo/ooo/*'))

libenv.StaticLibrary('lib/ooo', Glob('ooo/*.cc'))
libenv.SharedLibrary('lib/ooo', Glob('ooo/*.cc'))

testenv = Environment(CPPPATH=['include/'],
                      LIBPATH=['/usr/lib/lib/x86_64-linux-gnu/'],
                      CXXFLAGS='-g',
                      LIBS=['glog', 'boost_system', 'pthread'])

STATICLIBS=['lib/libooo.a', '/usr/lib/libgtest.a']

testenv.Program('test/unittest', Glob('test/*.cc')+STATICLIBS)

