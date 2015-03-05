include $(top_srcdir)/Makefile.am.common
cinamoTest_CPPFLAGS =\
	-isystem\
	$(top_srcdir)/external/gtest/include\
	$(GTEST_CPPFLAGS)\
	$(ICU_CPPFLAGS)\
	-I$(top_srcdir)/include\
	-I$(top_srcdir)/external/tinyxml2
cinamoTest_CXXFLAGS = $(GTEST_CXXFLAGS) $(GTEST_CXXFLAGS) $(ICU_CXXFLAGS)
cinamoTest_LDFLAGS = $(GTEST_LDFLAGS) $(ICU_LDFLAGS) \
	     $(top_srcdir)/external/gtest/lib/libgtest_main.la \
	     $(top_srcdir)/external/gtest/lib/libgtest.la
cinamoTest_LDADD = ../src/libcinamo.a $(ICU_LIBS) $(GTEST_LIBS)

TESTS = 
check_PROGRAMS = 

TESTS += cinamoTest
check_PROGRAMS += cinamoTest
cinamoTest_SOURCES =\
	TestUtil.cpp\
	TestCommon.h\
	case/XValueTestTypes.inc.h\
	case/ClassUtilTest.cpp\
	case/XArchiverTest.cpp\
	case/XValueTest.cpp\
	case/FormPayloadTest.cpp\
	case/LoggerTest.cpp\
	case/EitherTest.cpp\
	case/FileUtilTest.cpp\
	case/Base64Test.cpp\
	case/XMLAttrParserTest.cpp\
	case/UnitTest.cpp\
	case/TypeTraitsTest.cpp\
	case/ParserTest.cpp\
	case/DemangleTest.cpp\
	case/FunctorBaseTest.cpp\
	case/UrlTest.cpp\
	case/StringUtilTest.cpp\
	case/MatrixTest.cpp\
	case/VectorMapTest.cpp\
	case/ConstexprList.cpp\
	case/ExceptionTest.cpp\
	case/MixTypeTest.cpp\
	case/BoxTest.cpp\
	case/MaybeTest.cpp\
	case/XValueTestBinaryTypes.inc.h\
	main.cpp

