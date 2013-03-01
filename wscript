# -*- coding: utf-8 -*-

# Tarte
#
# Copyright 2012-2013, PSI
# Dual licensed under the BSD or GPL Version 3 (or any later) licenses.
# !! GPL is STRONGLY recommended !!
# see: http://donut-lang.org/license/

import sys
import os

APPNAME = 'Tarte'
VERSION = '1.0.0'

srcdir = '.'
blddir = 'build'

def enum(dirname, exclude=[], exts=['.cpp','.c']):
	dirname = os.path.join(*(dirname.split('/')))
	f = []
	for root,dirs,files in os.walk(dirname):
		matched = False
		for e in exclude:
			if root.startswith(e):
				matched = True
				break
		if matched:
			continue
		for fitem in files:
			fabs = os.path.join(root, fitem)
			_, ext = os.path.splitext(fabs)
			if ext in exts:
				f.append(os.path.relpath(fabs))
	return f

TARTE_DIR=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'src')
TARTE_INC=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'include')
TARTE_SRC=enum('src')

TINYXML2_INC=TINYXML2_DIR=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'external', 'tinyxml2')
TINYXML2_SRC=[os.path.join('.', 'external','tinyxml2','tinyxml2.cpp')]

TEST_DIR=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'test')
TEST_SRC=enum('test')

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
		source = TARTE_SRC+TINYXML2_SRC,
		target = 'tarte',
		use=['ICU', 'BOOST'],
		includes=[TARTE_INC, TINYXML2_INC])
	bld(
		features = "subst",
		source= "pkgconfig/tarte.pc.in",
		target= "tarte.pc",
		install_path='${PREFIX}/lib/pkgconfig/',
		PREFIX = bld.env['PREFIX'],
		VER=VERSION)
	bld(
		features = 'cxx cprogram',
		source = TEST_SRC+TINYXML2_SRC+TARTE_SRC,
		target = 'tarte_test',
		env = bld.all_envs["coverage"] if ("coverage" in bld.all_envs) else bld.env,
		use=['GTEST', 'ICU', 'PPROF','BOOST'],
		includes=[TARTE_INC, TINYXML2_INC])
	bld.install_files("${PREFIX}", enum('include',[],['.h']), relative_trick=True)
	bld.install_files("${PREFIX}/include", ['external/tinyxml2/tinyxml2.h'], relative_trick=False)
	bld.install_files("${PREFIX}/lib", 'libtarte.a')

# from http://docs.waf.googlecode.com/git/book_16/single.html#_custom_build_outputs
from waflib.Build import BuildContext, CleanContext, InstallContext, UninstallContext
for x in 'debug release'.split():
	for y in (BuildContext, CleanContext, InstallContext, UninstallContext):
		name = y.__name__.replace('Context','').lower()
		class tmp(y):
			cmd = name + '_' + x
			variant = x

def shutdown(ctx):
	pass

