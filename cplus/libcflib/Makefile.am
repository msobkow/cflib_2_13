SUBDIRS=cflib

MAJOR_VERSION = 2

MINOR_VERSION = 13

BUILD_NUMBER = 11185

RELEASE = $(MAJOR_VERSION).$(MINOR_VERSION).$(BUILD_NUMBER)

SUB_RELEASE = $(MAJOR_VERSION).$(MINOR_VERSION)

MAIN_RELEASE = $(MAJOR_VERSION)

DEPDIR = debug

LT_OBJDIR = .libs

lib_LTLIBRARIES=libcflib.la

BIN=$(prefix)/bin/msobkow/$(MAJOR_VERSION).0.$(MINOR)_VERSION

bindir=$(prefix)/bin/msobkow/$(MAJOR_VERSION).0.$(MINOR_VERSION)

libcflib_ladir=$(prefix)/include/msobkow/$(MAJOR_VERSION).0.$(MINOR_VERSION)/cflib

libcflib_CXXFLAGS = -I. -I$(prefix)/include/msobkow/$(MAJOR_VERSION).0.$(MINOR_VERSION) -I$(prefix)/include/msobkow/$(MAJOR_VERSION).0.$(MINOR_VERSION)

libcflib_la_SOURCES = ICFLibCloneableObj.cpp ICFLibObj.cpp ICFLibAnyObj.cpp ICFLibMessageLog.cpp ICFLibXmlCoreContextFactory.cpp CFLibXmlCoreLineCountBinInputStream.cpp CFLibXmlCoreLineCountMemBufInputSource.cpp CFLibGenericBigDecimal.cpp TCFLibBigDecimal.cpp CFLibExceptionInfo.cpp CFLibRuntimeException.cpp CFLibArgumentException.cpp CFLibArgumentOverflowException.cpp CFLibArgumentRangeException.cpp CFLibArgumentUnderflowException.cpp CFLibEmptyArgumentException.cpp CFLibInvalidArgumentException.cpp CFLibNullArgumentException.cpp CFLibCodeStateException.cpp CFLibMustOverrideException.cpp CFLibNotImplementedYetException.cpp CFLibNotSupportedException.cpp CFLibUsageException.cpp CFLibIntegrityException.cpp CFLibDependentsDetectedException.cpp CFLibPrimaryKeyNotNewException.cpp CFLibUniqueIndexViolationException.cpp CFLibUnrecognizedAttributeException.cpp CFLibUnresolvedRelationException.cpp CFLibUnsupportedClassException.cpp CFLibCollisionDetectedException.cpp CFLibDbException.cpp CFLibMathException.cpp CFLibStaleCacheDetectedException.cpp CFLibSubroutineException.cpp CFLibWrapSystemException.cpp CFLibWrapXercesException.cpp TCFLibOwningVector.cpp TCFLibOwningList.cpp CFLib.cpp ICFLibPublic.cpp CFLibDbUtil.cpp CFLibConsoleMessageLog.cpp CFLibCachedMessageLog.cpp CFLibXmlCore.cpp CFLibXmlCoreContext.cpp CFLibXmlCoreElementHandler.cpp CFLibXmlCoreIso8859Encoder.cpp CFLibXmlCoreParser.cpp CFLibXmlCoreSaxParser.cpp CFLibXmlUtil.cpp CFLibNullable.cpp CFLibNullableBool.cpp CFLibNullableInt16.cpp CFLibNullableInt32.cpp CFLibNullableInt64.cpp CFLibNullableUInt16.cpp CFLibNullableUInt32.cpp CFLibNullableUInt64.cpp CFLibNullableFloat.cpp CFLibNullableDouble.cpp

libcflib_la_LDFLAGS = -version-info $(MAJOR_VERSION):$(MINOR_VERSION) -lmpfr -lxerces-c -luuid

libcflib_la_HEADERS = cflib/CFLibXmlCoreLineCountBinInputStream.hpp cflib/CFLibXmlCoreLineCountMemBufInputSource.hpp cflib/CFLibExceptionInfo.hpp cflib/CFLibExceptionMacros.hpp cflib/CFLibRuntimeException.hpp cflib/CFLibArgumentException.hpp cflib/CFLibArgumentOverflowException.hpp cflib/CFLibArgumentRangeException.hpp cflib/CFLibArgumentUnderflowException.hpp cflib/CFLibGenericBigDecimal.hpp cflib/TCFLibBigDecimal.hpp cflib/CFLibEmptyArgumentException.hpp cflib/CFLibInvalidArgumentException.hpp cflib/CFLibNullArgumentException.hpp cflib/CFLibCodeStateException.hpp cflib/CFLibMustOverrideException.hpp cflib/CFLibNotImplementedYetException.hpp cflib/CFLibNotSupportedException.hpp cflib/CFLibUsageException.hpp cflib/CFLibIntegrityException.hpp cflib/CFLibDependentsDetectedException.hpp cflib/CFLibPrimaryKeyNotNewException.hpp cflib/CFLibUniqueIndexViolationException.hpp cflib/CFLibUnrecognizedAttributeException.hpp cflib/CFLibUnresolvedRelationException.hpp cflib/CFLibUnsupportedClassException.hpp cflib/CFLibCollisionDetectedException.hpp cflib/CFLibDbException.hpp cflib/CFLibMathException.hpp cflib/CFLibStaleCacheDetectedException.hpp cflib/CFLibSubroutineException.hpp cflib/CFLibWrapSystemException.hpp cflib/CFLibWrapXercesException.hpp cflib/TCFLibOwningVector.hpp cflib/TCFLibOwningList.hpp cflib/CFLib.hpp cflib/ICFLibPublic.hpp cflib/CFLibDbUtil.hpp cflib/CFLibConsoleMessageLog.hpp cflib/CFLibCachedMessageLog.hpp cflib/CFLibXmlCore.hpp cflib/CFLibXmlCoreContext.hpp cflib/CFLibXmlCoreElementHandler.hpp cflib/CFLibXmlCoreIso8859Encoder.hpp cflib/CFLibXmlCoreParser.hpp cflib/CFLibXmlCoreSaxParser.hpp cflib/CFLibXmlUtil.hpp cflib/ICFLibCloneableObj.hpp cflib/ICFLibObj.hpp cflib/ICFLibAnyObj.hpp cflib/ICFLibMessageLog.hpp cflib/ICFLibXmlCoreContextFactory.hpp cflib/CFLibNullable.hpp cflib/CFLibNullableBool.hpp cflib/CFLibNullableInt16.hpp cflib/CFLibNullableInt32.hpp cflib/CFLibNullableInt64.hpp cflib/CFLibNullableUInt16.hpp cflib/CFLibNullableUInt32.hpp cflib/CFLibNullableUInt64.hpp cflib/CFLibNullableFloat.hpp cflib/CFLibNullableDouble.hpp

libcflibxsd_ladir=$(prefix)/share/msobkow/$(MAJOR_VERSION).0.$(MINOR_VERSION)/xsd

libcflibxsd_la_HEADERS=xsd/cftip-envelope.xsd xsd/cftip-serverinfo.xsd

ACLOCAL_AMFLAGS = -Im4

