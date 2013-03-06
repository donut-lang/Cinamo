# -*- coding: utf-8 -*-

# Cinamo
#
# Copyright 2012-2013, PSI

import sys
import os
sys.path.append('external/WafHelper')
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
	opt.load('compiler_c compiler_cxx')
	opt.load('boost')

def configure(conf):
	# release
	conf.setenv('release')
	conf.env.append_value('CXXFLAGS', ['-O3', '-Wall', '-std=gnu++11', '-D__GXX_EXPERIMENTAL_CXX0X__=1'])
	conf.env.append_value('LINKFLAGS', ['-fvisibility=hidden'])
	configureLibrary(conf)
	# debug
	conf.setenv('debug')
	denv = conf.env;
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
	conf.check(features='cxx cxxprogram', lib=['gtest', 'gtest_main', 'pthread'], cflags=['-Wall'], uselib_store='GTEST')
	try:
		conf.check(features='cxx cxxprogram', lib=['tcmalloc','profiler'], cflags=['-Wall'], uselib_store='PPROF')
	except conf.errors.ConfigurationError:
		conf.to_log("Google perftools not found, so performance will not measureable.")
	if sys.platform == 'win32':
		#boost
		conf.env.append_value('CXXFLAGS', ['-DBOOST_THREAD_USE_LIB=1'])
		conf.load('boost')
		conf.check_boost(lib='system thread chrono')

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
	bld(
		features = "subst",
		source= "pkgconfig/cinamo.pc.in",
		target= "cinamo.pc",
		install_path='${PREFIX}/lib/pkgconfig/',
		PREFIX = bld.env['PREFIX'],
		VER=VERSION)
	bld(
		features = 'cxx cprogram',
		source = TEST_SRC+TINYXML2_SRC+CINAMO_SRC,
		target = 'cinamo_test',
		env = bld.all_envs["coverage"] if ("coverage" in bld.all_envs) else bld.env,
		use=['GTEST', 'ICU', 'PPROF','BOOST'],
		includes=[CINAMO_INC, TINYXML2_INC])
	bld.install_files("${PREFIX}", Util.enum('include',[],['.h']), relative_trick=True)
	bld.install_files("${PREFIX}/include", ['external/tinyxml2/tinyxml2.h'], relative_trick=False)
	bld.install_files("${PREFIX}/lib", 'libcinamo.a')

def shutdown(ctx):
	pass

