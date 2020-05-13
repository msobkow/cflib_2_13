
includedir=$(prefix)/include/cflib

include_HEADERS = CFLibXmlCoreLineCountBinInputStream.hpp CFLibXmlCoreLineCountMemBufInputSource.hpp CFLibExceptionInfo.hpp CFLibExceptionMacros.hpp CFLibRuntimeException.hpp CFLibArgumentException.hpp CFLibArgumentOverflowException.hpp CFLibArgumentRangeException.hpp CFLibArgumentUnderflowException.hpp CFLibGenericBigDecimal.hpp TCFLibBigDecimal.hpp CFLibEmptyArgumentException.hpp CFLibInvalidArgumentException.hpp CFLibNullArgumentException.hpp CFLibCodeStateException.hpp CFLibMustOverrideException.hpp CFLibNotImplementedYetException.hpp CFLibNotSupportedException.hpp CFLibUsageException.hpp CFLibIntegrityException.hpp CFLibDependentsDetectedException.hpp CFLibPrimaryKeyNotNewException.hpp CFLibUniqueIndexViolationException.hpp CFLibUnrecognizedAttributeException.hpp CFLibUnresolvedRelationException.hpp CFLibUnsupportedClassException.hpp CFLibCollisionDetectedException.hpp CFLibDbException.hpp CFLibMathException.hpp CFLibStaleCacheDetectedException.hpp CFLibSubroutineException.hpp CFLibWrapSystemException.hpp CFLibWrapXercesException.hpp TCFLibOwningVector.hpp TCFLibOwningList.hpp CFLib.hpp ICFLibPublic.hpp CFLibDbUtil.hpp CFLibConsoleMessageLog.hpp CFLibCachedMessageLog.hpp CFLibXmlCore.hpp CFLibXmlCoreContext.hpp CFLibXmlCoreElementHandler.hpp CFLibXmlCoreIso8859Encoder.hpp CFLibXmlCoreParser.hpp CFLibXmlCoreSaxParser.hpp CFLibXmlUtil.hpp ICFLibCloneableObj.hpp ICFLibObj.hpp ICFLibAnyObj.hpp ICFLibMessageLog.hpp ICFLibXmlCoreContextFactory.hpp CFLibNullable.hpp CFLibNullableBool.hpp CFLibNullableInt16.hpp CFLibNullableInt32.hpp CFLibNullableInt64.hpp CFLibNullableUInt16.hpp CFLibNullableUInt32.hpp CFLibNullableUInt64.hpp CFLibNullableFloat.hpp CFLibNullableDouble.hpp

install-HEADERS: $(include_HEADERS)
	@$(NORMAL_INSTALL)
	@list='$(include_HEADERS)' || list=; \
	if test -n "$$list"; then \
	  echo " $(MKDIR_P) '$(DESTDIR)$(prefix)/include/cflib'"; \
	  $(MKDIR_P) "$(DESTDIR)$(prefix)/include/cflib" || exit 1; \
	fi; \
	for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  echo "$$d$$p"; \
	done | $(am__base_list) | \
	while read files; do \
	  echo " $(INSTALL_HEADER) $$files '$(DESTDIR)$(prefix)/include/cflib'"; \
	  $(INSTALL_HEADER) $$files "$(DESTDIR)$(prefix)/include/cflib" || exit $$?; \
	done

all: $(include_HEADERS)
