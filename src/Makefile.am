include $(top_srcdir)/Makefile.am.common
lib_LIBRARIES=libcinamo.a
libcinamo_a_SOURCES=\
	Base64.cpp\
	Dynamic.cpp\
	Exception.cpp\
	FileSystem.cpp\
	FormPayload.cpp\
	Logger.cpp\
	String.cpp\
	StringICU.cpp\
	StringParse.cpp\
	Time.cpp\
	Url.cpp\
	Win32.cpp\
	XArchiver.cpp\
	XMLAttrParser.cpp\
	XVal.cpp\
	../external/tinyxml2/tinyxml2.cpp

libcinamo_a_CPPFLAGS = $(ICU_CFLAGS) -I$(top_srcdir)/external/tinyxml2
#libcinamo_a_LIBADD = $(ICU_LIBS)

#libcinamo_la_LDFLAGS = -no-undefined \
#        -avoid-version \
#        -Wl,-o,.libs/dolly.dll \
#        -Wl,--output-def,.libs/cinamo.def,--out-implib,.libs/cinamo.dll.a
