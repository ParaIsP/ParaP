// This is a generated source file for Chilkat version 9.5.0.76
#ifndef _C_CkPdfWH
#define _C_CkPdfWH
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC HCkPdfW CkPdfW_Create(void);
CK_VISIBLE_PUBLIC void CkPdfW_Dispose(HCkPdfW handle);
CK_VISIBLE_PUBLIC void CkPdfW_getDebugLogFilePath(HCkPdfW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkPdfW_putDebugLogFilePath(HCkPdfW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkPdfW_debugLogFilePath(HCkPdfW cHandle);
CK_VISIBLE_PUBLIC int CkPdfW_getI(HCkPdfW cHandle);
CK_VISIBLE_PUBLIC void  CkPdfW_putI(HCkPdfW cHandle, int newVal);
CK_VISIBLE_PUBLIC void CkPdfW_getLastErrorHtml(HCkPdfW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkPdfW_lastErrorHtml(HCkPdfW cHandle);
CK_VISIBLE_PUBLIC void CkPdfW_getLastErrorText(HCkPdfW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkPdfW_lastErrorText(HCkPdfW cHandle);
CK_VISIBLE_PUBLIC void CkPdfW_getLastErrorXml(HCkPdfW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkPdfW_lastErrorXml(HCkPdfW cHandle);
CK_VISIBLE_PUBLIC BOOL CkPdfW_getLastMethodSuccess(HCkPdfW cHandle);
CK_VISIBLE_PUBLIC void  CkPdfW_putLastMethodSuccess(HCkPdfW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkPdfW_getNumPages(HCkPdfW cHandle);
CK_VISIBLE_PUBLIC int CkPdfW_getNumSignatures(HCkPdfW cHandle);
CK_VISIBLE_PUBLIC BOOL CkPdfW_getVerboseLogging(HCkPdfW cHandle);
CK_VISIBLE_PUBLIC void  CkPdfW_putVerboseLogging(HCkPdfW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkPdfW_getVersion(HCkPdfW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkPdfW_version(HCkPdfW cHandle);
CK_VISIBLE_PUBLIC BOOL CkPdfW_ExtractPageTextSa(HCkPdfW cHandle, int pageNum, HCkStringArrayW sa);
CK_VISIBLE_PUBLIC BOOL CkPdfW_GetObjectInfo(HCkPdfW cHandle, const wchar_t *pdfPath, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkPdfW_getObjectInfo(HCkPdfW cHandle, const wchar_t *pdfPath);
CK_VISIBLE_PUBLIC BOOL CkPdfW_GetPageContents(HCkPdfW cHandle, int pageNum, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkPdfW_getPageContents(HCkPdfW cHandle, int pageNum);
CK_VISIBLE_PUBLIC BOOL CkPdfW_GetSignatureSigningTime(HCkPdfW cHandle, int index, HCkDateTimeW dt);
CK_VISIBLE_PUBLIC BOOL CkPdfW_GetSignerCert(HCkPdfW cHandle, int index, HCkCertW cert);
CK_VISIBLE_PUBLIC BOOL CkPdfW_GetSignerName(HCkPdfW cHandle, int index, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkPdfW_getSignerName(HCkPdfW cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkPdfW_GetSigningReason(HCkPdfW cHandle, int index, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkPdfW_getSigningReason(HCkPdfW cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkPdfW_HasSignatureSigningTime(HCkPdfW cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkPdfW_Open(HCkPdfW cHandle, const wchar_t *filePath);
CK_VISIBLE_PUBLIC BOOL CkPdfW_OpenBd(HCkPdfW cHandle, HCkBinDataW pdfData);
CK_VISIBLE_PUBLIC BOOL CkPdfW_SaveLastError(HCkPdfW cHandle, const wchar_t *path);
CK_VISIBLE_PUBLIC BOOL CkPdfW_VerifySignatures(HCkPdfW cHandle);
#endif
