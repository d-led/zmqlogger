include 'premake'

make_solution 'zmqlogger'

-- additional
platforms { "x64" }

g3log_root = 'deps/g3log-7cf42c535c3be83eec1ff0c374a626a2b45a033b/src'
zeromq_root = {
	x32 = [[C:\Program Files (x86)\ZeroMQ 3.2.4\]],
	x64 = [[C:\Program Files\ZeroMQ 3.2.4\]],
	osx = [[/usr/local/Cellar/zeromq/4.1.2/]]
}
zeromq_lib = {
	win = 'libzmq-v110-mt-3_2_4',
	osx = 'zmq'
}

includedirs {
	g3log_root,
	'deps/cpp-optparse',
	'deps/cppzmq',
	'deps/picojson',
}

-- libzmq config
configuration {'x32','windows'}
	includedirs { path.join(zeromq_root.x32,'include') }
	libdirs { path.join(zeromq_root.x32,'lib') }
configuration {'x64','windows'}
	includedirs { path.join(zeromq_root.x64,'include') }
	libdirs { path.join(zeromq_root.x64,'lib') }
configuration 'macosx'
	includedirs { path.join(zeromq_root.osx,'include') }
	libdirs { path.join(zeromq_root.osx,'lib') }	
configuration '*'

function deploy_libzmq()
	configuration {'x32','windows'}
		postbuildcommands {
			[[xcopy "]]..path.getabsolute(path.join(zeromq_root.x32,"bin/*.dll")):gsub('/','\\')..[[" "$(TargetDir)" /s /d /y]]	
		}
	configuration {'x64','windows'}
		postbuildcommands {
			[[xcopy "]]..path.getabsolute(path.join(zeromq_root.x64,"bin/*.dll")):gsub('/','\\')..[[" "$(TargetDir)" /s /d /y]]	
		}
	configuration '*'
end

defines {
	'CHANGE_G3LOG_DEBUG_TO_DBUG',
}

function link_zeromq_g3log()
	configuration 'windows'
		links {
			'dbghelp',
			zeromq_lib.win
		}
	configuration 'macosx'
		links {
			zeromq_lib.osx,
		}
	configuration '*'
		links 'g3log'
end

------------------------------------
make_static_lib('g3log',{
	g3log_root..'/**.cpp'
})
	make_cpp11()
	configuration 'windows'
		excludes {
			g3log_root..'/g3log/crashhandler_unix.cpp'
		}
	configuration 'not windows'
		excludes {
			g3log_root..'/g3log/*windows*.cpp'			
		}
	configuration '*'

------------------------------------
make_static_lib('cpp-optparse',{
	'deps/cpp-optparse/**.cpp'
})	
	make_cpp11()

------------------------------------
make_console_app('g2log_benchmark',{
	'g2log_benchmark/*.h',
	'g2log_benchmark/*.cpp'
})

	make_cpp11()
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

	make_cpp11()
	link_zeromq_g3log()
	deploy_libzmq()
	
	links 'cpp-optparse'

------------------------------------
make_console_app('zmqloggerclient',{
	'zmqloggerclient/*.h',
	'zmqloggerclient/*.cpp'
})

	make_cpp11()
	link_zeromq_g3log()

