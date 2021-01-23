#pragma once

/*
 *  MSS Code Factory CFLib 2.13
 *
 *	Copyright 2020-2021 Mark Stephen Sobkow
 *
 *	This file is part of MSS Code Factory.
 *
 *	MSS Code Factory is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	MSS Code Factory is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with MSS Code Factory.  If not, see https://www.gnu.org/licenses/.
 *
 *	Donations to support MSS Code Factory can be made at
 *	https://www.paypal.com/paypalme2/MarkSobkow
 *
 *	Please contact Mark Stephen Sobkow at mark.sobkow@gmail.com for commercial licensing.
 */

#include <ctype.h>
#include <uuid/uuid.h>
#include <time.h>
#include <memory.h>

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <chrono>
#include <ctime>
#include <list>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <stdexcept>

#include <cflib/ICFLibCloneableObj.hpp>
#include <cflib/ICFLibObj.hpp>
#include <cflib/ICFLibAnyObj.hpp>
#include <cflib/ICFLibMessageLog.hpp>
#include <cflib/ICFLibXmlCoreContextFactory.hpp>

#include <cflib/CFLib.hpp>

#include <cflib/CFLibDbUtil.hpp>
#include <cflib/CFLibConsoleMessageLog.hpp>
#include <cflib/CFLibCachedMessageLog.hpp>
#include <cflib/CFLibGenericBigDecimal.hpp>
#include <cflib/TCFLibBigDecimal.hpp>
#include <cflib/TCFLibOwningVector.hpp>
#include <cflib/TCFLibOwningList.hpp>

#include <cflib/CFLibNullable.hpp>
#include <cflib/CFLibNullableBool.hpp>
#include <cflib/CFLibNullableInt16.hpp>
#include <cflib/CFLibNullableInt32.hpp>
#include <cflib/CFLibNullableInt64.hpp>
#include <cflib/CFLibNullableUInt16.hpp>
#include <cflib/CFLibNullableUInt32.hpp>
#include <cflib/CFLibNullableUInt64.hpp>
#include <cflib/CFLibNullableFloat.hpp>
#include <cflib/CFLibNullableDouble.hpp>

#include <cflib/CFLibExceptionInfo.hpp>
#include <cflib/CFLibRuntimeException.hpp>
#include <cflib/CFLibRuntimeException.hpp>
#include <cflib/CFLibArgumentException.hpp>
#include <cflib/CFLibArgumentOverflowException.hpp>
#include <cflib/CFLibArgumentRangeException.hpp>
#include <cflib/CFLibArgumentUnderflowException.hpp>
#include <cflib/CFLibEmptyArgumentException.hpp>
#include <cflib/CFLibInvalidArgumentException.hpp>
#include <cflib/CFLibNullArgumentException.hpp>
#include <cflib/CFLibCodeStateException.hpp>
#include <cflib/CFLibMustOverrideException.hpp>
#include <cflib/CFLibNotImplementedYetException.hpp>
#include <cflib/CFLibNotSupportedException.hpp>
#include <cflib/CFLibUsageException.hpp>
#include <cflib/CFLibIntegrityException.hpp>
#include <cflib/CFLibDependentsDetectedException.hpp>
#include <cflib/CFLibPrimaryKeyNotNewException.hpp>
#include <cflib/CFLibUniqueIndexViolationException.hpp>
#include <cflib/CFLibUnrecognizedAttributeException.hpp>
#include <cflib/CFLibUnresolvedRelationException.hpp>
#include <cflib/CFLibUnsupportedClassException.hpp>
#include <cflib/CFLibCollisionDetectedException.hpp>
#include <cflib/CFLibDbException.hpp>
#include <cflib/CFLibMathException.hpp>
#include <cflib/CFLibStaleCacheDetectedException.hpp>
#include <cflib/CFLibSubroutineException.hpp>
#include <cflib/CFLibWrapSystemException.hpp>
#include <cflib/CFLibWrapXercesException.hpp>

#include <cflib/CFLibXmlCoreLineCountBinInputStream.hpp>
#include <cflib/CFLibXmlCoreLineCountMemBufInputSource.hpp>
#include <cflib/CFLibXmlCore.hpp>
#include <cflib/CFLibXmlCoreContext.hpp>
#include <cflib/CFLibXmlCoreElementHandler.hpp>
#include <cflib/CFLibXmlCoreIso8859Encoder.hpp>
#include <cflib/CFLibXmlCoreParser.hpp>
#include <cflib/CFLibXmlCoreSaxParser.hpp>
#include <cflib/CFLibXmlUtil.hpp>

#include <cflib/CFLibExceptionMacros.hpp>
