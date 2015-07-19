include 'premake'

make_solution 'zmqlogger'

g3log_root = 'deps/g3log-7cf42c535c3be83eec1ff0c374a626a2b45a033b/src'

includedirs {
	g3log_root
}

defines {
	'CHANGE_G3LOG_DEBUG_TO_DBUG',
}

make_static_lib('g3log',{
	g3log_root..'/**.cpp'
})

	configuration 'windows'
		excludes {
			g3log_root..'/g3log/crashhandler_unix.cpp'
		}
	configuration '*'

make_console_app('g2log_benchmark',{
	'g2log_benchmark/*.h',
	'g2log_benchmark/*.cpp'
})

	configuration 'windows'
		links 'dbghelp'
	configuration '*'

	links {
		'g3log'
	}
