include 'premake'

make_solution 'zmqlogger'

includedirs {
	'deps/g3log-7cf42c535c3be83eec1ff0c374a626a2b45a033b/src'
}

defines {
	'CHANGE_G3LOG_DEBUG_TO_DBUG',
}

make_console_app('g2log_benchmark',{
	'g2log_benchmark/*.h',
	'g2log_benchmark/*.cpp'
})
