include 'premake'

make_solution 'zmqlogger'

-- additional
platforms { "x64" }

g3log_root = 'deps/g3log-7cf42c535c3be83eec1ff0c374a626a2b45a033b/src'
zeromq_root = [[C:\Program Files\ZeroMQ 3.2.4\]]

includedirs {
	g3log_root,
	path.join(zeromq_root,'include'),
	'deps/cpp-optparse',
	'deps/cppzmq',
	'deps/picojson',
}

libdirs {
	path.join(zeromq_root,'lib'),
}

defines {
	'CHANGE_G3LOG_DEBUG_TO_DBUG',
}

function link_zeromq_g3log()
	configuration 'windows'
		links {
			'dbghelp',
			'g3log',
			'libzmq-v110-mt-3_2_4'
		}
	configuration '*'
end

------------------------------------
make_static_lib('g3log',{
	g3log_root..'/**.cpp'
})

	configuration 'windows'
		excludes {
			g3log_root..'/g3log/crashhandler_unix.cpp'
		}
	configuration '*'

------------------------------------
make_static_lib('cpp-optparse',{
	'deps/cpp-optparse/**.cpp'
})

------------------------------------
make_console_app('g2log_benchmark',{
	'g2log_benchmark/*.h',
	'g2log_benchmark/*.cpp'
})

	configuration 'windows'
		links {
			'dbghelp',
		}
	configuration '*'

	links {
		'g3log'
	}

------------------------------------
make_console_app('zmqlogger',{
	'zmqlogger/*.h',
	'zmqlogger/*.cpp'
})

	link_zeromq_g3log()
	links 'cpp-optparse'

------------------------------------
make_console_app('zmqloggerclient',{
	'zmqloggerclient/*.h',
	'zmqloggerclient/*.cpp'
})

	link_zeromq_g3log()

