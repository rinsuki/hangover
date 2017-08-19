/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "shlwapi.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shlwapi32);
#endif

#ifndef QEMU_DLL_GUEST
const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_ChrCmpIA,
    qemu_ChrCmpIW,
    qemu_DoesStringRoundTripA,
    qemu_DoesStringRoundTripW,
    qemu_HashData,
    qemu_IsCharSpaceA,
    qemu_IsCharSpaceW,
    qemu_IsInternetESCEnabled,
    qemu_IStream_Reset,
    qemu_IStream_Size,
    qemu_MLBuildResURLA,
    qemu_MLBuildResURLW,
    qemu_ParseURLA,
    qemu_ParseURLW,
    qemu_PathAddBackslashA,
    qemu_PathAddBackslashW,
    qemu_PathAddExtensionA,
    qemu_PathAddExtensionW,
    qemu_PathAppendA,
    qemu_PathAppendW,
    qemu_PathBuildRootA,
    qemu_PathBuildRootW,
    qemu_PathCanonicalizeA,
    qemu_PathCanonicalizeW,
    qemu_PathCombineA,
    qemu_PathCombineW,
    qemu_PathCommonPrefixA,
    qemu_PathCommonPrefixW,
    qemu_PathCompactPathA,
    qemu_PathCompactPathExA,
    qemu_PathCompactPathExW,
    qemu_PathCompactPathW,
    qemu_PathCreateFromUrlA,
    qemu_PathCreateFromUrlAlloc,
    qemu_PathCreateFromUrlW,
    qemu_PathFileExistsA,
    qemu_PathFileExistsAndAttributesA,
    qemu_PathFileExistsAndAttributesW,
    qemu_PathFileExistsDefExtA,
    qemu_PathFileExistsDefExtW,
    qemu_PathFileExistsW,
    qemu_PathFindExtensionA,
    qemu_PathFindExtensionW,
    qemu_PathFindFileNameA,
    qemu_PathFindFileNameW,
    qemu_PathFindNextComponentA,
    qemu_PathFindNextComponentW,
    qemu_PathFindOnPathA,
    qemu_PathFindOnPathExA,
    qemu_PathFindOnPathExW,
    qemu_PathFindOnPathW,
    qemu_PathFindSuffixArrayA,
    qemu_PathFindSuffixArrayW,
    qemu_PathGetArgsA,
    qemu_PathGetArgsW,
    qemu_PathGetCharTypeA,
    qemu_PathGetCharTypeW,
    qemu_PathGetDriveNumberA,
    qemu_PathGetDriveNumberW,
    qemu_PathIsContentTypeA,
    qemu_PathIsContentTypeW,
    qemu_PathIsDirectoryA,
    qemu_PathIsDirectoryEmptyA,
    qemu_PathIsDirectoryEmptyW,
    qemu_PathIsDirectoryW,
    qemu_PathIsFileSpecA,
    qemu_PathIsFileSpecW,
    qemu_PathIsLFNFileSpecA,
    qemu_PathIsLFNFileSpecW,
    qemu_PathIsNetworkPathA,
    qemu_PathIsNetworkPathW,
    qemu_PathIsPrefixA,
    qemu_PathIsPrefixW,
    qemu_PathIsRelativeA,
    qemu_PathIsRelativeW,
    qemu_PathIsRootA,
    qemu_PathIsRootW,
    qemu_PathIsSameRootA,
    qemu_PathIsSameRootW,
    qemu_PathIsSystemFolderA,
    qemu_PathIsSystemFolderW,
    qemu_PathIsUNCA,
    qemu_PathIsUNCServerA,
    qemu_PathIsUNCServerShareA,
    qemu_PathIsUNCServerShareW,
    qemu_PathIsUNCServerW,
    qemu_PathIsUNCW,
    qemu_PathIsURLA,
    qemu_PathIsURLW,
    qemu_PathIsValidCharA,
    qemu_PathIsValidCharW,
    qemu_PathMakePrettyA,
    qemu_PathMakePrettyW,
    qemu_PathMakeSystemFolderA,
    qemu_PathMakeSystemFolderW,
    qemu_PathMatchSpecA,
    qemu_PathMatchSpecW,
    qemu_PathParseIconLocationA,
    qemu_PathParseIconLocationW,
    qemu_PathQuoteSpacesA,
    qemu_PathQuoteSpacesW,
    qemu_PathRelativePathToA,
    qemu_PathRelativePathToW,
    qemu_PathRemoveArgsA,
    qemu_PathRemoveArgsW,
    qemu_PathRemoveBackslashA,
    qemu_PathRemoveBackslashW,
    qemu_PathRemoveBlanksA,
    qemu_PathRemoveBlanksW,
    qemu_PathRemoveExtensionA,
    qemu_PathRemoveExtensionW,
    qemu_PathRemoveFileSpecA,
    qemu_PathRemoveFileSpecW,
    qemu_PathRenameExtensionA,
    qemu_PathRenameExtensionW,
    qemu_PathSearchAndQualifyA,
    qemu_PathSearchAndQualifyW,
    qemu_PathSetDlgItemPathA,
    qemu_PathSetDlgItemPathW,
    qemu_PathSkipRootA,
    qemu_PathSkipRootW,
    qemu_PathStripPathA,
    qemu_PathStripPathW,
    qemu_PathStripToRootA,
    qemu_PathStripToRootW,
    qemu_PathUndecorateA,
    qemu_PathUndecorateW,
    qemu_PathUnExpandEnvStringsA,
    qemu_PathUnExpandEnvStringsW,
    qemu_PathUnmakeSystemFolderA,
    qemu_PathUnmakeSystemFolderW,
    qemu_PathUnquoteSpacesA,
    qemu_PathUnquoteSpacesW,
    qemu_SHAnsiToAnsi,
    qemu_SHAnsiToUnicode,
    qemu_SHAnsiToUnicodeCP,
    qemu_SHAutoComplete,
    qemu_SHCreateStreamOnFileA,
    qemu_SHCreateStreamOnFileEx,
    qemu_SHCreateStreamOnFileW,
    qemu_SHGetWebFolderFilePathA,
    qemu_SHGetWebFolderFilePathW,
    qemu_SHIsEmptyStream,
    qemu_SHIStream_Read,
    qemu_SHIStream_Write,
    qemu_SHLoadIndirectString,
    qemu_SHStrDupA,
    qemu_SHStrDupW,
    qemu_SHStripMneumonicA,
    qemu_SHStripMneumonicW,
    qemu_SHTruncateString,
    qemu_SHUnicodeToAnsi,
    qemu_SHUnicodeToAnsiCP,
    qemu_SHUnicodeToUnicode,
    qemu_StrCatBuffA,
    qemu_StrCatBuffW,
    qemu_StrCatChainW,
    qemu_StrCatW,
    qemu_StrChrA,
    qemu_StrChrIA,
    qemu_StrChrIW,
    qemu_StrChrNW,
    qemu_StrChrW,
    qemu_StrCmpIW,
    qemu_StrCmpLogicalW,
    qemu_StrCmpNA,
    qemu_StrCmpNIA,
    qemu_StrCmpNIW,
    qemu_StrCmpNW,
    qemu_StrCmpW,
    qemu_StrCpyNW,
    qemu_StrCpyNXA,
    qemu_StrCpyNXW,
    qemu_StrCpyW,
    qemu_StrCSpnA,
    qemu_StrCSpnIA,
    qemu_StrCSpnIW,
    qemu_StrCSpnW,
    qemu_StrDupA,
    qemu_StrDupW,
    qemu_StrFormatByteSize64A,
    qemu_StrFormatByteSizeA,
    qemu_StrFormatByteSizeW,
    qemu_StrFormatKBSizeA,
    qemu_StrFormatKBSizeW,
    qemu_StrFromTimeIntervalA,
    qemu_StrFromTimeIntervalW,
    qemu_StrIsIntlEqualA,
    qemu_StrIsIntlEqualW,
    qemu_StrNCatA,
    qemu_StrNCatW,
    qemu_StrPBrkA,
    qemu_StrPBrkW,
    qemu_StrRChrA,
    qemu_StrRChrIA,
    qemu_StrRChrIW,
    qemu_StrRChrW,
    qemu_StrRetToBSTR,
    qemu_StrRetToBufA,
    qemu_StrRetToBufW,
    qemu_StrRetToStrA,
    qemu_StrRetToStrW,
    qemu_StrRStrIA,
    qemu_StrRStrIW,
    qemu_StrSpnA,
    qemu_StrSpnW,
    qemu_StrStrA,
    qemu_StrStrIA,
    qemu_StrStrIW,
    qemu_StrStrNIW,
    qemu_StrStrNW,
    qemu_StrStrW,
    qemu_StrToInt64ExA,
    qemu_StrToInt64ExW,
    qemu_StrToIntA,
    qemu_StrToIntExA,
    qemu_StrToIntExW,
    qemu_StrToIntW,
    qemu_StrTrimA,
    qemu_StrTrimW,
    qemu_UrlApplySchemeA,
    qemu_UrlApplySchemeW,
    qemu_UrlCanonicalizeA,
    qemu_UrlCanonicalizeW,
    qemu_UrlCombineA,
    qemu_UrlCombineW,
    qemu_UrlCompareA,
    qemu_UrlCompareW,
    qemu_UrlCreateFromPathA,
    qemu_UrlCreateFromPathW,
    qemu_UrlEscapeA,
    qemu_UrlEscapeW,
    qemu_UrlFixupW,
    qemu_UrlGetLocationA,
    qemu_UrlGetLocationW,
    qemu_UrlGetPartA,
    qemu_UrlGetPartW,
    qemu_UrlHashA,
    qemu_UrlHashW,
    qemu_UrlIsA,
    qemu_UrlIsNoHistoryA,
    qemu_UrlIsNoHistoryW,
    qemu_UrlIsOpaqueA,
    qemu_UrlIsOpaqueW,
    qemu_UrlIsW,
    qemu_UrlUnescapeA,
    qemu_UrlUnescapeW,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side shlwapi wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
