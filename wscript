# -*- coding: utf-8 -*-

# Cinamo
#
# Copyright 2012-2013, PSI

import sys
import os
sys.path.append('.helper')
import Util

APPNAME = 'Cinamo'
VERSION = '1.0.0'

srcdir = '.'
blddir = 'build'

CINAMO_DIR=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'src')
CINAMO_INC=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'include')
CINAMO_SRC=Util.enum('src')

TINYXML2_INC=TINYXML2_DIR=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'external', 'tinyxml2')
TINYXML2_SRC=[os.path.join('.', 'external','tinyxml2','tinyxml2.cpp')]

TEST_DIR=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'test')
TEST_SRC=Util.enum('test')

def options(opt):
	opt.add_option('--coverage', action='store_true', default=False, help='Enabling coverage measuring.')
	opt.add_option('--debug', action='store_true', default=False, help='debug build')
	opt.add_option('--force-mt', dest='force_mt', action='store_true', default=False, help='enforce multi-thread feature to be enabled.')
	opt.load('compiler_c compiler_cxx')
	opt.load('boost')

def configure(conf):
	# release
	conf.setenv('release')
	if sys.platform != 'win32':
		conf.env.append_value('CXXFLAGS', ['-fPIC'])
	conf.env.append_value('CXXFLAGS', ['-O3', '-Wall', '-std=gnu++11', '-D__GXX_EXPERIMENTAL_CXX0X__=1'])
	conf.env.append_value('LINKFLAGS', ['-fvisibility=hidden'])
	configureLibrary(conf)
	# debug
	conf.setenv('debug')
	denv = conf.env;
	if sys.platform != 'win32':
		conf.env.append_value('CXXFLAGS', ['-fPIC'])
	conf.env.append_value('CXXFLAGS', ['-ggdb','-O0', '-Wall', '-std=gnu++11', '-D__GXX_EXPERIMENTAL_CXX0X__=1','-DDEBUG'])
	conf.env.append_value('LINKFLAGS', ['-fvisibility=hidden'])
	configureLibrary(conf)
	if conf.options.coverage:
		conf.setenv('coverage', denv)
		conf.env.append_value('LINKFLAGS', '-fprofile-arcs')
		conf.env.append_value('CXXFLAGS', ['-fprofile-arcs','-ftest-coverage'])

def configureLibrary(conf):
	conf.load('compiler_c compiler_cxx')
	conf.check_cfg(package='icu-uc icu-i18n', uselib_store='ICU', mandatory=True, args='--cflags --libs')
	conf.check(features='cxx cxxprogram', lib=['gtest', 'gtest_main', 'pthread'], cflags=['-Wall'], uselib_store='GTEST', mandatory=True)
	if not conf.check(features='cxx cxxprogram', lib=['tcmalloc','profiler'], cflags=['-Wall'], uselib_store='PPROF', mandatory=False):
		conf.to_log("Google perftools not found, so performance will not measureable.")

	# check boost
	have_boost=False
	if sys.platform == 'win32':
		#boost
		conf.env.append_value('CXXFLAGS', ['-DBOOST_THREAD_USE_LIB=1'])
		conf.check_boost(lib='system thread chrono', mandatory=False)
		have_boost = 'LIB_BOOST' in conf.env and 'LIBPATH_BOOST' in conf.env
		conf.env['HAVE_THREAD']=have_boost
	elif sys.platform in ['linux2', 'linux']:
		conf.env['HAVE_THREAD']=True
	else:
		conf.fatal('Your platform: {} is not supported yet.'.format(sys.platform))
	conf.define(conf.have_define('boost'), 1 if (have_boost) else 0)
	
	if conf.options.force_mt and (not conf.env['HAVE_THREAD']):
		conf.fatal('Thread feature is not enabled.')
	#
	bld_path = conf.path.get_bld().abspath()
	conf.write_config_header(os.path.join(conf.variant, 'config.h'))
	conf.env.append_value('CXXFLAGS', ['-I'+os.path.join(bld_path, conf.variant)])

def build(bld):
	if not bld.variant:
		bld.set_env(bld.all_envs['debug' if (bld.options.debug) else 'release'])
	bld(
		is_install=True,
		features = 'cxx cxxstlib',
		source = CINAMO_SRC+TINYXML2_SRC,
		target = 'cinamo',
		use=['ICU', 'BOOST'],
		includes=[CINAMO_INC, TINYXML2_INC])
	boost_libpath=' '.join( [ '-L'+x for x in bld.env['LIBPATH_BOOST'] ])
	boost_libs = ' '.join( [ '-l'+x for x in bld.env['LIB_BOOST'] ])
	boost_inc = '' if len(bld.env['INCLUDES_BOOST']) == 0 else "-I{}".format(bld.env['INCLUDES_BOOST'])
	bld(
		features = "subst",
		source= "pkgconfig/cinamo.pc.in",
		target= "cinamo.pc",
		install_path='${PREFIX}/lib/pkgconfig/',
		NAME='cinamo',
		BOOST_LIBPATH = boost_libpath,
		BOOST_LIBS = boost_libs,
		BOOST_INC = boost_inc,
		PREFIX = bld.env['PREFIX'],
		VER=VERSION)
	# マルチスレッド版のインストール
	if ('HAVE_THREAD' in bld.env) and bld.env['HAVE_THREAD']:
		bld(
			features = "subst",
			source= "pkgconfig/cinamo.pc.in",
			target= "cinamo-mt.pc",
			install_path='${PREFIX}/lib/pkgconfig/',
			NAME='cinamo-mt',
			BOOST_LIBPATH = boost_libpath,
			BOOST_LIBS = boost_libs,
			BOOST_INC = boost_inc,
			PREFIX = bld.env['PREFIX'],
			VER=VERSION)
	bld(
		features = 'cxx cprogram',
		source = TEST_SRC+TINYXML2_SRC,
		target = 'cinamoTest',
		env = bld.all_envs["coverage"] if ("coverage" in bld.all_envs) else bld.env,
		use=['GTEST', 'ICU', 'PPROF','BOOST', 'cinamo'],
		includes=[CINAMO_INC, TINYXML2_INC])
	bld.install_files("${PREFIX}", Util.enum('include',[],['.h']), relative_trick=True)
	bld.install_files("${PREFIX}/include", ['external/tinyxml2/tinyxml2.h'], relative_trick=False)
	bld.install_files("${PREFIX}/include/cinamo", [os.path.join(bld.path.get_bld().path_from(bld.path.find_node('.')), 'config.h')], relative_trick=False)
	bld.install_files("${PREFIX}/lib", 'libcinamo.a')

def shutdown(ctx):
	pass

